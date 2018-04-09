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
	Mat imageDilate;
	Mat imageErode;

	//获取自定义核
	Mat kernelRect = getStructuringElement(MORPH_RECT,
		Size(10,10));

	Mat kernelCircle = getStructuringElement(MORPH_ELLIPSE,
		Size(10, 10));

	//膨胀
	dilate(imageOrigin, imageDilate, kernelRect);

	//腐蚀
	erode(imageOrigin, imageErode, kernelCircle);

	namedWindow("原图");
	namedWindow("膨胀");
	namedWindow("腐蚀");

	imshow("原图", imageOrigin);
	imshow("膨胀", imageDilate);
	imshow("腐蚀", imageErode);

	waitKey();
}