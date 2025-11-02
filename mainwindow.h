#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "clcommon.h"
#include "vtkwidget.h"
#include <QtDataVisualization/Q3DScatter>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    VTKWidget* vtkWidget;

    void CreateViewWidget();
    void InitViewWidget();
    void UpdateViewWidget();

private slots:
    void on_action_Load_triggered();
    void on_actionSave_As_triggered();

    void on_btn_Rewind_clicked();

    void on_btn_PlayForward_clicked();

    void on_btn_FrameForward_clicked();

private:
    Ui::MainWindow *ui;
    clCommon M_COMMON;
    QtDataVisualization::Q3DScatter* M_SCATTER;
};
#endif // MAINWINDOW_H
