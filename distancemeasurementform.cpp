#include "distancemeasurementform.h"
#include "ui_distancemeasurementform.h"

DistanceMeasurementForm::DistanceMeasurementForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DistanceMeasurementForm)
{
    ui->setupUi(this);

    ui->graphicsView->setScene(&scene);
    ui->graphicsView->setTransformationAnchor(QGraphicsView::AnchorViewCenter);
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

    scene.clear();
    scene.addPixmap(QPixmap::fromImage(loadImage));
}

void DistanceMeasurementForm::refreshMask()
{
    mask = QImage(loadImage.width(), loadImage.height(), QImage::Format_ARGB32_Premultiplied);
    mask.fill(Qt::transparent);
}
