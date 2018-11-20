#include "pdf_demo.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	PDF_Demo w;
	w.show();
	return a.exec();
}
