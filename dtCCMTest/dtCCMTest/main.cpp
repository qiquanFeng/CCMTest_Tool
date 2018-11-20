#include "dtccmtest.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QString strText;
	
	for (int i=0;i<argc;i++)
	{
		strText = QString::fromLatin1(argv[i]);
		if (strText.contains("PlatformType")) {

		}
	}

	dtCCMTest w;
	w.show();
	return a.exec();
}
