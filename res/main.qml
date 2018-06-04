import QtQuick 2.10
import QtQuick.Controls 2.3
import Qt.labs.platform 1.0
import QtQuick.Layouts 1.3

ApplicationWindow {
    title: "My Application"
    width: 640
    height: 480
    visible: true
    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 11
        GroupBox{
            background: Rectangle {
                        border.width: 0
            }

            Layout.fillWidth: true
            RowLayout {
                    anchors.fill: parent
                    TextField {
                        id: acceptedLabel
                        Layout.fillWidth: true
                        readOnly: true
                        text: qsTr("...")
                    }

                    Button {
                        text: "Pick song"
                        onClicked: fileDialog.open()
                    }

                    FileDialog {
                        id: fileDialog
                        title: "Please choose a file"
                        folder: StandardPaths.writableLocation(StandardPaths.DocumentsLocation)
                        onAccepted: {
                            acceptedLabel.text = fileDialog.file
                            audioController.playSong(fileDialog.file)
                        }

                    }
            }
        }
        GroupBox{
            background: Rectangle {
                border.width: 0
            }
            Layout.fillWidth: true
            RowLayout{
                anchors.fill: parent
                  Switch {
                    text: qsTr("Echo")
                   }
                  Switch {
                    text: qsTr("delay")
                  }
            }
        }
        GroupBox {
            Layout.fillWidth: true
            background: Rectangle {
                border.color: "#26282a"
                border.width: 1

            }
            RowLayout{
                anchors.fill: parent
                     ColumnLayout{
                                anchors.fill: parent
                                Label {
                                    text: "40 dB"
                                    Layout.fillHeight: true
                                }

                                Label {
                                    id: botLabel
                                    text: "-3 dB"

                                }
                     }

                     Repeater {
                        model: ["0 - 396 Hz", "396 - 630 Hz",
                        "630 - 1000 Hz",
                        "1000 - 1587 Hz",
                        "1587 - 2520 Hz",
                        "2520 - 3400 Hz"
                        ]
                        ColumnLayout{
                            Label {
                                 id: sliderIndicator
                                 Layout.alignment: Qt.AlignHCenter
                                 Layout.fillHeight: true
                                 text: slider.value
                            }

                            Slider {
                                id: slider
                                value: 1
                                stepSize: 1
                                from: -3
                                to: 40
                                orientation: Qt.Vertical
                                Layout.fillWidth: true
                                onMoved:{
                                    sliderIndicator.text = value
                                    audioController.setGain(index, value)
                                }
                            }
                              Label {
                                text: modelData
                                Layout.alignment: Qt.AlignHCenter
                                Layout.fillHeight: true
                             }
                        }
                    }
                }
        }
    }
}