#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void buildGraph();
private slots:
    void on_pushButton_clicked();
    //void buildGraph();

private:
    QVector<double> * result = new QVector<double>[2];
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
