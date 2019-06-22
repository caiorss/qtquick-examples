// Modified from video:
// Introduction to Qt – Intro to Qt Quick Controls {tutorial}
//  - https://www.youtube.com/watch?v=uuhmSZxK1mk
//

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQuick/QtQuick>
#include <QQmlContext>

#include "canvasarea.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

   qmlRegisterType<CanvasArea>("com.mycompany.canvas", 1, 0, "CanvasArea");

    QQmlApplicationEngine engine;
    engine.load("qrc:/main.qml");
    if(engine.rootObjects().isEmpty())
        return EXIT_FAILURE;

    return app.exec();
}
