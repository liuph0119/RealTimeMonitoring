#include "mainwindow.h"
#include <QMessageBox>
#include "my_algorithms.h"

mainwindow::mainwindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	// 初始化摄像头;
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
		ui.cameraId->addItem(QString("camera - %1").arg(i + 1));
	ui.cameraId->setCurrentIndex(0);

	load_init();

	mbIsCameraRuning = false;
	mnProcSize = 256;
	if (!mcVideo.open(0))
	{
		addOutput("no avail camera. error.");
		mbIsCameraRuning = false;
	}
	else
	{
		addOutput("camera 1(default) running...");
		mbIsCameraRuning = true;
		//申请内存;
		mImgSrc = cv::Mat::zeros(mcVideo.get(CV_CAP_PROP_FRAME_HEIGHT), mcVideo.get(CV_CAP_PROP_FRAME_WIDTH), CV_8UC3);
		mImgProc = cv::Mat::zeros(mnProcSize, mnProcSize, CV_8UC3);

		//启动摄像头;
		mTimerCamera.start(100);	//100 ms间隔;
		connect(&mTimerCamera, SIGNAL(timeout()), this, SLOT(updateCamera()));
	}


	connect(ui.lunchCamera, SIGNAL(clicked()), this, SLOT(startCamera()));
	connect(ui.loadModel, SIGNAL(clicked()), this, SLOT(load_init()));
}

mainwindow::~mainwindow()
{
	mcVideo.release();
	mbIsCameraRuning = false;
	closeCamera();
}

bool mainwindow::load_init()
{
	//设置文件当前存储路径;
	msCurrentDir = QCoreApplication::applicationDirPath()+"/data";
	QDir _dir(msCurrentDir);
	if (!_dir.exists(msCurrentDir))
		_dir.mkdir(msCurrentDir);
	addOutput(QString("file will be saved to ") + msCurrentDir);

	msDlibPoseModels = "shape_predictor_68_face_landmarks.dat";
	msDlib_Face_Recognition_Resnet_Model_v1 = "dlib_face_recognition_resnet_model_v1.dat";

	//dlib检测子和深度神经网络识别子载入;
	mcFrontFaceDetector = get_frontal_face_detector();
	deserialize(msDlibPoseModels.toStdString()) >> mcPoseModel;
	deserialize(msDlib_Face_Recognition_Resnet_Model_v1.toStdString()) >> mcNet;

	//遍历样本文件;
	QString sImgDir = msCurrentDir + "/images";
	QDir _qdir(sImgDir);
	QFileInfoList finfo = _qdir.entryInfoList(QStringList(QString("*.jpg")), QDir::Files, QDir::Time);
	if (finfo.isEmpty())
	{
		addOutput(QString("there is no file exists in directory %1").arg(sImgDir));
		return false;
	}

	//处理每一张样本图片;
	foreach(QFileInfo _f, finfo)
	{
		//打开图片;
		QString _sfileName = _f.absoluteFilePath();
		addOutput(QString("load sample image - %1...").arg(_sfileName));

		cv::Mat cv_img = cv::imread(_sfileName.toStdString().c_str());

		/*检测人脸*/
		std::vector<dlib::rectangle> vfaces;
		std::vector<dlib::full_object_detection> vshapes;
		int nfaces = GetFaceShapesFromImg(cv_img, mcPoseModel, vfaces, vshapes);
		addOutput(QString("detected %1 faces in %2").arg(nfaces).arg(_sfileName));
		if (nfaces != 1)
			continue;

		/*计算特征*/
		std::vector<double> _vfeatures = ComputeFeaturesFromFaceByDNN(cv_img, mcNet, vshapes[0]);
		
		/*加入样本库中*/
		FACE_DESC sigle_face; 
		sigle_face.name = _f.fileName().toStdString();
		sigle_face.vfeatures = _vfeatures;
		
		mvface_desc.push_back(sigle_face);

		cv_img.release();
	}
	return true;
}

bool mainwindow::detectFaceByDlib(cv::Mat &img)
{
	std::vector<dlib::rectangle> vfaces;
	std::vector<dlib::full_object_detection> vshapes;

	//识别人脸并且绘制矩形;
	int nfaces = GetFaceShapesFromImg(img, mcPoseModel, vfaces, vshapes, true);

	
	bool flag = false;
	if (nfaces < 1)
		return false;
	else
	{
		std::vector<std::vector<double>> _vvFeatures = GetAllFaceFeaturesByDNN(img, mcNet, vshapes);
		for (int i = 0; i < nfaces; i ++)
		{
			for (int j = 0; j < mvface_desc.size(); j ++)
			{
				double _dis = ComputeFaceFeaturesDist(_vvFeatures[i], mvface_desc[j].vfeatures, true);
				double _prob = distance2prob(_dis, true);
				if (_prob > 0.5)
				{
					addOutput(QString("Dangerous!!! [%1] is coming soon!!! probability=[%2%]").arg(mvface_desc[j].name.substr(0, mvface_desc[j].name.length()-4).c_str()).arg(_prob*100, 0, 'f', 5));

					//如果相似，将照片存入样本库中;
					QDateTime _t = QDateTime::currentDateTime();
					QString _fn = _t.toString("yyyyMMdd_hhmmss");
					_fn = msCurrentDir + "/images/lxp_" + _fn + ".jpg";
					cv::Mat new_img = img.clone();
					cv::cvtColor(img, new_img, CV_BGR2RGB);
					cv::imwrite(_fn.toStdString(), new_img);
					new_img.release();
					flag = true;
				}
			}
		}
	}
	//显示小图像;
	mImgShow_small = QImage((uchar*)(img.data), img.cols, img.rows, QImage::Format_RGB888).scaled(ui.cameralbl_small->size());
	return flag;
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
		mTimerCamera.start(100);
		connect(&mTimerCamera, SIGNAL(timeout()), this, SLOT(updateCamera()));
	}
}

void mainwindow::updateCamera()
{
	if (mbIsCameraRuning == false)
	{
		addOutput("can not find camera.");
		mTimerCamera.stop();
	}

	mcVideo >> mImgSrc;

	//显示大小图像;
	if (mImgSrc.data)
	{
		cv::cvtColor(mImgSrc, mImgSrc, CV_BGR2RGB);//Qt中支持的是RGB图像, OpenCV中支持的是BGR  
		mImgShow = QImage((uchar*)(mImgSrc.data), mImgSrc.cols, mImgSrc.rows, QImage::Format_RGB888).scaled(ui.cameralbl->size());
		cv::resize(mImgSrc, mImgProc, cv::Size(mnProcSize, mnProcSize));
		mImgShow_small = QImage((uchar*)(mImgProc.data), mImgProc.cols, mImgProc.rows, QImage::Format_RGB888).scaled(ui.cameralbl_small->size());
		this->update();
	}

	if (this->detectFaceByDlib(mImgProc))
	{
		mTimerCamera.stop();
		//system("python");
		//system("D:/A_Install/professional/vs2015/Common7/IDE/devenv /run D:/0_cppcode_vs2015/demo/demo.sln");
	}
}

void mainwindow::closeCamera()
{
	if (mbIsCameraRuning)
	{
		mTimerCamera.stop();
		mcVideo.release();
		mbIsCameraRuning = false;
		addOutput("close camera.");
	}
}


void mainwindow::paintEvent(QPaintEvent *e)
{
	ui.cameralbl->setPixmap(QPixmap::fromImage(mImgShow));
	ui.cameralbl->show();

	ui.cameralbl_small->setPixmap(QPixmap::fromImage(mImgShow_small));
	ui.cameralbl_small->show();
}