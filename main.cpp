#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtWidgets/QFileSystemModel>
#include <QtQuick/QtQuick>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

#if 0
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
                         if (!obj && url == objUrl)
                             QCoreApplication::exit(-1);
                     }, Qt::QueuedConnection);
    engine.load(url);
#endif

//    QFileSystemModel* model = new QFileSystemModel();
//    model->setRootPath(QDir::homePath());
//    model->resolveSymlinks();

    QQuickView* view = new QQuickView();
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    view->setSource(url);
    view->show();

    //QQmlApplicationEngine engine;
    // view->rootContext()->setContextProperty("fileSystemModel", model);


    return app.exec();
}
