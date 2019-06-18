import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Window 2.0
import QtQuick.Layouts 1.3


ApplicationWindow {
    id: mainWindow
    title: "QML Evaluator"

    width:  800
    height: 690
    color: "#2D3238"
    visible: true

    // Make window always on Top
    // See: https://stackoverflow.com/questions/44951046
    flags:  Qt.WindowStaysOnTopHint

    property var currentObject: null

    RowLayout{
        anchors.bottom: parent.bottom

        Label{
            id: statusBar
            text: "Status: "
            color: "white"

        }

    }


    ColumnLayout
    {
        x: 39
        y: 12

        // Button panel
        RowLayout
        {
            y: 23

            // btnRunQML - Evaluate QML code typed or pasted by user
            Button
            {
                id: btnRunQML
                text: "Run QML"

                onClicked: {

                    /* Reference:
                     *  + https://doc.qt.io/archives/qt-5.8/qtqml-javascript-dynamicobjectcreation.html
                     *  + https://wiki.qt.io/QML_Dynamic_Objects
                     *  + https://www.qtcentre.org/threads/61164-QML-Qt-createQmlObject
                     */
                    try{
                        var code = ""

                        if(checkBoxWrapCode.checked === true){
                             code = "import QtQuick 2.7; import QtQuick.Controls 2.1
                                        import QtQuick.Window 2.0; import QtQuick.Layouts 1.3

                                        ApplicationWindow
                                        {
                                        id: main; visible: true; width:  400;
                                        height: 400\n\n" + qmlEntry.text + "\n}"
                        } else
                        {
                             code = qmlEntry.text
                        }


                        currentObject = Qt.createQmlObject( code,
                                                            mainWindow,
                                                            "" );

                        statusBar.text = "Object created. OK.";

                    } catch(error)
                    {
                        statusBar.text = "Error: " + JSON.stringify(error.qmlErrors);
                    }

                }
            }

            // btnClear - Clear text
            Button
            {
                id: btnClear
                text: "Clear"
                onClicked: qmlEntry.text = ""
            }

            // btnDestroy - Destroy QML object generated from user QML code
            Button
            {
                id: btnDestroy
                text: "Destroy"
                onClicked: currentObject.destroy()
            }

            // checkBoxAlwaysOnTop - Keeping this Window on top of all others
            CheckBox {
                id: checkBoxAlwaysOnTop
                width: 30
                height: 40

                Text {
                    // x: 20
                    y: 15
                    anchors.left: parent.right
                    text:  qsTr("On Top")
                    anchors.leftMargin: -5
                    color: "white"
                }
                checked: true

                onCheckStateChanged: {
                    if(checked){
                        mainWindow.flags = Qt.WindowStaysOnTopHint
                        statusBar.text = "Windows always on Top OK."
                    } else {
                        mainWindow.flags = Qt.Window
                        statusBar.text = "Windows reset to default behavior OK."
                    }
                }
            }


            // checkBoxAlwaysOnTop - Keeping this Window on top of all others
            CheckBox {
                id: checkBoxWrapCode
                width: 30
                height: 40
                anchors.left: parent.right
                Text {
                    // x: 20
                    y: 15
                    anchors.left: parent.right
                    text:  qsTr("Wrap code")
                    color: "white"
                }
                checked: false
            }


        } // --- End of RowLayout --- //

        // Textbox where user supplies a QML code
        TextScrollBox {
            id: qmlEntry
            x: 20
            y: 112
            width:           mainWindow.width - 100
            height:          mainWindow.height - 200
            color:           "white"
            backgroundColor: "#444646"

            text: "
import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Window 2.0
import QtQuick.Layouts 1.3

ApplicationWindow
{
   id: main
   visible: true
   width:  400
   height: 400

   Button {
             id: click
             text: 'Click me'
             onClicked: main.color = 'red'
          }

}

          "
        }

    }

    // --- EoF - ColumnLayout --- //

}
