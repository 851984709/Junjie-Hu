#include "displayview.h"

DisplayView::DisplayView(QWidget *parent) : QScrollArea(parent)
{
    setBackgroundRole(QPalette::Dark);
    label = new TouchableLabel(this);

    setWidget(label);

    connect(label,SIGNAL(mouseLeftButtonPress(QPoint)),this,SLOT(floodFill(QPoint)));
    connect(this,SIGNAL(floodFilled()),this,SLOT(refresh()));
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

    QPixmap *pixmap = new QPixmap(QPixmap::fromImage(MyOpenCV::cvMat2QImage(GlobalVariable::matScreen)));

    label->setPixmap(*pixmap);

    label->resize(pixmap->size());
}

void DisplayView::floodFill(QPoint pos)
{
    int lowerParam = GlobalVariable::lowerBrightnessDifference;
    int higherParam = GlobalVariable::higherBrightnessDifference;

    cv::floodFill(GlobalVariable::matScreen,cv::Point(pos.x(), pos.y()),GlobalVariable::color, 0,
                  cv::Scalar(lowerParam, lowerParam, lowerParam),
                  cv::Scalar(higherParam, higherParam, higherParam));

    emit floodFilled();
}
