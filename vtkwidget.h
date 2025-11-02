#ifndef VTKWIDGET_H
#define VTKWIDGET_H

#include <unordered_map>

#include <QVTKOpenGLNativeWidget.h>
#include <vtkNamedColors.h>
//#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include <vtkActor.h>

class vtkActor;
class vtkRenderer;
class vtkRenderWindow;

class VTKWidget : public QVTKOpenGLNativeWidget {
    Q_OBJECT

public:
    explicit VTKWidget(QWidget* parent = nullptr);
    ~VTKWidget();

    // Global public VTK items
    //vtkRenderWindowInteractor* renderWindowInteractor;
    vtkRenderer* getRenderer();
    void safeRender();
    vtkSmartPointer<vtkNamedColors> vtkColors;

    // Actor Management
    void clearActors();
    vtkSmartPointer<vtkActor> constructActor(double x, double y, double z , std::string obj_id);
    std::unordered_map<std::string, vtkSmartPointer<vtkActor>>& getActors() { return vecActors; }


private:
    vtkSmartPointer<vtkRenderer> renderer;

    std::unordered_map<std::string, vtkSmartPointer<vtkActor>> vecActors;
};


#endif // VTKWIDGET_H
