#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"
#include <QDebug>
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(4);
    QStringList headers;
    headers<<"Module"<<"Credit Units"<<"Grade"<<"Current CAP";
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    convert["A+"]=5.0;
    convert["A"]=5.0;
    convert["A-"]=4.5;
    convert["B+"]=4.0;
    convert["B"]=3.5;
    convert["B-"]=3.0;
    convert["C+"]=2.5;
    convert["C"]=2.0;
    convert["D+"]=1.5;
    convert["D"]=1.0;
    convert["F"]=0;
    setGradeTable();
    setGradTable();
}
void MainWindow::setGradeTable()
{
    ui->tableWidget_3->setColumnCount(2);
    ui->tableWidget_3->setAlternatingRowColors(true);
    QStringList headers;

    headers<<"Grade"<<"Score";
    ui->tableWidget_3->setHorizontalHeaderLabels(headers);

    int num=ui->tableWidget_3->rowCount();
    num=makenew(num,"A+","5.0");
    num=makenew(num,"A","5.0");
    num=makenew(num,"A-","4.5");
    num=makenew(num,"B+","4.0");
    num=makenew(num,"B","3.5");
    num=makenew(num,"B-","3.0");
    num=makenew(num,"C+","2.5");
    num=makenew(num,"C","2.0");
    num=makenew(num,"D+","1.5");
    num=makenew(num,"D","1.0");
    num=makenew(num,"F","0");

    for(int x=0;x<num;x++)
        for(int y=0;y<2;y++)
            ui->tableWidget_3->item(x,y)->setTextAlignment(Qt::AlignCenter);
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::setGradTable()
{
    ui->tableWidget_2->setColumnCount(2);
    ui->tableWidget_2->setAlternatingRowColors(true);
    QStringList headers;
    headers<<"HONOURS DEGREE CLASSIFICATION"<<"CAP CUT-OFFS";
    ui->tableWidget_2->setHorizontalHeaderLabels(headers);
    int num=ui->tableWidget_2->rowCount();
    num=makenew2(num,"Honours (Highest Distinction)/First Class Honours",">4.5");
    num=makenew2(num,"Honours (Distinction)/Second Upper Class","4.00-4.99");
    num=makenew2(num,"Honours (Merit)/Second Lower Class","3.50-3.99");
    num=makenew2(num,"Honours/Third Class","3.0-3.49");
    num=makenew2(num,"Pass","2.00-2.99");
    ui->tableWidget_2->resizeColumnsToContents();

}
int MainWindow::makenew(int num,QString str,QString score)
{
    ui->tableWidget_3->insertRow(ui->tableWidget_3->rowCount());
    ui->tableWidget_3->setItem(num,f,new QTableWidgetItem(str));
    ui->tableWidget_3->setItem(num,s,new QTableWidgetItem(score));
    return ++num;
}
int MainWindow::makenew2(int num,QString str,QString score)
{
    ui->tableWidget_2->insertRow(ui->tableWidget_2->rowCount());
    ui->tableWidget_2->setItem(num,f,new QTableWidgetItem(str));
    ui->tableWidget_2->setItem(num,s,new QTableWidgetItem(score));
    return ++num;
}
void MainWindow::on_pushButton_clicked()
{
    Dialog add;
    int outcome;
    add.setWindowTitle("Add a module!");
    outcome=add.exec();
    if(outcome==QDialog::Rejected){
        return;
    }
    else{
        QString mod=add.Module();
        QString grade=add.Grade();
        float units=add.Creditunits();

        //qDebug()<<mod<<grade<<units;
        previousCAP=totalcreditunits*CAP;//takes the previous cap
        totalcreditunits+=units;//total units
        gradescore=convert[grade];
        CAP=(gradescore*units+previousCAP)/totalcreditunits;
        qDebug()<<gradescore<<units<<previousCAP<<totalcreditunits;

        //sets the tables
        int num=ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        ui->tableWidget->setItem(num,first,new QTableWidgetItem(mod));
        ui->tableWidget->setItem(num,second,new QTableWidgetItem(QString::number(units)));
        ui->tableWidget->setItem(num,third,new QTableWidgetItem(grade));
        ui->tableWidget->setItem(num,fourth,new QTableWidgetItem(QString::number(CAP)));
        rows++;
        //qDebug()<<mod<<grade<<units;
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    previousCAP=0;
    totalcreditunits=0;
    ui->tableWidget->setRowCount(0);
}

void MainWindow::on_pushButton_3_clicked()
{
    //Write function to determine 1st class honours assuming 160MCS
    float current=CAP*totalcreditunits;
    float unitsleft=160-totalcreditunits;
    //1st class
    float firstclass=(4.5*160-current)/unitsleft;
    //2nd upper
    float secondclass=(4.0*160-current)/unitsleft;
    //2nd lower
    float secondlower=(3.5*160-current)/unitsleft;
    float thirdclass=(3.0*160-current)/unitsleft;
    float pass=(2.0*160-current)/unitsleft;
    QString string;
    string.append("The numbers reflected are the minimum average grade you need for the remaining modular credits units towards 160mcs:\n\n");
    string.append("To get 1st Class Honours(CPA=4.5) you need "+QString::number(firstclass)+"\n\n");
    string.append("To get 2nd Upper Class Honours(CPA=4.0) you need "+QString::number(secondclass)+"\n\n");
    string.append("To get 2nd Lower Class Honours(CPA=3.5) you need "+QString::number(secondlower)+"\n\n");
    string.append("To get 3rd Class Honours(CPA=3.0) you need "+QString::number(thirdclass)+"\n\n");
    string.append("To get pass(CPA=2.0) you need "+QString::number(pass)+"\n\n");
    string.append("JiaYou and all the Best");
    QMessageBox::information(this,"CAP Goals",string);
}
