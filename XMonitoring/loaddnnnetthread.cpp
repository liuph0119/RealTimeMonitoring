#include "loaddnnnetthread.h"
#include <QMessageBox>

LoadDnnNetThread::LoadDnnNetThread(QObject *parent)
	: QThread(parent)
{

}

LoadDnnNetThread::~LoadDnnNetThread()
{
}


void LoadDnnNetThread::setParam(QFileInfoList& vfinfos,  dlib::shape_predictor& pose_model, anet_type& dnn_net, std::vector<FACE_DESC>& vfaceinfo)
{
	mvfinfos = vfinfos;

	mcposemodel = pose_model;
	mcdnnnet = dnn_net;
	mvFaceInfo = vfaceinfo;
}

void LoadDnnNetThread::run()
{
#pragma omp parallel for schedule(dynamic)
	for (int i = 0; i < mvfinfos.size(); i++)
	{
		//打开图片;
		std::string _fn = mvfinfos[i].absoluteFilePath().toStdString();
		cv::Mat cv_img = cv::imread(_fn);

		/*检测人脸*/
		std::vector<dlib::rectangle> vfaces;
		std::vector<dlib::full_object_detection> vshapes;
		int nfaces = GetFaceShapesFromImg(cv_img, mcposemodel, vfaces, vshapes);
		emit sig_message(QString("detected %1 face(s) in sample image[%2]").arg(nfaces).arg(i+1));
		if (nfaces != 1)
			continue;

		/*计算特征*/
		std::vector<double> _vfeatures = ComputeFeaturesFromFaceByDNN(cv_img, mcdnnnet, vshapes[0]);

		/*加入样本库中*/
		FACE_DESC sigle_face;
		sigle_face.name = mvfinfos[i].fileName().toStdString();
		sigle_face.vfeatures = _vfeatures;

		mvFaceInfo.push_back(sigle_face);

		cv_img.release();
	}
	finished();
}