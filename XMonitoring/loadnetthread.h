#ifndef LOADNETTHREAD_H
#define LOADNETTHREAD_H


#include <QThread>
#include "mainwindow.h"

class LoadNetThread : public QThread
{
	Q_OBJECT

public:
	LoadNetThread(QObject *parent);
	~LoadNetThread();

signals:
	void sig_message(QString smsg);
	void finished();

public:
	void setParam(std::string sposefn, std::string snetfn, std::vector<std::string>vfns,  std::string obj_label, dlib::shape_predictor &pose_model, anet_type &dnn_net, std::vector<FACE_DESC>& vfaceinfo);
	void run();

private:
	std::string msposefn;
	std::string msnetfn;
	std::vector<std::string> mvfns;
	std::string mslabel;

	dlib::shape_predictor mcposemodel;
	anet_type mcdnnnet;
	std::vector<FACE_DESC> mvFaceInfo;

};

#endif // LOADTRAINTHREAD_H
