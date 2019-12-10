
#include <QQmlContext>
#include <QQmlApplicationEngine>
#include <Qt>

#include "QmlOpenGLWindowInteractor.h"
#include "QmlVTKOpenGLRenderWindowInteractor.h"

QmlOpenGLWindowInteractor::QmlOpenGLWindowInteractor()
{
    qDebug() << "QmlOpenGLWindowInteractor::QmlOpenGLWindowInteractor: Initialize";
    setAcceptedMouseButtons(Qt::LeftButton | Qt::RightButton);

}

QQuickFramebufferObject::Renderer * QmlOpenGLWindowInteractor::createRenderer() const
{
    qDebug() << "QmlOpenGLWindowInteractor::createRenderer";
    return new QmlVTKOpenGLRenderWindowInteractor();
}

void QmlOpenGLWindowInteractor::mousePressEvent(QMouseEvent * e)
{
    qDebug() << "QmlOpenGLWindowInteractor::MouseEvent: {}" << e->buttons();

}

void QmlOpenGLWindowInteractor::testMethod()
{
    qDebug() << "Test print";    
}

WId QmlOpenGLWindowInteractor::getWinId()
{
    QQmlContext * currentContext = QQmlApplicationEngine::contextForObject(this);
    QQmlApplicationEngine * engine = qobject_cast<QQmlApplicationEngine *>(currentContext->engine());
    QObject * rootObject = engine->rootObjects().first();
/*     QObject * interactor = rootObject->findChild<QObject*>("interactor");
    itemWindow = qobject_cast<QQuickItem*>(interactor)->window();  */
    QObject * iWin = rootObject->findChild<QObject*>("iWin");
    itemWindow = qobject_cast<QQuickItem*>(iWin)->window(); 
    WId widQuick = itemWindow->winId();
    qDebug() << "window Quick ID: " << widQuick;
    QWindow * window = qobject_cast<QWindow *>(rootObject);
    WId wid = window->winId();
    qDebug() << "window ID: " << wid;
    return widQuick;
}