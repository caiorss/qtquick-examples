import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import QtQuick.Window 2.0

ApplicationWindow {
    title: "Sample QML HTTP Request"
    id:     mainWindow
    objectName: "mainWindow"

    width:  500
    height: 500
    color: "#5bedbc"
    visible: true

    // Variable counter
    property var counter: 0
    property var currentURL: "http://old.reddit.com/r/"
                             + redditCbox.model[redditCbox.currentIndex] + ".json"


    // Executed when the window defined by this file runs
    Component.onCompleted: {
        console.log(" [INFO] Application started OK")
    }

    // Source: https://retifrav.github.io/blog/2018/06/09/qml-xmlhttprequest/
    function request(url, callback) {

        console.log(" [INFO] Running http request to " + url)

        var xhr = new XMLHttpRequest();
        xhr.onreadystatechange = (function(myxhr) {
            return function() {
                if(myxhr.readyState === XMLHttpRequest.DONE) { callback(myxhr); }
            }
        })(xhr);                

        console.log(" [INFO] Before GET request")
        xhr.open("GET", url);
        xhr.send();
    }

    ColumnLayout {
        x: 25
        y: 11
        width: 450
        height: 345
        // Multiline scrollable text area

        RowLayout {

            Button{
              id:   button1      // Unique identifier in QT
              text: "Run Request"

              onClicked: request(currentURL, function(o){
                  console.log("Button Clicked")

                  if(o.status !== 200)
                     return;

                  var json = JSON.parse(o.responseText);
                  console.log("json = " + json)
                  console.log("Length = " + Object.keys(json.data.children).length)

                  display.text = "\n"

                  for(var t = 0; t < Object.keys(json.data.children).length; t++){
                      var data = json.data.children[t].data
                      console.log("title = " + data.title)
                      display.text += "Title    = " + data.title + "\n";
                      display.text += "Post ID  = " + data.id + "\n";
                      display.text += "Upvotes  = " + data.ups + "\n";
                      display.text += "POSTL    = " + data.permalink + "\n"
                      display.text += "Shared URL = " + data.url + "\n"
                      // display.text += "Text  = " + json.data.children[t].data.selftext + "\n";
                      display.text += "\n----------------------------------\n\n";
                  }


              });
            }

            ComboBox {
                id:  redditCbox
                currentIndex: 0
                width: 300
                model: [ "cpp", "Qt5", "ocaml", "programming" ]
                displayText: "SUB: " + currentText

//                onCurrentIndexChanged: {
//                    var subr = redditCbox.model[redditCbox.currentIndex]
//                    currentURL = "http://old.reddit.com/r/" + subr + ".json"
//                    console.log(" [INFO] Subreddit changed to URL => " + currentURL)
//                }

            }

        }

        TextScrollBox{
            id: display
            y: 65
            width: 450
            text: "My text"
            // width:  400
            // fillWidth: parent.fillWidth
            height: 400
            // anchors.bottom: parent.bottom

            color: "#00FF33" // Text Color
            backgroundColor: "black"

            readOnly: false

            Component.onCompleted: {
                console.log(" Created TextScrollBox OK")
            }
        }

//        TextArea {
//            id: display
//            text: "A Label text"
//            anchors.horizontalCenter: parent.horizontalCenter
//        }

    }

} // ---- End of ApplicationWindow --- //
