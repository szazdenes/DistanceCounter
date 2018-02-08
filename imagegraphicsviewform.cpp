#include "imagegraphicsviewform.h"
#include "ui_imagegraphicsviewform.h"

ImageGraphicsViewForm::ImageGraphicsViewForm(QWidget *parent) :
    QGraphicsView(parent),
    ui(new Ui::ImageGraphicsViewForm)
{
    ui->setupUi(this);
}

ImageGraphicsViewForm::~ImageGraphicsViewForm()
{
    delete ui;
}

void ImageGraphicsViewForm::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
        emit signalLeftButtonPressed(mapToScene(event->pos()));
    else
        QGraphicsView::mousePressEvent(event);
}

void ImageGraphicsViewForm::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
        emit signalLeftButtonReleased(mapToScene(event->pos()));
    else
        QGraphicsView::mouseReleaseEvent(event);
}
