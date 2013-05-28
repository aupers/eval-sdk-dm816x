import QtQuick 1.0

Rectangle {
    width: 639
    height: 40

    Image{

        source:"qrc:/bar"
    }

    Image{
        id: batteryImg
        source: "qrc:/battery_0"
        x :10
        anchors.verticalCenter: parent.verticalCenter
    }

    Image{
        id: signalImg
        source: "qrc:/signal_0"
        x: 590
        height: 30
        anchors.verticalCenter: parent.verticalCenter
    }

    Rectangle{

        width: 639
        height: 40
        border.width: 1
        border.color: "#000000"
        color:"transparent"
    }

    function setSignalLevel(state){
        if(state === 0)
            signalImg.source = "qrc:/signal_0"
        else if (state === 1)
            signalImg.source = "qrc:/signal_1"
        else if (state === 2)
            signalImg.source = "qrc:/signal_2"
        else if (state === 3)
            signalImg.source = "qrc:/signal_3"
        else if (state === 4)
            signalImg.source = "qrc:/signal_4"
    }

    function setBatteryLevel(state){
        if(state === 0)
            batteryImg.source = "qrc:/battery_0"
        else if (state === 1)
            batteryImg.source = "qrc:/battery_1"
        else if (state === 2)
            batteryImg.source = "qrc:/battery_2"
        else if (state === 3)
            batteryImg.source = "qrc:/battery_3"
        else if (state === 4)
            batteryImg.source = "qrc:/battery_4"
    }
}
