#ifndef ANALIZATIONFORM_H
#define ANALIZATIONFORM_H

#include <QWidget>
#include <QtMath>

namespace Ui {
class AnalizationForm;
}

class AnalizationForm : public QWidget
{
    Q_OBJECT

public:
    explicit AnalizationForm(QWidget *parent = 0);
    ~AnalizationForm();

public slots:
    void slotAddDistanceData(double data);
    void slotClearDistanceData();


private:
    Ui::AnalizationForm *ui;

    void calculateAveStD();
    double getAverage(QList<double> &list);
    double getStd(QList<double> &list);
    void refreshTableWidget();

    QList<double> distanceDataList;
};

#endif // ANALIZATIONFORM_H
