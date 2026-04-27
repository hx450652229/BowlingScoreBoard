import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: root
    width: 80
    height: 100
    color: "#f0f0f0"
    border.color: "#cccccc"
    border.width: 1
    radius: 4

    // External properties exposed for each frame box.
    property int frameNumber: 1
    property string throw1: ""
    property string throw2: ""
    property string throw3: "" // Used only in the tenth frame.
    property string frameScore: ""

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 5
        spacing: 2

        // Top: frame number.
        Text {
            Layout.alignment: Qt.AlignHCenter
            text: root.frameNumber
            font.bold: true
            font.pixelSize: 14
        }

        // Middle: pin display for individual throws.
        RowLayout {
            Layout.fillWidth: true
            Layout.preferredHeight: 30
            spacing: 2

            Rectangle {
                Layout.fillWidth: true
                Layout.fillHeight: true
                border.color: "#999"
                Text { anchors.centerIn: parent; text: root.throw1; font.bold: true }
            }
            Rectangle {
                Layout.fillWidth: true
                Layout.fillHeight: true
                border.color: "#999"
                Text { anchors.centerIn: parent; text: root.throw2; font.bold: true }
            }
            // Third roll display visible only for the tenth frame.
            Rectangle {
                visible: root.frameNumber === 10
                Layout.fillWidth: true
                Layout.fillHeight: true
                border.color: "#999"
                Text { anchors.centerIn: parent; text: root.throw3; font.bold: true }
            }
        }

        // Bottom: cumulative frame score.
        Text {
            Layout.alignment: Qt.AlignHCenter | Qt.AlignBottom
            Layout.fillHeight: true
            text: root.frameScore
            font.pixelSize: 24
            font.bold: true
            verticalAlignment: Text.AlignBottom
        }
    }
}
