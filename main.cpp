#include <QApplication>
#include <QLabel>
#include <QWidget>

#include <QLogValueAxis>
#include <QLineSeries>
#include <QValueAxis>
#include <QChart>
#include <QChartView>

#include <math.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /*
     * LineChart Example
     */
    //Add a QLineSeries instance
    QLineSeries *lineseries = new QLineSeries();
    //There are two ways to add data (points)
    lineseries->append(0, 6);  //The parameters are the horizontal and vertical coordinates
    lineseries->append(2, 4);
    lineseries->append(3, 8);
    lineseries->append(7, 4);
    *lineseries << QPointF(11, 1) << QPointF(13, 3) << QPointF(17, 6) << QPointF(18, 3) << QPointF(20, 2);
    //Add a QChart instance, in order to display data
    QChart *chart = new QChart();
    chart->legend()->hide();  //Hide legend
    chart->addSeries(lineseries);
    chart->createDefaultAxes();
    chart->setTitle("Simple line chart example");
    //Add a QChartView legend
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);  //ways of presenting
    //display
    this->setCentralWidget(chartView);
    this->setCentralWidget(chartView);
    this->resize(400, 300);
    this->show();
}


int main(int argc, char *argv[ ])
{
	QApplication app(argc, argv);
	QLabel hello("<center>Mayatnik simulation</center>");
	hello.setWindowTitle("My First Qt Program");
	hello.resize(700,700);
	hello.show();
	return app.exec();

}