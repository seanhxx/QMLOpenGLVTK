
#include <windows.h>
#include <wingdi.h>

#include <QCoreApplication>
#include <QWGLNativeContext>
#include <QSurfaceFormat>
#include <QOffscreenSurface>

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
/*     renderWindow = vtkSmartPointer<vtkWin32OpenGLRenderWindow>::New(); */
    renderWindow = vtkSmartPointer<vtkExternalOpenGLRenderWindow>::New();

    ren = vtkSmartPointer<vtkRenderer>::New();
    Iren = vtkSmartPointer<vtkGenericRenderWindowInteractor>::New();
/*     Iren = vtkSmartPointer<vtkRenderWindowInteractor>::New(); */
    renderWindow->AddRenderer(ren);
    Iren->SetRenderWindow(renderWindow);
    renderWindow->OpenGLInitContext();
}

QOpenGLContext * QmlVTKOpenGLRenderWindowInteractor::getWin32GLContext(HDC hdc, HWND hWnd) const
{
    HGLRC win32GLRenderingContext = wglCreateContext(hdc);

    QSurfaceFormat format;
    format.setVersion(3, 2);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);

    QWGLNativeContext wglContext(win32GLRenderingContext, hWnd);
    QOpenGLContext * glContext = new QOpenGLContext();
    glContext->setFormat(format);
    glContext->setNativeHandle(QVariant::fromValue(wglContext));
    return glContext;
}

QOpenGLFramebufferObject * QmlVTKOpenGLRenderWindowInteractor::createFramebufferObject(const QSize & size)
{
    qDebug() << "QmlVTKOpenGLRenderWIndowInteractor::createFramebufferObject";
    QOpenGLFramebufferObjectFormat glFormat;
    glFormat.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);

    return new QOpenGLFramebufferObject(size, glFormat);
}

void QmlVTKOpenGLRenderWindowInteractor::synchronize(QQuickFramebufferObject * item)
{
    qDebug() << "Synchronize";    

/*     try
    {
        m_qmlIwen = static_cast<QmlOpenGLWindowInteractor *>(item);
        WId wid = m_qmlIwen->getWinId();
        HDC hdc = GetDC((HWND)wid);
        qtGLContext = this->getWin32GLContext(hdc, (HWND)wid);
        qtGLContext->create();
        qtGLContext->makeCurrent(m_qmlIwen->itemWindow);
        std::string sWId = std::to_string(wid);
        char * pWId = new char[sWId.length() + 1];
        strcpy(pWId, sWId.c_str());
        qDebug() << "Synchronize Wid: " << wid;
        renderWindow->SetWindowInfo(pWId);
    }
    catch(...)
    {
        qWarning() << "Get Wid Error";
    } */
}

void QmlVTKOpenGLRenderWindowInteractor::render()
{
/*     renderWindow->Initialize(); */
    qDebug() << "Render";    
/*     renderWindow->InitializeFromCurrentContext(); */
/*     renderWindow->PushContext(); */
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

/*     int params = 0;
    this->glGetIntegerv(32883, &params);
    qDebug() << "max 3d texture size is: " << params; */
/*     renderWindow->PopContext(); */
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

    vtkSmartPointer<vtkGPUVolumeRayCastMapper> volumeMapper = vtkSmartPointer<vtkGPUVolumeRayCastMapper>::New();
/*     vtkSmartPointer<vtkFixedPointVolumeRayCastMapper> volumeMapper = vtkSmartPointer<vtkFixedPointVolumeRayCastMapper>::New(); */
    volumeMapper->SetBlendModeToComposite();
    volumeMapper->SetInputConnection(reader->GetOutputPort());

    vtkSmartPointer<vtkVolume> volume = vtkSmartPointer<vtkVolume>::New();
    volume->SetMapper(volumeMapper);
    volume->SetProperty(volumeProperty);
    return volume;
}