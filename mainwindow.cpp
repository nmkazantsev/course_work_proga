#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "calculatethread.h"
#include <QMainWindow>
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

void  MainWindow:: buildGraph(QVector<double> keys, QVector<double> values, QVector<double> DX )
{
    if(ui->widget->graphCount()>0){
        ui->widget->removeGraph(0);
    }
    this->T.clear();
    this->X.clear();
    this->DX.clear();
    this->T=keys;
    this->X=values;
    this->DX=DX;
    if(phase!=NULL){
        phase->data()->clear();
    }
    ui->phase->setChecked(false);
    ui->x_t->setChecked(true);
    ui->widget->addGraph();
    ui->widget->graph(0)->addData(T,X);
    ui->widget->graph(0)->setAntialiased(true);
    QPen pen = QPen(QColor(100, 100, 255));
    pen.setWidthF(2);
    ui->widget->graph(0)->setPen(pen);
    ui->widget->rescaleAxes();
    ui->widget->replot();
}


void MainWindow::on_phase_clicked()
{
    if(ui->widget->graphCount()>0){
        ui->widget->removeGraph(0);
    }
    if(phase!=NULL){
    phase->data()->clear();
    }
    phase = new QCPCurve(ui->widget->xAxis, ui->widget->yAxis);
    QVector<QCPCurveData> pahse_data(DX.size());
    for(long int i=0;i<DX.size();i++){
        pahse_data[i]=QCPCurveData(i,X[i],DX[i]);
    }
     phase->data()->set(pahse_data,true);
     ui->widget->rescaleAxes();
     ui->widget->replot();
}


void MainWindow::on_x_t_clicked()
{
    if(phase!=NULL){
        phase->data()->clear();
    }
    if(ui->widget->graphCount()>0){
        ui->widget->removeGraph(0);
    }
    ui->widget->addGraph();
    ui->widget->graph(0)->addData(T,X);
    ui->widget->graph(0)->setAntialiased(true);
    QPen pen = QPen(QColor(100, 100, 255));
    pen.setWidthF(2);
    ui->widget->graph(0)->setPen(pen);
    ui->widget->rescaleAxes();
    ui->widget->replot();
}

