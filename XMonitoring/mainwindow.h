#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "my_algorithms.h"

struct FACE_DESC 
{
	std::string name;
	std::vector<double> vfeatures;
};

class mainwindow : public QMainWindow
{
	Q_OBJECT

public:
	mainwindow(QWidget *parent = 0);
	~mainwindow();


private:
	bool detectFaceByDlib(cv::Mat &img);

protected:
	void mainwindow::paintEvent(QPaintEvent *e);

private slots:
	bool load_init();
	void addOutput(QString msg);
	void openCamera();
	void updateCamera();
	void closeCamera();


private:
	Ui::mainwindowClass ui;

	QTimer mTimerCamera;
	QTimer mTimerProgram;
	QString msCurrentDir;

	QString msDlibPoseModels;
	QString msDlib_Face_Recognition_Resnet_Model_v1;


	cv::VideoCapture mcVideo;						//��Ƶ��׽;
	dlib::frontal_face_detector mcFrontFaceDetector;	//ǰ�������;
	dlib::shape_predictor mcPoseModel;				//����������;
	anet_type mcNet;							//�в�����;
	std::vector<FACE_DESC> mvface_desc;			//�����⣬��������������;

	bool mbIsCameraRuning;

	int mnProcSize;			//256*256
	cv::Mat mImgSrc;			//����ͷ��ȡ��ͼ��;
	cv::Mat mImgProc;			//�����ͼ��;
	QImage mImgShow;		//��ʾ��ͼ��;
	QImage mImgShow_small;	//����Ľ��ͼ��;
};

#endif // MAINWINDOW_H
