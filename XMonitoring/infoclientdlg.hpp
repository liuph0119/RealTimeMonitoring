#pragma once
#include <QDialog>
#include "ui_infoclientdlg.h"
#include <QtNetWork/QUdpSocket>
#include <QtCore/QtCore>

class InfoClientDlg : public QDialog {
	Q_OBJECT

public:
	InfoClientDlg(QDialog * parent = Q_NULLPTR);
	~InfoClientDlg();

public slots:
	void receiveInfo();

private:
	Ui::InfoClientDlgClass ui;
	QUdpSocket* mpUdpSocket;
};
