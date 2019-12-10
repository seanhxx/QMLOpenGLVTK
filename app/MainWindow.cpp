#include <QDebug>
#include <QQmlContext>
#include <QQmlApplicationEngine>

#include "MainWindow.h"
#include "QmlOpenGLWindowInteractor.h"


MainWindow::MainWindow()
{

}

void MainWindow::mousePressHandler(const int & button, const int & mouseX, const int & mouseY)
{
    qDebug() << "mouse click";
    QQmlContext * currentContext = QQmlApplicationEngine::contextForObject(this);
    QQmlApplicationEngine * engine = qobject_cast<QQmlApplicationEngine *>(currentContext->engine());
    QObject * rootObject = engine->rootObjects().first();
    QmlOpenGLWindowInteractor * interactor = rootObject->findChild<QmlOpenGLWindowInteractor *>("interactor");
    interactor->testMethod();
}