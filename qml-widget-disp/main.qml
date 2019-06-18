import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Window 2.0
import QtQuick.Layouts 1.3


ApplicationWindow {
    id: mainWindow
    title: "QML Runner"

    width:  800
    height: 690
    color: "black"
    visible: true

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
        RowLayout
        {
            y: 23
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
                        currentObject = Qt.createQmlObject( qmlEntry.text,
                                                           mainWindow,
                                                           "" );
                        statusBar.text = "Object created. OK.";

                    } catch(error)
                    {
                        statusBar.text = "Error: " + JSON.stringify(error.qmlErrors);
                    }

                }
            }

            Button
            {
                id: btnClear
                text: "Clear"
                onClicked: qmlEntry.text = ""
            }

            Button
            {
                id: btnDestroy
                text: "Destroy"
                onClicked: currentObject.destroy()
            }

        } // --- End of RowLayout --- //

        TextScrollBox {
            id: qmlEntry
            x: 20
            y: 112
            width:           mainWindow.width - 100
            height:          mainWindow.height - 200
            color:           "white"
            backgroundColor: "#444646"
        }

    } // --- EoF - ColumnLayout --- //

}
