#include "operationview.h"

OperationView::OperationView(QWidget *parent) : QDockWidget(parent)
{
    widget = new QWidget(this);
    layout = new QGridLayout(widget);
    labelImage = new QLabel("图片区域",widget);
    labelName = new QLabel("图片名",widget);
    button = new QPushButton("导入图片",widget);
    labelBinarizationClass = new QLabel("二值化类型：",widget);
    combox = new QComboBox(widget);
    labelThreshold = new QLabel("阈值：",widget);
    scrollBar = new QScrollBar(Qt::Horizontal,widget);

    combox->addItem("二进制阈值化");
    combox->addItem("反二进制阈值化");

    layout->setSpacing(20);
    widget->setMaximumSize(250,250);

    labelThreshold->setText("阀值：" + QString::number(GlobalVariable::nThreshold));

    scrollBar->setMaximum(255);//设置滚动条最大值
    scrollBar->setMinimumWidth(100);//设置滚动条长度
    scrollBar->setValue(GlobalVariable::nThreshold);

    layout->addWidget(labelImage,0,0,2,1);
    layout->addWidget(labelName,0,1,1,1);
    layout->addWidget(button,1,1,1,1);
    layout->addWidget(labelBinarizationClass,2,0,1,1);
    layout->addWidget(combox,2,1,1,1);
    layout->addWidget(labelThreshold,3,0,1,1);
    layout->addWidget(scrollBar,3,1,1,1);

    setWidget(widget);

    connect(button,SIGNAL(clicked()),this,SLOT(importImage()));
    connect(scrollBar,SIGNAL(valueChanged(int)),this,SLOT(thresholdChanged(int)));
    connect(combox,SIGNAL(currentIndexChanged(int)),this,SLOT(binarizationClassChanged(int)));
}

void OperationView::getImage(QString imageName)
{
    labelName->setText(imageName);

    QPixmap *pixmap = new QPixmap(QPixmap::fromImage(GlobalVariable::imageSource->scaled(100,100)));

    labelImage->setPixmap(*pixmap);

    labelImage->resize(pixmap->size());

    button->setText("重新导入图片");

    emit refresh();
}


void OperationView::thresholdChanged(int _scrollBarValue)
{
    GlobalVariable::nThreshold = _scrollBarValue;

    labelThreshold->setText("阈值：" + QString::number(_scrollBarValue));

    emit refresh();
}

void OperationView::binarizationClassChanged(int index)
{
    if(index == 0)
        GlobalVariable::binarizationClass = true;
    else
        GlobalVariable::binarizationClass = false;

    emit refresh();
}
