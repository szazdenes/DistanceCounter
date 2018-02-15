#include "calibrationdialog.h"
#include "ui_calibrationdialog.h"

CalibrationDialog::CalibrationDialog(QWidget *parent, double pixels) :
    QDialog(parent),
    ui(new Ui::CalibrationDialog)
{
    ui->setupUi(this);

    calibration = pixels;
    ui->measuredLineEdit->setText(QString::number(pixels));
}

CalibrationDialog::~CalibrationDialog()
{
    delete ui;
}

void CalibrationDialog::on_pushButton_clicked()
{
    if(!ui->referenceLineEdit->text().isEmpty()){
        calibration = ui->referenceLineEdit->text().toDouble()/calibration;
        emit signalSendCalibrationValue(calibration);
        this->accept();
    }
}
