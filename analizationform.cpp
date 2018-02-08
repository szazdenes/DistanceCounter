#include "analizationform.h"
#include "ui_analizationform.h"

AnalizationForm::AnalizationForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AnalizationForm)
{
    ui->setupUi(this);
}

AnalizationForm::~AnalizationForm()
{
    delete ui;
}
