#include "mainwindow.h"
#include <QMessageBox>
#include "my_algorithms.h"
#include "loaddnnnetthread.h"
#include "facerecodnitionthread.h"

mainwindow::mainwindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	setFixedSize(661, 528);
	//初始化未导入模型;
	mbNetLoaded = false;
	mbDatabaseConnected = false;
	mnProcSize = 256;
	msCurrentDir = QCoreApplication::applicationDirPath() + "/data";


	//设置界面不可见;
	ui.label->setVisible(false);
	ui.label_2->setVisible(false);
	ui.warningprob->setVisible(false);
	ui.cameraId->setVisible(false);
	ui.btn_restart->setVisible(false);
	ui.output->setVisible(false);

	//从文件导入模型，并且计算图片的特征，存入数据库;
	connect(ui.actioninitialfromimages, &QAction::triggered, this, &mainwindow::init_env_mode1);
	//从文件导入模型，从数据库中获取特征信息;
	connect(ui.actioninitial_from_db, &QAction::triggered, this, &mainwindow::init_env_mode2);
	//重选摄像头;
	connect(ui.btn_restart, &QPushButton::clicked, this, &mainwindow::openCamera);
	//模拟测试警报;
	connect(ui.actionsimulation_danger, &QAction::triggered, this, &mainwindow::simulate_danger);
	connect(ui.actionsimulation_safe, &QAction::triggered, this, &mainwindow::simulate_safe);
	//关于;
	connect(ui.actionCopyRight, &QAction::triggered, this, &mainwindow::whatisit);
	//退出;
	connect(ui.actionExit, &QAction::triggered, this, &mainwindow::close);
}

mainwindow::~mainwindow()
{
	mcVideo.release();
	mbIsCameraRuning = false;
	closeCamera();
	mDatabase.close();
}



void mainwindow::addOutput(QString msg)
{
	ui.output->append(QDateTime::currentDateTime().toString("yyyyMMdd hh:mm:ss") + " >> " + msg);
}

void mainwindow::openCamera()
{
	//获取摄像头个数;
	mbIsCameraRuning = false;
	int nCurIdx = ui.cameraId->currentIndex();
	mcVideo.release();

	if (!mcVideo.open(nCurIdx))
	{
		addOutput("no avail camera. error.");
		mbIsCameraRuning = false;
	}
	else
	{
		addOutput(QString("camera %1 running...").arg(nCurIdx + 1));
		mbIsCameraRuning = true;
		mImgSrc = cv::Mat::zeros(mcVideo.get(CV_CAP_PROP_FRAME_HEIGHT), mcVideo.get(CV_CAP_PROP_FRAME_WIDTH), CV_8UC3);
		mImgProc = cv::Mat::zeros(mnProcSize, mnProcSize, CV_8UC3);

		//启动;
		mTimerCamera = new QTimer();
		mTimerCamera->start(100);
		connect(mTimerCamera, &QTimer::timeout, this, &mainwindow::updateCamera);

		mTimerDetection = new QTimer();
		mTimerDetection->start(1);
		connect(mTimerDetection, &QTimer::timeout, this, &mainwindow::realTimeDetection);
	}
}

void mainwindow::closeCamera()
{
	if (mbIsCameraRuning)
	{
		mTimerCamera->stop();
		delete mTimerCamera;
		mcVideo.release();
		mbIsCameraRuning = false;
		addOutput("close camera.");
	}
}

void mainwindow::realTimeDetection()
{
	if (mImgProc.empty())
		return;
	mTimerDetection->stop();
	//另辟线程，实时监测;
	QEventLoop loop;
	FaceRecodnitionThread _facerecognitionthread(this);
	_facerecognitionthread.setParams(mImgProc, mcPoseModel, mcNet, mvface_desc);
	_facerecognitionthread.start();

	connect(&_facerecognitionthread, &FaceRecodnitionThread::finished, &loop, &QEventLoop::quit);
	connect(&_facerecognitionthread, &FaceRecodnitionThread::sig_message, this, &mainwindow::parseProb);
	loop.exec();
	_facerecognitionthread.wait();//防止线程意外中止;

	mTimerDetection->start(1);
}

void mainwindow::simulate_danger()
{
	if (!mbDatabaseConnected)
	{
		if (!connect_database(mDatabase))
		{
			addOutput("connect database fail!");
			return;
		}
	}
	QSqlQuery _query;
	QString _time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
	QString _sql = QString("update real_time_state_tbl set tm='%1',state='danger',danger_index=%2").arg(_time).arg(100);
	_query.exec(_sql);
}

