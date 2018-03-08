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

    switch(GlobalVariable::operationType){
    case 0:
        processDilation();
        break;
    case 1:
        processErosion();
        break;
    }

    QPixmap *pixmap = new QPixmap(QPixmap::fromImage(MyOpenCV::cvMat2QImage(GlobalVariable::matScreen)));

    label->setPixmap(*pixmap);

    label->resize(pixmap->size());
}

void DisplayView::processDilation()
{
    if(GlobalVariable::nStructElementSize == 0 || GlobalVariable::niteration == 0)
    {
        GlobalVariable::matScreen = GlobalVariable::matSource.clone();
    }
    else{
        //获取自定义核
        Mat kernelRect = getStructuringElement(MORPH_RECT,
            Size(2*GlobalVariable::nStructElementSize,2*GlobalVariable::nStructElementSize));

        //膨胀
        dilate(GlobalVariable::matSource, GlobalVariable::matScreen, kernelRect,Point(-1,-1),GlobalVariable::niteration);
    }
}

void DisplayView::processErosion()
{
    if(GlobalVariable::nStructElementSize == 0 || GlobalVariable::niteration == 0)
    {
        GlobalVariable::matScreen = GlobalVariable::matSource.clone();
    }
    else{
        //获取自定义核
        Mat kernelRect = getStructuringElement(MORPH_RECT,
            Size(2*GlobalVariable::nStructElementSize,2*GlobalVariable::nStructElementSize));

        //腐蚀
        erode(GlobalVariable::matSource, GlobalVariable::matScreen, kernelRect,Point(-1,-1),GlobalVariable::niteration);
    }
}
