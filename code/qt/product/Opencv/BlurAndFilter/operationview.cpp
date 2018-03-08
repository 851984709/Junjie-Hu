#include "operationview.h"

OperationView::OperationView(QWidget *parent) : QDockWidget(parent)
{
    widget = new QWidget(this);
    layout = new QGridLayout(widget);
    labelImage = new QLabel("图片区域",widget);
    labelName = new QLabel("图片名",widget);
    button = new QPushButton("导入图片",widget);
    labelBlurType = new QLabel("模糊类型：",widget);
    combox = new QComboBox(widget);
    labelParam = new QLabel(widget);
    scrollBar = new QScrollBar(Qt::Horizontal,widget);

    combox->addItem("均值滤波");
    combox->addItem("高斯滤波");
    combox->addItem("中值滤波");
    combox->addItem("双边滤波");

    layout->setSpacing(20);
    widget->setMaximumSize(250,250);

    labelParam->setText("参数值：" + QString::number(GlobalVariable::nParam));
    labelParam->setMinimumWidth(100);

    scrollBar->setMaximum(40);//设置滚动条最大值
    scrollBar->setMinimumWidth(100);//设置滚动条长度
    scrollBar->setValue(GlobalVariable::nParam);

    layout->addWidget(labelImage,0,0,2,1);
    layout->addWidget(labelName,0,1,1,1);
    layout->addWidget(button,1,1,1,1);
    layout->addWidget(labelBlurType,2,0,1,1);
    layout->addWidget(combox,2,1,1,1);
    layout->addWidget(labelParam,3,0,1,1);
    layout->addWidget(scrollBar,3,1,1,1);

    setWidget(widget);

    connect(button,SIGNAL(clicked()),this,SLOT(importImage()));
    connect(scrollBar,SIGNAL(valueChanged(int)),this,SLOT(paramChanged(int)));
    connect(combox,SIGNAL(currentIndexChanged(int)),this,SLOT(blurTypeChanged(int)));
}

void OperationView::getImage(QString imageName)
{
    labelName->setText(imageName);

    QPixmap *pixmap = new QPixmap(QPixmap::fromImage(MyOpenCV::cvMat2QImage(GlobalVariable::matSource).scaled(100,100)));

    labelImage->setPixmap(*pixmap);

    labelImage->resize(pixmap->size());

    button->setText("重新导入图片");

    emit refresh();
}


void OperationView::paramChanged(int _scrollBarValue)
{
    GlobalVariable::nParam = _scrollBarValue;

    labelParam->setText("参数值：" + QString::number(_scrollBarValue));

    emit refresh();
}

void OperationView::blurTypeChanged(int index)
{
    switch(index){
    case 0:
        GlobalVariable::blurType = BlurType::MeanBlur;
        break;
    case 1:
        GlobalVariable::blurType = BlurType::GaussianBlur;
        break;
    case 2:
        GlobalVariable::blurType = BlurType::MedianBlur;
        break;
    case 3:
        GlobalVariable::blurType = BlurType::BilateralFilter;
    }

    emit refresh();
}
