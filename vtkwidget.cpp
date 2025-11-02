#include "VTKWidget.h"


#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRendererCollection.h>
#include <vtkRenderWindow.h>
#include <vtkVertexGlyphFilter.h>

VTKWidget::VTKWidget(QWidget* parent)
    : QVTKOpenGLNativeWidget(parent),
    vtkColors(vtkSmartPointer<vtkNamedColors>::New()),
    renderer(vtkSmartPointer<vtkRenderer>::New())
{
    this->renderWindow()->AddRenderer(renderer);
    this->renderWindow()->SetMultiSamples(0);
    getRenderer()->SetBackground(vtkColors->GetColor3d("White").GetData());
    vecActors.clear();
}

VTKWidget::~VTKWidget() {
    this->renderWindow()->RemoveRenderer(renderer);
}

vtkRenderer* VTKWidget::getRenderer() {
    return renderer;
}

void VTKWidget::clearActors()
{
    for (auto& [key, actor] : getActors()) {
        getRenderer()->RemoveActor(actor);
    }
    getActors().clear();
}

void VTKWidget::safeRender()
{
    if (this->renderWindow() && this->renderWindow()->GetRenderers()->GetFirstRenderer()) {
        this->renderWindow()->Render();
    } else {
        qDebug() << "Render skipped: window or renderer not ready.";
    }
    getRenderer()->ResetCamera();
}


/* Method: constructActor ( double double double )
 * returns vtkSmartPointer<vtkActor>
 * Description: this method constructs a vtkActor for a datapoint
 * at the given x, y, z location. The returned pointer is for
 * assigning to the individual clParticle for localized direct
 * actor access.
 */

vtkSmartPointer<vtkActor> VTKWidget::constructActor(double x,
                                                    double y,
                                                    double z,
                                                    std::string strObject )
{
    vtkSmartPointer<vtkPoints> point = vtkSmartPointer<vtkPoints>::New();
    point->InsertNextPoint( x, y, z );

    vtkSmartPointer<vtkPolyData> pointPolyData = vtkSmartPointer<vtkPolyData>::New();
    pointPolyData->SetPoints( point );

    vtkSmartPointer<vtkVertexGlyphFilter> glyphFilter = vtkSmartPointer<vtkVertexGlyphFilter>::New();
    glyphFilter->SetInputData( pointPolyData );
    glyphFilter->Update();

    vtkSmartPointer<vtkPolyDataMapper> dataMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    dataMapper->SetInputConnection( glyphFilter->GetOutputPort() );

    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper( dataMapper );
    actor->GetProperty()->SetPointSize(6);
    actor->GetProperty()->SetColor( vtkColors->GetColor3d("Black").GetData() );

    getActors()[strObject] = actor;
    getRenderer()->AddActor(actor);

    return actor;
}
