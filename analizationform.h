#ifndef ANALIZATIONFORM_H
#define ANALIZATIONFORM_H

#include <QWidget>

namespace Ui {
class AnalizationForm;
}

class AnalizationForm : public QWidget
{
    Q_OBJECT

public:
    explicit AnalizationForm(QWidget *parent = 0);
    ~AnalizationForm();

private:
    Ui::AnalizationForm *ui;
};

#endif // ANALIZATIONFORM_H
