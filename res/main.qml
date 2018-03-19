
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

            Layout.fillWidth: true
            RowLayout {
                    anchors.fill: parent
                    TextField {
                        id: acceptedLabel
                        Layout.fillWidth: true
                        readOnly: true
                        text: qsTr("Default...")
                    }

                    Button {
                        text: "Push Me"
                        onClicked: fileDialog.open()
                    }

                    FileDialog {
                        id: fileDialog
                        title: "Please choose a file"
                        folder: StandardPaths.writableLocation(StandardPaths.DocumentsLocation)
                        onAccepted: {
                            acceptedLabel.text = fileDialog.file
                        }

                    }
            }
        }

        GroupBox {
            Layout.fillWidth: true
            RowLayout{
                anchors.fill: parent
                     ColumnLayout{
                                anchors.fill: parent
                                Label {
                                    text: "10 db"
                                    Layout.fillHeight: true
                                }

                                Label {
                                    id: botLabel
                                    text: "-3 db"

                                }
                     }

                     Repeater {
                        model: ["0 - 600 Hz", "600 - 1200 Hz", "1200 - 1800 Hz"]
                        ColumnLayout{
                            Label {
                                 id: sliderIndicator
                                 Layout.alignment: Qt.AlignHCenter
                                 Layout.fillHeight: true
                                 text: slider.value
                            }

                            Slider {
                                id: slider
                                value: 0
                                orientation: Qt.Vertical
                                Layout.fillWidth: true
                                onMoved:{
                                    sliderIndicator.text = value
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