void mainwindow::simulate_safe()
{
	if (!mbDatabaseConnected)
	{
		if (!connect_database(mDatabase))
		{
			addOutput("connect database fail!");
			return;
		}
	}
	QSqlQuery _query;
	QString _time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
	QString _sql = QString("update real_time_state_tbl set tm='%1',state='safe',danger_index=%2").arg(_time).arg(0);
	_query.exec(_sql);
}

void mainwindow::whatisit()
{
	QMessageBox::information(this, "Information", "Touch Fish Server 1.0\nCopyright (c) 2017 Touch Fish Group\n\nThis software is based on Qt, Opencv and Dlib.");
}

void mainwindow::paintEvent(QPaintEvent *e)
{
	ui.cameralbl->setPixmap(QPixmap::fromImage(mImgShow));
	ui.cameralbl->show();

	ui.cameralbl_small->setPixmap(QPixmap::fromImage(mImgShow_small));
	ui.cameralbl_small->show();
}

void mainwindow::getCameras()
{
	// 获取有效摄像头数目;
	int camera_count = -1;
	int i = 0;
	while (1)
	{
		++camera_count;
		if (!mcVideo.open(camera_count))
			break;
		mcVideo.release();
	}
	addOutput(QString("camera count = %1").arg(camera_count));

	if (camera_count <= 0)
	{
		addOutput("no avail camera. error.");
		mbIsCameraRuning = false;
	}

	for (i = 0; i < camera_count; i++)
		ui.cameraId->addItem(QString("camera-%1").arg(i + 1));
	ui.cameraId->setCurrentIndex(0);
}

void mainwindow::updateCamera()
{
	if (mbIsCameraRuning == false)
	{
		addOutput("can not find camera.");
		mTimerCamera->stop();
		delete mTimerCamera;
	}

	mcVideo >> mImgSrc;

	//显示大小图像;
	if (mImgSrc.data)
	{
		cv::cvtColor(mImgSrc, mImgSrc, CV_BGR2RGB);//Qt中支持的是RGB图像, OpenCV中支持的是BGR  
		mImgShow = QImage((uchar*)(mImgSrc.data), mImgSrc.cols, mImgSrc.rows, QImage::Format_RGB888).scaled(ui.cameralbl->size());
		cv::resize(mImgSrc, mImgProc, cv::Size(mnProcSize, mnProcSize));
		//mImgShow_small = QImage((uchar*)(mImgProc.data), mImgProc.cols, mImgProc.rows, QImage::Format_RGB888).scaled(ui.cameralbl_small->size());
		this->update();
	}
}

void mainwindow::init_env_mode1()
{
	ui.label->setVisible(true);
	ui.label_2->setVisible(true);
	ui.warningprob->setVisible(true);
	ui.cameraId->setVisible(true);
	ui.btn_restart->setVisible(true);
	ui.output->setVisible(true);

	//连接数据库;
	if (connect_database(mDatabase))
	{
		addOutput("connect database success!");
		mbDatabaseConnected = true;
	}
	else
	{
		addOutput("connect database success!");
	}

	//加载模型;
	std::string posefn = "shape_predictor_68_face_landmarks.dat";
	std::string netfn = "dlib_face_recognition_resnet_model_v1.dat";
	deserialize(posefn.c_str()) >> mcPoseModel;
	deserialize(netfn.c_str()) >> mcNet;

	QString _name = "xjp";
	//读取样本信息, 存入数据库;
	if (!mbNetLoaded)
		load_samples_from_images(_name);
	
	//获取摄像头数目信息;
	getCameras();
	//打开摄像头;
	openCamera();
}


void mainwindow::init_env_mode2()
{
	ui.label->setVisible(true);
	ui.label_2->setVisible(true);
	ui.warningprob->setVisible(true);
	ui.cameraId->setVisible(true);
	ui.btn_restart->setVisible(true);
	ui.output->setVisible(true);

	//连接数据库;
	if (connect_database(mDatabase))
	{
		addOutput("connect database success!");
		mbDatabaseConnected = true;
	}
	else
		addOutput("connect database fail!");
	

	//加载模型;
	std::string posefn = "shape_predictor_68_face_landmarks.dat";
	std::string netfn = "dlib_face_recognition_resnet_model_v1.dat";
	deserialize(posefn.c_str()) >> mcPoseModel;
	deserialize(netfn.c_str()) >> mcNet;


	QDomDocument doc;
	QFile xmlfile("configure.xml"); //filepath为xml文件路径  
	if (!xmlfile.open(QIODevice::ReadOnly))
		return;

	if (!doc.setContent(&xmlfile))
	{
		xmlfile.close();
		return;
	}
	QDomElement root = doc.documentElement();

	QString _name = root.elementsByTagName("Name").at(0).toElement().text();
	//读取样本信息, 存入数据库;
	load_samples_from_db(mDatabase, _name);

	//获取摄像头数目信息;
	getCameras();
	//打开摄像头;
	openCamera();
}


