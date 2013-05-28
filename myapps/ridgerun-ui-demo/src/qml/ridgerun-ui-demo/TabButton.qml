import QtQuick 1.0

Rectangle {
    id:tabButton
    SystemPalette { id: activePalette }
    width: 163
    height: 50

    property string text: "TabButton"
    property string color: "Black"
    property int textSize: 12
    signal active
    signal inactive

    property bool isActive: false

    border { width: 1 }
    smooth: true

    // color the button with a gradient
    gradient: Gradient {
        GradientStop {
            position: 0.0
            color: {
                if (tabButton.isActive)
                    return activePalette.dark
                else
                    return activePalette.light
            }
        }
        GradientStop { position: 1.0; color: activePalette.button }
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onReleased:{

            if(!tabButton.isActive){
                tabButton.isActive = true;
                active();
            }
        }
    }

    Text {
        id: buttonLabel
        anchors.centerIn: tabButton
        text: tabButton.text
        font.pixelSize: 19
        color: tabButton.color
    }
    states: [
        State {
            name: "State1"
        }
    ]
 }
