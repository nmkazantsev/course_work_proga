#ifndef CALCULATETHREAD_H
#define CALCULATETHREAD_H

#include <QThread>
#include <QVector>

class CalculateThread : public QObject
{
    Q_OBJECT
public:
     explicit CalculateThread(QObject *parent = nullptr);
     virtual ~CalculateThread();

signals:
   void calculationFinished(QVector<double> keys, QVector<double> values, QVector<double> DX);

public slots:
   void startCalcualation(double sigma, double w2, double t_end, double step, double X0, double V0);

private:
     // A differential equation "dy/dx = ..."
     double dydx_coord(double x, double y);
     double dydx_spd(double sigma, double w2, double x, double y, double v);

     // and initial value y0 at x0.
     void rungeKutta(double x0, double y0, double n, double h);
     //QVector<double> x,y;
};
#endif // CALCULATETHREAD_H
