#include "analizationform.h"
#include "ui_analizationform.h"

AnalizationForm::AnalizationForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AnalizationForm)
{
    ui->setupUi(this);

    distanceDataList.clear();
    areaDataList.clear();
    tableSetHeader();
}

AnalizationForm::~AnalizationForm()
{
    delete ui;
}

void AnalizationForm::slotAddDistanceData(double data)
{
    distanceDataList.append(data);
    refreshTableWidget();
}

void AnalizationForm::slotAddAreaData(double area)
{
    areaDataList.append(area);
    if(!areaDataList.isEmpty()){
        ui->tableWidget->clear();
        ui->tableWidget->setRowCount(0);
        tableSetHeader();
        foreach(double currentItem, distanceDataList){
            ui->tableWidget->insertRow(ui->tableWidget->rowCount());
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0, new QTableWidgetItem(QString::number(currentItem)));
        }
    }
    else
        return;

}

void AnalizationForm::slotClearDistanceData()
{
    distanceDataList.clear();
    areaDataList.clear();
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    tableSetHeader();
}

void AnalizationForm::calculateAveStD()
{
    if(ui->tableWidget->rowCount() > 0){
        int rows = ui->tableWidget->rowCount();
        QList<double> tableValues;
        for(int i = 0; i < rows; i++){
            tableValues.append(ui->tableWidget->item(i, 0)->text().toDouble());
//            qDebug() << ui->tableWidget->item(i, 0)->text();
        }
        double average = getAverage(tableValues);
        double StD = getStd(tableValues, average);
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        ui->tableWidget->setVerticalHeaderItem(ui->tableWidget->rowCount()-1, new QTableWidgetItem(QString("Average")));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0, new QTableWidgetItem(QString::number(average)));
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        ui->tableWidget->setVerticalHeaderItem(ui->tableWidget->rowCount()-1, new QTableWidgetItem(QString("StD")));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0, new QTableWidgetItem(QString::number(StD)));
    }
    else
        return;
}

double AnalizationForm::getAverage(QList<double> &list)
{
    double result = 0;
    for (int i = 0; i < list.size(); i++){
        result += (double)list.at(i) / (double)list.size();
//        qDebug() << QString::number(list.at(i));
    }
    return result;
}

double AnalizationForm::getStd(QList<double> &list, double average)
{
    double result = 0;
//    double average = getAverage(list);
    for (int i = 0; i < list.size(); i++)
        result += (((double)list.at(i) - average)*((double)list.at(i) - average)) / (double)list.size();
    result = qSqrt(result);
    return result;
}

void AnalizationForm::refreshTableWidget()
{
    if(!distanceDataList.isEmpty()){
        ui->tableWidget->clear();
        ui->tableWidget->setRowCount(0);
        tableSetHeader();
        foreach(double currentItem, distanceDataList){
            ui->tableWidget->insertRow(ui->tableWidget->rowCount());
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0, new QTableWidgetItem(QString::number(currentItem)));
        }
        calculateAveStD();
    }
    else
        return;
}

void AnalizationForm::exportTableData(QString exportFilename)
{
    QFile exportFile(exportFilename);
    if(!exportFile.fileName().endsWith(".csv"))
        exportFile.setFileName(exportFile.fileName() + ".csv");
    if(!exportFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug("baj");
        return;
    }

    QTextStream out(&exportFile);
    out << "#" << ui->tableWidget->horizontalHeaderItem(0)->text() << "\n";

    for(int i = 0; i < ui->tableWidget->rowCount()-2; i++){
        out << ui->tableWidget->item(i, 0)->text() << "\n";
    }
    out << "Average:" << "\t" << ui->tableWidget->item(ui->tableWidget->rowCount()-2, 0)->text() << "\n";
    out << "StD:" << "\t" << ui->tableWidget->item(ui->tableWidget->rowCount()-1, 0)->text();

    exportFile.close();
}

void AnalizationForm::tableSetHeader()
{
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Distance (mm)/Area (mm2)");
}

void AnalizationForm::on_clearPushButton_clicked()
{
    slotClearDistanceData();
}

void AnalizationForm::on_exportPushButton_clicked()
{
    QString outFileName = QFileDialog::getSaveFileName(this, "Save table", "../");
    exportTableData(outFileName);
}
