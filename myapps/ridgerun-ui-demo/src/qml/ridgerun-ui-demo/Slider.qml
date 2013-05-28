import QtQuick 1.0

 Item {
     id: slider; width: 16; height: 180

     // value is read/write.
     property real value: 1
     property real maximum: 10
     property real minimum: 1
     property int yMax: height - handle.height - 4

     onValueChanged: updatePos();
     onYMaxChanged: updatePos();
     onMinimumChanged: updatePos();

     function updatePos() {
         if (maximum > minimum) {
             var pos = 2 + (value - minimum) * slider.yMax / (maximum - minimum);
             pos = Math.min(pos, height - handle.height - 2);
             pos = Math.max(pos, 2);
             handle.y = pos;
         } else {
             handle.y = 2;
         }
     }

     Rectangle {
         smooth:false
         anchors.fill: parent
         color: "transparent";
         border.color: "white"; border.width: 2; radius: 8
     }

     Rectangle {
         border.color: "black";
         id: handle;
         x: -7; y: 0; height: 30; width: 30; radius: 29
         border.width: 2
         gradient: Gradient {
             GradientStop { position: 0.0; color: "lightgray" }
             GradientStop { position: 1.0; color: "gray" }
         }

         MouseArea {
             id: mouse
             anchors.fill: parent; drag.target: parent
             drag.axis: Drag.YAxis; drag.minimumY: 2; drag.maximumY: slider.yMax+2
             onPositionChanged: { value = (maximum - minimum) * (handle.y-2) / slider.yMax + minimum;
                 main.actionRequested("changeVolume "+value)}
         }
     }
 }
