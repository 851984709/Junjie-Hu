#include "displayview.h"

DisplayView::DisplayView(QWidget *parent) : QScrollArea(parent)
{
    setBackgroundRole(QPalette::Dark);
    label = new QLabel(this);

    setWidget(label);
}

void DisplayView::refresh()
{
    //判断是否有可供处理的图片
    if(GlobalVariable::matSource.empty())
    {
        qDebug()<<"不满足显示条件";
        return;
    }

    emit saveEnable();

    switch(GlobalVariable::graphicType){
    case 0:
        processLine();
        break;
    case 1:
        processCircle();
        break;
    }

    QPixmap *pixmap = new QPixmap(QPixmap::fromImage(MyOpenCV::cvMat2QImage(GlobalVariable::matScreen)));

    label->setPixmap(*pixmap);

    label->resize(pixmap->size());
}

void DisplayView::processLine()
{
    //载入原始图和Mat变量定义
    cv::Mat matEdge;

    //进行边缘检测
    cv::Canny(GlobalVariable::matSource, matEdge, 50, 200, 3);

    cv::cvtColor(matEdge, GlobalVariable::matScreen, CV_GRAY2RGB);

    //进行霍夫线变换
    std::vector<cv::Vec4i> lines;//定义一个矢量结构lines用于存放得到的线段矢量集合
    cv::HoughLinesP(matEdge, lines, 1, CV_PI / 180, GlobalVariable::nParam, 50, 10);

    //依次在图中绘制出每条线段
    for (size_t i = 0; i < lines.size(); i++)
    {
        cv::Vec4i l = lines[i];
        cv::line(GlobalVariable::matScreen, cv::Point(l[0], l[1]), cv::Point(l[2], l[3]), cv::Scalar(255, 0, 0), 1, CV_AA);
    }
}

void DisplayView::processCircle()
{
    //载入原始图和Mat变量定义
    cv::Mat matMid;

    GlobalVariable::matSource.copyTo(GlobalVariable::matScreen);

    //转为灰度图，进行图像平滑
    cv::cvtColor(GlobalVariable::matSource, matMid, CV_RGB2GRAY);
    cv::GaussianBlur(matMid, matMid, cv::Size(9, 9), 2, 2);

    //进行霍夫圆变换
    std::vector<cv::Vec3f> circles;
    cv::HoughCircles(matMid, circles, CV_HOUGH_GRADIENT, 1.5,10 , 200, GlobalVariable::nParam, 0, 0);

    //依次在图中绘制出圆
    for (size_t i = 0; i < circles.size(); i++)
    {
        cv::Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
        int radius = cvRound(circles[i][2]);
        //绘制圆心
        cv::circle(GlobalVariable::matScreen, center, 3, cv::Scalar(0, 255, 0), -1, 8, 0);
        //绘制圆轮廓
        cv::circle(GlobalVariable::matScreen, center, radius, cv::Scalar(255, 0, 0), 3, 8, 0);
    }
}
