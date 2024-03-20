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

    _thread = new QThread();
    _solver = new CalculateThread();
    _solver->moveToThread(_thread);

    QObject::connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::on_pushButton_clicked);
    QObject::connect(this, &MainWindow::startCalcualation, _solver, &CalculateThread::startCalcualation, Qt::QueuedConnection);
    QObject::connect(_solver, &CalculateThread::calculationFinished, this, &MainWindow::buildGraph, Qt::QueuedConnection);

    _thread->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    auto sigma =  ui->sigma->value();
    auto w2 =  ui->w_square->value();
    auto t_end =  ui->t_end->value();
    auto step =  ui->step->value();
    auto V0 =  ui->v0->value();
    auto X0 =  ui->x0->value();
    emit startCalcualation(sigma, w2, V0, X0, t_end, step);
}
void  MainWindow:: buildGraph(QVector<double> keys, QVector<double> values)
{
    if(ui->widget->graphCount()>0){
        ui->widget->removeGraph(0);
    }
    ui->widget->addGraph();
    ui->widget->graph(0)->addData(keys,values);
    ui->widget->graph(0)->setAntialiased(true);
    QPen pen = QPen(QColor(100, 100, 255));
    pen.setWidthF(2);
    ui->widget->graph(0)->setPen(pen);
    ui->widget->rescaleAxes();
    ui->widget->replot();
}

