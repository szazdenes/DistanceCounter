#ifndef ANALIZATIONFORM_H
#define ANALIZATIONFORM_H

#include <QWidget>
#include <QtMath>
#include <QFileDialog>
#include <QTextStream>
#include <QDebug>

namespace Ui {
class AnalizationForm;
}

class AnalizationForm : public QWidget
{
    Q_OBJECT

public:
    explicit AnalizationForm(QWidget *parent = nullptr);
    ~AnalizationForm();

public slots:
    void slotAddDistanceData(double data);
    void slotAddAreaData(double area);
    void slotClearDistanceData();


private slots:
    void on_clearPushButton_clicked();

    void on_exportPushButton_clicked();

private:
    Ui::AnalizationForm *ui;

    void calculateAveStD();
    double getAverage(QList<double> &list);
    double getStd(QList<double> &list, double average);
    void refreshTableWidget();
    void exportTableData(QString exportFilename);
    void tableSetHeader();

    QList<double> distanceDataList;
    QList<double> areaDataList;
};

#endif // ANALIZATIONFORM_H
