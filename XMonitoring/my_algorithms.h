#ifndef MY_ALGORITHMS_H
#define MY_ALGORITHMS_H

#include <stdlib.h>
#include <stdio.h>
#include <QtCore\QtCore>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtWidgets/QMainWindow>
#include "ui_mainwindow.h"
#include "opencv2/core.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/objdetect.hpp"
#include <dlib/image_processing/frontal_face_detector.h>  
#include <dlib/image_processing/render_face_detections.h>  
#include <dlib/image_processing.h>  
#include <dlib/opencv.h>

#include <dlib/gui_widgets.h>
#include <dlib/clustering.h>
#include <dlib/string.h>
#include <dlib/dnn.h>
#include <dlib/image_io.h>

#include <vector>
#include <QtXml/QtXml>

using namespace dlib;
using namespace std;

template <template <int, template<typename>class, int, typename> class block, int N, template<typename>class BN, typename SUBNET>
using residual = add_prev1<block<N, BN, 1, tag1<SUBNET>>>;

template <template <int, template<typename>class, int, typename> class block, int N, template<typename>class BN, typename SUBNET>
using residual_down = add_prev2<avg_pool<2, 2, 2, 2, skip1<tag2<block<N, BN, 2, tag1<SUBNET>>>>>>;

template <int N, template <typename> class BN, int stride, typename SUBNET>
using block = BN<con<N, 3, 3, 1, 1, relu<BN<con<N, 3, 3, stride, stride, SUBNET>>>>>;

template <int N, typename SUBNET> using ares = relu<residual<block, N, affine, SUBNET>>;
template <int N, typename SUBNET> using ares_down = relu<residual_down<block, N, affine, SUBNET>>;

template <typename SUBNET> using alevel0 = ares_down<256, SUBNET>;
template <typename SUBNET> using alevel1 = ares<256, ares<256, ares_down<256, SUBNET>>>;
template <typename SUBNET> using alevel2 = ares<128, ares<128, ares_down<128, SUBNET>>>;
template <typename SUBNET> using alevel3 = ares<64, ares<64, ares<64, ares_down<64, SUBNET>>>>;
template <typename SUBNET> using alevel4 = ares<32, ares<32, ares<32, SUBNET>>>;

/*���������ṹ*/
using anet_type = loss_metric<fc_no_bias<128, avg_pool_everything<alevel0<alevel1<alevel2<alevel3<alevel4<max_pool<3, 3, 2, 2, relu<affine<con<32, 7, 7, 2, 2, input_rgb_image_sized<150>>>>>>>>>>>>>;


struct FACE_DESC
{
	std::string name;
	std::vector<double> vfeatures;
};

/*
@function: �������������shape;
@input:     img: ͼ��, Mat, BGR����;
pose_model: ���������, dlib::shape_predictor
faces: ��������, std::vector<dlib::rectangle>
face_shapes: ����������, std::vector<dlib::full_object_detection>
bIsShowImg: �Ƿ���ʾͼ��, bool
@output:    ����������Ŀ, int;
*/
int GetFaceShapesFromImg(cv::Mat &img, dlib::shape_predictor pose_model, std::vector<dlib::rectangle>& faces, std::vector<dlib::full_object_detection>& face_shapes, bool bIsShowImg = false);


/*
@function: ������Ȳв��������һ��ͼ�������;
@input:     cv_img: ͼ��, Mat, BGR����
dnn_net: �в�����ṹ, anet_type
face_shape: ����������, dlib::full_object_detection
@output:    ͼ���������128ά��std::vector<double>;
*/
std::vector<double> ComputeFeaturesFromFaceByDNN(cv::Mat cv_img, anet_type dnn_net, dlib::full_object_detection face_shape);


/*
@function: ������Ȳв����������ͼ�������;
@input:     cv_img: ͼ��, Mat
dnn_net: �в�����ṹ, anet_type
face_shapes: �������������, std::vector<dlib::full_object_detection>
@output:    ���ͼ���������std::vector<std::vector<double>>;
*/
std::vector<std::vector<double>> GetAllFaceFeaturesByDNN(cv::Mat cv_img, anet_type dnn_net, std::vector<dlib::full_object_detection> face_shapes);


/*
@function: ������������֮��ľ���;
@input:     f1: ����, vector
f2: ����, vector
bIsEulDist: �Ƿ����ŷ�Ͼ���,bool
@output:    ����֮��ľ���,double
*/
double ComputeFaceFeaturesDist(std::vector<double> f1, std::vector<double> f2, bool bIsEulDist = false);

/*
@function: ����������תΪ����
@input   : _dis: ����, double
		   bIsEulDist: �Ƿ���ŷʽ����, bool
@output: ��Ӧ�ĸ���ֵ,double;
*/
double distance2prob(double _dis, bool bIsEulDist = false);


/*********************************************/
/***************���ݿ����**********************/

/*
@function:�������ݿ�,��ȡ���ݿ�����״ֵ̬;
@input: db: ���ݿ����, QSqlDatabase
@output: �Ƿ�ɹ�, bool
*/
bool connect_database(QSqlDatabase& db);


#endif
