// Code from Tutorial (QT Company)
// Using C++ Models in QML {tutorial} - https://www.youtube.com/watch?v=9BcAYDlpuT8
//
//  This video tutorial walks you through the process of creating and using a C++
//  model in QML by creating a to-do list application. If you're new to Qt Quick and
//  Qt Creator, consider watching the "Getting started with Qt: Hello Quick World" video first:
//

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtWidgets/QFileSystemModel>
#include <QtQuick/QtQuick>
#include <QQmlContext>

#include "todolist.hpp"
#include "todomodel.hpp"


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    qmlRegisterType<TodoModel>("ToDo", 1, 0, "TodoModel");
    qmlRegisterUncreatableType<TodoList>("ToDo", 1, 0, "ToDoList"
                              ,"ToDoList should not be created in QML");

    QQuickView* view = new QQuickView();
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    view->setSource(url);
    view->show();

    TodoList toDoList;

    //TodoModel* model = new TodoModel(view);
    view->rootContext()->setContextProperty("toDoList", &toDoList);

    // When Qt object in QML side sends the signal quit, it calls the method
    // QGuiApplication::quit() of the object app and exits the application.
    QObject::connect(view->engine(), &QQmlEngine::quit, &app, &QGuiApplication::quit);

    // view->rootContext()->setContextProperty("TodoModel", model);
    //QQmlApplicationEngine engine;
    // view->rootContext()->setContextProperty("fileSystemModel", model);


    return app.exec();
}
