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


private:
    Ui::AnalizationForm *ui;

    void calculateAveStD();
    double getAverage(QList<double> &list);
    double getStd(QList<double> &list);
};

#endif // ANALIZATIONFORM_H
