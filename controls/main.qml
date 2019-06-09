import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Window 2.0
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3

ApplicationWindow {
    visible: true
    width:   640
    height:  400
    title:   "Window title"

    // x: Screen.width / 4
    // y: Screen.height / 4

    Action {
        id:          actionNew
        text:        "&New"
        shortcut:    StandardKey.New // Ctrl + N
        icon.name:   "document-new"
        onTriggered: {
            tarea.placeholderText = "To do - New"
            console.info("Menu New file clicked")
        }
    }

    Action {
        id:          actionOpen
        text:        "&Open"
        shortcut:    StandardKey.Open // Ctrl + O
        icon.name:   "document-open"
        onTriggered: {
            tarea.placeholderText += "To do - open"
            console.info("Menu open document opened")
        }
    }

    Action {
        id:          actionSave
        text:        "&Save"
        shortcut:    StandardKey.Save // Ctrl + S
        icon.name:   "document-save"
        onTriggered: tarea.placeholderText += "To do save document"
    }

    Action {
        id:          actionExit
        text:        "&Exit"
        shortcut:    StandardKey.Quit // Ctrl + Q
        onTriggered: {
            console.log("Exit application")
            Qt.quit() // Exit Application
        }
    }

    menuBar: MenuBar {
        Menu {
            title: "File"
            MenuItem{ action: actionNew  }
            MenuItem{ action: actionOpen }
            MenuItem{ action: actionSave }
            MenuItem{ action: actionExit }
        }
    }

    header: ToolBar {
        RowLayout {
            ToolButton{ action: actionNew }
            ToolButton{ action: actionOpen }
            ToolButton{ action: actionSave }
        }
    }

    // Object named tarea - multi-line text entry/output
    TextArea {
        id: tarea
        anchors.fill: parent
    }

}
