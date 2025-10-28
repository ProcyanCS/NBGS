#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QFileDialog>
#include <QDebug>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    M_COMMON = clCommon();
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
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

    M_COMMON.Data()->calcTotalMass();
    std::cout << M_COMMON.Data()->getTotalMass() << std::endl;
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
}

