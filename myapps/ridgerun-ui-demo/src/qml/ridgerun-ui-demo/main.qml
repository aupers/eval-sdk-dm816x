import QtQuick 1.0

Rectangle {
    id: main
    width: 640
    height: 480

    property bool live_active : false

    signal actionRequested(string a)
    signal mainStateChanged(string a)

    Loader{
        id: statusBarLoader
        source:"qrc:/statusBar"

        onLoaded:{
            statusBarLoader.item.objectName="statusBar"
        }
    }

    function setMainState(state){
        mainPaneLoader.item.state = state
        mainStateChanged(state)
    }

    function setSignalLevel(state){
        statusBarLoader.item.setSignalLevel(state)
    }

    function setBatteryLevel(state){
        statusBarLoader.item.setBatteryLevel(state)
    }

    function showInfoMessage(text){
        infoMessage.item.show(text)
    }

    function cancelViewerToggle(){
        sideBarLoader.item.cancelViewerToggle()
    }

    Loader{
        id: sideBarLoader
        source:"qrc:/sideBar"

        onLoaded:{
            sideBarLoader.item.y = 41
            sideBarLoader.item.objectName="sideBar"
        }
    }

    Loader{
        id: mainPaneLoader
        source:"qrc:/mainPane"

        onLoaded:{
            mainPaneLoader.item.y = 41
            mainPaneLoader.item.x = 151
            mainPaneLoader.item.objectName="mainPane"
        }
    }

    Loader{
        id:infoMessage
        source:"qrc:/infoMessage"

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
    }
}
