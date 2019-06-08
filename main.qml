import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3 // RowLayout
// import io.qt.examples.quick.controls.filesystembrowser 1.0


Frame {
    width:  400
    height: 500

    ListView {
        implicitWidth:  250;
        implicitHeight: 250;
        clip: true

        /* Sample Model for the list view */
        model: ListModel {
            ListElement {
                done: true
                description: "Buy Groceries"
            }

            ListElement {
                done: false
                description: "Reinstall system"
            }

            ListElement {
                done: false
                description: "Study math - calculus 4"
            }

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

}
