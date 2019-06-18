import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Window 2.0
import QtQuick.Layouts 1.3

import QtQuick.XmlListModel 2.0

// XML Source: https://www.ecb.europa.eu/stats/eurofxref/eurofxref-daily.xml

ApplicationWindow {
    id:      rectangle
    visible: true
    width:   425
    height:  393

    color:   "#0dedaa"

    property string statusMessage: ""
    property var fxRate_USD2EUR: 0.0

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

    XmlListModel {
        // Exchange rates from European Central Bank
        id:     model_EcbFXRatesXML
        source: "https://www.ecb.europa.eu/stats/eurofxref/eurofxref-daily.xml"

        // XML namespace declaration 'xlmns'
        namespaceDeclarations: "declare default element namespace 'http://www.ecb.int/vocabulary/2002-08-01/eurofxref' ; "
                               + " declare  namespace gesmes = 'http://www.gesmes.org/xml/2002-08-01' ; "

        // XPath to nodes where the data will be extracted
        query: "/gesmes:Envelope/Cube/Cube/Cube"

        // Get tags <Cube currency='XXX' rate='dddd.ddd'>
        XmlRole { name: "currency" ; query: "string(@currency)" }
        XmlRole { name: "rate"     ; query: "number(@rate)" }

        onStatusChanged: {
            if(status == XmlListModel.Loading ){
                console.log(" [INFO] Loading Xml ... ")
                statusMessage = " Loading XML ..."
            }

            if(status == XmlListModel.Ready ){
                console.log(" [INFO] XML loaded OK")
                statusMessage = " Loaded OK."

                for(var i = 0; i < count; i++)
                    if(get(i).currency === "USD"){
                        fxRate_USD2EUR = get(i).rate
                        break;
                    }

                console.log(" [TRACE] fxRate_USD2EUR = " + fxRate_USD2EUR)

            }

            if(status == XmlListModel.Error){
                console.log(" [INFO] XML parsing error = " + errorString())
                statusMessage = " XML Error " + errorString()
            }
        }
    }

    Label {
        x: 28;
        y: 5;
        text: "Echange Rates (Dollar) => 1 USD = \n" + statusMessage
        // background: "cyan"
    }


    ListView{
        anchors.rightMargin: 21
        anchors.bottomMargin: 20
        anchors.leftMargin: 21
        anchors.topMargin: 53
        anchors.fill: parent

        // model: model
        // delegate:  Text { text: name + " = " + value + " / rate = " + 4.5 * rate }

        model:     model_EcbFXRatesXML
        delegate: Text { text: currency + "\t" + roundDigits(rate / fxRate_USD2EUR, 2) }
    }

}
