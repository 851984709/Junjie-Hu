//     ���������ø���Ȥ����ROIʵ��ͼ�����  

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
	//����ԭʼͼ��Mat��������  
	Mat matSrc = imread("��¥����.jpg");
	Mat matEdge;
	Mat matDst;

	//���б�Ե���
	Canny(matSrc, matEdge, 50, 200, 3);

	cvtColor(matEdge, matDst, CV_GRAY2RGB);

	//���л����߱任
	vector<Vec4i> lines;//����һ��ʸ���ṹlines���ڴ�ŵõ����߶�ʸ������
	HoughLinesP(matEdge, lines, 1, CV_PI / 180, 80, 50, 10);

	//������ͼ�л��Ƴ�ÿ���߶�
	for (size_t i = 0; i < lines.size(); i++)
	{
		Vec4i l = lines[i];
		line(matDst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255, 0, 0), 1, CV_AA);
	}
  
	imshow("��ԭͼ", matSrc);
	imshow("�߱�Ե", matEdge);
	imshow("������", matDst);
}

void houghcircle()
{
	//����ԭʼͼ��Mat��������     
	Mat matSrc = imread("Բ.jpg");
	Mat matMid, matDst;

	matSrc.copyTo(matDst);

	//תΪ�Ҷ�ͼ������ͼ��ƽ��  
	cvtColor(matSrc, matMid, CV_RGB2GRAY);
	GaussianBlur(matMid, matMid, Size(9, 9), 2, 2);

	//���л���Բ�任
	vector<Vec3f> circles;
	HoughCircles(matMid, circles, CV_HOUGH_GRADIENT, 1.5, 10, 200, 100, 0, 0);

	//������ͼ�л��Ƴ�Բ  
	for (size_t i = 0; i < circles.size(); i++)
	{
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);
		//����Բ��  
		circle(matDst, center, 3, Scalar(0, 255, 0), -1, 8, 0);
		//����Բ����  
		circle(matDst, center, radius, Scalar(255, 0, 0), 3, 8, 0);
	}

	imshow("Բԭͼ", matSrc);
	imshow("����Բ", matDst);
}