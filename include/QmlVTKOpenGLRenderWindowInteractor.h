#ifndef QmlVTKOpenGLRenderWindowInteractor
#define QmlVTKOpenGLRenderWindowInteractor

#include <QQuick/QQuickFramebufferObject>
#include <QtGui/QOpenGLFramebufferObject>
#include <QtGui/QOpenGLFramebufferObjectFormat>

class QmlVTKOpenGLRenderWindowInteractor : public QQuickFramebufferObject::Renderer
{
    Q_OBJECT

public:
    QmlVTKOpenGLRenderWindowInteractor();    

    QOpenGLFramebufferObject *createFramebufferObject(const QSize &size)
}

#endif