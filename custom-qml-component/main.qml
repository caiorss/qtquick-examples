import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Window 2.0

import com.mycompany.canvas 1.0

ApplicationWindow {
    id:     rectangle
    x: 0
    y: 0

    width:  425
    height: 500
    color: "#5bedbc"
    visible: true

    CanvasArea {
        id: canvas
        anchors.fill: parent

        Component.onCompleted: {
            console.log("Component started OK")
            canvas.setPen("blue", 3);
            canvas.drawLine(0, 0, 400.0, 0.0);
            canvas.drawLine(200, 80.54, 100, 50.34);
        }
    }

}
