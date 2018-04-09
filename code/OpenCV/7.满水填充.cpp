#include <opencv2/core/core.hpp>  
#include<opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp> // resize()  
#include<iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat matSrc = imread("Lena.jpg");

	Mat matDst = matSrc.clone();

	floodFill(matDst, Point(100, 100), Scalar(0, 255, 0), 0, Scalar(10, 10, 10), Scalar(10, 10, 10));

	imshow("Ô­Í¼", matSrc);
	imshow("ÂúË®Ìî³ä", matDst);

	waitKey();

	return 0;
}