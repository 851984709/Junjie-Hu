#ifndef MYOPENCV_H
#define MYOPENCV_H

#include <QImage>
#include <opencv2/opencv.hpp>

class MyOpenCV
{
public:
    MyOpenCV();

    static QImage cvMat2QImage(cv::Mat mat);
    static cv::Mat QImage2cvMat(QImage image);
};

#endif // MYOPENCV_H
