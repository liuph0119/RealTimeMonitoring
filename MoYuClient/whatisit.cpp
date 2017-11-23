#include "whatisit.h"
#include <QPixmap>
whatisit::whatisit(QDialog *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	
	ui.label->setPixmap(QPixmap("icon/smile.png"));

	QString msg =	"Name   : MoYu Client\n"
					"Version: 1.0(Build: 2017-11-17 09:00:00)\n"
					"Author : Penghua Liu\n"
					"E-mail : liuph3@mail2.sysu.edu.cn\n\n"

					"update log :\n"
					"v1.0 == connect to LAN and get real time\ninformation\n";
	ui.label_text->setText(msg);
}

whatisit::~whatisit()
{

}
