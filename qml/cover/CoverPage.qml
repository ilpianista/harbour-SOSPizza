import QtQuick 2.0
import Sailfish.Silica 1.0
import dev.scarpino.sospizza 1.0

CoverBackground {
    id: cover

    function format(value, decimals) {
        return value.toLocaleString(Qt.locale(), 'f', decimals);
    }

    Column {
        anchors.centerIn: parent
        spacing: Theme.paddingSmall

        Label {
            anchors.horizontalCenter: parent.horizontalCenter
            text: "SOSPizza"
            font.pixelSize: Theme.fontSizeMedium
            color: Theme.highlightColor
        }

        Label {
            anchors.horizontalCenter: parent.horizontalCenter
            text: qsTr("Total dough") + ": " + cover.format(Calculator.totalDough, 0) + " g"
            font.pixelSize: Theme.fontSizeSmall
            color: Theme.primaryColor
        }

        Label {
            anchors.horizontalCenter: parent.horizontalCenter
            text: qsTr("Flour") + ": " + cover.format(Calculator.flour, 0) + " g"
            font.pixelSize: Theme.fontSizeSmall
            color: Theme.primaryColor
        }

        Label {
            anchors.horizontalCenter: parent.horizontalCenter
            text: qsTr("Water") + ": " + cover.format(Calculator.water, 0) + " g"
            font.pixelSize: Theme.fontSizeSmall
            color: Theme.primaryColor
        }

        Label {
            anchors.horizontalCenter: parent.horizontalCenter
            text: qsTr("Salt") + ": " + cover.format(Calculator.saltGrams, 1) + " g"
            font.pixelSize: Theme.fontSizeSmall
            color: Theme.primaryColor
        }

        Label {
            anchors.horizontalCenter: parent.horizontalCenter
            visible: Calculator.fatsPercent > 0
            text: qsTr("Fats") + ": " + cover.format(Calculator.fatsGrams, 1) + " g"
            font.pixelSize: Theme.fontSizeSmall
            color: Theme.primaryColor
        }

        Label {
            anchors.horizontalCenter: parent.horizontalCenter
            text: (Calculator.sourdough ? qsTr("Sourdough") : qsTr("Yeast")) + ": " + cover.format(Calculator.yeastGrams, Calculator.yeastGrams < 0.1 ? 3 : 2) + " g"
            font.pixelSize: Theme.fontSizeSmall
            color: Theme.primaryColor
        }

        Label {
            anchors.horizontalCenter: parent.horizontalCenter
            visible: Calculator.poolishEnabled
            text: qsTr("Poolish") + ": " + cover.format(Calculator.poolishTotal, 0) + " g"
            font.pixelSize: Theme.fontSizeSmall
            color: Theme.primaryColor
        }

        Label {
            anchors.horizontalCenter: parent.horizontalCenter
            visible: Calculator.bigaEnabled
            text: qsTr("Biga") + ": " + cover.format(Calculator.bigaTotal, 0) + " g"
            font.pixelSize: Theme.fontSizeSmall
            color: Theme.primaryColor
        }
    }
}
