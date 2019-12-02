#include <memory>
#include "include/QmlVTKOpenGLRenderWindowInteractor.h"

QmlVTKOpenGLRenderWindowInteractor::QmlVTKOpenGLRenderWindowInteractor()
{
    qDebug() << "QmlVTKOpenGLRenderWindowInteractor::QmlVTKOpenGLRenderWindowInteractor: Initialize";
}

QOpenGLFramebufferObject * QmlVTKOpenGLRenderWindowInteractor::createFramebufferObject(const QSize & size)
{
    qDebug() << "QmlVTKOpenGLRenderWIndowInteractor::createFramebufferObject";
    QOpenGLFramebufferObjectFormat glFormat;
    glFormat.setAttachment(QOpenGLFramebufferObject::Depth);

/*     std::unique_ptr<QOpenGLFramebufferObject> fbo = std::make_unique<QOpenGLFramebufferObject>(size, glFormat); */
    return new QOpenGLFramebufferObject(size, glFormat);
}

void QmlVTKOpenGLRenderWindowInteractor::synchronize(QQuickFramebufferObject * item)
{
    qDebug() << "Synchronize";    
}

void QmlVTKOpenGLRenderWindowInteractor::render()
{
    qDebug() << "Render";    
}