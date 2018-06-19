import QtQuick 2.9
import QtQuick.Controls 2.2
import Qt.labs.platform 1.0
import QtQuick.Layouts 1.3
import QtQuick.Window 2.10
import QtCharts 2.2

ApplicationWindow {
    objectName: "app"
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

    ColumnLayout {
        id: effects
        anchors.horizontalCenter: parent.horizontalCenter
        Row {

            Layout.alignment: Qt.AlignHCenter
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
                id: switches
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
            }
            Slider {
                anchors.top: switches.verticalCenter
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
                anchors.verticalCenter: echoControllerSlider.verticalCenter
                text: echoControllerSlider.value
            }
        }
    }

    ChartView {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: effects.bottom
        anchors.bottom: footer.top

        id: spectrum
        ValueAxis {
            id: axisLeft
            min: -40
            max: 25
        }

        ValueAxis {
            id: axisRight
            min: -40
            max: 25
        }

        ValueAxis {
            id: axisX
            min: 0
            max: 22050
        }

        LineSeries {
            id: lineSeries1
            name: "left"
            axisX: axisX
            axisY: axisLeft
            useOpenGL: false
        }

        LineSeries {
            id: lineSeries2
            name: "right"
            axisX: axisX
            axisYRight: axisRight
            useOpenGL: false
        }
    }

    function updateInput() {
        audioSpectrum.update(spectrum.series(0), 0)
    }

    function updateOutput() {
        audioSpectrum.update(spectrum.series(1), 1)
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
