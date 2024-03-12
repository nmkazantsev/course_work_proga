#include "calculatethread.h"
#include <cmath>

CalculateThread::CalculateThread(QVector<double> * array, double sigma,
                                 double w2, double t_end, double step, double X0, double V0)
{
    this->array=array;
    this->sigma=sigma;
    this->w2=w2;
    this->t_end=t_end;
    this->step=step;
    this->V0=V0;
    this->X0=X0;
}

void CalculateThread::run(){
    rungeKutta(V0,X0,t_end,step);
}

// A differential equation "dx/dt = ..."
double CalculateThread:: dydx_coord(double t, double v)
{
    return(v);
}

// A differential equation "dx/dt = ..."
double CalculateThread:: dydx_spd(double t, double x,double v)
{
    using namespace std;
    return(-2*sigma*v-w2*sin(x));
}


// and initial value y0 at x0.
void CalculateThread::rungeKutta(double v0, double x0, double t_max, double h)
{
    double k1, k2, k3, k4;
    unsigned long int n=(long)(t_max/h);
    // Iterate for number of iterations
    double x = x0;
    double v= v0;
    double t0=0;
    for (unsigned long  i=1; i<=n; i++)
    {
        // Apply Runge Kutta Formulas to find
        // next value of y
        k1 = h*dydx_spd(t0, x,v);
        k2 = h*dydx_spd(t0 + 0.5*h, x + 0.5*k1,v);
        k3 = h*dydx_spd(t0 + 0.5*h, x + 0.5*k2,v);
        k4 = h*dydx_spd(t0 + h, x + k3,v);

        // Update next value of y
        v = v + (1.0/6.0)*(k1 + 2*k2 + 2*k3 + k4);

        // Apply Runge Kutta Formulas to find
        // next value of y
        k1 = h*dydx_coord(t0, v);
        k2 = h*dydx_coord(t0 + 0.5*h, v + 0.5*k1);
        k3 = h*dydx_coord(t0 + 0.5*h, v + 0.5*k2);
        k4 = h*dydx_coord(t0 + h, v + k3);

        // Update next value of y
        x = x + (1.0/6.0)*(k1 + 2*k2 + 2*k3 + k4);

        // Update next value of x
        t0 = t0 + h;
        this->array[0].push_back(t0);
        this->array[1].push_back(x);
    }
    //emit calculation_Finished();
}
