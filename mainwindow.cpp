#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QCoreApplication>
#include <QFile>
#include <QFileDialog>
#include <QDebug>
#include <QThread>
#include <iostream>

#include <vtkRenderWindow.h>

using namespace QtDataVisualization;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    M_COMMON = clCommon();
    ui->setupUi(this);
    CreateViewWidget();
    this->setWindowTitle(QString("N-body Gravitational Simulator"));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::CreateViewWidget()
{
    vtkWidget = new VTKWidget(ui->viewWidget);
    QVBoxLayout* layout = new QVBoxLayout(ui->viewWidget);
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(vtkWidget);

}

void MainWindow::InitViewWidget()
{
    for (auto& p : M_COMMON.Data()->Particles() )
    {
        vtkSmartPointer<vtkActor> actor =
            vtkWidget->constructActor( p.getX(), p.getY(), p.getZ(), p.getID());
        p.setActor( actor );

    }
    vtkWidget->safeRender();
}

void MainWindow::UpdateViewWidget()
{
    for (auto& p : M_COMMON.Data()->Particles())
    {
        auto id = p.getID();
        auto actorIt = vtkWidget->getActors().find(id);
        if (actorIt != vtkWidget->getActors().end())
        {
            actorIt->second->SetPosition(p.getX(), p.getY(), p.getZ());
        }
    }

    vtkWidget->update();
    vtkWidget->safeRender();
}

void MainWindow::on_action_Load_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(
        nullptr,
        "Open CSV File",
        "",
        "CSV Files (*.csv);;All Files (*)"
        );

    // Check if a file was selected
    if (fileName.isEmpty()) {
        qDebug() << "No file selected.";
        return;
    }

    M_COMMON.Data()->reset();

    const std::string& file = fileName.toStdString();
    M_COMMON.Data()->loadCSV( file );
    M_COMMON.setFilename( file );

    //DataUpdate();
    M_COMMON.Data()->calcTotalMass();
    InitViewWidget();
}


void MainWindow::on_actionSave_As_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(
        nullptr,
        "Save CSV File",
        "",
        "CSV Files (*.csv);;All Files (*)"
        );

    const std::string& file = fileName.toStdString();
    M_COMMON.Data()->saveCSV( file );
    M_COMMON.setFilename( fileName.toStdString() );
}

/* The rewind button is used to reset a simulation back to it's
 * inital state from a loaded csv file. It should stop a simulation
 * and reload the original csv
 */
void MainWindow::on_btn_Rewind_clicked()
{
    M_COMMON.Data()->reset();
    M_COMMON.Data()->loadCSV(M_COMMON.getFilename());

    M_COMMON.Data()->calcTotalMass();
    InitViewWidget();
}


void MainWindow::on_btn_PlayForward_clicked()
{
    // Mock play simulation - just force for duration
    double dTime = 0.0;
    double dTime_END = 0.001;
    while (dTime < dTime_END)
    {
        M_COMMON.Data()->update( M_COMMON.getTimeStep() );
        std::cout << "Current Time: " << std::to_string(dTime) << std::endl;
        UpdateViewWidget();

        QCoreApplication::processEvents(); // Let Qt repaint
        QThread::msleep(30);               // ~30ms delay for visibility

        dTime += M_COMMON.getTimeStep();
    }

}


void MainWindow::on_btn_FrameForward_clicked()
{
    M_COMMON.Data()->update( M_COMMON.getTimeStep() );
    UpdateViewWidget();
}

