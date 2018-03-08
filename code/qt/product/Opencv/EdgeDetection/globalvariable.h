#ifndef GLOBALVARIABLE_H
#define GLOBALVARIABLE_H

#include <QImage>
#include <opencv2/opencv.hpp>

//定义滤波的枚举类型
enum OperationType{
    Canney,
    Sobel,
};

class GlobalVariable
{
public:
    GlobalVariable();

    static cv::Mat matSource;
    static cv::Mat matScreen;
    static OperationType operationType;
    static int nParam;
    static bool isColorful;
};

#endif // GLOBALVARIABLE_H
