#pragma once

#include <QObject>
#include <QtGlobal>

class Calculator : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int style READ style WRITE setStyle NOTIFY inputChanged)
    Q_PROPERTY(int balls READ balls WRITE setBalls NOTIFY inputChanged)
    Q_PROPERTY(int ballWeight READ ballWeight WRITE setBallWeight NOTIFY inputChanged)
    Q_PROPERTY(double hydration READ hydration WRITE setHydration NOTIFY inputChanged)
    Q_PROPERTY(double saltPercent READ saltPercent WRITE setSaltPercent NOTIFY inputChanged)
    Q_PROPERTY(double fatsPercent READ fatsPercent WRITE setFatsPercent NOTIFY inputChanged)
    Q_PROPERTY(double rtHours READ rtHours WRITE setRtHours NOTIFY inputChanged)
    Q_PROPERTY(double rtTemp READ rtTemp WRITE setRtTemp NOTIFY inputChanged)
    Q_PROPERTY(bool coldEnabled READ coldEnabled WRITE setColdEnabled NOTIFY inputChanged)
    Q_PROPERTY(double ctHours READ ctHours WRITE setCtHours NOTIFY inputChanged)
    Q_PROPERTY(double ctTemp READ ctTemp WRITE setCtTemp NOTIFY inputChanged)
    Q_PROPERTY(int yeastType READ yeastType WRITE setYeastType NOTIFY inputChanged)
    Q_PROPERTY(
        double yeastCorrection READ yeastCorrection WRITE setYeastCorrection NOTIFY inputChanged)
    Q_PROPERTY(int wastage READ wastage WRITE setWastage NOTIFY inputChanged)
    Q_PROPERTY(bool poolishEnabled READ poolishEnabled WRITE setPoolishEnabled NOTIFY inputChanged)
    Q_PROPERTY(double poolishFlourPercent READ poolishFlourPercent WRITE setPoolishFlourPercent
                   NOTIFY inputChanged)
    Q_PROPERTY(double poolishHours READ poolishHours WRITE setPoolishHours NOTIFY inputChanged)
    Q_PROPERTY(bool bigaEnabled READ bigaEnabled WRITE setBigaEnabled NOTIFY inputChanged)
    Q_PROPERTY(
        double bigaFlourPercent READ bigaFlourPercent WRITE setBigaFlourPercent NOTIFY inputChanged)

    Q_PROPERTY(double totalDough READ totalDough NOTIFY resultsChanged)
    Q_PROPERTY(double flour READ flour NOTIFY resultsChanged)
    Q_PROPERTY(double water READ water NOTIFY resultsChanged)
    Q_PROPERTY(double saltGrams READ saltGrams NOTIFY resultsChanged)
    Q_PROPERTY(double fatsGrams READ fatsGrams NOTIFY resultsChanged)
    Q_PROPERTY(double yeastGrams READ yeastGrams NOTIFY resultsChanged)
    Q_PROPERTY(double yeastPercent READ yeastPercent NOTIFY resultsChanged)
    Q_PROPERTY(bool sourdough READ sourdough NOTIFY resultsChanged)
    Q_PROPERTY(double poolishFlour READ poolishFlour NOTIFY resultsChanged)
    Q_PROPERTY(double poolishWater READ poolishWater NOTIFY resultsChanged)
    Q_PROPERTY(double poolishYeast READ poolishYeast NOTIFY resultsChanged)
    Q_PROPERTY(double poolishTotal READ poolishTotal NOTIFY resultsChanged)
    Q_PROPERTY(double bigaFlour READ bigaFlour NOTIFY resultsChanged)
    Q_PROPERTY(double bigaWater READ bigaWater NOTIFY resultsChanged)
    Q_PROPERTY(double bigaYeast READ bigaYeast NOTIFY resultsChanged)
    Q_PROPERTY(double bigaTotal READ bigaTotal NOTIFY resultsChanged)
    Q_PROPERTY(bool waterExceeded READ waterExceeded NOTIFY resultsChanged)
    Q_PROPERTY(bool mainFlourEmpty READ mainFlourEmpty NOTIFY resultsChanged)

