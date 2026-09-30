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

        Column {
            id: column
            width: page.width
            spacing: Theme.paddingMedium

            PageHeader {
                title: qsTr("Settings")
            }

            SectionHeader {
                text: qsTr("Fermentation")
            }

            TextSwitch {
                width: parent.width
                text: qsTr("Controlled temperature stage")
                description: qsTr("Allows to insert cold fermentation details")
                checked: Calculator.coldEnabled
                onCheckedChanged: Calculator.coldEnabled = checked
            }

            SectionHeader {
                text: qsTr("Pre-ferments")
            }

            TextSwitch {
                id: poolishSwitch
                width: parent.width
                text: qsTr("Poolish")
                description: qsTr("Allows to insert Poolish details")
                checked: Calculator.poolishEnabled
                onCheckedChanged: {
                    Calculator.poolishEnabled = checked;
                    if (checked) {
                        Calculator.bigaEnabled = false;
                        bigaSwitch.checked = false;
                    }
                }
            }

            TextSwitch {
                id: bigaSwitch
                width: parent.width
                text: qsTr("Biga")
                description: qsTr("Allows to insert Biga details")
                checked: Calculator.bigaEnabled
                onCheckedChanged: {
                    Calculator.bigaEnabled = checked;
                    if (checked) {
                        Calculator.poolishEnabled = false;
                        poolishSwitch.checked = false;
                    }
                }
            }

            SectionHeader {
                text: qsTr("Yeast")
            }

            Slider {
                width: parent.width
                label: qsTr("Yeast adjustment")
                minimumValue: -50
                maximumValue: 50
                stepSize: 5
                value: Math.round((Calculator.yeastCorrection - 1) * 100)
                valueText: (value > 0 ? "+" : "") + page.format(value, 0) + " %"
                onValueChanged: Calculator.yeastCorrection = 1 + value / 100
            }
        }

        VerticalScrollDecorator {}
    }
}
