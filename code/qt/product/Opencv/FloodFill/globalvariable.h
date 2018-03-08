#ifndef GLOBALVARIABLE_H
#define GLOBALVARIABLE_H

#include <opencv2/opencv.hpp>

class GlobalVariable
{
public:
    GlobalVariable();

    static cv::Mat matSource;
    static cv::Mat matScreen;
    static int lowerBrightnessDifference;
    static int higherBrightnessDifference;
    static cv::Scalar color;
};

#endif // GLOBALVARIABLE_H
