// Modified from video:
// Introduction to Qt – Intro to Qt Quick Controls {tutorial}
//  - https://www.youtube.com/watch?v=uuhmSZxK1mk
//

#define QT_QML_DEBUG
#define QT_DECLARATIVE_DEBUG

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQuick/QtQuick>
#include <QQmlContext>
#include <QIcon>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    app.setWindowIcon(QIcon("qrc:/tray-icon.png"));

    QQmlApplicationEngine engine;
    engine.load("qrc:/main.qml");
    if(engine.rootObjects().isEmpty())
        return EXIT_FAILURE;



    return app.exec();
}
