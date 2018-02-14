#ifndef DISTANCEMEASUREMENTFORM_H
#define DISTANCEMEASUREMENTFORM_H

#include <QWidget>
#include <QFileDialog>
#include <QGraphicsScene>
#include <QtMath>
#include <QToolTip>

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
    void signalSendDistance(double distance);

private slots:
    void on_pushButton_clicked();
    void slotMouseMoved(QPointF pos);
    void slotMouseButtonPressed(QPointF pos);
    void slotMouseButtonReleased(QPointF pos);

    void on_clearPushButton_clicked();

    void on_savePushButton_clicked();

private:
    Ui::DistanceMeasurementForm *ui;

    QImage loadImage, mask, image, originalImage;
    QGraphicsScene scene;
    QPointF startPosition;
    bool mousePressed;

    void refreshMask();
    void refreshImage();
    void refreshLine(QPointF &startPos, QPointF &endPos);
    double calculateDistance(QPointF &startPos, QPointF &endPos);
};

#endif // DISTANCEMEASUREMENTFORM_H
