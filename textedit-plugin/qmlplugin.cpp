#include <QtQuick/QtQuick>
#include <QtQml/QQmlExtensionPlugin>
#include <QDebug>


#include "logger.hpp"
#include "textfilemodel.hpp"

class SampleQMLPlugin: public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "sampleqmlplugin")

public:
    void registerTypes(const char* uri) override
    {
        // Q_ASSERT(uri == QLatin1String("SampleQMLPlugin"));
        qmlRegisterType<Logger>(uri, 1, 0, "Logger");
    }
};

// #include "qmlplugin.moc"
#include "qmlplugin.moc"
