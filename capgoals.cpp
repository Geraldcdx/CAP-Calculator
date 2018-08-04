#include "capgoals.h"
#include "ui_capgoals.h"

CAPGoals::CAPGoals(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CAPGoals)
{
    ui->setupUi(this);
}

CAPGoals::~CAPGoals()
{
    delete ui;
}

void CAPGoals::on_pushButton_clicked()
{
    delete ui;
}
