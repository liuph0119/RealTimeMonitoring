#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "my_algorithms.h"
#include <QtGui/QtGui>


class mainwindow : public QMainWindow
{
	Q_OBJECT

public:
	mainwindow(QWidget *parent = 0);
	~mainwindow();


private:
	void getCameras();
	bool detectFaceByDlib(cv::Mat &img);
	bool insert_faceinfo_into_db(QSqlDatabase& db, FACE_DESC _info);
	bool load_samples_from_images(QString _name);
	bool load_samples_from_db(QSqlDatabase& db, QString _name);

protected:
	void mainwindow::paintEvent(QPaintEvent *e);

private slots:
	void init_env_mode1();
	void init_env_mode2();
	void parseProb(QString msg="1.0");
	void addOutput(QString msg);
	void openCamera();
	void updateCamera();
	void closeCamera();
	void realTimeDetection();
	void simulate_danger();
	void simulate_safe();

	void whatisit();

private:
	Ui::mainwindowClass ui;

	QTimer *mTimerCamera;
	QTimer *mTimerDetection;
	QString msCurrentDir;

	bool mbIsCameraRuning;
	bool mbNetLoaded;//是否加载了网络模型并且计算了图片向量;
	QSqlDatabase mDatabase;
	bool mbDatabaseConnected;//是否已经连接数据库;

	cv::VideoCapture mcVideo;				//视频捕捉;
	dlib::shape_predictor mcPoseModel;		//特征点检测子;
	anet_type mcNet;						//残差网络;
	std::vector<FACE_DESC> mvface_desc;		//样本库，包括特征和名称;



	int mnProcSize;				//256*256
	cv::Mat mImgSrc;			//摄像头获取的图像;
	cv::Mat mImgProc;			//处理的图像;
	QImage mImgShow;			//显示的图像;
	QImage mImgShow_small;		//处理的结果图像;
};

#endif // MAINWINDOW_H
