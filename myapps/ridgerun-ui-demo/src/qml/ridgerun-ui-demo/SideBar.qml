import QtQuick 1.0

Rectangle {
    width: 150
    height: 438
    border.width: 1
    border.color: "#000000"

    Image{
        source:"qrc:/sidebar"
    }

    Column{
        spacing: 20
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter

        Loader{
            id: snapshotBtn
            source: "qrc:/button"
            onLoaded:{
                snapshotBtn.item.text="Take Snapshot"
            }
            Connections {
                target: snapshotBtn.item
                onClicked: main.actionRequested("snapshot")
            }
        }

        Loader{
            id: liveViewToggle
            source: "qrc:/toggleButton"
            onLoaded:{
                liveViewToggle.item.text="Start Live View"
                liveViewToggle.item.altText="Stop Live View"
            }
            Connections {
                target: liveViewToggle.item
                onToggled: main.actionRequested("live_view start")
                onUntoggled: main.actionRequested("live_view stop")
            }
        }

        Loader{
            id: configBtn
            source: "qrc:/button"
            onLoaded:{
                configBtn.item.text="Configure"
            }
            Connections {
                target: configBtn.item
                onClicked: main.actionRequested("config")
            }
        }
    }

    function cancelViewerToggle(){
        liveViewToggle.item.toggle()
    }

    Rectangle{
        width: 150
        height: 438
        border.width: 1
        border.color: "#000000"
        color: "transparent"
    }
}
