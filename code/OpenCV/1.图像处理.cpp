//     ���������ø���Ȥ����ROIʵ��ͼ�����  

#include <opencv2/core/core.hpp>  
#include<opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp> // resize()  
#include<iostream>

using namespace cv;
using namespace std;

bool ROI_AddImage();
bool LinearBlending();
bool Contrastratio();

int main()
{
	Contrastratio();

	waitKey();
}
bool ROI_AddImage()
{
	//����ͼ��
	Mat imgKiana = imread("������.jpg");
	Mat imgLogo = imread("����3logo.jpg");

	//�ж�ͼ���Ƿ���ɹ�
	if (!imgKiana.data)
		return false;
	if (!imgLogo.data)
		return false;

	//����ͼ��ߴ�
	resize(imgKiana, imgKiana, Size(800, 600));
	resize(imgLogo, imgLogo, Size(100, 100));

	//����һ��Mat���Ͳ������趨ROI���� 
	Mat roiKiana = imgKiana(Rect(0, 0, imgLogo.cols, imgLogo.rows));

	//������ģ�������ǻҶ�ͼ��  
	Mat maskLogo = imread("����3logo.jpg", 0);

	resize(maskLogo, maskLogo, Size(100, 100));

	//����Ĥ������ROI 
	imgLogo.copyTo(roiKiana, maskLogo);

	//��ʾ���  
	namedWindow("������", WINDOW_NORMAL);
	imshow("������", imgKiana);

	return true;
}

//---------------------------------��ROI_LinearBlending������-------------------------------------  
// ��������ROI_LinearBlending����  
// ���������Ի��ʵ�ֺ���,ָ����������ͼ����.����cv::addWeighted����������϶���  
//                     ����Ȥ����ROI��ʵ���Զ�����������Ի��  
//--------------------------------------------------------------------------------------------  
bool LinearBlending()
{
	//����һЩ�ֲ�����
	double dAlphaValue = 0.8;
	double dBetaaluealue = (1.0 - dAlphaValue);
	Mat imgKiana, imgLogo, imgTarget;

	//����ͼ��
	imgKiana = imread("������.jpg");
	imgLogo = imread("����3logo.jpg");

	//�ж�ͼ���Ƿ���ɹ�
	if (!imgKiana.data)
		return false;
	if (!imgLogo.data)
		return false;

	resize(imgKiana, imgKiana, Size(800, 600));
	resize(imgLogo, imgLogo, Size(800, 600));

	//��ͼ���ϼ�Ȩ����
	addWeighted(imgKiana, dAlphaValue, imgLogo, dBetaaluealue, 0.0, imgTarget);

	//��ʾ���  
	namedWindow("ԭͼ", WINDOW_NORMAL);
	imshow("ԭͼ", imgKiana);

	namedWindow("������", WINDOW_NORMAL);
	imshow("������", imgTarget);

	return true;
}


bool Contrastratio()
{
	double alpha;
	double beta;

	Mat image1 = imread("Lena.jpg");
	Mat image2 = Mat::zeros(image1.size(), image1.type());

	//���� alpha �� beta ֵ
	cout << "Enter the alpha value [1.0-3.0]:";
	cin >> alpha;
	cout << "Enter the beta value [0-100]:";
	cin >> beta;

	/*��forѭ������ÿһ��Ԫ�أ����жԱȶȺ����ȵĲ���
	// ִ������ new_image(i,j) = alpha*image(i,j) + beta
	for(int i = 0;i<image1.rows;i++)
		for (int j = 0; j < image1.cols; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				image2.at<Vec3b>(i, j)[k] = saturate_cast<uchar>(alpha * image1.at<Vec3b>(i, j)[k] + beta);
			}
		}
	*/
	//������forѭ�������жԱȶȺ����ȵĲ���
	image1.convertTo(image2,-1, alpha, beta);

	//��������
	namedWindow("Original image", 1);
	namedWindow("New image", 1);

	//��ʾͼ��
	imshow("Original image", image1);
	imshow("New image", image2);

	return true;
}