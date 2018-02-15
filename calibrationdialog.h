#ifndef CALIBRATIONDIALOG_H
#define CALIBRATIONDIALOG_H

#include <QDialog>

namespace Ui {
class CalibrationDialog;
}

class CalibrationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CalibrationDialog(QWidget *parent = 0, double pixels = 1);
    ~CalibrationDialog();

signals:
    void signalSendCalibrationValue(double calib);

private slots:
    void on_pushButton_clicked();

private:
    Ui::CalibrationDialog *ui;
    double calibration;
};

#endif // CALIBRATIONDIALOG_H
