import QtQuick 1.0

Rectangle {
    id:radio
    height: 24
    width: 100

    signal set()
    property string text: "text"

    Row{
        y: 2
        spacing: 6

        Image{
            id:selectedImage
            sourceSize.height: 20
            sourceSize.width: 20
            source: "notSelected"
        }
        Text{
            id:descriptionText
            text: radio.text
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: 18
        }
    }

    states: [
        State {
            name: "on"
            PropertyChanges { target: selectedImage; source: "selected" }
        },
        State {
            name: "off"
            PropertyChanges { target: selectedImage; source: "notSelected" }
        }
    ]

    MouseArea {
        id: mouseArea
        width: 100
        height: 22
        anchors.bottomMargin: 2
        anchors.fill: parent
        onReleased: {
            radio.state="on";
            radio.set();
        }
    }

    state:"off"
}