public:
    enum Style { Neapolitan = 0, Roman = 1 };
    Q_ENUM(Style)

    enum Yeast {
        Compressed = 0,
        InstantDry = 1,
        ActiveDry = 2,
        FirmSourdough = 3,
        LiquidSourdough = 4
    };
    Q_ENUM(Yeast)

    explicit Calculator(QObject *parent = nullptr);

    int style() const { return m_style; }
    int balls() const { return m_balls; }
    int ballWeight() const { return m_ballWeight; }
    double hydration() const { return m_hydration; }
    double saltPercent() const { return m_saltPercent; }
    double fatsPercent() const { return m_fatsPercent; }
    double rtHours() const { return m_rtHours; }
    double rtTemp() const { return m_rtTemp; }
    bool coldEnabled() const { return m_coldEnabled; }
    double ctHours() const { return m_ctHours; }
    double ctTemp() const { return m_ctTemp; }
    int yeastType() const { return m_yeastType; }
    double yeastCorrection() const { return m_yeastCorrection; }
    int wastage() const { return m_wastage; }
    bool poolishEnabled() const { return m_poolishEnabled; }
    double poolishFlourPercent() const { return m_poolishFlourPercent; }
    double poolishHours() const { return m_poolishHours; }
    bool bigaEnabled() const { return m_bigaEnabled; }
    double bigaFlourPercent() const { return m_bigaFlourPercent; }

    double totalDough() const { return m_totalDough; }
    double flour() const { return m_flour; }
    double water() const { return m_water; }
    double saltGrams() const { return m_saltGrams; }
    double fatsGrams() const { return m_fatsGrams; }
    double yeastGrams() const { return m_yeastGrams; }
    double yeastPercent() const { return m_yeastPercent; }
    bool sourdough() const { return m_sourdough; }
    double poolishFlour() const { return m_poolishFlour; }
    double poolishWater() const { return m_poolishWater; }
    double poolishYeast() const { return m_poolishYeast; }
    double poolishTotal() const { return m_poolishTotal; }
    double bigaFlour() const { return m_bigaFlour; }
    double bigaWater() const { return m_bigaWater; }
    double bigaYeast() const { return m_bigaYeast; }
    double bigaTotal() const { return m_bigaTotal; }
    bool waterExceeded() const { return m_waterExceeded; }
    bool mainFlourEmpty() const { return m_mainFlourEmpty; }

    Q_INVOKABLE void applyPreset(int style);

    void setStyle(int v)
    {
        if (assign(m_style, v)) {
            changed();
        }
    }
    void setBalls(int v)
    {
        if (assign(m_balls, v)) {
            changed();
        }
    }
    void setBallWeight(int v)
    {
        if (assign(m_ballWeight, v)) {
            changed();
        }
    }
    void setHydration(double v)
    {
        if (assign(m_hydration, v)) {
            changed();
        }
    }
    void setSaltPercent(double v)
    {
        if (assign(m_saltPercent, v)) {
            changed();
        }
    }
    void setFatsPercent(double v)
    {
        if (assign(m_fatsPercent, v)) {
            changed();
        }
    }
    void setRtHours(double v)
    {
        if (assign(m_rtHours, v)) {
            changed();
        }
    }
    void setRtTemp(double v)
    {
        if (assign(m_rtTemp, v)) {
            changed();
        }
    }
    void setColdEnabled(bool v)
    {
        if (assign(m_coldEnabled, v)) {
            changed();
        }
    }
    void setCtHours(double v)
    {
        if (assign(m_ctHours, v)) {
            changed();
        }
    }
    void setCtTemp(double v)
    {
        if (assign(m_ctTemp, v)) {
            changed();
        }
    }
    void setYeastType(int v)
    {
        if (assign(m_yeastType, v)) {
            changed();
        }
    }
    void setYeastCorrection(double v)
    {
        if (assign(m_yeastCorrection, v)) {
            changed();
        }
    }
    void setWastage(int v)
    {
        if (assign(m_wastage, v)) {
            changed();
        }
    }
    void setPoolishFlourPercent(double v)
    {
        if (assign(m_poolishFlourPercent, v)) {
            changed();
        }
    }
    void setPoolishHours(double v)
    {
        if (assign(m_poolishHours, v)) {
            changed();
        }
    }
    void setBigaFlourPercent(double v)
    {
        if (assign(m_bigaFlourPercent, v)) {
            changed();
        }
    }

    // Poolish and biga are mutually exclusive.
    void setPoolishEnabled(bool v)
    {
        if (m_poolishEnabled == v) {
            return;
        }
        m_poolishEnabled = v;
        if (v) {
            m_bigaEnabled = false;
        }
        changed();
    }
    void setBigaEnabled(bool v)
    {
        if (m_bigaEnabled == v) {
            return;
        }
        m_bigaEnabled = v;
        if (v) {
            m_poolishEnabled = false;
        }
        changed();
    }

signals:
    void inputChanged();
    void resultsChanged();

private:
    // Store value in member and report whether it changed. The double overload
    // uses a fuzzy comparison that also behaves for values around zero.
    template<typename T>
    static bool assign(T &member, const T &value)
    {
        if (member == value) {
            return false;
        }
        member = value;
        return true;
    }
    static bool assign(double &member, double value)
    {
        if (qFuzzyCompare(member + 1.0, value + 1.0)) {
            return false;
        }
        member = value;
        return true;
    }

    void recalc();
    void changed()
    {
        recalc();
        emit inputChanged();
    }

    int m_style = Neapolitan;
    int m_balls = 4;
    int m_ballWeight = 250;
    double m_hydration = 60.0;
    double m_saltPercent = 3.0;
    double m_fatsPercent = 0.0;
    double m_rtHours = 8.0;
    double m_rtTemp = 20.0;
    bool m_coldEnabled = false;
    double m_ctHours = 43.0;
    double m_ctTemp = 4.0;
    int m_yeastType = Compressed;
    double m_yeastCorrection = 1.0;
    int m_wastage = 0;
    bool m_poolishEnabled = false;
    double m_poolishFlourPercent = 30.0;
    double m_poolishHours = 4.0;
    bool m_bigaEnabled = false;
    double m_bigaFlourPercent = 30.0;

    double m_totalDough = 0.0;
    double m_flour = 0.0;
    double m_water = 0.0;
    double m_saltGrams = 0.0;
    double m_fatsGrams = 0.0;
    double m_yeastGrams = 0.0;
    double m_yeastPercent = 0.0;
    bool m_sourdough = false;
    double m_poolishFlour = 0.0;
    double m_poolishWater = 0.0;
    double m_poolishYeast = 0.0;
    double m_poolishTotal = 0.0;
    double m_bigaFlour = 0.0;
    double m_bigaWater = 0.0;
    double m_bigaYeast = 0.0;
    double m_bigaTotal = 0.0;
    bool m_waterExceeded = false;
    bool m_mainFlourEmpty = false;
};
