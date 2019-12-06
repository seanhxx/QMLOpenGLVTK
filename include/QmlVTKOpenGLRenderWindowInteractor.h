#ifndef QmlVTKOpenGLRenderWindowInteractor_h
#define QmlVTKOpenGLRenderWindowInteractor_h

#include <QQuickFramebufferObject>
#include <QOpenGLFramebufferObject>
#include <QOpenGLFramebufferObjectFormat>
#include <QOpenGLFunctions>

#include <QOpenGLContext>
#include <QOffscreenSurface>

#include <vtkActor.h>
#include <vtkVolume.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkWin32OpenGLRenderWindow.h>
#include <vtkGenericRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>

#include "QmlOpenGLWindowInteractor.h"

class QmlOpenGLWindowInteractor;

class QmlVTKOpenGLRenderWindowInteractor : public QObject, public QQuickFramebufferObject::Renderer, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    QmlVTKOpenGLRenderWindowInteractor();    

    QOpenGLFramebufferObject * createFramebufferObject(const QSize & size);
    virtual void synchronize(QQuickFramebufferObject * item);
    virtual void render();
    QOpenGLContext * getGLContext() const;

private:
/*     vtkSmartPointer<vtkGenericOpenGLRenderWindow> renderWindow; */
    vtkSmartPointer<vtkWin32OpenGLRenderWindow> renderWindow;
    vtkSmartPointer<vtkRenderer> ren;
    vtkSmartPointer<vtkGenericRenderWindowInteractor> Iren;

    vtkSmartPointer<vtkActor> getPolyDataActor();
    vtkSmartPointer<vtkVolume> getVolumeDataActor();

    QmlOpenGLWindowInteractor * m_qmlIwen = nullptr;

    void openGLInitState();
};

#endif