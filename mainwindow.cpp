#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->distanceMeasurementWidget, &DistanceMeasurementForm::signalClearDistanceDataList, ui->analizationWidget, &AnalizationForm::slotClearDistanceData);
    connect(ui->distanceMeasurementWidget, &DistanceMeasurementForm::signalSendDistance, ui->analizationWidget, &AnalizationForm::slotAddDistanceData);
    connect(ui->distanceMeasurementWidget, &DistanceMeasurementForm::signalSendArea, ui->analizationWidget, &AnalizationForm::slotAddAreaData);
}

MainWindow::~MainWindow()
{
    delete ui;
}
