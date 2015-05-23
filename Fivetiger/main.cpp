#include "Fivetiger.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Fivetiger w;
	w.show();
	return a.exec();
}
