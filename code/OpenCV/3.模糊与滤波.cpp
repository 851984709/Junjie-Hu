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
	Mat imageBlur;
	Mat imageGaussianBlur;
	Mat imageMedianBlur;
	Mat imageBilateralFilter;

	namedWindow("ԭͼ");
	namedWindow("��ֵ�˲�");
	namedWindow("��˹�˲�");
	namedWindow("��ֵ�˲�");
	namedWindow("˫���˲�");

	//��ֵ�˲�
	blur(imageOrigin, imageBlur, Size(3, 3));

	//��˹�˲�
	GaussianBlur(imageOrigin, imageGaussianBlur, Size(3, 3), 0, 0);

	//��ֵ�˲�
	medianBlur(imageOrigin, imageMedianBlur, 3);

	//˫���˲�
	bilateralFilter(imageOrigin, imageBilateralFilter, 255, 255 * 2, 255 / 2);

	imshow("ԭͼ", imageOrigin);
	imshow("��ֵ�˲�", imageBlur);
	imshow("��˹�˲�",imageGaussianBlur);
	imshow("��ֵ�˲�", imageMedianBlur);
	imshow("˫���˲�", imageBilateralFilter);

	waitKey();
}