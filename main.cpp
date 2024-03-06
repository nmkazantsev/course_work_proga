#include <QApplication>
#include <QLabel>
#include <QWidget>

int main(int argc, char *argv[ ])
{
	QApplication app(argc, argv);
	QLabel hello("<center>Mayatnik simulation</center>");
	hello.setWindowTitle("My First Qt Program");
	hello.resize(700,700);
	hello.show();
	return app.exec();

}