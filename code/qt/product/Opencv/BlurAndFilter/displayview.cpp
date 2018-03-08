#include "displayview.h"

using namespace cv;

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

    switch(GlobalVariable::blurType){
    case 0:
        processMeanBlur();
        break;
    case 1:
        processGaussianBlur();
        break;
    case 2:
        processMedianBlur();
        break;
    case 3:
        processBilateralFilter();
        break;
    }

    QPixmap *pixmap = new QPixmap(QPixmap::fromImage(MyOpenCV::cvMat2QImage(GlobalVariable::matScreen)));

    label->setPixmap(*pixmap);

    label->resize(pixmap->size());
}

void DisplayView::processMeanBlur()
{
    //均值滤波
    blur(GlobalVariable::matSource, GlobalVariable::matScreen,
         Size(GlobalVariable::nParam*2+1, GlobalVariable::nParam*2+1));
}

void DisplayView::processGaussianBlur()
{
    //高斯滤波
    cv::GaussianBlur(GlobalVariable::matSource, GlobalVariable::matScreen,
                     Size(GlobalVariable::nParam*2+1, GlobalVariable::nParam*2+1), 0, 0);
}

void DisplayView::processMedianBlur()
{
    //中值滤波
    medianBlur(GlobalVariable::matSource, GlobalVariable::matScreen,
               GlobalVariable::nParam*2+1);
}

void DisplayView::processBilateralFilter()
{
    bilateralFilter(GlobalVariable::matSource, GlobalVariable::matScreen,
                    GlobalVariable::nParam, GlobalVariable::nParam * 2, GlobalVariable::nParam / 2);
}
