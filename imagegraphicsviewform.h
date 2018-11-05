#ifndef IMAGEGRAPHICSVIEWFORM_H
#define IMAGEGRAPHICSVIEWFORM_H

#include <QWidget>
#include <QGraphicsView>
#include <QMouseEvent>

namespace Ui {
class ImageGraphicsViewForm;
}

class ImageGraphicsViewForm : public QGraphicsView
{
    Q_OBJECT

public:
    explicit ImageGraphicsViewForm(QWidget *parent = nullptr);
    ~ImageGraphicsViewForm();

    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

signals:
    void signalLeftButtonPressed(QPointF pos);
    void signalLeftButtonReleased(QPointF pos);
    void signalMouseMoved(QPointF pos);
    void signalWheelUp();
    void signalWheelDown();

private:
    Ui::ImageGraphicsViewForm *ui;
};

#endif // IMAGEGRAPHICSVIEWFORM_H
