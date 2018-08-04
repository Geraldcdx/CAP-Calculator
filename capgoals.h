#ifndef CAPGOALS_H
#define CAPGOALS_H

#include <QDialog>

namespace Ui {
class CAPGoals;
}

class CAPGoals : public QDialog
{
    Q_OBJECT

public:
    explicit CAPGoals(QWidget *parent = 0, int, int);
    ~CAPGoals();

private slots:
    void on_pushButton_clicked();

private:
    Ui::CAPGoals *ui;
};

#endif // CAPGOALS_H
