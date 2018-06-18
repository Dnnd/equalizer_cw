import QtQuick 2.9
import QtQuick.Controls 2.2
import Qt.labs.platform 1.0
import QtQuick.Layouts 1.3
import QtQuick.Window 2.10

ApplicationWindow {
    title: "Equalizer"
    width: Screen.width
    height: Screen.height
    visible: true

    header: RowLayout {
        GroupBox {
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
                    folder: StandardPaths.writableLocation(
                                StandardPaths.DocumentsLocation)
                    onAccepted: {
                        acceptedLabel.text = fileDialog.file
                        audioController.playSong(fileDialog.file)
                        playButton.text = "\u23F9"
                    }
                }
            }
        }
    }

    RowLayout {
        anchors.fill: parent
        Row {

            Layout.alignment: Qt.AlignCenter
            RoundButton {
                id: playButton
                text: "\u25BA"
                onClicked: {

                    if (text == "\u25BA") {
                        audioController.resume()
                        text = "\u23F9"
                    } else {
                        text = "\u25BA"
                        audioController.stop()
                    }
                }
            }
            Column {
                Switch {
                    text: qsTr("Overdrive")
                    onToggled: {
                        audioController.toggleEffect("overdrive")
                    }
                }
                Switch {
                    text: qsTr("Echo")
                    onToggled: {
                        audioController.toggleEffect("echo")
                        if (position == 1.0) {
                            echoControllerSlider.visible = true
                            echoIndicator.visible = true
                        } else if (position == 0) {
                            echoControllerSlider.visible = false
                            echoIndicator.visible = false
                        }
                    }
                }
                Slider {
                    id: echoControllerSlider
                    value: 100
                    stepSize: 10
                    from: 50
                    to: 200
                    visible: false
                    onMoved: {
                        audioController.changeEffectParam("echo", value)
                        echoIndicator.text = value
                    }
                }
                Label {
                    visible: false
                    id: echoIndicator
                    Layout.alignment: Qt.AlignHCenter
                    text: echoControllerSlider.value
                }
            }
        }
    }

    footer: RowLayout {
        Layout.alignment: Qt.AlignCenter

        ColumnLayout {
            Label {
                text: "3 dB"
                Layout.fillHeight: true
            }

            Label {
                id: botLabel
                text: "-40 dB"
            }
        }
        Repeater {

            model: ["0 - 100", "100 - 157", "157 - 250", "250 - 397", "397 - 630", "630 - 1000", "1000 - 1587", "1587 - 2520", "2520 - 4000", "4000 - 6350", "6350 - 10079", "10079 - 16000", "16000 - 20000"]
            ColumnLayout {
                Label {
                    id: sliderIndicator
                    Layout.alignment: Qt.AlignHCenter
                    Layout.fillHeight: true
                    text: slider.value
                }
                Slider {
                    id: slider
                    value: 0
                    stepSize: 1
                    from: -40
                    to: 3
                    orientation: Qt.Vertical

                    Layout.fillWidth: true
                    onMoved: {
                        sliderIndicator.text = value
                        audioController.setGain(index, value)
                    }
                }
                Label {
                    text: modelData.concat(" Hz")
                    Layout.alignment: Qt.AlignHCenter
                    Layout.fillHeight: true
                }
            }
        }
    }
}
