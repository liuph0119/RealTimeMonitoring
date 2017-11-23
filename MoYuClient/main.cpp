#include "moyuclientdlg.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MoYuClient w;
	w.show();
	return a.exec();
}
