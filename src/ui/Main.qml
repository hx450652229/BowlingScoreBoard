import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Window {
    id: root
    width: 1000  // Slightly wider to ensure ten frames fit comfortably.
    height: 300
    visible: true
    title: qsTr("Bowling Scoreboard")
    color: "#2c3e50" // Darker background for a polished appearance.

    ColumnLayout {
        anchors.centerIn: parent
        spacing: 30

        // Header and live total score display.
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
                    // Bind directly to the view model's totalScore property.
                    text: bowlingVM.totalScore
                    font.pixelSize: 32
                    font.bold: true
                    color: "#2c3e50"
                }
            }
        }

        // Main scoreboard row.
        RowLayout {
            Layout.alignment: Qt.AlignHCenter
            spacing: 8
            
            Repeater {
                // Bind to the QVariantList frames exposed by the view model.
                model: bowlingVM.frames 
                
                delegate: FrameBox {
                    // modelData maps to each QVariantMap item.
                    frameNumber: modelData.frameNumber
                    throw1: modelData.t1
                    throw2: modelData.t2
                    throw3: modelData.t3
                    frameScore: modelData.score
                    
                    // Highlight the current active frame.
                    // Logic: highlight when the frame has no score yet and the previous frame is completed or this is the first frame.
                    border.color: (modelData.score === "" && (index === 0 || bowlingVM.frames[index-1].score !== "")) 
                                  ? "#3498db" : "#cccccc"
                    border.width: border.color == "#3498db" ? 3 : 1
                }
            }
        }

        // Bottom status bar.
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

            Item { Layout.fillWidth: true } // Spacer.

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
