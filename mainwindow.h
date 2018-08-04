#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void setGradeTable();
    void setGradTable();
    int makenew(int, QString,QString);
    int makenew2(int, QString,QString);

    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    int rows=0;
    float Units=0,gradescore,CAP=0,totalcreditunits=0,previousCAP;
    QMap<QString,float> convert;
    enum columns{
        first,second,third,fourth
    };
    enum color
    {
        f,s
    };
};

#endif // MAINWINDOW_H
