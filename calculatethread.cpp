#include "calculatethread.h"
#include <cmath>

CalculateThread::CalculateThread(QObject *parent)
    : QObject(parent)
{
}

CalculateThread::~CalculateThread()
{

}

// A differential equation "dx/dt = ..."
double CalculateThread:: dydx_coord(double t, double v)
{
    return(v);
}

// A differential equation "dx/dt = ..."
double CalculateThread:: dydx_spd(double sigma, double w2, double t, double x,double v)
{
    using namespace std;
    return(-2*sigma*v-w2*sin(x));
}


// and initial value y0 at x0.
void CalculateThread::startCalcualation(double sigma, double w2, double v0, double x0, double t_max, double h)
{
    double k1, k2, k3, k4,kv1, kv2, kv3, kv4;
    unsigned long int n=(long)(t_max/h);
    // Iterate for number of iterations
    double x = x0;
    double v = v0;
    double t0 = 0;
    QVector<double> keys;
    QVector<double> values;
    for (unsigned long  i=1; i<=n; i++)
    {
        kv1 = h*dydx_spd(sigma, w2, t0, x,v);
        k1 = h*dydx_coord(t0, v);

        kv2 = h*dydx_spd(sigma, w2, t0 + 0.5*h, x + 0.5*k1,v+0.5*kv1);
        k2 = h*dydx_coord(t0 + 0.5*h, v + 0.5*kv1);

        kv3 = h*dydx_spd(sigma, w2, t0 + 0.5*h, x + 0.5*k2,v+0.5*kv2);
        k3 = h*dydx_coord(t0 + 0.5*h, v + 0.5*kv2);

         kv4 = h*dydx_spd(sigma, w2, t0 + h, x + k3,v+kv3);
         k4 = h*dydx_coord(t0 + h, v + kv3);

         v = v + (1.0/6.0)*(kv1 + 2*kv2 + 2*kv3 + kv4);
         x = x + (1.0/6.0)*(k1 + 2*k2 + 2*k3 + k4);
         t0 = t0 + h;
         keys.push_back(t0);
         values.push_back(x);
    }
    emit calculationFinished(keys, values);
}
