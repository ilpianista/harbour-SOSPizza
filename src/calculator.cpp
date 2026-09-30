#include "calculator.h"

#include <cmath>

namespace {

// --- Yeast growth model ---------------------------------------------------
// The fermentation rate depends exponentially on temperature:
//     rate(T) = kRateBase * exp(kRatePerDegree * T)
// and the fresh-yeast dose scales with (rate(T) / hours) ^ (1 / kGrowthExponent).

constexpr double kRatePerDegree = -0.12816;
constexpr double kRateBase = 2.52766;
constexpr double kGrowthExponent = 0.68982;
constexpr double kInvGrowthExponent = 1.0 / kGrowthExponent;

// The dose also grows slightly with the dough size (a small economy of scale).
constexpr double kDoughScaleExponent = -0.1;
constexpr double kDoughScaleFactor = 1.8;

// The main-dough dose is reduced when a pre-ferment carries part of the work.
constexpr double kPrefermentYeastFactor = 0.5;

// The dry yeasts are more concentrated, so the main dose is divided by (T * factor + 1).
constexpr double kInstantDryTempFactor = 0.0643;
constexpr double kActiveDryTempFactor = 0.042;

// Conversion factors used for the yeast that goes into a pre-ferment.
constexpr double kInstantDryConversion = 0.45;
constexpr double kActiveDryConversion = 0.54;

constexpr double kNeapolitanFactor = 0.9;
constexpr double kRomanFactor = 2.2;

// --- Sourdough model ------------------------------------------------------
// Empirical time-temperature model for sourdough fermentation:
//     progress(hours, T) = exp((hours - P(T)) / Q(T))
// where P and Q are the quartics below, with T in Celsius.

constexpr double kSourdoughNumT4 = 0.00159331210952735;
constexpr double kSourdoughNumT3 = -0.163153907011014;
constexpr double kSourdoughNumT2 = 6.51108858674971;
constexpr double kSourdoughNumT1 = -120.920943205013;
constexpr double kSourdoughNumC = 902.459330136656;

constexpr double kSourdoughDenT4 = -0.000343046132670815;
constexpr double kSourdoughDenT3 = 0.0352173329513804;
constexpr double kSourdoughDenT2 = -1.4114518234581;
constexpr double kSourdoughDenT1 = 26.3558449944149;
constexpr double kSourdoughDenC = -197.88697208344;

// Liquid sourdough is weaker than firm sourdough for the same maturation.
constexpr double kLiquidSourdoughFactor = 0.75;

// --- Pre-ferment model ----------------------------------------------------
constexpr double kPoolishHydration = 1.0; // flour : water = 1 : 1
constexpr double kPoolishYeastCoefficient = 3.9;
constexpr double kPoolishYeastDecay = -0.23;
constexpr double kBigaHydration = 0.45;  // water = 45% of the biga flour
constexpr double kBigaYeastRatio = 0.01; // 1% fresh yeast on the biga flour

// --- Style presets --------------------------------------------------------
struct Preset
{
    int ballWeight;
    double hydration;
    double saltPercent;
    double fatsPercent;
    double rtHours;
    double rtTemp;
    bool coldEnabled;
    double ctHours;
    double ctTemp;
};

// Indexed by Calculator::Style (Neapolitan, Roman).
constexpr Preset kPresets[] = {{250, 60.0, 3.0, 0.0, 8.0, 20.0, false, 43.0, 4.0},
                               {600, 80.0, 2.5, 2.5, 5.0, 20.0, true, 43.0, 4.0}};

// Evaluate a quartic c4*t^4 + c3*t^3 + c2*t^2 + c1*t + c0 using Horner's method.
constexpr double quartic(double t, double c4, double c3, double c2, double c1, double c0)
{
    return (((c4 * t + c3) * t + c2) * t + c1) * t + c0;
}

double sourdoughPoly(double t)
{
    return quartic(t,
                   kSourdoughNumT4,
                   kSourdoughNumT3,
                   kSourdoughNumT2,
                   kSourdoughNumT1,
                   kSourdoughNumC);
}

double sourdoughDen(double t)
{
    return quartic(t,
                   kSourdoughDenT4,
                   kSourdoughDenT3,
                   kSourdoughDenT2,
                   kSourdoughDenT1,
                   kSourdoughDenC);
}

double rate(double temperature)
{
    return std::exp(kRatePerDegree * temperature) * kRateBase;
}

double growthRoot(double value)
{
    return std::pow(value, kInvGrowthExponent);
}

double doughScale(double flour)
{
    return std::pow(flour, kDoughScaleExponent) * kDoughScaleFactor;
}

} // namespace

Calculator::Calculator(QObject *parent)
    : QObject(parent)
{
    recalc();
}

void Calculator::applyPreset(int style)
{
    const int index = (style == Roman) ? Roman : Neapolitan;
    const Preset &preset = kPresets[index];

    m_style = index;
    m_ballWeight = preset.ballWeight;
    m_hydration = preset.hydration;
    m_saltPercent = preset.saltPercent;
    m_fatsPercent = preset.fatsPercent;
    m_rtHours = preset.rtHours;
    m_rtTemp = preset.rtTemp;
    m_coldEnabled = preset.coldEnabled;
    m_ctHours = preset.ctHours;
    m_ctTemp = preset.ctTemp;

    changed();
}

