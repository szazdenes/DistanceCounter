#include "distancemeasurementform.h"
#include "ui_distancemeasurementform.h"

DistanceMeasurementForm::DistanceMeasurementForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DistanceMeasurementForm)
{
    ui->setupUi(this);
}

DistanceMeasurementForm::~DistanceMeasurementForm()
{
    delete ui;
}

void DistanceMeasurementForm::on_pushButton_clicked()
{
    emit signalClearDistanceDataList();
}
