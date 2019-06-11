#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQuick/QtQuick>
#include <QQmlContext>

#include "blscalculator.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    qmlRegisterType<BlsCalculator>("com.mycompany.blscalculator", 1, 0, "BlsCalculator");

    QQmlApplicationEngine engine;
    engine.load("qrc:/main.qml");

    // BlsCalculator calc;
    //engine.rootContext()->setContextProperty("blsCalculator", &calc);

    if(engine.rootObjects().isEmpty())
        return EXIT_FAILURE;

    return app.exec();
}
