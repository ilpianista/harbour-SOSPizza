import QtQuick 2.2
import Sailfish.Silica 1.0
import dev.scarpino.sospizza 1.0

Page {
    id: page
    allowedOrientations: Orientation.All

    function format(value, decimals) {
        return value.toLocaleString(Qt.locale(), 'f', decimals);
    }

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: column.height + Theme.paddingLarge

        PullDownMenu {
            MenuItem {
                text: qsTr("Settings")
                onClicked: pageStack.push(Qt.resolvedUrl("SettingsPage.qml"))
            }
        }

        Column {
            id: column
            width: page.width
            spacing: Theme.paddingMedium

            PageHeader {
                title: "SOSPizza"
            }

            ComboBox {
                width: parent.width
                label: qsTr("Dough style")
                currentIndex: Calculator.style
                menu: ContextMenu {
                    MenuItem {
                        text: qsTr("Neapolitan")
                    }
                    MenuItem {
                        text: qsTr("Roman")
                    }
                }
                onCurrentIndexChanged: Calculator.applyPreset(currentIndex)
            }

            SectionHeader {
                text: qsTr("Dough")
            }

            Slider {
                width: parent.width
                label: qsTr("Dough balls")
                minimumValue: 1
                maximumValue: 100
                stepSize: 1
                value: Calculator.balls
                valueText: page.format(value, 0)
                onValueChanged: Calculator.balls = Math.round(value)
            }

            Slider {
                width: parent.width
                label: qsTr("Ball weight")
                minimumValue: 10
                maximumValue: 1500
                stepSize: 5
                value: Calculator.ballWeight
                valueText: page.format(value, 0) + " g"
                onValueChanged: Calculator.ballWeight = Math.round(value)
            }

            SectionHeader {
                text: qsTr("Ingredients")
            }

            Slider {
                width: parent.width
                label: qsTr("Hydration")
                minimumValue: 40
                maximumValue: 100
                stepSize: 1
                value: Calculator.hydration
                valueText: page.format(value, 0) + " %"
                onValueChanged: Calculator.hydration = value
            }

            Slider {
                width: parent.width
                label: qsTr("Salt")
                minimumValue: 0
                maximumValue: 6
                stepSize: 0.1
                value: Calculator.saltPercent
                valueText: page.format(value, 1) + " %"
                onValueChanged: Calculator.saltPercent = value
            }

            Slider {
                width: parent.width
                label: qsTr("Fats")
                minimumValue: 0
                maximumValue: 10
                stepSize: 0.1
                value: Calculator.fatsPercent
                valueText: page.format(value, 1) + " %"
                onValueChanged: Calculator.fatsPercent = value
            }

            Slider {
                width: parent.width
                label: qsTr("Wastage")
                minimumValue: 0
                maximumValue: 5
                stepSize: 1
                value: Calculator.wastage
                valueText: page.format(value, 0) + " %"
                onValueChanged: Calculator.wastage = Math.round(value)
            }

            SectionHeader {
                text: qsTr("Fermentation")
            }

            Slider {
                width: parent.width
                label: qsTr("Room temperature time")
                minimumValue: 1
                maximumValue: 100
                stepSize: 1
                value: Calculator.rtHours
                valueText: page.format(value, 0) + " h"
                onValueChanged: Calculator.rtHours = Math.round(value)
            }

            Slider {
                width: parent.width
                label: qsTr("Room temperature")
                minimumValue: 10
                maximumValue: 40
                stepSize: 0.5
                value: Calculator.rtTemp
                valueText: page.format(value, 1) + " °C"
                onValueChanged: Calculator.rtTemp = value
            }

            SectionHeader {
                visible: Calculator.coldEnabled
                text: qsTr("Controlled temperature")
            }

            Slider {
                width: parent.width
                visible: Calculator.coldEnabled
                label: qsTr("Controlled temperature time")
                minimumValue: 1
                maximumValue: 100
                stepSize: 1
                value: Calculator.ctHours
                valueText: page.format(value, 0) + " h"
                onValueChanged: Calculator.ctHours = Math.round(value)
            }

            Slider {
                width: parent.width
                visible: Calculator.coldEnabled
                label: qsTr("Controlled temperature")
                minimumValue: 1
                maximumValue: 20
                stepSize: 0.5
                value: Calculator.ctTemp
                valueText: page.format(value, 1) + " °C"
                onValueChanged: Calculator.ctTemp = value
            }

            SectionHeader {
                text: qsTr("Yeast")
            }

            ComboBox {
                width: parent.width
                label: qsTr("Yeast type")
                currentIndex: Calculator.yeastType
                menu: ContextMenu {
                    MenuItem {
                        text: qsTr("Compressed yeast")
                    }
                    MenuItem {
                        text: qsTr("Instant dry yeast")
                    }
                    MenuItem {
                        text: qsTr("Active dry yeast")
                    }
                    MenuItem {
                        text: qsTr("Firm sourdough")
                    }
                    MenuItem {
                        text: qsTr("Liquid sourdough")
                    }
                }
                onCurrentIndexChanged: Calculator.yeastType = currentIndex
            }

            Label {
                x: Theme.horizontalPageMargin
                width: parent.width - 2 * Theme.horizontalPageMargin
                visible: Math.abs(Calculator.yeastCorrection - 1) > 0.001
                wrapMode: Text.WordWrap
                text: qsTr("Yeast adjustment") + ": " + (Calculator.yeastCorrection > 1 ? "+" : "") + page.format((Calculator.yeastCorrection - 1) * 100, 0) + " %"
                color: Theme.highlightColor
                font.pixelSize: Theme.fontSizeSmall
            }

            SectionHeader {
                visible: Calculator.poolishEnabled
                text: qsTr("Poolish")
            }

            Slider {
                width: parent.width
                visible: Calculator.poolishEnabled
                label: qsTr("Poolish flour")
                minimumValue: 10
                maximumValue: 100
                stepSize: 1
                value: Calculator.poolishFlourPercent
                valueText: page.format(value, 0) + " %"
                onValueChanged: Calculator.poolishFlourPercent = Math.round(value)
            }

            Slider {
                width: parent.width
                visible: Calculator.poolishEnabled
                label: qsTr("Poolish time")
                minimumValue: 1
                maximumValue: 24
                stepSize: 1
                value: Calculator.poolishHours
                valueText: page.format(value, 0) + " h"
                onValueChanged: Calculator.poolishHours = Math.round(value)
            }

            SectionHeader {
                visible: Calculator.bigaEnabled
                text: qsTr("Biga")
            }

            Slider {
                width: parent.width
                visible: Calculator.bigaEnabled
                label: qsTr("Biga flour")
                minimumValue: 10
                maximumValue: 100
                stepSize: 1
                value: Calculator.bigaFlourPercent
                valueText: page.format(value, 0) + " %"
                onValueChanged: Calculator.bigaFlourPercent = Math.round(value)
            }

            Label {
                x: Theme.horizontalPageMargin
                width: parent.width - 2 * Theme.horizontalPageMargin
                visible: Calculator.waterExceeded
                wrapMode: Text.WordWrap
                text: qsTr("Pre-ferment water exceeds the dough water!")
                color: Theme.highlightColor
                font.pixelSize: Theme.fontSizeSmall
            }

            Label {
                x: Theme.horizontalPageMargin
                width: parent.width - 2 * Theme.horizontalPageMargin
                visible: Calculator.mainFlourEmpty
                wrapMode: Text.WordWrap
                text: qsTr("No flour left in the main dough!")
                color: Theme.highlightColor
                font.pixelSize: Theme.fontSizeSmall
            }

            SectionHeader {
                text: qsTr("Doses")
            }

            DetailItem {
                width: parent.width
                label: qsTr("Total dough")
                value: page.format(Calculator.totalDough, 0) + " g"
            }

            DetailItem {
                width: parent.width
                label: qsTr("Flour")
                value: page.format(Calculator.flour, 0) + " g"
            }

            DetailItem {
                width: parent.width
                label: qsTr("Water")
                value: page.format(Calculator.water, 0) + " g"
            }

            DetailItem {
                width: parent.width
                label: qsTr("Salt")
                value: page.format(Calculator.saltGrams, 1) + " g"
            }

            DetailItem {
                width: parent.width
                visible: Calculator.fatsPercent > 0
                label: qsTr("Fats")
                value: page.format(Calculator.fatsGrams, 1) + " g"
            }

            DetailItem {
                width: parent.width
                label: Calculator.sourdough ? qsTr("Sourdough") : qsTr("Yeast")
                value: page.format(Calculator.yeastGrams, Calculator.yeastGrams < 0.1 ? 3 : 2) + " g"
            }

            DetailItem {
                width: parent.width
                label: qsTr("Yeast on flour")
                value: page.format(Calculator.yeastPercent, 2) + " %"
            }

            SectionHeader {
                visible: Calculator.poolishEnabled
                text: qsTr("Poolish doses")
            }

            DetailItem {
                width: parent.width
                visible: Calculator.poolishEnabled
                label: qsTr("Poolish flour")
                value: page.format(Calculator.poolishFlour, 0) + " g"
            }

            DetailItem {
                width: parent.width
                visible: Calculator.poolishEnabled
                label: qsTr("Poolish water")
                value: page.format(Calculator.poolishWater, 0) + " g"
            }

            DetailItem {
                width: parent.width
                visible: Calculator.poolishEnabled
                label: qsTr("Poolish yeast")
                value: page.format(Calculator.poolishYeast, Calculator.poolishYeast < 0.1 ? 3 : 2) + " g"
            }

            DetailItem {
                width: parent.width
                visible: Calculator.poolishEnabled
                label: qsTr("Poolish total")
                value: page.format(Calculator.poolishTotal, 0) + " g"
            }

            SectionHeader {
                visible: Calculator.bigaEnabled
                text: qsTr("Biga doses")
            }

            DetailItem {
                width: parent.width
                visible: Calculator.bigaEnabled
                label: qsTr("Biga flour")
                value: page.format(Calculator.bigaFlour, 0) + " g"
            }

            DetailItem {
                width: parent.width
                visible: Calculator.bigaEnabled
                label: qsTr("Biga water")
                value: page.format(Calculator.bigaWater, 0) + " g"
            }

            DetailItem {
                width: parent.width
                visible: Calculator.bigaEnabled
                label: qsTr("Biga yeast")
                value: page.format(Calculator.bigaYeast, Calculator.bigaYeast < 0.1 ? 3 : 2) + " g"
            }

            DetailItem {
                width: parent.width
                visible: Calculator.bigaEnabled
                label: qsTr("Biga total")
                value: page.format(Calculator.bigaTotal, 0) + " g"
            }
        }

        VerticalScrollDecorator {}
    }
}
