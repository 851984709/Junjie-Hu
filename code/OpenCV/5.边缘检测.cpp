#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void cannyEdge();//Canny算子边缘检测
void laplaceEdge();//Laplace算子边缘检测

Mat imageOrigin = imread("Lena.jpg");

int main()
{
	//显示原图
	imshow("原图", imageOrigin);

	cannyEdge();
	laplaceEdge();

	waitKey();
}

void cannyEdge()
{
	Mat imageCanny;

	//一、最简单的Canny用法，拿到原图后直接用
	Canny(imageOrigin, imageCanny, 150, 100, 3);
	imshow("Canny边缘检测（简单）", imageCanny);

	//二、高阶的Canny用法，转成灰度图，降噪，用Canny，最后将得到的边缘作为掩码，拷贝原图到效果图上，得到彩色的边缘图
	Mat imageGray, imageEdge;
	cvtColor(imageOrigin, imageGray, CV_RGB2GRAY);//转成灰度
	blur(imageGray, imageGray, Size(3, 3));//降噪
	Canny(imageGray, imageEdge, 3, 9, 3);//边缘检测
	imageOrigin.copyTo(imageCanny, imageEdge);
	imshow("Canny边缘检测（高级）", imageCanny);
}

void laplaceEdge()
{
	Mat imageLaplace;
	Mat imageGray;
	Mat imageEdge;

	//转成灰度
	cvtColor(imageOrigin, imageGray,CV_RGB2GRAY);

	//使用高斯滤波降噪
	GaussianBlur(imageGray, imageGray, Size(3, 3), 0, 0);

	//使用Laplace边缘检测
	Laplacian(imageGray, imageEdge, CV_8UC3);

	imageOrigin.copyTo(imageLaplace, imageEdge);

	imshow("Laplace边缘检测（黑白）", imageEdge);

	imshow("Laplace边缘检测（彩色）", imageLaplace);
}