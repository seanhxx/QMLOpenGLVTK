#ifndef QmlVTKRenderWindowInteractor_h
#define QmlVTKRenderWindowInteractor_h

#include <QQuickFramebufferObject>

class QmlOpenGLWindowInteractor : public QQuickFramebufferObject
{
    Q_OBJECT

public:
    QmlOpenGLWindowInteractor();    

    Renderer *createRenderer() const Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *e) override;
    void testMethod();
}


#endif