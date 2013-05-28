import QtQuick 1.0

Rectangle {
    width: 488
    height: 438
    color: "#bbbbbb"
    border.width: 1
    border.color: "#000000"


    Loader{
        id: configPane
        source: "qrc:/configPane"
    }

    Rectangle {

        id:viewerPane
        width: 488
        border.width: 1
        height: 438
        color:"#ff00ff"

        Loader{
            anchors.verticalCenter : parent.verticalCenter;
            id: sliderLoader
            source: "qrc:/slider"

            onLoaded:{
                sliderLoader.item.objectName="slider"
                sliderLoader.item.x=430
                sliderLoader.item.height=300
            }
        }

        Text {
            x: 80
            y: 15
            width: 328
            height: 44
            text: qsTr("Live View Window")
            font.pixelSize: 40
        }
    }

    Rectangle {
        x:0
        id:splashPane
        border.width: 1
        width: 488
        height: 438

        Image{
            source: "qrc:/logo"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
        }
    }

    states: [
        State {
            name: "splash"
            PropertyChanges { target: splashPane; x: 0  }
            PropertyChanges { target: configPane; x: 489  }
            PropertyChanges { target: viewerPane; x: 489 }
        },
        State {
            name: "config"
            PropertyChanges { target: splashPane; x: 489 }
            PropertyChanges { target: configPane; x: 0  }
            PropertyChanges { target: viewerPane; x: 489 }
        },
        State {
            name: "viewer"
            PropertyChanges { target: splashPane; x: 489 }
            PropertyChanges { target: configPane; x: 489 }
            PropertyChanges { target: viewerPane; x: 0  }
        }
    ]

    state:"splash"


    transitions: [
        Transition {
            from: "*"
            to: "*"
            NumberAnimation { target: splashPane ; property:"x" ; duration: 500 }
            NumberAnimation { target: configPane ; property:"x" ; duration: 500 }
            NumberAnimation { target: viewerPane ; property:"x" ; duration: 500 }
        }
    ]

}
