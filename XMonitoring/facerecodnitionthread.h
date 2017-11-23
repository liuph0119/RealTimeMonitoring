#ifndef FACERECODNITIONTHREAD_H
#define FACERECODNITIONTHREAD_H

#include <QThread>
#include "my_algorithms.h"
class FaceRecodnitionThread : public QThread
{
	Q_OBJECT

public:
	FaceRecodnitionThread(QObject *parent);
	~FaceRecodnitionThread();

signals:
	//�Զ�����źţ����Խ���������̴߳���;
	void sig_message(QString smsg);
	void finished();

public:
	void setParams(cv::Mat& img, dlib::shape_predictor& posemodel, anet_type& dnn_net, std::vector<FACE_DESC>& vfaceinfo);
	void run();
private:
	cv::Mat mcvimg;
	dlib::shape_predictor mposemodel;
	anet_type mdnnnet;
	std::vector<FACE_DESC> mvface_desc;
};

#endif // FACERECODNITIONTHREAD_H