void Calculator::recalc()
{
    const bool cold = m_coldEnabled && m_ctHours > 0.0;
    const double hr = m_rtHours;
    const double tr = m_rtTemp;
    const double hc = cold ? m_ctHours : 0.0;
    const double tc = m_ctTemp;

    const double dough = static_cast<double>(m_balls) * m_ballWeight * (1.0 + m_wastage / 100.0);

    // Yeast (or sourdough) percentage referred to the flour.
    const bool isSourdough = (m_yeastType == FirmSourdough || m_yeastType == LiquidSourdough);
    m_sourdough = isSourdough;

    double yeast = 0.0;
    if (isSourdough) {
        const double room = std::exp((hr - sourdoughPoly(tr)) / sourdoughDen(tr));
        const double matured = cold ? room * std::exp(hc / sourdoughDen(tc)) : room;
        yeast = (m_yeastType == LiquidSourdough) ? kLiquidSourdoughFactor * matured : matured;
    } else {
        const bool dry = (m_yeastType == InstantDry || m_yeastType == ActiveDry);
        const double tempFactor = (m_yeastType == InstantDry)  ? kInstantDryTempFactor
                                  : (m_yeastType == ActiveDry) ? kActiveDryTempFactor
                                                               : 0.0;

        const double rateRoom = rate(tr);
        const double rateCold = cold ? rate(tc) : 0.0;

        // The stage whose temperature drives the conversion to a dry yeast.
        double stageTemp = tr;
        double base = 0.0;
        if (!cold) {
            base = growthRoot(rateRoom / hr);
        } else if (!dry || tr >= tc) {
            const double equivalentCold = rateCold * hr / rateRoom;
            base = growthRoot(rateCold / (hc + equivalentCold));
        } else {
            // The room stage is colder than the controlled stage: swap them.
            const double equivalentRoom = rateRoom * hc / rateCold;
            base = growthRoot(rateRoom / (hr + equivalentRoom));
            stageTemp = tc;
        }

        yeast = base * 100.0;
        if (dry) {
            yeast /= stageTemp * tempFactor + 1.0;
        }
    }

    const double styleFactor = (m_style == Roman) ? kRomanFactor : kNeapolitanFactor;
    const bool preferred = m_poolishEnabled || m_bigaEnabled;

    const double firstFlour = dough
                              / (1.0
                                 + (m_hydration + m_saltPercent + m_fatsPercent + yeast) / 100.0);
    double totalYeast = m_yeastCorrection * styleFactor * doughScale(firstFlour)
                        * (firstFlour * yeast / 100.0);

    if (preferred) {
        totalYeast *= kPrefermentYeastFactor;
    }

    const double yeastPercent = totalYeast * 100.0 / firstFlour;
    double flourBasis = dough
                        / (1.0
                           + (m_hydration + m_saltPercent + m_fatsPercent + yeastPercent) / 100.0);

    if (m_style == Roman) {
        totalYeast = m_yeastCorrection * styleFactor * doughScale(flourBasis)
                     * (flourBasis * m_hydration / 100.0 * yeast / 100.0);
    }

    double solidPart = 0.0;
    double liquidPart = 0.0;
    if (isSourdough) {
        const bool firm = (m_yeastType == FirmSourdough);
        solidPart = firm ? totalYeast * 2.0 / 3.0 : totalYeast / 2.0;
        liquidPart = firm ? totalYeast / 3.0 : totalYeast / 2.0;
        flourBasis = dough / (1.0 + (m_hydration + m_saltPercent + m_fatsPercent) / 100.0)
                     - solidPart;
    }

    const double basis = flourBasis + solidPart;
    const double water = basis * m_hydration / 100.0 - liquidPart;
    const double saltGrams = basis * m_saltPercent / 100.0;
    const double fatsGrams = basis * m_fatsPercent / 100.0;

    // Pre-ferments, expressed as a share of the total flour.
    const double dryConversion = (m_yeastType == InstantDry)  ? kInstantDryConversion
                                 : (m_yeastType == ActiveDry) ? kActiveDryConversion
                                                              : 1.0;

    if (m_poolishEnabled) {
        m_poolishFlour = (m_poolishHours > 0.0) ? flourBasis * m_poolishFlourPercent / 100.0 : 0.0;
        m_poolishWater = kPoolishHydration * m_poolishFlour;
        m_poolishYeast = m_poolishFlour * kPoolishYeastCoefficient
                         * std::exp(kPoolishYeastDecay * m_poolishHours) / 100.0 * dryConversion;
        m_poolishTotal = m_poolishFlour + m_poolishWater + m_poolishYeast;
    } else {
        m_poolishFlour = m_poolishWater = m_poolishYeast = m_poolishTotal = 0.0;
    }

    if (m_bigaEnabled) {
        m_bigaFlour = flourBasis * m_bigaFlourPercent / 100.0;
        m_bigaWater = kBigaHydration * m_bigaFlour;
        m_bigaYeast = m_bigaFlour * kBigaYeastRatio * dryConversion;
        m_bigaTotal = m_bigaFlour + m_bigaWater + m_bigaYeast;
    } else {
        m_bigaFlour = m_bigaWater = m_bigaYeast = m_bigaTotal = 0.0;
    }

    const double mainFlour = flourBasis - m_poolishFlour - m_bigaFlour;
    const double mainWater = water - m_poolishWater - m_bigaWater;
    const double mainYeast = qMax(totalYeast - m_poolishYeast - m_bigaYeast, 0.0);

    m_waterExceeded = preferred && (mainWater < 0.0);
    m_mainFlourEmpty = preferred && (mainFlour <= 0.0);

    m_totalDough = dough;
    m_flour = mainFlour;
    m_water = mainWater;
    m_saltGrams = saltGrams;
    m_fatsGrams = fatsGrams;
    m_yeastGrams = mainYeast;

    // Total yeast actually added (main dough plus pre-ferments) on the total flour.
    const double doughYeast = mainYeast + m_poolishYeast + m_bigaYeast;
    m_yeastPercent = (flourBasis > 0.0) ? doughYeast * 100.0 / flourBasis : 0.0;

    emit resultsChanged();
}
