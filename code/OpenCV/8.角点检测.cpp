#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	//�ԻҶ�ģʽ����ͼ����ʾ  
	Mat matSrc = imread("Lena.jpg", 0);//����0��ʾ�ԻҶ�ģʽ����

	//����Harris�ǵ����ҳ��ǵ�  
	Mat cornerStrength;
	cornerHarris(matSrc, cornerStrength, 2, 3, 0.01);

	//�ԻҶ�ͼ������ֵ�������õ���ֵͼ����ʾ    
	Mat harrisCorner;
	threshold(cornerStrength, harrisCorner, 0.0001, 255, THRESH_BINARY);

	imshow("ԭʼͼ", matSrc);
	imshow("�м�ֵ", cornerStrength);
	imshow("�ǵ�ͼ", harrisCorner);

	waitKey();
	return 0;
}