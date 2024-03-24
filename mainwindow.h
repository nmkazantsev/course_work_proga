#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "calculatethread.h"
#include <QMainWindow>
#include <QVector>
#include <qcustomplot.h>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
 Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void callBack();

signals:
    void startCalcualation(double sigma, double w2, double v0, double x0, double t_max, double h);

private slots:
    void on_pushButton_clicked();
    void buildGraph(QVector<double> keys, QVector<double> values,QVector<double> DX);

    void on_phase_clicked();

    void on_x_t_clicked();

private:
    QThread *_thread;
    CalculateThread *_solver;
    Ui::MainWindow *ui;
    QVector<double> T,X,DX;
    QCPCurve *phase=NULL;
};
#endif // MAINWINDOW_H
