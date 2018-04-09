#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	//以灰度模式载入图像并显示  
	Mat matSrc = imread("Lena.jpg", 0);//参数0表示以灰度模式载入

	//进行Harris角点检测找出角点  
	Mat cornerStrength;
	cornerHarris(matSrc, cornerStrength, 2, 3, 0.01);

	//对灰度图进行阈值操作，得到二值图并显示    
	Mat harrisCorner;
	threshold(cornerStrength, harrisCorner, 0.0001, 255, THRESH_BINARY);

	imshow("原始图", matSrc);
	imshow("中间值", cornerStrength);
	imshow("角点图", harrisCorner);

	waitKey();
	return 0;
}