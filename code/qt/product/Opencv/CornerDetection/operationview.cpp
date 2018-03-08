#include "operationview.h"

OperationView::OperationView(QWidget *parent) : QDockWidget(parent)
{
    widget = new QWidget(this);
    layout = new QGridLayout(widget);
    labelImage = new QLabel("图片区域",widget);
    labelName = new QLabel("图片名",widget);
    button = new QPushButton("导入图片",widget);
    labelThresh = new QLabel(widget);
    scrollBar = new QScrollBar(Qt::Horizontal,widget);

    layout->setSpacing(20);
    widget->setMaximumSize(250,250);

    labelThresh->setText("阈值：" + QString::number(GlobalVariable::nThresh));
    labelThresh->setMinimumWidth(100);

    scrollBar->setMaximum(255);//设置滚动条最大值
    scrollBar->setMinimumWidth(100);//设置滚动条长度
    scrollBar->setValue(GlobalVariable::nThresh);

    layout->addWidget(labelImage,0,0,2,1);
    layout->addWidget(labelName,0,1,1,1);
    layout->addWidget(button,1,1,1,1);
    layout->addWidget(labelThresh,2,0,1,1);
    layout->addWidget(scrollBar,2,1,1,1);

    setWidget(widget);

    connect(button,SIGNAL(clicked()),this,SLOT(importImage()));
    connect(scrollBar,SIGNAL(valueChanged(int)),this,SLOT(threshChanged(int)));
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


void OperationView::threshChanged(int _scrollBarValue)
{
    GlobalVariable::nThresh = _scrollBarValue;

    labelThresh->setText("阈值：" + QString::number(_scrollBarValue));

    emit refresh();
}
