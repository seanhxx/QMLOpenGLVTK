#ifndef QmlVTKOpenGLRenderWindowInteractor_h
#define QmlVTKOpenGLRenderWindowInteractor_h

#include <QQuickFramebufferObject>
#include <QOpenGLFramebufferObject>
#include <QOpenGLFramebufferObjectFormat>
#include <QOpenGLFunctions>

#include <vtkActor.h>
#include <vtkVolume.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkGenericRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>

class QmlVTKOpenGLRenderWindowInteractor : public QObject, public QQuickFramebufferObject::Renderer, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    QmlVTKOpenGLRenderWindowInteractor();    

    QOpenGLFramebufferObject * createFramebufferObject(const QSize & size);
    virtual void synchronize(QQuickFramebufferObject * item);
    virtual void render();

private:
    vtkSmartPointer<vtkGenericOpenGLRenderWindow> renderWindow;
    vtkSmartPointer<vtkRenderer> ren;
    vtkSmartPointer<vtkGenericRenderWindowInteractor> Iren;

    vtkSmartPointer<vtkActor> getPolyDataActor();
    vtkSmartPointer<vtkVolume> getVolumeDataActor();

    void openGLInitState();
};

#endif