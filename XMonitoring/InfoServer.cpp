﻿#include "InfoServer.h"
#include <QtCore>
#include <QtNetwork/QtNetwork>
#include <QtGui>
#include <QMessageBox>

InfoServer::InfoServer(QMainWindow *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	mudpSocket = new QUdpSocket(this);
	mpTimer = new QTimer(this);
	mpTimer->setInterval(5000);
	mpTimer->stop();

	connect(ui.actionSend, &QAction::triggered, this, &InfoServer::sendMessage);
	connect(ui.actionRunTimer, &QAction::triggered, this, &InfoServer::startTimer);
	connect(mpTimer, &QTimer::timeout, this, &InfoServer::sendMessage);
	

	mnSendTime = 0;
	ui.statusBar->showMessage("server is stop now.");
}

InfoServer::~InfoServer()
{
	mudpSocket->close();
}

void InfoServer::startTimer()
{
	if (mpTimer->isActive())
	{
		mpTimer->stop();
		ui.statusBar->showMessage("server is stop now.");		
	}
	else
	{
		mpTimer->start();
		ui.statusBar->showMessage("server is running...");
		
	}
}

void InfoServer::sendMessage()
{
	mnSendTime += 1;

	QByteArray block;
	QDataStream out(&block, QIODevice::WriteOnly);
	//out.setVersion(QDataStream::Qt_5_8);

	QString msg = QString("%1, send times: %2").arg(ui.text->toPlainText()).arg(mnSendTime);
	out << msg;
	out << ui.dangerAttention->value();
	//out.flush();
	int nlength = mudpSocket->writeDatagram(/*msg.toLatin1(), msg.length(),*/block, QHostAddress::Broadcast, 40016);
	
	ui.statusBar->showMessage("server is running... length: " + QString::number(nlength) + " times: "+QString::number(mnSendTime));
	//QMessageBox::information(this, "Send", "Send Success, length = " + QString::number(nlength));
}
