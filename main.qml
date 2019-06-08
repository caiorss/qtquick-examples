import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3 // RowLayout
// import io.qt.examples.quick.controls.filesystembrowser 1.0

import ToDo 1.0

ColumnLayout {

    width:  400
    height: 500

    Frame {
        Layout.fillWidth: true

        ListView {
            implicitWidth:  250;
            implicitHeight: 250;
            anchors.fill: parent
            clip: true

            /* Sample Model for the list view */
            model: TodoModel {
                list: toDoList
            }

            // Row layout configuration
            // (Field, followed by a CheckBox)
            // [ ] ________________
            delegate: RowLayout {
                width: parent.width
                // CheckBox column 0 of current row

                CheckBox {
                    // Conect Checkbox property: CheckBox.checked to
                    // model property model.done
                    checked: model.done

                    onClicked: model.done = checked
                }
                // TextField column 1 of current row
                TextField {
                    Layout.fillWidth: true
                    text: model.description

                    onEditingFinished: model.description = text
                }
            }

            // model: 100

        } // -- End of ListView --- //

    } // --- End of Frame --- //

    RowLayout {
        Button{
            text: "Add new Items   "
            Layout.fillWidth: true
            onClicked: {
                console.log("Button 'Add new Items' clicked")
                toDoList.appendItem()
            }
        }
        Button{
            text: "Remove completed  "
            Layout.fillWidth: true
            onClicked: {
                console.log("Button 'remove clompled 'clicked.")
                toDoList.removeCompletedItems()
            }
        }
        Button{
            text: "Exit"
            Layout.fillWidth: true
            onClicked: {
                console.log("Button Exit clicked")
                Qt.quit()
            }
        }
    }

} // --- End of ColumnLayout --- //
