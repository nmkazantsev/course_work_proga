#ifndef CALCULATETHREAD_H
#define CALCULATETHREAD_H

#include <QThread>
class CalculateThread : public QThread
{
public:
    CalculateThread(float**data);
     void run();
private:
     // A differential equation "dy/dx = ..."
     float dydx(float x, float y);

     // and initial value y0 at x0.
     void rungeKutta(float x0, float y0, int n, float h);
     float**data;
};

#endif // CALCULATETHREAD_H
