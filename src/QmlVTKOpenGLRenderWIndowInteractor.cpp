#include <QCoreApplication>

#include <vtkCylinderSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkCamera.h>
#include <vtkProperty.h>

#include <vtkStructuredPointsReader.h>
#include <vtkPiecewiseFunction.h>
#include <vtkColorTransferFunction.h>
#include <vtkVolumeProperty.h>
#include <vtkGPUVolumeRayCastMapper.h>
#include <vtkFixedPointVolumeRayCastMapper.h>


#include "QmlVTKOpenGLRenderWindowInteractor.h"

QmlVTKOpenGLRenderWindowInteractor::QmlVTKOpenGLRenderWindowInteractor()
{
    qDebug() << "QmlVTKOpenGLRenderWindowInteractor::QmlVTKOpenGLRenderWindowInteractor: Initialize";
/*     renderWindow = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New(); */
    renderWindow = vtkSmartPointer<vtkWin32OpenGLRenderWindow>::New();
    ren = vtkSmartPointer<vtkRenderer>::New();
    Iren = vtkSmartPointer<vtkGenericRenderWindowInteractor>::New();
    renderWindow->AddRenderer(ren);
    Iren->SetRenderWindow(renderWindow);

    QOpenGLContext * glContext = this->getGLContext();
/*     renderWindow->OpenGLInitContext(); */
}

QOpenGLContext * QmlVTKOpenGLRenderWindowInteractor::getGLContext() const
{
    QOpenGLContext * glContext = new QOpenGLContext();
    glContext->create();
    QOffscreenSurface * glSurface = new QOffscreenSurface();
    glSurface->create();
    glContext->makeCurrent(glSurface);
    return glContext;
}

QOpenGLFramebufferObject * QmlVTKOpenGLRenderWindowInteractor::createFramebufferObject(const QSize & size)
{
    qDebug() << "QmlVTKOpenGLRenderWIndowInteractor::createFramebufferObject";
    QOpenGLFramebufferObjectFormat glFormat;
    glFormat.setAttachment(QOpenGLFramebufferObject::Depth);

    return new QOpenGLFramebufferObject(size, glFormat);
}

void QmlVTKOpenGLRenderWindowInteractor::synchronize(QQuickFramebufferObject * item)
{
    qDebug() << "Synchronize";    
    m_qmlIwen = static_cast<QmlOpenGLWindowInteractor *>(item);
    int wid = m_qmlIwen->getWinId();
    std::string sWId = std::to_string(wid);
    char * pWId = new char[sWId.length() + 1];
    strcpy(pWId, sWId.c_str());
    qDebug() << "Synchronize Wid: " << wid;

    renderWindow->SetWindowInfo(pWId);
}

void QmlVTKOpenGLRenderWindowInteractor::render()
{
    renderWindow->InitializeFromCurrentContext();
    renderWindow->PushContext();
    qDebug() << "Render";    
    this->openGLInitState();

/*     vtkSmartPointer<vtkActor> cylinder = this->getPolyDataActor();
    ren->AddActor(cylinder);
    ren->SetBackground(0.1, 0.2, 0.4); */

    vtkSmartPointer<vtkVolume> ironProtVolume = this->getVolumeDataActor();    
    ren->AddVolume(ironProtVolume);
    ren->SetBackground(1, 1, 1);

    renderWindow->SetSize(150, 150);

    Iren->Initialize();
    ren->ResetCamera();
    ren->GetActiveCamera()->Zoom(1.5);
    renderWindow->Render();
    qDebug() << "Start Rendering";
    Iren->Start();

    int params = 0;
    this->glGetIntegerv(32883, &params);
    qDebug() << "max 3d texture size is: " << params;
    renderWindow->PopContext();
}

void QmlVTKOpenGLRenderWindowInteractor::openGLInitState()
{
    renderWindow->OpenGLInitState();
    renderWindow->MakeCurrent();
    this->initializeOpenGLFunctions();
    this->glUseProgram(0);
}

vtkSmartPointer<vtkActor> QmlVTKOpenGLRenderWindowInteractor::getPolyDataActor()
{
    vtkSmartPointer<vtkCylinderSource> cylinder = vtkSmartPointer<vtkCylinderSource>::New();
    cylinder->SetResolution(8);
    vtkSmartPointer<vtkPolyDataMapper> cylinderMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    cylinderMapper->SetInputConnection(cylinder->GetOutputPort());
    vtkSmartPointer<vtkActor> cylinderActor = vtkSmartPointer<vtkActor>::New();
    cylinderActor->SetMapper(cylinderMapper);
    cylinderActor->GetProperty()->SetColor(0.45, 0.45, 0.45);
    cylinderActor->RotateX(30.0);
    cylinderActor->RotateY(-45.0);
    return cylinderActor;
}

vtkSmartPointer<vtkVolume> QmlVTKOpenGLRenderWindowInteractor::getVolumeDataActor()
{
    QString filePath =  QCoreApplication::applicationDirPath() + "/ironProt.vtk";
    qDebug() << "Read file from: " << filePath;

    vtkSmartPointer<vtkStructuredPointsReader> reader = vtkSmartPointer<vtkStructuredPointsReader>::New();
    reader->SetFileName(filePath.toStdString().c_str());

    vtkSmartPointer<vtkPiecewiseFunction> opacityTransferFunction = vtkSmartPointer<vtkPiecewiseFunction>::New();
    opacityTransferFunction->AddPoint(20, 0.0);
    opacityTransferFunction->AddPoint(255, 0.2);

    vtkSmartPointer<vtkColorTransferFunction> colorTransferFunction = vtkSmartPointer<vtkColorTransferFunction>::New();
    colorTransferFunction->AddRGBPoint(0.0, 0.0, 0.0, 0.0);
    colorTransferFunction->AddRGBPoint(64.0, 1.0, 0.0, 0.0);
    colorTransferFunction->AddRGBPoint(128.0, 0.0, 0.0, 1.0);
    colorTransferFunction->AddRGBPoint(192.0, 0.0, 1.0, 0.0);
    colorTransferFunction->AddRGBPoint(255.0, 0.0, 0.2, 0.0);

    vtkSmartPointer<vtkVolumeProperty> volumeProperty = vtkSmartPointer<vtkVolumeProperty>::New();    
    volumeProperty->SetColor(colorTransferFunction);
    volumeProperty->SetScalarOpacity(opacityTransferFunction);
    volumeProperty->ShadeOn();
    volumeProperty->SetInterpolationTypeToLinear();

/*     vtkSmartPointer<vtkGPUVolumeRayCastMapper> volumeMapper = vtkSmartPointer<vtkGPUVolumeRayCastMapper>::New(); */
    vtkSmartPointer<vtkFixedPointVolumeRayCastMapper> volumeMapper = vtkSmartPointer<vtkFixedPointVolumeRayCastMapper>::New();
    volumeMapper->SetBlendModeToComposite();
    volumeMapper->SetInputConnection(reader->GetOutputPort());

    vtkSmartPointer<vtkVolume> volume = vtkSmartPointer<vtkVolume>::New();
    volume->SetMapper(volumeMapper);
    volume->SetProperty(volumeProperty);
    return volume;
}