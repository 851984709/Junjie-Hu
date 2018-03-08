#ifndef GLOBALVARIABLE_H
#define GLOBALVARIABLE_H

#include <QImage>
#include <opencv2/opencv.hpp>

//定义滤波的枚举类型
enum OperationType{
    Dilation,
    Erosion,
};

class GlobalVariable
{
public:
    GlobalVariable();

    static cv::Mat matSource;
    static cv::Mat matScreen;
    static OperationType operationType;
    static int nStructElementSize;
    static int niteration;
};

#endif // GLOBALVARIABLE_H
