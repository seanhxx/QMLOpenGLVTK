#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QObject>

#include "MainWindow.h"
#include "QmlOpenGLWindowInteractor.h"

int main(int argc, char **argv)
{
    qDebug() << "Program Start!";
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;

    qmlRegisterType<QmlOpenGLWindowInteractor>("QmlVTK", 1, 0, "Interactor");

    QQmlContext * context = engine.rootContext();
    MainWindow mainWindow; 
    engine.setContextForObject(&mainWindow, context);
    context->setContextProperty("mainWindow", &mainWindow);

    engine.load(QUrl(QStringLiteral("qrc:/app.qml")));

    if(engine.rootObjects().isEmpty())
    {
        qCritical() << "Unable to get opengl instance";
        return -1;
    }

    int rc = app.exec();
    qDebug() << "Application Exit Code: " << rc;

    return 0;
}