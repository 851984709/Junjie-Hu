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
    if(GlobalVariable::imageSource->isNull())
    {
        qDebug()<<"不满足显示条件";
        return;
    }

    emit saveEnable();

    Mat matSrc = MyOpenCV::QImage2cvMat(*GlobalVariable::imageSource);
    Mat matGray;
    Mat matDst;

    //先转化为灰度
    cvtColor(matSrc,matGray,CV_RGB2GRAY);

    //二进制阈值化与反二进制阈值化
    if(GlobalVariable::binarizationClass == true)
    {
        //将灰度图像转化为阀值图像
        threshold(matGray,matDst,GlobalVariable::nThreshold,255,THRESH_BINARY);
    }
    else{
        threshold(matGray,matDst,GlobalVariable::nThreshold,255,THRESH_BINARY_INV);
    }

    *GlobalVariable::imageScreen = MyOpenCV::cvMat2QImage(matDst);

    QPixmap *pixmap = new QPixmap(QPixmap::fromImage(*GlobalVariable::imageScreen));

    label->setPixmap(*pixmap);

    label->resize(pixmap->size());
}
