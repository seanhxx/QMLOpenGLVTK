#include "include/QmlVTKOpenGLRenderWindowInteractor.h"
#include "include/QmlOpenGLWindowInteractor.h"

QmlOpenGLWindowInteractor::QmlOpenGLWindowInteractor
{
    qDebug() << "QmlOpenGLWindowInteractor::QmlOpenGLWindowInteractor: Initialize";
}

QQuickFramebufferObject::Render * QmlOpenGLWindowInteractor::createRenderer() const
{
    return new QmlVTKOpenGLRenderWindowInteractor();
}

void QmlOpenGLWindowInteractor::mousePressEvent(QMouseEvent * e)
{
    qDebug() << "QmlOpenGLWindowInteractor::MouseEvent: {}" << e.buttons();
}

void QmlOpenGLWindowInteractor::testMethod()
{
    qDebug() << "Test print";    
}