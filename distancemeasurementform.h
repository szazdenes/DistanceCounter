#ifndef DISTANCEMEASUREMENTFORM_H
#define DISTANCEMEASUREMENTFORM_H

#include <QWidget>
#include <QFileDialog>
#include <QGraphicsScene>

namespace Ui {
class DistanceMeasurementForm;
}

class DistanceMeasurementForm : public QWidget
{
    Q_OBJECT

public:
    explicit DistanceMeasurementForm(QWidget *parent = 0);
    ~DistanceMeasurementForm();

signals:
    void signalClearDistanceDataList();

private slots:
    void on_pushButton_clicked();

private:
    Ui::DistanceMeasurementForm *ui;

    QImage loadImage, mask;
    QGraphicsScene scene;

    void refreshMask();
};

#endif // DISTANCEMEASUREMENTFORM_H
