#include "imageview.h"

using namespace cv;

ImageView::ImageView(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("资源视图");

    layout = new QGridLayout(this);

    //滚动条区域
    scrollArea = new QScrollArea(this);

    scrollArea->setBackgroundRole(QPalette::Dark);

    layout->addWidget(scrollArea);//将滚动条区域放在窗口布局中，以铺满整个窗口

    //标签
    label = new QLabel(this);

    scrollArea->setWidget(label);
}

void ImageView::showImage()
{
    QPixmap *pixmap =
            new QPixmap(QPixmap::fromImage(*Globalvariable::imageObjectCurrent->image));

    //将图片绘制到 label 控件上
    label->setPixmap(*pixmap);

    //设置 label 为尺寸可随图片大小变化而变化
    label->setScaledContents(true);

    //使 label 大小和图像大小相同
    label->resize(pixmap->width(),pixmap->height());

    //this->resize(pixmap->width(),pixmap->height());
}

void ImageView::refresh()
{
    QPixmap *pixmap = new QPixmap(QPixmap::fromImage(*Globalvariable::imageObjectCurrent->image));

    //将图片绘制到 label 控件上
    label->setPixmap(*pixmap);

    if(label->size()!=pixmap->size())
    {
        label->resize(pixmap->width(),pixmap->height());

        //this->resize(pixmap->width(),pixmap->height());
    }
}

void ImageView::toGray()
{

    //imshow("Gray",mat);
}
