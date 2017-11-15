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


	cv::VideoCapture mcVideo;						//视频捕捉;
	dlib::frontal_face_detector mcFrontFaceDetector;	//前脸检测子;
	dlib::shape_predictor mcPoseModel;				//特征点检测子;
	anet_type mcNet;							//残差网络;
	std::vector<FACE_DESC> mvface_desc;			//样本库，包括特征和名称;

	bool mbIsCameraRuning;

	int mnProcSize;			//256*256
	cv::Mat mImgSrc;			//摄像头获取的图像;
	cv::Mat mImgProc;			//处理的图像;
	QImage mImgShow;		//显示的图像;
	QImage mImgShow_small;	//处理的结果图像;
};

#endif // MAINWINDOW_H
