#ifndef QmlOpenGLWindowInteractor_h
#define QmlOpenGLWindowInteractor_h

#include <QQuickFramebufferObject>

class QmlOpenGLWindowInteractor : public QQuickFramebufferObject
{
    Q_OBJECT

public:
    QmlOpenGLWindowInteractor();    

    QQuickFramebufferObject::Renderer * createRenderer() const Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent * e) override;
    void testMethod();
};

#endif