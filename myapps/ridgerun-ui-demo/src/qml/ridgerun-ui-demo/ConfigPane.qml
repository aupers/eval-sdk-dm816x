import QtQuick 1.0

Rectangle {
    id:configPane
    width: 488
    height: 438
    color: "#bbbbbb"
    border.width: 1
    border.color: "#000000"

    Row{
        spacing:0
        Loader{
            id: optionTab1Loader
            source:"qrc:/tabButton"

            onLoaded:{
                optionTab1Loader.item.objectName="optionTab1"
                optionTab1Loader.item.text="General"
            }
            Connections {
                target: optionTab1Loader.item
                onActive: configPane.state = "general"
            }
        }

        Loader{
            id: optionTab2Loader
            source:"qrc:/tabButton"

            onLoaded:{
                optionTab2Loader.item.objectName="optionTab2"
                optionTab2Loader.item.text="Screenshots"
            }
            Connections {
                target: optionTab2Loader.item
                onActive: configPane.state = "screenshot"
            }
        }

        Loader{
            id: optionTab3Loader
            source:"qrc:/tabButton"

            onLoaded:{
                optionTab3Loader.item.objectName="optionTab3"
                optionTab3Loader.item.text="Live View"

            }
            Connections {
                target: optionTab3Loader.item
                onActive: configPane.state = "liveview"
            }
        }
    }

    Rectangle {
        id: generalSettings
        width: 422
        height: 278
        x: 33
        y: 79
        radius: 30
        border.width: 2
        border.color: "#000000"


        Column{
            id:generalSelector
            x: 35
            y:18
            width: 88
            height: 53
            anchors.horizontalCenterOffset: -18
            anchors.horizontalCenter: parent.horizontalCenter
            spacing:5

            //RadioButtons for on and off states.
            Text{
                id:optionsText
                width:50
                text: "Backlight Level"
                font.pointSize: 15
            }
            //RadioButtons for on and off states.

            Loader{
                id: backlight0
                source: "qrc:/customRadioButton"
                onLoaded:{
                    backlight0.item.width = 50
                    backlight0.item.text = "OFF"
                    backlight0.item.state = "off"
                }
                Connections {
                    target: backlight0.item
                    onSet: {
                        generalSelector.state="0"
                    }
                }
            }

            Loader{
                id: backlight20
                source: "qrc:/customRadioButton"
                onLoaded:{
                    backlight20.item.width = 50
                    backlight20.item.text = "20"
                    backlight20.item.state = "off"
                }
                Connections {
                    target: backlight20.item
                    onSet: {
                        generalSelector.state="20"
                    }
                }
            }

            Loader{
                id: backlight40
                source: "qrc:/customRadioButton"
                onLoaded:{
                    backlight40.item.width = 50
                    backlight40.item.text = "40"
                    backlight40.item.state = "off"
                }
                Connections {
                    target: backlight40.item
                    onSet: {
                        generalSelector.state="40"
                    }
                }
            }

            Loader{
                id: backlight60
                source: "qrc:/customRadioButton"
                onLoaded:{
                    backlight60.item.width = 50
                    backlight60.item.text = "60"
                    backlight60.item.state = "off"
                }
                Connections {
                    target: backlight60.item
                    onSet: {
                        generalSelector.state="60"
                    }
                }
            }

            Loader{
                id: backlight80
                source: "qrc:/customRadioButton"
                onLoaded:{
                    backlight80.item.width = 50
                    backlight80.item.text = "80"
                    backlight80.item.state = "off"
                }
                Connections {
                    target: backlight80.item
                    onSet: {
                        generalSelector.state="80"
                    }
                }
            }

            Loader{
                id: backlight100
                source: "qrc:/customRadioButton"
                onLoaded:{
                    backlight100.item.width = 50
                    backlight100.item.text = "100"
                    backlight100.item.state = "off"
                }
                Connections {
                    target: backlight100.item
                    onSet: {
                        generalSelector.state="100"
                    }
                }
            }

            //States of this selector.
            states: [
                State {
                    name: "0"
                    PropertyChanges { target: backlight0.item;   state:"on"  }
                    PropertyChanges { target: backlight20.item;  state:"off" }
                    PropertyChanges { target: backlight40.item;  state:"off" }
                    PropertyChanges { target: backlight60.item;  state:"off" }
                    PropertyChanges { target: backlight80.item;  state:"off" }
                    PropertyChanges { target: backlight100.item; state:"off" }
                },
                State {
                    name: "20"
                    PropertyChanges { target: backlight0.item;   state:"off" }
                    PropertyChanges { target: backlight20.item;  state:"on" }
                    PropertyChanges { target: backlight40.item;  state:"off" }
                    PropertyChanges { target: backlight60.item;  state:"off" }
                    PropertyChanges { target: backlight80.item;  state:"off" }
                    PropertyChanges { target: backlight100.item; state:"off" }
                },
                State {
                    name: "40"
                    PropertyChanges { target: backlight0.item;   state:"off" }
                    PropertyChanges { target: backlight20.item;  state:"off" }
                    PropertyChanges { target: backlight40.item;  state:"on" }
                    PropertyChanges { target: backlight60.item;  state:"off" }
                    PropertyChanges { target: backlight80.item;  state:"off" }
                    PropertyChanges { target: backlight100.item; state:"off" }
                },
                State {
                    name: "60"
                    PropertyChanges { target: backlight0.item;   state:"off" }
                    PropertyChanges { target: backlight20.item;  state:"off" }
                    PropertyChanges { target: backlight40.item;  state:"off" }
                    PropertyChanges { target: backlight60.item;  state:"on" }
                    PropertyChanges { target: backlight80.item;  state:"off" }
                    PropertyChanges { target: backlight100.item; state:"off" }
                },
                State {
                    name: "80"
                    PropertyChanges { target: backlight0.item;   state:"off" }
                    PropertyChanges { target: backlight20.item;  state:"off" }
                    PropertyChanges { target: backlight40.item;  state:"off" }
                    PropertyChanges { target: backlight60.item;  state:"off" }
                    PropertyChanges { target: backlight80.item;  state:"on" }
                    PropertyChanges { target: backlight100.item; state:"off" }
                },
                State {
                    name: "100"
                    PropertyChanges { target: backlight0.item;   state:"off" }
                    PropertyChanges { target: backlight20.item;  state:"off" }
                    PropertyChanges { target: backlight40.item;  state:"off" }
                    PropertyChanges { target: backlight60.item;  state:"off" }
                    PropertyChanges { target: backlight80.item;  state:"off" }
                    PropertyChanges { target: backlight100.item; state:"on" }
                }
            ]
        }


    }

    Rectangle {
        id: screenshotSettings
        x: 33
        y: 79
        width: 422
        height: 278
        radius: 30
        border.width: 2
        border.color: "#000000"
        visible:false
    }

    Rectangle {
        id: recordingSettings
        x: 33
        y: 79
        width: 422
        height: 278
        radius: 30
        border.width: 2
        border.color: "#000000"
        visible:false
    }

    states: [
        State {
            name: "general"
            PropertyChanges { target: optionTab1Loader.item; isActive: true  }
            PropertyChanges { target: optionTab2Loader.item; isActive: false }
            PropertyChanges { target: optionTab3Loader.item; isActive: false }
            PropertyChanges { target: generalSettings;       visible: true   }
        },
        State {
            name: "screenshot"
            PropertyChanges { target: optionTab1Loader.item; isActive: false }
            PropertyChanges { target: optionTab2Loader.item; isActive: true  }
            PropertyChanges { target: optionTab3Loader.item; isActive: false }
            PropertyChanges { target: screenshotSettings;     visible: true  }
        },
        State {
            name: "liveview"
            PropertyChanges { target: optionTab1Loader.item; isActive: false }
            PropertyChanges { target: optionTab2Loader.item; isActive: false }
            PropertyChanges { target: optionTab3Loader.item; isActive: true  }
            PropertyChanges { target: recordingSettings;     visible: true   }
        }
    ]

    state:"general"

    Row{
        anchors.horizontalCenter: configPane.horizontalCenter
        y: 370
        spacing: 10

        Loader{
            id: saveButton
            source: "qrc:/button"
            onLoaded:{
                saveButton.item.text="Save and Exit"
            }
            Connections {
                target: saveButton.item
                onClicked: {
                    main.actionRequested("save_config " + "" + "" + "")
                    main.setMainState("splash")
                }
            }
        }

        Loader{
            id: backButton
            source: "qrc:/button"
            onLoaded:{
                backButton.item.text="Exit"
            }
            Connections {
                target: backButton.item
                onClicked: {
                    main.setMainState("splash")
                }
            }
        }
    }

    Rectangle {
        width: 488
        height: 438
        border.width: 1
        color:"transparent"
    }
}
