import QtQuick 2.7
import QtQuick.Controls 2.4
import QtQuick.Window 2.0
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2

import com.qtdeveloper.textedit 1.0

ApplicationWindow {
    id:     rectangle

    width:  425
    height: 500
    maximumWidth:  425
    maximumHeight: 500

    // color: "#5bedbc"
    visible: true

    TextFileModel {
        id: tmodel
    }


    FileDialog{
        id: fileSelectionDlg
        title: "Select a text file"
        folder: shortcuts.home

        onAccepted: {
            console.log("File chosed was " + fileSelectionDlg.fileUrl)            
            tmodel.file = fileSelectionDlg.fileUrl

        }

        onRejected: {
            console.log("File selection rejected.")
        }
    }

    ColumnLayout {

        Label {
            id: labelCurrentFile
            text: "File: " + tmodel.file
        }

        Button{
            id:   btnOpenFile
            text: "Open file"
            onClicked: {
                console.info("Button clicked")
                fileSelectionDlg.visible = true
             }
        }

        // --- Text Area with ScrollBar
        Flickable {
            id: flickable
            x: 25
            y: 100
            width: 370
            height: 370
            // anchors.fill: parent
            flickableDirection: Flickable.VerticalFlick

            TextArea.flickable: TextArea {
                id:       textDisplay
                text:     tmodel.text
                // wrapMode: TextArea.Wrap

                readOnly: true
            }

            ScrollBar.vertical: ScrollBar {
                id: vscrollbar1
                policy: ScrollBar.AlwaysOn
                interactive: false
            }

            ScrollBar.horizontal: ScrollBar {
                id: hscrollbar1
                policy: ScrollBar.AlwaysOn
                interactive: false
            }

            Keys.onUpPressed:   vscrollbar1.decrease()
            Keys.onDownPressed: vscrollbar1.increase()
            Keys.onLeftPressed: hscrollbar1.decrease()
            Keys.onRightPressed: hscrollbar1.increase()
        }


    } // -- EoF - ColumnLayout ----//
}
