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
	bool mbNetLoaded;//�Ƿ����������ģ�Ͳ��Ҽ�����ͼƬ����;
	QSqlDatabase mDatabase;
	bool mbDatabaseConnected;//�Ƿ��Ѿ��������ݿ�;

	cv::VideoCapture mcVideo;				//��Ƶ��׽;
	dlib::shape_predictor mcPoseModel;		//����������;
	anet_type mcNet;						//�в�����;
	std::vector<FACE_DESC> mvface_desc;		//�����⣬��������������;



	int mnProcSize;				//256*256
	cv::Mat mImgSrc;			//����ͷ��ȡ��ͼ��;
	cv::Mat mImgProc;			//�����ͼ��;
	QImage mImgShow;			//��ʾ��ͼ��;
	QImage mImgShow_small;		//����Ľ��ͼ��;
};

#endif // MAINWINDOW_H
