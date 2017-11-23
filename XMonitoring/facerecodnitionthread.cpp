#include "facerecodnitionthread.h"
#include <omp.h>
FaceRecodnitionThread::FaceRecodnitionThread(QObject *parent)
	: QThread(parent)
{

}

FaceRecodnitionThread::~FaceRecodnitionThread()
{
	mvface_desc.clear();
}

void FaceRecodnitionThread::setParams(cv::Mat& img, dlib::shape_predictor& posemodel, anet_type& dnn_net, std::vector<FACE_DESC>& vfaceinfo)
{
	mcvimg = img;
	mposemodel = posemodel;
	mdnnnet = dnn_net;
	mvface_desc = vfaceinfo;
}

void FaceRecodnitionThread::run()
{
	std::vector<dlib::rectangle> vfaces;
	std::vector<dlib::full_object_detection> vshapes;

	//识别人脸并且绘制矩形;
	int nfaces = GetFaceShapesFromImg(mcvimg, mposemodel, vfaces, vshapes, true);
	if (nfaces < 1)
		finished();
	else
	{
		//获取图像上所有的脸部特征;
		std::vector<std::vector<double>> _vvFeatures = GetAllFaceFeaturesByDNN(mcvimg, mdnnnet, vshapes);
		//分别与数据库中的数据比对;
#pragma omp parallel for schedule(dynamic)
		for (int i = 0; i < nfaces; i++)
		{
			for (int j = 0; j < mvface_desc.size(); j++)
			{
				double _dis = ComputeFaceFeaturesDist(_vvFeatures[i], mvface_desc[j].vfeatures, true);
				double _prob = distance2prob(_dis, true);
				sig_message(QString("%1").arg(_prob, 0, 'f', 6));
			}
		}
// 		_vvFeatures.clear();
// 		vfaces.clear();
// 		vshapes.clear();
		finished();
	}
}
