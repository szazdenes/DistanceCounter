#include "distancemeasurementform.h"
#include "ui_distancemeasurementform.h"

DistanceMeasurementForm::DistanceMeasurementForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DistanceMeasurementForm)
{
    ui->setupUi(this);

    connect(ui->graphicsView, &ImageGraphicsViewForm::signalMouseMoved, this, &DistanceMeasurementForm::slotMouseMoved);
    connect(ui->graphicsView, &ImageGraphicsViewForm::signalLeftButtonPressed, this, &DistanceMeasurementForm::slotMouseButtonPressed);
    connect(ui->graphicsView, &ImageGraphicsViewForm::signalLeftButtonReleased, this, &DistanceMeasurementForm::slotMouseButtonReleased);

    ui->graphicsView->setScene(&scene);
    ui->graphicsView->setTransformationAnchor(QGraphicsView::AnchorViewCenter);

    mousePressed = false;
}

DistanceMeasurementForm::~DistanceMeasurementForm()
{
    delete ui;
}

void DistanceMeasurementForm::on_pushButton_clicked()
{
    emit signalClearDistanceDataList();
    QString imagePath = QFileDialog::getOpenFileName(this, "Open image", "../");
    loadImage = QImage(imagePath);
    image = QImage(loadImage);
    originalImage = QImage(loadImage);
    mask = QImage(loadImage.width(), loadImage.height(), QImage::Format_ARGB32_Premultiplied);
    refreshMask();
    refreshImage();
}

void DistanceMeasurementForm::slotMouseMoved(QPointF pos)
{
    if(mousePressed){
        refreshMask();
        refreshLine(startPosition, pos);
        refreshImage();
        double distance = calculateDistance(startPosition, pos);
        QToolTip::showText(QCursor::pos(), QString::number(distance) + " um", ui->graphicsView);
    }
    else
        return;
}

void DistanceMeasurementForm::slotMouseButtonPressed(QPointF pos)
{
    mousePressed = true;
    startPosition = pos;
}

void DistanceMeasurementForm::slotMouseButtonReleased(QPointF pos)
{
    mousePressed = false;
    refreshMask();
    refreshLine(startPosition, pos);
    refreshImage();
    double distance = calculateDistance(startPosition, pos);
    emit signalSendDistance(distance);
}

void DistanceMeasurementForm::refreshMask()
{
    mask.fill(Qt::transparent);
}

void DistanceMeasurementForm::refreshImage()
{
    QPainter painter(&image);
    QPainter painter2(&loadImage);

    if(mousePressed){
        painter.drawImage(0, 0, loadImage);
        painter.drawImage(0, 0, mask);
        painter.end();
        scene.clear();
        scene.addPixmap(QPixmap::fromImage(image));
    }
    else{
        painter2.drawImage(0,0, image);
        painter2.end();
        scene.clear();
        scene.addPixmap(QPixmap::fromImage(image));
    }
}

void DistanceMeasurementForm::refreshLine(QPointF &startPos, QPointF &endPos)
{
    QPainter painter(&mask);
    QPen pen;
    pen.setColor(Qt::yellow);
    pen.setWidth(1);
    painter.setPen(pen);
    painter.drawLine(startPos, endPos);
    painter.end();
}

double DistanceMeasurementForm::calculateDistance(QPointF &startPos, QPointF &endPos)
{
    double result = qSqrt((endPos.x()-startPos.x())*(endPos.x()-startPos.x())+(endPos.y()-startPos.y())*(endPos.y()-startPos.y()));
    return result;
}

void DistanceMeasurementForm::on_clearPushButton_clicked()
{
    refreshMask();
    image = originalImage;
    refreshImage();
}

void DistanceMeasurementForm::on_savePushButton_clicked()
{
    if(!image.isNull()){
        QString saveName = QFileDialog::getSaveFileName(this, "Save image", "../");
        if(!saveName.endsWith(".png")) saveName.append(".png");
        image.save(saveName);
    }
}
