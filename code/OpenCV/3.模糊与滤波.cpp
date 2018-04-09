//     描述：利用感兴趣区域ROI实现图像叠加  

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

	namedWindow("原图");
	namedWindow("均值滤波");
	namedWindow("高斯滤波");
	namedWindow("中值滤波");
	namedWindow("双边滤波");

	//均值滤波
	blur(imageOrigin, imageBlur, Size(3, 3));

	//高斯滤波
	GaussianBlur(imageOrigin, imageGaussianBlur, Size(3, 3), 0, 0);

	//中值滤波
	medianBlur(imageOrigin, imageMedianBlur, 3);

	//双边滤波
	bilateralFilter(imageOrigin, imageBilateralFilter, 255, 255 * 2, 255 / 2);

	imshow("原图", imageOrigin);
	imshow("均值滤波", imageBlur);
	imshow("高斯滤波",imageGaussianBlur);
	imshow("中值滤波", imageMedianBlur);
	imshow("双边滤波", imageBilateralFilter);

	waitKey();
}