//     描述：利用感兴趣区域ROI实现图像叠加  

#include <opencv2/core/core.hpp>  
#include<opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp> // resize()  
#include<iostream>

using namespace cv;
using namespace std;

void houghline();
void houghcircle();

int main()
{
	houghline();
	houghcircle();

	waitKey();
}

void houghline()
{
	//载入原始图和Mat变量定义  
	Mat matSrc = imread("高楼大厦.jpg");
	Mat matEdge;
	Mat matDst;

	//进行边缘检测
	Canny(matSrc, matEdge, 50, 200, 3);

	cvtColor(matEdge, matDst, CV_GRAY2RGB);

	//进行霍夫线变换
	vector<Vec4i> lines;//定义一个矢量结构lines用于存放得到的线段矢量集合
	HoughLinesP(matEdge, lines, 1, CV_PI / 180, 80, 50, 10);

	//依次在图中绘制出每条线段
	for (size_t i = 0; i < lines.size(); i++)
	{
		Vec4i l = lines[i];
		line(matDst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255, 0, 0), 1, CV_AA);
	}
  
	imshow("线原图", matSrc);
	imshow("线边缘", matEdge);
	imshow("霍夫线", matDst);
}

void houghcircle()
{
	//载入原始图和Mat变量定义     
	Mat matSrc = imread("圆.jpg");
	Mat matMid, matDst;

	matSrc.copyTo(matDst);

	//转为灰度图，进行图像平滑  
	cvtColor(matSrc, matMid, CV_RGB2GRAY);
	GaussianBlur(matMid, matMid, Size(9, 9), 2, 2);

	//进行霍夫圆变换
	vector<Vec3f> circles;
	HoughCircles(matMid, circles, CV_HOUGH_GRADIENT, 1.5, 10, 200, 100, 0, 0);

	//依次在图中绘制出圆  
	for (size_t i = 0; i < circles.size(); i++)
	{
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);
		//绘制圆心  
		circle(matDst, center, 3, Scalar(0, 255, 0), -1, 8, 0);
		//绘制圆轮廓  
		circle(matDst, center, radius, Scalar(255, 0, 0), 3, 8, 0);
	}

	imshow("圆原图", matSrc);
	imshow("霍夫圆", matDst);
}