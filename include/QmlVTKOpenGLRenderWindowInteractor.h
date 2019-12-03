#ifndef QmlVTKOpenGLRenderWindowInteractor_h
#define QmlVTKOpenGLRenderWindowInteractor_h

#include <QQuickFramebufferObject>
#include <QOpenGLFramebufferObject>
#include <QOpenGLFramebufferObjectFormat>

class QmlVTKOpenGLRenderWindowInteractor : public QObject, public QQuickFramebufferObject::Renderer
{
    Q_OBJECT

public:
    QmlVTKOpenGLRenderWindowInteractor();    

    QOpenGLFramebufferObject * createFramebufferObject(const QSize & size);
    virtual void synchronize(QQuickFramebufferObject * item);
    virtual void render();
};

#endif