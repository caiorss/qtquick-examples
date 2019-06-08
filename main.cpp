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

    TodoModel* model = new TodoModel(view);
    view->rootContext()->setContextProperty("toDoList", &toDoList);
    // view->rootContext()->setContextProperty("TodoModel", model);

    //QQmlApplicationEngine engine;
    // view->rootContext()->setContextProperty("fileSystemModel", model);


    return app.exec();
}
