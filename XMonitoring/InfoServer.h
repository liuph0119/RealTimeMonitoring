#pragma once

#include "ui_InfoServer.h"

#include <QtNetwork/QUdpSocket>
#include <QDialog>

class InfoServer : public QMainWindow
{
	Q_OBJECT

public:
	InfoServer(QMainWindow *parent = Q_NULLPTR);
	~InfoServer();

public slots:
	void startTimer();
	void sendMessage();

private:
	Ui::InfoServerClass ui;
	QUdpSocket *mudpSocket;
	QTimer* mpTimer;
	int mnSendTime;
};
