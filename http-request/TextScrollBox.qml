import QtQuick 2.7
import QtQuick.Controls 2.4
import QtQuick.Window 2.0
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2


// --- Text Area with ScrollBar --- //
Flickable {

    // Exposed properties
    property alias text:     tarea.text
    property alias readOnly: tarea.readOnly
    property alias color:    tarea.color
    property alias backgroundColor: bgrectangle.color

    // x: 27
    // y: 99
    // width: window_width - 50
    // height: 392
    // anchors.fill: parent
    flickableDirection: Flickable.VerticalFlick

    TextArea.flickable: TextArea {
        id: tarea
        // x: 0

        // text: tmodel.text
        // wrapMode: TextArea.Wrap

        readOnly:false
        persistentSelection: true

        leftPadding:   6
        rightPadding:  6
        topPadding:    0
        bottomPadding: 0

        // Text color in text area
        color: "black" // "#3fcbe2"

        background: Rectangle {
            id: bgrectangle
            // background color
            color: "white"
            border.color: "black"
        }

    }

    ScrollBar.vertical: ScrollBar {
        id: vscrollbar1
        policy: ScrollBar.AlwaysOn
        interactive: false
        width: 10
    }

    ScrollBar.horizontal: ScrollBar {
        id: hscrollbar1
        policy: ScrollBar.AlwaysOn
        interactive: false
        height: 10
    }

    focus: true

    Keys.onPressed: {
        if(event.key === Qt.Key_PageDown)
            vscrollbar1.increase()

        if(event.key === Qt.Key_PageUp)
            vscrollbar1.decrease()

    }

    Keys.onUpPressed:    vscrollbar1.decrease()
    Keys.onDownPressed:  vscrollbar1.increase()
    Keys.onLeftPressed:  hscrollbar1.decrease()
    Keys.onRightPressed: hscrollbar1.increase()
}


// Item { }
