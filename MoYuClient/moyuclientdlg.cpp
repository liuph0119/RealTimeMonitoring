#include "moyuclientdlg.h"
#include <QLabel>
#include <QMovie>
#include <QAction>
#include <QPushButton>
#include "whatisit.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QtCore/QtCore>
#include <QtXml/QtXml>

MoYuClient::MoYuClient(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	
	mbdbconnected = false;
	setFixedSize(320, 330);
	ui.btn_police->setVisible(false);
	// show gif
	QMovie *movie = new QMovie("moyu.gif");
	ui.label->setMovie(movie);
	movie->start();
	ui.label_state->setVisible(false);

	connect(ui.actionStart, &QAction::triggered, this, &MoYuClient::startListening);
	connect((ui.actionExit), &QAction::triggered, this, &MoYuClient::close);
	connect(ui.actionAbout, &QAction::triggered, this, &MoYuClient::showaboutdlg);
	connect(ui.btn_police, &QPushButton::clicked, this, &MoYuClient::criticalWarning);
}

MoYuClient::~MoYuClient()
{
	mDatabase.close();
}

bool MoYuClient::connect_database()
{
	QDomDocument doc;
	QFile xmlfile("configure.xml"); //filepath为xml文件路径  
	if (!xmlfile.open(QIODevice::ReadOnly))
		return false;
	
	if (!doc.setContent(&xmlfile))
	{
		xmlfile.close();
		return false;
	}
	QDomElement root = doc.documentElement();
	QString _hostname = root.elementsByTagName("HostName").at(0).toElement().text();
	QString _username = root.elementsByTagName("UserName").at(0).toElement().text();
	QString _password = root.elementsByTagName("Password").at(0).toElement().text();
	int _port = root.elementsByTagName("Port").at(0).toElement().text().toInt();
	QString _dbName = root.elementsByTagName("DatabaseName").at(0).toElement().text();
	xmlfile.close();

	mDatabase = QSqlDatabase::addDatabase("QMYSQL");
	mDatabase.setHostName(_hostname);
	mDatabase.setUserName(_username);
	mDatabase.setPassword(_password);
	mDatabase.setPort(_port);
	mDatabase.setDatabaseName(_dbName);
	if (!mDatabase.open())
	{
		QMessageBox::warning(this, "warning", "sorry but cannot connect to server.");
		return false;
	}
	mbdbconnected = true;
	return true;
}

void MoYuClient::showaboutdlg()
{
	whatisit *dlg = new whatisit();
	dlg->exec();
	delete dlg;
}

void MoYuClient::startListening()
{
	if (!mbdbconnected)
	{
		//首先尝试连接服务器;
		if (!connect_database())
			return;
	}

	ui.label_state->setText("state: safe");
	ui.label_state->setVisible(true);
	ui.btn_police->setVisible(true);
	
	mTimer = new QTimer();
	mTimer->start(100);
	connect(mTimer, &QTimer::timeout, this, &MoYuClient::boot_feedback);
}


//反馈机制;
/*此处，即不断地向数据库发送请求，查询是否危险*/
void MoYuClient::boot_feedback()
{
	QString _sql = "select state,danger_index from real_time_state_tbl";
	QStringList _v_sql_results;
	if (select_query_db(_sql, _v_sql_results))
	{
		int nrcdnum = _v_sql_results.size();
		if (nrcdnum > 0)
		{
			// 查询结果的最后一条（最新）的最后一列如果是dangerous，则报警;
			QStringList slist = _v_sql_results[0].split(",");
			if (slist[0] == "danger")
			{
				mTimer->stop();
				delete mTimer;
				int danger_index = slist[1].toInt();
				ui.label_state->setText(QString("state: danger! index: %1(remember to restart)").arg(danger_index));
				//QMessageBox::information(this, "info", "danger");
				system("start https://cn.bing.com");
			}
		}
	}
	_sql.clear();
}


bool MoYuClient::select_query_db(QString _sql, QStringList& _vresults)
{
	QSqlQuery _query;
	if (!_query.exec(_sql))
		return false;
	while (_query.next())
	{
		// 表头形式： time, state
		QString _result = _query.value(0).toString();
		_result = _result + "," + _query.value(1).toString();
		_vresults.append(_result);
	}
	return true;
}



void MoYuClient::criticalWarning()
{
	//更新记录;
	QSqlQuery _query;
	QString _time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
	QString _sql = QString("update real_time_state_tbl set tm='%1',state='danger',danger_index=100;").arg(_time);
	_query.exec(_sql);
	ui.btn_police->setVisible(false);
}
