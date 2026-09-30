TARGET = harbour-sospizza

CONFIG += sailfishapp

QT += qml quick

SOURCES += \
    src/main.cpp \
    src/calculator.cpp

HEADERS += \
    src/calculator.h

DISTFILES += \
    qml/harbour-sospizza.qml \
    qml/pages/CalculatorPage.qml \
    qml/pages/SettingsPage.qml \
    qml/cover/CoverPage.qml \
    rpm/harbour-sospizza.changes \
    rpm/harbour-sospizza.spec \
    translations/*.ts \
    harbour-sospizza.desktop

SAILFISHAPP_ICONS = 86x86 108x108 128x128 172x172 256x256

CONFIG += sailfishapp_i18n

TRANSLATIONS += \
    translations/harbour-sospizza-it.ts
