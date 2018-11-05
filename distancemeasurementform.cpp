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
    connect(ui->graphicsView, &ImageGraphicsViewForm::signalWheelUp, this, &DistanceMeasurementForm::slotWheelUp);
    connect(ui->graphicsView, &ImageGraphicsViewForm::signalWheelDown, this, &DistanceMeasurementForm::slotWheelDown);

    ui->graphicsView->setScene(&scene);
    ui->graphicsView->setTransformationAnchor(QGraphicsView::AnchorViewCenter);

    mousePressed = false;
    calibration = false;

    calibValue = 1;
    zoom = 1;

    pensize = 50;

    ui->clearPushButton->setDisabled(true);
    ui->pushButton->setDisabled(true);
    ui->savePushButton->setDisabled(true);
    ui->distanceRadioButton->setChecked(true);
    ui->areaRadioButton->setDisabled(true);
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
        if(ui->distanceRadioButton->isChecked()){
            refreshMask();
            refreshLine(startPosition, pos);
            refreshImage();
            double distance = calculateDistance(startPosition, pos);
            QToolTip::showText(QCursor::pos(), QString::number(distance) + " mm", ui->graphicsView);
        }
        if(ui->areaRadioButton->isChecked()){
            refreshArea(pos);
            refreshImage();
        }
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
    if(ui->distanceRadioButton->isChecked()){
        refreshMask();
        refreshLine(startPosition, pos);
        refreshImage();
        double distance = calculateDistance(startPosition, pos);
        if(calibration) emit signalSendDistance(distance);
        if(!calibration){
            CalibrationDialog calibDialog(this, distance);
            connect(&calibDialog, &CalibrationDialog::signalSendCalibrationValue, this, &DistanceMeasurementForm::slotSetCalibrationValue);
            calibDialog.exec();
        }
    }
}

void DistanceMeasurementForm::slotSetCalibrationValue(double calib)
{
    calibValue = calib;
    calibration = true;
    ui->pushButton->setEnabled(true);
    ui->clearPushButton->setEnabled(true);
    ui->savePushButton->setEnabled(true);
    ui->areaRadioButton->setEnabled(true);
}

void DistanceMeasurementForm::slotWheelUp()
{
    pensize += 5;
    setCursorImage(pensize);
}

void DistanceMeasurementForm::slotWheelDown()
{
    pensize -= 5;
    setCursorImage(pensize);
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
    pen.setColor(Qt::red);
    pen.setWidth(2);
    painter.setPen(pen);
    painter.drawLine(startPos, endPos);
    painter.end();
}

void DistanceMeasurementForm::refreshArea(QPointF &pos)
{
    QPainter painter(&mask);
    QBrush brush;
    brush.setColor(Qt::yellow);
    brush.setStyle(Qt::SolidPattern);
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.setOpacity(0.5);
    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(pos.x() - pensize/zoom/2.0, pos.y() - pensize/zoom/2.0, pensize/zoom, pensize/zoom);
    painter.end();
}

double DistanceMeasurementForm::calculateDistance(QPointF &startPos, QPointF &endPos)
{
    double result = calibValue * qSqrt((endPos.x()-startPos.x())*(endPos.x()-startPos.x())+(endPos.y()-startPos.y())*(endPos.y()-startPos.y()));
    return result;
}

void DistanceMeasurementForm::setCursorImage(double size)
{
    if(ui->areaRadioButton->isChecked()){
        QImage cursorImage = QImage(size, size, QImage::Format_ARGB32);
        QPainter cursorPainter(&cursorImage);
        cursorPainter.setCompositionMode(QPainter::CompositionMode_Source);
        cursorPainter.fillRect(cursorImage.rect(), Qt::transparent);
        cursorPainter.setPen(Qt::yellow);
        cursorPainter.drawEllipse(0, 0, size, size);
        cursorPainter.end();
        cursor = QCursor(QPixmap::fromImage(cursorImage));
        ui->graphicsView->setCursor(cursor);
    }
    else
        return;
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

void DistanceMeasurementForm::on_calibrationPushButton_clicked()
{
    calibration = false;
    calibValue = 1;
    QString imagePath = QFileDialog::getOpenFileName(this, "Open image", "../");
    loadImage = QImage(imagePath);
    image = QImage(loadImage);
    originalImage = QImage(loadImage);
    mask = QImage(loadImage.width(), loadImage.height(), QImage::Format_ARGB32_Premultiplied);
    refreshMask();
    refreshImage();
}

void DistanceMeasurementForm::on_fitPushButton_clicked()
{
    ui->graphicsView->scale(1.0/zoom, 1.0/zoom);

    QRectF imageRect = image.rect();
    QRectF rect = ui->graphicsView->viewport()->rect();
    double fitSize = qMin<double>(rect.width() / imageRect.width(), rect.height() / imageRect.height());

    ui->graphicsView->scale(fitSize, fitSize);
    zoom = fitSize;
}

void DistanceMeasurementForm::on_originalPushButton_clicked()
{
    ui->graphicsView->scale(1.0/zoom, 1.0/zoom);
    zoom = 1;
}

void DistanceMeasurementForm::on_distanceRadioButton_toggled(bool checked)
{
    if(checked) ui->graphicsView->setCursor(QCursor());
}

void DistanceMeasurementForm::on_areaRadioButton_toggled(bool checked)
{
    if(checked) setCursorImage(pensize);
}
