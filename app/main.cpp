#include <QDebug>
#include <QApplication>
#include <QQmlApplicationEngine>

/* #include "MainWindow.h" */
/* #include "include/QmlOpenGLWindowInteractor.h" */

int main(int argc, char **argv)
{
    qDebug() << "Program Start!";
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;
/*     qmlRegisterType<QmlOpenGLWindowInteractor>("QmlVTK", 1, 0, "Interactor"); */


/*     QQmlContext * context = engine.rootContext();
    MainWindow mainWindow; 
    engine.setContextForObject(&mainWindow, context);
    context->setContextProperty("mainWindow", &mainWindow); */

    engine.load(QUrl(QStringLiteral("qrc:/app.qml")));

    
    if(engine.rootObjects().isEmpty())
    {
        return -1;
    }

    return app.exec();
}