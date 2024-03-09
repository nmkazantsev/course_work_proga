#ifndef CALCULATETHREAD_H
#define CALCULATETHREAD_H

#include <QThread>
#include <QVector>
class CalculateThread : public QThread
{
public:
    CalculateThread(QVector<double> * array);
     void run();
private:
     // A differential equation "dy/dx = ..."
     double dydx_coord(double x, double y);
     double dydx_spd(double x, double y, double v);

     // and initial value y0 at x0.
     void rungeKutta(double x0, double y0, double n, double h);
     QVector<double> x,y;
     QVector <double> * array;
};
#endif // CALCULATETHREAD_H
