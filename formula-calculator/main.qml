import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Window 2.0
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.3

import com.mycompany.blscalculator 1.0

ApplicationWindow {
    visible: true
    width:   350
    height:  400
    title:   "Eropean Options - Black Scholes Calculator"

    // property var blsCalc: blsCalculator

    BlsCalculator{
        id: blsCalc
    }

    function roundDigits(number, digits)
    {
        if(digits === 2)
            return Math.round(number * 100) / 100;
        if(digits === 3)
            return Math.round(number * 1000) / 1000;
        if(digits === 4)
            return Math.round(number * 10000) / 10000;
        if(digits === 5)
            return Math.round(number * 100000) / 100000;
        return number;

    }

    function resetForm()
    {
        blsCalc.K = 50.0
        blsCalc.S = 50.0
        blsCalc.T = 0.5
        blsCalc.V = 0.30
        blsCalc.R = 0.05
    }

    Component.onCompleted: {
        console.info("Intialized QML UI and update calculations")
        // updateCalculation()
        setX(Screen.width / 2 - width / 2);
        setY(Screen.height / 2 - height / 2);


        resetForm()
    }

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
                text: blsCalc.K

                Binding {
                    target:   blsCalc
                    property: "K"
                    value:    Number(entryK.text)
                }
            }

            // Current underlying asset price
            Label { text: "S" }
            TextField{
                id: entryS
                text: blsCalc.S

                Binding {
                    target:   blsCalc
                    property: "S"
                    value:    Number(entryS.text)
                }
            }

            // Time in years input
            Label{ text: "T" }
            TextField {
                id: entryT
                text: blsCalc.T

                Binding {
                    target:   blsCalc
                    property: "T"
                    value:    Number(entryT.text)
                }
            }

            // Volatility input
            Label{ text: "v (sigma)" }
            TextField{
                id: entryV
                text: blsCalc.V

                Binding {
                    target:   blsCalc
                    property: "V"
                    value:    Number(entryV.text)
                }
            }

            Label{ text: "r" }
            TextField{
                id: entryR

                text: blsCalc.R

                Binding {
                    target:   blsCalc
                    property: "R"
                    value:    Number(entryR.text)
                }
            }
        }

        Button {
            id:   btnUpdate
            text: "Reset"
            onClicked: resetForm()
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

               text: "Call price = " + roundDigits(blsCalc.call, 4)
                     + "\n Put Price = " + roundDigits(blsCalc.put, 4)

               readOnly: true

               anchors {
                           top: parent.top;
                           topMargin: 10;
                           left: parent.left;
                           leftMargin: 10;
                           right: parent.right;
                           rightMargin: 10;
                       }

//               Binding {
//                   target:   calcDisplay
//                   property: "text"
//                   value:    blsCalc.callPrice()
//               }

            }
        }

    } // ---- Eof ColumnLayout --- //

}
