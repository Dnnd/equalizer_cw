import QtQuick 2.9
import QtQuick.Controls 2.2
import Qt.labs.platform 1.0
import QtQuick.Layouts 1.3

ApplicationWindow {
    title: "Equalizer"
    width: 960
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
                            playButton.text = "\u23F9"
                        }

                    }
            }
        }
        RowLayout{
          Layout.fillWidth: true

        Layout.alignment: Qt.AlignHCenter
    RoundButton {

        id: playButton
        text: "\u25BA"
        onClicked:{

            if (text == "\u25BA" ){
                audioController.resume()
                text =  "\u23F9"
            }else {
                 text = "\u25BA"
                 audioController.stop()
            }
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
                             if(position == 1.0){
                                echoControllerSlider.visible = true
                                echoIndicator.visible = true
                             }else if(position == 0){
                                echoControllerSlider.visible = false
                                echoIndicator.visible = false
                             }
                        }
                    }
                    RowLayout{
                    Slider {
                        id: echoControllerSlider
                        value: 100
                        stepSize: 10
                        from: 50
                        to: 200
                        visible: false
                        onMoved:{
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

                     ColumnLayout{
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
                        model: [
                        "0 - 396 Hz",
                        "396 - 630 Hz",
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
                                from: -40
                                to: 3
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