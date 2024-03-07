#include "calculatethread.h"

CalculateThread::CalculateThread(float ** data)
{
 this->data=data;
}

void CalculateThread::run(){
    rungeKutta(0,0,100,0.01);
}

// A differential equation "dy/dx = ..."
float CalculateThread:: dydx(float x, float y)
{
    return((x - y)/2);
}

// and initial value y0 at x0.
void CalculateThread::rungeKutta(float x0, float y0,int n, float h)
{
    float k1, k2, k3, k4;

    // Iterate for number of iterations
    float y = y0;
    for (int i=1; i<=n; i++)
    {
        // Apply Runge Kutta Formulas to find
        // next value of y
        k1 = h*dydx(x0, y);
        k2 = h*dydx(x0 + 0.5*h, y + 0.5*k1);
        k3 = h*dydx(x0 + 0.5*h, y + 0.5*k2);
        k4 = h*dydx(x0 + h, y + k3);

        // Update next value of y
        y = y + (1.0/6.0)*(k1 + 2*k2 + 2*k3 + k4);;

        // Update next value of x
        x0 = x0 + h;
        this->data[i][0]=x0;
        this->data[i][1]=y;
    }
}
