import QtQuick 1.0

Rectangle {
    id: notificationMessage
    objectName: "notificationMessage"

    anchors.horizontalCenter: parent.left
    anchors.verticalCenter: parent.bottom
    anchors.verticalCenterOffset: -48
    anchors.horizontalCenterOffset: 258

    width: 500
    height: 80
    radius: 15

    color:"#B0ffffff"

    property string text: "Streaming at address: xxx.xxx.xxx.xxx"

    function showStreamingError(){
        text = "No stream address available"
        notificationMessage.state="shownd"
    }

    function setShown(shown, message){
        text = message
        if(shown){
            notificationMessage.state="shownd"
        }
        else{
            notificationMessage.state="hidden"
        }
    }

    Text{
        width: 450
        height: 153
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        font.pixelSize: 25
        horizontalAlignment:Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        color: "black"
        text: notificationMessage.text
        wrapMode: Text.WordWrap
    }

    states: [
        State {
            name: "shown"
            PropertyChanges { target: notificationMessage; opacity: 100 }
        },
        State {
            name: "hidden"
            PropertyChanges { target: notificationMessage; opacity: 0 }
        }
    ]
    state:"hidden"

    transitions: [
        Transition {
            from: "*"
            to: "*"
            NumberAnimation { target: notificationMessage; property:"opacity" ; duration: 200 }
        }
    ]

}
