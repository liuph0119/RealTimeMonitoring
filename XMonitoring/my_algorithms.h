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

/*深度神经网络结构*/
using anet_type = loss_metric<fc_no_bias<128, avg_pool_everything<alevel0<alevel1<alevel2<alevel3<alevel4<max_pool<3, 3, 2, 2, relu<affine<con<32, 7, 7, 2, 2, input_rgb_image_sized<150>>>>>>>>>>>>>;


struct FACE_DESC
{
	std::string name;
	std::vector<double> vfeatures;
};

/*
@function: 检测人脸和特征shape;
@input:     img: 图像, Mat, BGR输入;
pose_model: 特征检测子, dlib::shape_predictor
faces: 检测的人脸, std::vector<dlib::rectangle>
face_shapes: 人脸的特征, std::vector<dlib::full_object_detection>
bIsShowImg: 是否显示图像, bool
@output:    检测的人脸数目, int;
*/
int GetFaceShapesFromImg(cv::Mat &img, dlib::shape_predictor pose_model, std::vector<dlib::rectangle>& faces, std::vector<dlib::full_object_detection>& face_shapes, bool bIsShowImg = false);


/*
@function: 采用深度残差网络计算一幅图像的特征;
@input:     cv_img: 图像, Mat, BGR输入
dnn_net: 残差网络结构, anet_type
face_shape: 人脸的特征, dlib::full_object_detection
@output:    图像的特征，128维，std::vector<double>;
*/
std::vector<double> ComputeFeaturesFromFaceByDNN(cv::Mat cv_img, anet_type dnn_net, dlib::full_object_detection face_shape);


/*
@function: 采用深度残差网络计算多幅图像的特征;
@input:     cv_img: 图像, Mat
dnn_net: 残差网络结构, anet_type
face_shapes: 多个人脸的特征, std::vector<dlib::full_object_detection>
@output:    多个图像的特征，std::vector<std::vector<double>>;
*/
std::vector<std::vector<double>> GetAllFaceFeaturesByDNN(cv::Mat cv_img, anet_type dnn_net, std::vector<dlib::full_object_detection> face_shapes);


/*
@function: 计算两个向量之间的距离;
@input:     f1: 向量, vector
f2: 向量, vector
bIsEulDist: 是否采用欧氏距离,bool
@output:    向量之间的距离,double
*/
double ComputeFaceFeaturesDist(std::vector<double> f1, std::vector<double> f2, bool bIsEulDist = false);

/*
@function: 将向量距离转为概率
@input   : _dis: 距离, double
		   bIsEulDist: 是否是欧式距离, bool
@output: 对应的概率值,double;
*/
double distance2prob(double _dis, bool bIsEulDist = false);


/*********************************************/
/***************数据库操作**********************/

/*
@function:连接数据库,获取数据库对象和状态值;
@input: db: 数据库对象, QSqlDatabase
@output: 是否成功, bool
*/
bool connect_database(QSqlDatabase& db);


#endif
