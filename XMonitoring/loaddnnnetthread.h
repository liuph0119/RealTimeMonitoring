#ifndef LOADDNNNETTHREAD_H
#define LOADDNNNETTHREAD_H

#include <QThread>
#include "my_algorithms.h"
class LoadDnnNetThread : public QThread
{
	Q_OBJECT

public:
	LoadDnnNetThread(QObject *parent);
	~LoadDnnNetThread();

signals:
	//自定义的信号，可以将结果与主线程传输;
	void sig_message(QString smsg);
	void finished();

public:
	void setParam( QFileInfoList& vfinfos, dlib::shape_predictor& pose_model, anet_type& dnn_net, std::vector<FACE_DESC>& vfaceinfo);
	void run();

private:
	QFileInfoList mvfinfos;

public:
	dlib::shape_predictor mcposemodel;
	anet_type mcdnnnet;
	std::vector<FACE_DESC> mvFaceInfo;
	
};

#endif // LOADDNNNETTHREAD_H
