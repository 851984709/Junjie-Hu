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

    //初始化目标 Mat
    GlobalVariable::matScreen.release();
    GlobalVariable::matScreen = GlobalVariable::matSource.clone();

    //获取源图像的灰度图像
    cv::Mat matGray;
    cv::Mat matCornerStrength;
    cv::Mat matNormalize;

    cv::cvtColor(GlobalVariable::matSource,matGray,CV_RGB2GRAY);

    //进行Harris角点检测找出角点强度
    cv::cornerHarris(matGray,matCornerStrength,2,3,0.01);
    //经 cornerHarris 函数转化后的图像类型为 CV_32FC1

    //使用归一化函数将数据线性变化到 0 - 255 范围内
    cv::normalize(matCornerStrength,matNormalize,0,255,cv::NORM_MINMAX);//使用 normalize 归一化后，mat 的 type 不变

    //将归一化后的图线性变换成8位无符号整型
    convertScaleAbs( matNormalize, matNormalize );//先缩放元素再取绝对值，最后转换格式为8bit型

    // 将检测到的，且符合阈值条件的角点绘制出来
    for(int i = 0;i<matNormalize.rows;i++)
        for(int j = 0;j<matNormalize.cols;j++)
        {
            if(matNormalize.at<uchar>(i,j) >= GlobalVariable::nThresh)
            {
                //把角点圈出来
                cv::circle(GlobalVariable::matScreen,cv::Point(j,i),5,cv::Scalar(255,0,0));
                //Point的参数为 (x,y),和 rows 与 cols 相反
            }
        }

    QPixmap *pixmap = new QPixmap(QPixmap::fromImage(MyOpenCV::cvMat2QImage(GlobalVariable::matScreen)));

    label->setPixmap(*pixmap);

    label->resize(pixmap->size());
}
