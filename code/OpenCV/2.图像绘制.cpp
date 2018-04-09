//     ���������ø���Ȥ����ROIʵ��ͼ�����  

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

	//ֱ��
	//�����б�ͼƬ����㣬�յ㣬��ɫ�����
	line(image, Point(10, 10), Point(80, 80), Scalar(255, 255, 255), 1);

	//��Բ
	//�����б�ͼƬ��Բ�ģ��ߴ磨a,b������ת�Ƕȣ�������㣬�����յ㣬��ɫ�����
	ellipse(image, Point(200, 60), Size(100, 50),0, 0, 360, Scalar(255, 0, 0), 3);

	//Բ
	//�����б�ͼƬ��Բ�ģ��뾶����ɫ�����
	circle(image, Point(350, 100), 40, Scalar(0, 255, 255), -1);

	//�����
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
	//�����б�ͼƬ������ζ��㼯�ļ�������ζ������ļ�����Ҫ���ƵĶ����������ɫ
	fillPoly(image, ppt, npt, 2, Scalar(255, 255, 255),8);

	//����
	//�����б�ͼƬ���ԽǶ���1���ԽǶ���2����ɫ�����
	rectangle(image, Point(300, 190), Point(380, 290), Scalar(255,255,0),1);



	namedWindow("Window");

	imshow("Window", image);

	waitKey();
}