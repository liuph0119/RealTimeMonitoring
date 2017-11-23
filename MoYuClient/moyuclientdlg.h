#ifndef MOYUCLIENTDLG_H
#define MOYUCLIENTDLG_H

#include <QtWidgets/QMainWindow>
#include "ui_moyuclientdlg.h"

#include <QTimer>
#include <QSqlDatabase>
class MoYuClient : public QMainWindow
{
	Q_OBJECT

public:
	MoYuClient(QWidget *parent = 0);
	~MoYuClient();
private:
	bool connect_database();
	bool select_query_db(QString _sql, QStringList& _vresults);
private slots:
void showaboutdlg();
void startListening();
void  boot_feedback();
void criticalWarning();

private:
	Ui::MoYuClientClass ui;
	QTimer *mTimer;
	QSqlDatabase mDatabase;
	QString mmsg;
	bool mbdbconnected;
};

#endif // MOYUCLIENTDLG_H
