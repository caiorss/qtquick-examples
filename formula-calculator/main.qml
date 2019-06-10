import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Window 2.0
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.3

ApplicationWindow {
    visible: true
    width:   640
    height:  400
    title:   "Window title"

    ColumnLayout {

        Text { text: "European Option Black-Scholes Calculator" }

        GridLayout {
            id: grid
            columns: 2

           // anchors.right: parent.right
            // anchors.left: parent.left
            anchors.rightMargin: 12
            anchors.leftMargin: 12
            anchors.topMargin: 12
            columnSpacing: 8
            rowSpacing: 8

            // Strike Price
            Label { text: "K" }
            TextField {
                id: entryK
            }

            // Current underlying asset price
            Label { text: "S" }
            TextField{
                id: entryS
            }

            // Time in years input
            Label{ text: "T" }
            TextField {
                id: entryT
            }

            // Volatility input
            Label{ text: "v (sigma)" }
            TextField{
                id: entryV
            }

            Label{ text: "r" }
            TextField{
                id: entryR
            }

        }


        Rectangle {
            color: 'blue'
            border.color: 'red'
            anchors.bottom: parent.bottom
            anchors.verticalCenter: parent
            border.width: 4
            antialiasing: true;


            TextEdit {
               id:  calcDisplay

               //  background:      "blue"
               // anchors.fill: parent
               text: "Multiline\ntext \n C++ \n QML"
               readOnly: true

               anchors {
                           top: parent.top;
                           topMargin: 10;
                           left: parent.left;
                           leftMargin: 10;
                           right: parent.right;
                           rightMargin: 10;
                       }
            }
        }

    } // ---- Eof ColumnLayout --- //

}
