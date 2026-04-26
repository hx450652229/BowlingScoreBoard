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

    // 暴露给外部设置的属性 (相当于 C++ 的 public variables)
    property int frameNumber: 1
    property string throw1: ""
    property string throw2: ""
    property string throw3: "" // 仅第10局使用
    property string frameScore: ""

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 5
        spacing: 2

        // 顶部：局数
        Text {
            Layout.alignment: Qt.AlignHCenter
            text: root.frameNumber
            font.bold: true
            font.pixelSize: 14
        }

        // 中间：击倒的瓶数展示 (分成两个/三个小框)
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
            // 第10局才显示的第三个框
            Rectangle {
                visible: root.frameNumber === 10
                Layout.fillWidth: true
                Layout.fillHeight: true
                border.color: "#999"
                Text { anchors.centerIn: parent; text: root.throw3; font.bold: true }
            }
        }

        // 底部：累计总分
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