//     ���������ø���Ȥ����ROIʵ��ͼ�����  

#include <opencv2/core/core.hpp>  
#include<opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp> // resize()  
#include<iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat imageOrigin = imread("Lena.jpg");
	Mat imageDilate;
	Mat imageErode;

	//��ȡ�Զ����
	Mat kernelRect = getStructuringElement(MORPH_RECT,
		Size(10,10));

	Mat kernelCircle = getStructuringElement(MORPH_ELLIPSE,
		Size(10, 10));

	//����
	dilate(imageOrigin, imageDilate, kernelRect);

	//��ʴ
	erode(imageOrigin, imageErode, kernelCircle);

	namedWindow("ԭͼ");
	namedWindow("����");
	namedWindow("��ʴ");

	imshow("ԭͼ", imageOrigin);
	imshow("����", imageDilate);
	imshow("��ʴ", imageErode);

	waitKey();
}