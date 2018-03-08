#ifndef GLOBALVARIABLE_H
#define GLOBALVARIABLE_H

#include <QImage>
#include <opencv2/opencv.hpp>

class GlobalVariable
{
public:
    GlobalVariable();

    static cv::Mat matSource;
    static cv::Mat matScreen;
    static int nThresh;
};

#endif // GLOBALVARIABLE_H