void mainwindow::parseProb(QString msg)
{
	//显示小图像;
	mImgShow_small = QImage((uchar*)(mImgProc.data), mImgProc.cols, mImgProc.rows, QImage::Format_RGB888).scaled(ui.cameralbl_small->size());

	double val = msg.toDouble();
	addOutput(QString("dangerous index = %1").arg(val * 100, 0, 'f', 2));
	QString _state = "safe";
	if (val > ui.warningprob->value())
		_state = "danger";

	QSqlQuery _query;
	QString _time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
	QString _sql = QString("update real_time_state_tbl set tm='%1',state='%2',danger_index=%3").arg(_time).arg(_state).arg(int(val * 100));
	_query.exec(_sql);
}

bool mainwindow::load_samples_from_images(QString _name)
{
	//遍历样本文件;
	QString sImgDir = msCurrentDir + "/images";
	QDir _qdir(sImgDir);
	QFileInfoList finfo = _qdir.entryInfoList(QStringList(QString("*.jpg")), QDir::Files, QDir::Time);
	if (finfo.isEmpty())
	{
		addOutput(QString("there is no file exists in directory %1").arg(sImgDir));
		return false;
	}

	addOutput(QString("load sample images, number = %1").arg(finfo.size()));
	// 外部线程提取每张图片的特征和标签;
	QEventLoop loop;
	LoadDnnNetThread _loadnetthread(this);
	
	_loadnetthread.setParam(finfo, mcPoseModel, mcNet, mvface_desc);
	_loadnetthread.start();
	connect(&_loadnetthread, &LoadDnnNetThread::finished, &loop, &QEventLoop::quit);
	connect(&_loadnetthread, &LoadDnnNetThread::sig_message, this, &mainwindow::addOutput);
	loop.exec();
	_loadnetthread.wait();//防止线程意外中止;

	mbNetLoaded = true;
	addOutput("load samples...success!");
	addOutput("save to database...");

	/*计算完毕，存入数据库*/
	//尝试将样本信息插入数据库;
	mvface_desc = _loadnetthread.mvFaceInfo;
	for (int i = 0; i < mvface_desc.size(); i++)
		insert_faceinfo_into_db(mDatabase, mvface_desc[i]);
	
	return true;
}


bool mainwindow::load_samples_from_db(QSqlDatabase& db, QString _name)
{
	if (!mbDatabaseConnected)
		if (!connect_database(db))
		{
			addOutput("connect database fail!");
			return false;
		};

	//查询特定名称的向量;
	QString _sql = QString("select photo_id,feature from face_feature_tbl");
	QSqlQuery _query;
	if (!_query.exec(_sql))
		return false;

	//解析名称和特征向量;
	mvface_desc.clear();
	while (_query.next())
	{
		FACE_DESC _info;
		// 名称;
		_info.name = _query.value(0).toString().toStdString();
		QString sfeatures = _query.value(1).toString();
		QStringList slist = sfeatures.split(",");
		// 特征向量;
		for (int i = 0; i < slist.size(); i ++)
			_info.vfeatures.push_back(slist[i].toDouble());
		mvface_desc.push_back(_info);
	}
	return true;
}

bool mainwindow::detectFaceByDlib(cv::Mat &img)
{
	
	return true;
}

bool mainwindow::insert_faceinfo_into_db(QSqlDatabase& db, FACE_DESC _info)
{
	QSqlQuery _query;
	QString msg = QString("'%1','%2").arg(_info.name.c_str()).arg(_info.vfeatures[0], 0, 'f', 6);
	for (int i = 1; i < _info.vfeatures.size(); i ++)
		msg = msg + QString(",%1").arg(_info.vfeatures[i], 0, 'f', 6);
	msg = msg + "'";
	QString _sql = QString("insert into face_feature_tbl (photo_id,feature) values(%1)").arg(msg);
	if (!_query.exec(_sql))
		return false;
	else
		addOutput("save to database...success!");
	return true;
}

