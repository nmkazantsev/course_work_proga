#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "calculatethread.h"
#include <QMainWindow>
#include <QVector>
#include <QPen>

void delay()
{
    QTime dieTime= QTime::currentTime().addSecs(1);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    result[0]=QVector<double>();
    result[1]=QVector<double>();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void test(){

}
void MainWindow::on_pushButton_clicked()
{
    result[0].erase(result[0].begin(),result[0].end());
    result[1].erase(result[1].begin(),result[1].end());
    CalculateThread calculateThread(result);
    //QObject::connect(&calculateThread, SIGNAL(calculation_Finished),this,SLOT(buildGraph));
    calculateThread.run();
    delay();
    buildGraph();

}
void  MainWindow:: buildGraph(){
    ui->widget->addGraph();
    ui->widget->graph(0)->addData(result[0],result[1]);
    ui->widget->graph(0)->setAntialiased(true);
    QPen pen = QPen(QColor(100, 100, 255));
    pen.setWidthF(2);
    ui->widget->graph(0)->setPen(pen);
    ui->widget->rescaleAxes();
    ui->widget->replot();
}

