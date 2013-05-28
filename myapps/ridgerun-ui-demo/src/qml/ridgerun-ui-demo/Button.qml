import QtQuick 1.0

Rectangle {
    id:button
    SystemPalette { id: activePalette }
    width: 125
    height: 50

    property string text: "Button"
    property int textSize: 20
    signal clicked

    border { width: 1 }
    smooth: true
    radius: 4

    gradient: Gradient {
        GradientStop {
            position: 0.0
            color: {
                if (mouseArea.pressed)
                    return activePalette.dark
                else
                    return activePalette.light
            }
        }
        GradientStop { position: 1.0; color: activePalette.button }
    }

    MouseArea {
        id: mouseArea
        x: 0
        y: 0
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
        anchors.fill: parent
        onClicked: button.clicked();
    }

    Text {
        id: buttonLabel
        anchors.centerIn: button
        text: button.text
        font.pixelSize: 16
    }
    states: [
        State {
            name: "State1"
        }
    ]
 }
