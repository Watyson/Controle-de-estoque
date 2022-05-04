#include <QApplication>
#include <QMessageBox>
#include "fm_menu.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	fm_menu w;
	w.show();
	return a.exec();
}
