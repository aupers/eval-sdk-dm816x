import QtQuick 1.0

Rectangle {
    id:button
    SystemPalette { id: activePalette }
    width: 125
    height: 50

    property string text: "Button"
    property string altText: "Button"

    property int textSize: 16
    signal toggled
    signal untoggled

    border { width: 1 }
    smooth: true
    radius: 4

    function toggle(){
        if(button.state == "normal"){
            button.state = "toggled"
        }
        else{
            button.state = "normal"
        }
    }

    // color the button with a gradient
    gradient: Gradient {
        GradientStop {
            id: gradientStop
            position: 0.0
        }
        GradientStop { position: 1.0; color: activePalette.button }
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onClicked:{
            if(button.state == "normal"){
                button.state = "toggled"
                button.toggled();
            }
            else{
                button.state = "normal"
                button.untoggled();
            }
        }
    }

    Text {
        id: buttonLabel
        anchors.centerIn: button
        text: button.text
        horizontalAlignment:Text.AlignHCenter
        font.pixelSize: button.textSize
    }

    states: [
        State {
            name: "toggled"
            PropertyChanges { target: gradientStop; color: activePalette.dark }
            PropertyChanges { target: buttonLabel; text: button.altText }
        },
        State {
            name: "normal"
            PropertyChanges { target: gradientStop; color: activePalette.light }
            PropertyChanges { target: buttonLabel; text: button.text }
        }
    ]
    state:"normal"
 }
