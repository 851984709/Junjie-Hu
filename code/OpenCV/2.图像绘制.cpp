//     描述：利用感兴趣区域ROI实现图像叠加  

#include <opencv2/core/core.hpp>  
#include<opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp> // resize()  
#include<iostream>

using namespace cv;
using namespace std;

int main()
{
	int width = 400;
	int height = 300;

	Mat image = Mat::zeros(height, width, CV_8UC3);

	//直线
	//参数列表：图片，起点，终点，颜色，厚度
	line(image, Point(10, 10), Point(80, 80), Scalar(255, 255, 255), 1);

	//椭圆
	//参数列表：图片，圆心，尺寸（a,b），旋转角度，弧度起点，弧度终点，颜色，厚度
	ellipse(image, Point(200, 60), Size(100, 50),0, 0, 360, Scalar(255, 0, 0), 3);

	//圆
	//参数列表：图片，圆心，半径，颜色，厚度
	circle(image, Point(350, 100), 40, Scalar(0, 255, 255), -1);

	//多边形
	Point points1[10],points2[5];
	for (int i = 0; i < 10; i++)
	{
		points1[i].x = 50 + 50 * cos(2 * 3.14 / 10 * i);
		points1[i].y = 200 + 50 * sin(2 * 3.14 / 10 * i);
	}
	for (int i = 0; i < 5; i++)
	{
		points2[i].x = 200 + 50 * cos(2 * 3.14 / 5 * i);
		points2[i].y = 200 + 50 * sin(2 * 3.14 / 5 * i);
	}
	const Point *ppt[2] = { points1, points2 };
	int npt[2] = { 10 ,5 };
	//参数列表：图片，多边形顶点集的集，多边形顶点数的集，需要绘制的多边形数，颜色
	fillPoly(image, ppt, npt, 2, Scalar(255, 255, 255),8);

	//矩形
	//参数列表：图片，对角顶点1，对角顶点2，颜色，厚度
	rectangle(image, Point(300, 190), Point(380, 290), Scalar(255,255,0),1);



	namedWindow("Window");

	imshow("Window", image);

	waitKey();
}