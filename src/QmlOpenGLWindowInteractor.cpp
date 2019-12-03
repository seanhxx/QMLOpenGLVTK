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