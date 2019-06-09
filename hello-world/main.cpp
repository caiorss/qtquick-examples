// Code from Tutorial (QT Company)
// Using C++ Models in QML {tutorial} - https://www.youtube.com/watch?v=9BcAYDlpuT8
//
//  This video tutorial walks you through the process of creating and using a C++
//  model in QML by creating a to-do list application. If you're new to Qt Quick and
//  Qt Creator, consider watching the "Getting started with Qt: Hello Quick World" video first:
//

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQuick/QtQuick>
#include <QQmlContext>


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QQuickView* view = new QQuickView();
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    view->setSource(url);
    view->show();

    return app.exec();
}
