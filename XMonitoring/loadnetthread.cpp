#include "loadnetthread.h"
#include "my_algorithms.h"

LoadNetThread::LoadNetThread(QObject *parent)
{

}

LoadNetThread::~LoadNetThread()
{
	mvfns.clear();
	mvFaceInfo.clear();
}

void LoadNetThread::setParam(std::string sposefn, std::string snetfn, std::vector<std::string>vfns, std::string obj_label, dlib::shape_predictor &pose_model, anet_type &dnn_net, std::vector<FACE_DESC>& vfaceinfo)
{
	msposefn = sposefn;
	msnetfn = msnetfn;
	mvfns = vfns;
	mslabel = obj_label;

	mcposemodel = pose_model;
	mcdnnnet = dnn_net;
	mvFaceInfo = vfaceinfo;
}

void LoadNetThread::run()
{
	deserialize(msposefn) >> mcposemodel;
	deserialize(msnetfn) >> mcdnnnet;

	for (size_t i = 0; i < mvfns.size(); i ++)
	{
		//打开图片;
		std::string _fn = mvfns[i];
		emit sig_message(QString("load sample image - %1...").arg(_fn.c_str()));

		cv::Mat cv_img = cv::imread(_fn);

		/*检测人脸*/
		std::vector<dlib::rectangle> vfaces;
		std::vector<dlib::full_object_detection> vshapes;
		int nfaces = GetFaceShapesFromImg(cv_img, mcposemodel, vfaces, vshapes);
		emit sig_message(QString("detected %1 faces in %2").arg(nfaces).arg(_fn.c_str()));
		if (nfaces != 1)
			continue;

		/*计算特征*/
		std::vector<double> _vfeatures = ComputeFeaturesFromFaceByDNN(cv_img, mcdnnnet, vshapes[0]);

		/*加入样本库中*/
		FACE_DESC sigle_face;
		sigle_face.name = mslabel;
		sigle_face.vfeatures = _vfeatures;

		mvFaceInfo.push_back(sigle_face);

		cv_img.release();
	}
}
