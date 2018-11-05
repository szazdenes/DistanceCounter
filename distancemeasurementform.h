#ifndef DISTANCEMEASUREMENTFORM_H
#define DISTANCEMEASUREMENTFORM_H

#include <QWidget>
#include <QFileDialog>
#include <QGraphicsScene>
#include <QtMath>
#include <QToolTip>

#include "calibrationdialog.h"

namespace Ui {
class DistanceMeasurementForm;
}

class DistanceMeasurementForm : public QWidget
{
    Q_OBJECT

public:
    explicit DistanceMeasurementForm(QWidget *parent = nullptr);
    ~DistanceMeasurementForm();

signals:
    void signalClearDistanceDataList();
    void signalSendDistance(double distance);

private slots:
    void on_pushButton_clicked();
    void slotMouseMoved(QPointF pos);
    void slotMouseButtonPressed(QPointF pos);
    void slotMouseButtonReleased(QPointF pos);
    void slotSetCalibrationValue(double calib);
    void slotWheelUp();
    void slotWheelDown();

    void on_clearPushButton_clicked();

    void on_savePushButton_clicked();

    void on_calibrationPushButton_clicked();

    void on_fitPushButton_clicked();

    void on_originalPushButton_clicked();

    void on_distanceRadioButton_toggled(bool checked);

    void on_areaRadioButton_toggled(bool checked);

private:
    Ui::DistanceMeasurementForm *ui;

    QImage loadImage, mask, image, originalImage;
    QGraphicsScene scene;
    QPointF startPosition;
    bool mousePressed;
    double calibValue;
    bool calibration;
    double zoom;
    double pensize;
    QCursor cursor;

    void refreshMask();
    void refreshImage();
    void refreshLine(QPointF &startPos, QPointF &endPos);
    void refreshArea(QPointF &pos);
    double calculateDistance(QPointF &startPos, QPointF &endPos);
    void setCursorImage(double size);
};

#endif // DISTANCEMEASUREMENTFORM_H
