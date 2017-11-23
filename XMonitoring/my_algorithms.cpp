#include "my_algorithms.h"
#include <omp.h>



double ComputeFaceFeaturesDist(std::vector<double> f1, std::vector<double> f2, bool bIsEulDist /*= false*/)
{
	if (f1.size() != f2.size())
		return -999;

	int i = 0;

	if (bIsEulDist)
	{
		double dist = 0;
		for (i = 0; i < f1.size(); i++)
		{
			dist += (f1[i] - f2[i])*(f1[i] - f2[i]);
		}

		return sqrt(dist);
	}
	else
	{
		double sum = 0;
		double sum1_2 = 0;
		double sum2_2 = 0;
		for (i = 1; i < f1.size(); ++i)
		{
			sum += f1[i] * f2[i];
			sum1_2 += f1[i] * f1[i];
			sum2_2 += f2[i] * f2[i];
		}

		return 1 - sum / (sqrt(sum1_2)*sqrt(sum2_2));
	}
}

int GetFaceShapesFromImg(cv::Mat &img, dlib::shape_predictor pose_model, std::vector<dlib::rectangle>& faces, std::vector<dlib::full_object_detection>& face_shapes, bool bIsShowImg /*= false*/)
{
	frontal_face_detector detector = get_frontal_face_detector();

	//faces;
	dlib::cv_image<bgr_pixel> cimg(img);
	faces.clear();
	faces = detector(cimg);
	if (faces.size() < 1)
		return 0;

	//feature points pairs;
	face_shapes.clear();

#pragma omp parallel for schedule(dynamic)
	for (int i = 0; i < faces.size(); ++i)
	{
		face_shapes.push_back(pose_model(cimg, faces[i]));
	}

	if (bIsShowImg)
	{
#pragma omp parallel for schedule(dynamic)
		for (int j = 0; j < faces.size(); j++)		//number of faces
		{
			//draw rects and numbers
			cv::rectangle(img, cv::Rect(faces[j].left(), faces[j].top(), faces[j].width(), faces[j].height()), cv::Scalar(int(255.0 / (j + 1)), 0, 255), 3);
		}
	}
	return faces.size();
}

std::vector<double> ComputeFeaturesFromFaceByDNN(cv::Mat cv_img, anet_type dnn_net, dlib::full_object_detection face_shape)
{
	dlib::cv_image<bgr_pixel> img(cv_img);
	dlib::matrix<rgb_pixel> face_chip;
	dlib::extract_image_chip(img, dlib::get_face_chip_details(face_shape, 150, 0.25), face_chip);


	std::vector<matrix<rgb_pixel>> vface_chips;
	vface_chips.push_back(face_chip);
	std::vector<matrix<float, 0, 1>> face_all;
	face_all = dnn_net(vface_chips);

	std::vector<double> features;
	for (int i = 0; i < face_all[0].nr(); i++)
		features.push_back((face_all[0])(i, 0));

	return features;
}

std::vector<std::vector<double>> GetAllFaceFeaturesByDNN(cv::Mat cv_img, anet_type dnn_net, std::vector<dlib::full_object_detection> face_shapes)
{
	std::vector<std::vector<double>> all_features;
	all_features.clear();

#pragma omp parallel for schedule(dynamic)
	for (int i = 0; i < face_shapes.size(); i++)
	{
		std::vector<double> feas = ComputeFeaturesFromFaceByDNN(cv_img, dnn_net, face_shapes[i]);
		all_features.push_back(feas);
	}

	return all_features;
}

double distance2prob(double _dis, bool bIsEulDist /*= false*/)
{
	if (bIsEulDist)
	{
		if (_dis <= 0.2)
			return 1.0;
		else if (_dis < 0.6)
			return (0.6 - _dis) / 0.4;
		else
			return 0;
	}
	else
		return 1.0 - _dis;
}


bool connect_database(QSqlDatabase& db)
{
	QDomDocument doc;
	QFile xmlfile("configure.xml"); //filepath为xml文件路径  
	if (!xmlfile.open(QIODevice::ReadOnly))
		return false;

	if (!doc.setContent(&xmlfile))
	{
		xmlfile.close();
		return false;
	}
	QDomElement root = doc.documentElement();
	QString _hostname = root.elementsByTagName("HostName").at(0).toElement().text();
	QString _username = root.elementsByTagName("UserName").at(0).toElement().text();
	QString _password = root.elementsByTagName("Password").at(0).toElement().text();
	int _port = root.elementsByTagName("Port").at(0).toElement().text().toInt();
	QString _dbName = root.elementsByTagName("DatabaseName").at(0).toElement().text();
	xmlfile.close();

	db = QSqlDatabase::addDatabase("QMYSQL");
	db.setHostName(_hostname);			//数据库地址  
	db.setUserName(_username);			//用户名称  
	db.setPassword(_password);			//用户密码 
	db.setPort(_port);
	db.setDatabaseName(_dbName);		//数据库名称
	if (!db.open())
		return false;
	return true;
}

