#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "calculatethread.h"
#include <QMainWindow>
#include <QVector>

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
    QVector<double> * result = new QVector<double>[2];
    CalculateThread calculateThread(result);
    calculateThread.run();
    ui->setupUi(this);
    delay();
    ui->widget->addGraph();
    ui->widget->graph(0)->addData(result[0],result[1]);
    ui->widget->rescaleAxes();
    ui->widget->replot();

}

MainWindow::~MainWindow()
{
    delete ui;
}

