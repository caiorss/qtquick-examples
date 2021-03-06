import QtQuick 2.4
import QtQuick.Controls 1.4
import QtQuick.Window 2.0
import QtQuick.Layouts 1.3


import com.mycompany.canvas 1.0

ApplicationWindow {
    id:    mainWindow
    // x: 0
    // y: 0

    width:  425
    height: 500
    // color: "#5bedbc"
    visible: true


    ColumnLayout{
        RowLayout{
            Button {
                id: btnClear
                text: "Clear"
                onClicked: {
                    canvas.clear();
                }
            }

            Button{
                id: btnDrawCircles
                text: "Draw Circles"
                onClicked: {
                    canvas.setPen("black", 1.0);
                    canvas.drawCircle(0.0, 0.0, 50.0);
                    canvas.drawCircle(0.0, 0.0, 60.0);
                    canvas.drawCircle(0.0, 0.0, 80.0);
                    canvas.drawCircle(0.0, 0.0, 90.0);
                    canvas.drawCircle(0.0, 0.0, 150.0);
                    canvas.drawCircle(0.0, 0.0, 250.0);

                    canvas.setBounds(-2 * 3.1415, 2 * 3.1415, -1.0, 1.0)
                }
            }
        }


        CanvasArea {
            id: canvas
            x: 100
            y: 100
            width: mainWindow.width - 50
            height: 400

            anchors.bottom: parent.bottom

            Component.onCompleted: {
                console.log("Component started OK")
                canvas.drawAxis()

                canvas.setPen("blue", 3);
                // canvas.drawSine();
                canvas.setBounds(0, 10, 0.0, 100.0)
                canvas.plotPoints([0, 1, 2, 3, 5, 6, 10], [0, 1, 4, 9, 25, 36, 100])

/*
                canvas.setPen("blue", 3);

                canvas.drawText(100, 10, "X axis");
                canvas.drawLine(0, 0.0, 400.0, 0.0);
                canvas.drawText(10, 100, "Y axis");
                canvas.drawLine(0, 0.0, 0.0,   400.0);

                canvas.setPen("red", 2);
                canvas.drawLine(200, 80.54, 100, 50.34);

                canvas.drawEllipse(0.0, 0.0, 100.0, 200.0);
                */
            }
        }


    } // --- End of ColumnLayout

}
