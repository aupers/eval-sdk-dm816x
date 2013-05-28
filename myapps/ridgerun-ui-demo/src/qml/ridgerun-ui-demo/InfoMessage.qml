import QtQuick 1.0

Rectangle {
    id: infoMessage
    objectName: "infoMessage"

    anchors.horizontalCenter: parent.horizontalCenter
    anchors.verticalCenter: parent.verticalCenter

    width: 400
    height: 100
    color: "#be000000"
    radius: 30

    opacity: 100
    visible: false

    property string text: "Now Recording"

    function show(message){
        disappear.complete()
        text = message
        visible = true
    }

    Text{
        x: -7
        y: 53
        width: 406
        height: 93
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        font.pixelSize: 25
        horizontalAlignment:Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        color: "#ffffff"
        text: infoMessage.text
        wrapMode: Text.WordWrap
    }

    SequentialAnimation {
        id: disappear
        running: false
        NumberAnimation { target: infoMessage; property: "opacity"; to: 0; duration: 1000}
    }

    onVisibleChanged: {
        if(infoMessage.visible == true)
        disappear.start()
    }

    onOpacityChanged: {
        if(infoMessage.opacity == 0){
            visible = false
            opacity = 1
        }
    }
}
