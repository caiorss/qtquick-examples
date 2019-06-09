// Code from Tutorial (QT Company)
//
// Video: https://www.youtube.com/watch?v=uuhmSZxK1mk
//

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQuick/QtQuick>
#include <QQmlContext>


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load("qrc:/main.qml");
    if(engine.rootObjects().isEmpty())
        return EXIT_FAILURE;

    return app.exec();
}
