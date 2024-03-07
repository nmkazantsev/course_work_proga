#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "calculatethread.h"
#include <QMainWindow>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    float ** data = new float* [101];
    for(int i=0;i<101;i++){
        data[i]=new float[2];
    }
    CalculateThread calculateThread(data);
    calculateThread.run();
    ui->setupUi(this);


}

MainWindow::~MainWindow()
{
    delete ui;
}

