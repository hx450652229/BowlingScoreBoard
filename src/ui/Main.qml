import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Window {
    id: root
    width: 1000  // 稍微加宽一点，确保10局显示不拥挤
    height: 300
    visible: true
    title: qsTr("Bowling Scoreboard")
    color: "#2c3e50" // 改深色背景更有生产感

    ColumnLayout {
        anchors.centerIn: parent
        spacing: 30

        // 标题和实时总分
        RowLayout {
            Layout.alignment: Qt.AlignHCenter
            spacing: 20
            
            Text {
                text: "PLAYER 1"
                color: "white"
                font.pixelSize: 28
                font.bold: true
                font.letterSpacing: 2
            }

            Rectangle {
                width: 120
                height: 50
                color: "#f1c40f"
                radius: 4
                Text {
                    anchors.centerIn: parent
                    // 直接绑定 ViewModel 的 totalScore 属性
                    text: bowlingVM.totalScore
                    font.pixelSize: 32
                    font.bold: true
                    color: "#2c3e50"
                }
            }
        }

        // 核心计分板
        RowLayout {
            Layout.alignment: Qt.AlignHCenter
            spacing: 8
            
            Repeater {
                // 绑定到 ViewModel 暴露的 QVariantList frames
                model: bowlingVM.frames 
                
                delegate: FrameBox {
                    // modelData 对应的是 QVariantMap 中的每一项
                    frameNumber: modelData.frameNumber
                    throw1: modelData.t1
                    throw2: modelData.t2
                    throw3: modelData.t3
                    frameScore: modelData.score
                    
                    // 增加一个简单的状态提示：如果是当前正在进行的局，可以加个高亮
                    // 这里判断依据：如果该局还没分且前一局有分或者是第一局
                    border.color: (modelData.score === "" && (index === 0 || bowlingVM.frames[index-1].score !== "")) 
                                  ? "#3498db" : "#cccccc"
                    border.width: border.color == "#3498db" ? 3 : 1
                }
            }
        }

        // 底部状态条
        RowLayout {
            Layout.fillWidth: true
            Layout.leftMargin: 20
            Layout.rightMargin: 20

            Text {
                text: bowlingVM.isFinished ? "GAME OVER" : "WAITING FOR UDP DATA..."
                color: bowlingVM.isFinished ? "#e74c3c" : "#2ecc71"
                font.pixelSize: 14
                font.bold: true
                
                SequentialAnimation on opacity {
                    running: !bowlingVM.isFinished
                    loops: Animation.Infinite
                    NumberAnimation { from: 1; to: 0.3; duration: 800 }
                    NumberAnimation { from: 0.3; to: 1; duration: 800 }
                }
            }

            Item { Layout.fillWidth: true } // 弹簧

            Button {
                text: "RESET GAME"
                onClicked: bowlingVM.reset()
                contentItem: Text {
                    text: parent.text
                    color: "white"
                    horizontalAlignment: Text.AlignHCenter
                }
                background: Rectangle {
                    color: parent.down ? "#c0392b" : "#e74c3c"
                    radius: 4
                }
            }
        }
    }
}