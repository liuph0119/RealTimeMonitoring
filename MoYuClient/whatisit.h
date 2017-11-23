#ifndef WHATISIT_H
#define WHATISIT_H

#include <QDialog>
#include "ui_whatisit.h"

class whatisit : public QDialog
{
	Q_OBJECT

public:
	whatisit(QDialog *parent = 0);
	~whatisit();

private:
	Ui::whatisit ui;
};

#endif // WHATISIT_H
