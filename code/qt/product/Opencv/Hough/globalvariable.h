#ifndef GLOBALVARIABLE_H
#define GLOBALVARIABLE_H

#include <QImage>
#include <opencv2/opencv.hpp>

//定义滤波的枚举类型
enum GraphicType{
    Line,
    Circle,
};

class GlobalVariable
{
public:
    GlobalVariable();

    static cv::Mat matSource;
    static cv::Mat matScreen;
    static GraphicType graphicType;
    static int nParam;
};

#endif // GLOBALVARIABLE_H
