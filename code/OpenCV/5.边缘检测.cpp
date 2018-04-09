#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void cannyEdge();//Canny���ӱ�Ե���
void laplaceEdge();//Laplace���ӱ�Ե���

Mat imageOrigin = imread("Lena.jpg");

int main()
{
	//��ʾԭͼ
	imshow("ԭͼ", imageOrigin);

	cannyEdge();
	laplaceEdge();

	waitKey();
}

void cannyEdge()
{
	Mat imageCanny;

	//һ����򵥵�Canny�÷����õ�ԭͼ��ֱ����
	Canny(imageOrigin, imageCanny, 150, 100, 3);
	imshow("Canny��Ե��⣨�򵥣�", imageCanny);

	//�����߽׵�Canny�÷���ת�ɻҶ�ͼ�����룬��Canny����󽫵õ��ı�Ե��Ϊ���룬����ԭͼ��Ч��ͼ�ϣ��õ���ɫ�ı�Եͼ
	Mat imageGray, imageEdge;
	cvtColor(imageOrigin, imageGray, CV_RGB2GRAY);//ת�ɻҶ�
	blur(imageGray, imageGray, Size(3, 3));//����
	Canny(imageGray, imageEdge, 3, 9, 3);//��Ե���
	imageOrigin.copyTo(imageCanny, imageEdge);
	imshow("Canny��Ե��⣨�߼���", imageCanny);
}

void laplaceEdge()
{
	Mat imageLaplace;
	Mat imageGray;
	Mat imageEdge;

	//ת�ɻҶ�
	cvtColor(imageOrigin, imageGray,CV_RGB2GRAY);

	//ʹ�ø�˹�˲�����
	GaussianBlur(imageGray, imageGray, Size(3, 3), 0, 0);

	//ʹ��Laplace��Ե���
	Laplacian(imageGray, imageEdge, CV_8UC3);

	imageOrigin.copyTo(imageLaplace, imageEdge);

	imshow("Laplace��Ե��⣨�ڰף�", imageEdge);

	imshow("Laplace��Ե��⣨��ɫ��", imageLaplace);
}