//     描述：利用感兴趣区域ROI实现图像叠加  

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
	//读入图像
	Mat imgKiana = imread("琪亚娜.jpg");
	Mat imgLogo = imread("崩坏3logo.jpg");

	//判断图像是否导入成功
	if (!imgKiana.data)
		return false;
	if (!imgLogo.data)
		return false;

	//调整图像尺寸
	resize(imgKiana, imgKiana, Size(800, 600));
	resize(imgLogo, imgLogo, Size(100, 100));

	//定义一个Mat类型并给其设定ROI区域 
	Mat roiKiana = imgKiana(Rect(0, 0, imgLogo.cols, imgLogo.rows));

	//加载掩模（必须是灰度图）  
	Mat maskLogo = imread("崩坏3logo.jpg", 0);

	resize(maskLogo, maskLogo, Size(100, 100));

	//将掩膜拷贝到ROI 
	imgLogo.copyTo(roiKiana, maskLogo);

	//显示结果  
	namedWindow("琪亚娜", WINDOW_NORMAL);
	imshow("琪亚娜", imgKiana);

	return true;
}

//---------------------------------【ROI_LinearBlending（）】-------------------------------------  
// 函数名：ROI_LinearBlending（）  
// 描述：线性混合实现函数,指定区域线性图像混合.利用cv::addWeighted（）函数结合定义  
//                     感兴趣区域ROI，实现自定义区域的线性混合  
//--------------------------------------------------------------------------------------------  
bool LinearBlending()
{
	//定义一些局部变量
	double dAlphaValue = 0.8;
	double dBetaaluealue = (1.0 - dAlphaValue);
	Mat imgKiana, imgLogo, imgTarget;

	//读入图像
	imgKiana = imread("琪亚娜.jpg");
	imgLogo = imread("崩坏3logo.jpg");

	//判断图像是否导入成功
	if (!imgKiana.data)
		return false;
	if (!imgLogo.data)
		return false;

	resize(imgKiana, imgKiana, Size(800, 600));
	resize(imgLogo, imgLogo, Size(800, 600));

	//做图像混合加权操作
	addWeighted(imgKiana, dAlphaValue, imgLogo, dBetaaluealue, 0.0, imgTarget);

	//显示结果  
	namedWindow("原图", WINDOW_NORMAL);
	imshow("原图", imgKiana);

	namedWindow("琪亚娜", WINDOW_NORMAL);
	imshow("琪亚娜", imgTarget);

	return true;
}


bool Contrastratio()
{
	double alpha;
	double beta;

	Mat image1 = imread("Lena.jpg");
	Mat image2 = Mat::zeros(image1.size(), image1.type());

	//输入 alpha 和 beta 值
	cout << "Enter the alpha value [1.0-3.0]:";
	cin >> alpha;
	cout << "Enter the beta value [0-100]:";
	cin >> beta;

	/*用for循环访问每一个元素，进行对比度和亮度的操作
	// 执行运算 new_image(i,j) = alpha*image(i,j) + beta
	for(int i = 0;i<image1.rows;i++)
		for (int j = 0; j < image1.cols; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				image2.at<Vec3b>(i, j)[k] = saturate_cast<uchar>(alpha * image1.at<Vec3b>(i, j)[k] + beta);
			}
		}
	*/
	//不采用for循环，进行对比度和亮度的操作
	image1.convertTo(image2,-1, alpha, beta);

	//创建窗口
	namedWindow("Original image", 1);
	namedWindow("New image", 1);

	//显示图像
	imshow("Original image", image1);
	imshow("New image", image2);

	return true;
}