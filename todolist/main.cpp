// Code from Tutorial (QT Company)
// Using C++ Models in QML {tutorial} - https://www.youtube.com/watch?v=9BcAYDlpuT8
//
//  This video tutorial walks you through the process of creating and using a C++
//  model in QML by creating a to-do list application. If you're new to Qt Quick and
//  Qt Creator, consider watching the "Getting started with Qt: Hello Quick World" video first:
//
#include <iostream>

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

    // ------------- Register QML Types ---------------//

    // qmlRegisterType<TYPE>(  [FULFLY QUAFIED NAME]
    //                       , [MAJOR VERSION]
    //                       , [MINOR VERSION]
    //                       , [NAME] )
    //
    //  On qml-side (file: main.qml) import the registered type with
    //  import import com.mycompany.todoapp.ToDo 1.0
    //
    qmlRegisterType<TodoModel>("com.mycompany.todoapp.ToDo", 1, 0, "TodoModel");
    qmlRegisterUncreatableType<TodoList>("com.mycompany.todoapp.ToDo"
                                         , 1, 0, "ToDoList"
                                         ,"ToDoList should not be created in QML");

    TodoList toDoList;

    QQmlApplicationEngine engine;

    // ----- Set QT exposed objects to QML before
    // loading QML GUI layout file.
    engine.rootContext()->setContextProperty("toDoList", &toDoList);

    // ----- Load QML GUI Layout file
    engine.load("qrc:/main.qml");
    if(engine.rootObjects().isEmpty())
        return EXIT_FAILURE;


    int status = app.exec();
    std::cout << " [INFO] Application quit => status code = " << status << std::endl;
    return status;
}
