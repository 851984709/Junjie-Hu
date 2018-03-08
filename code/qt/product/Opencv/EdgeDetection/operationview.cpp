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
    checkBox = new QCheckBox("彩色",widget);

    combox->addItem("Canney边缘检测");
    combox->addItem("Sobel边缘检测");

    layout->setSpacing(20);
    widget->setMaximumSize(250,250);

    labelParam->setText("参数值：" + QString::number(GlobalVariable::nParam));
    labelParam->setMinimumWidth(100);

    scrollBar->setMaximum(60);//设置滚动条最大值
    scrollBar->setMinimumWidth(100);//设置滚动条长度
    scrollBar->setValue(GlobalVariable::nParam);

    layout->addWidget(labelImage,0,0,2,1);
    layout->addWidget(labelName,0,1,1,1);
    layout->addWidget(button,1,1,1,1);
    layout->addWidget(labelBlurType,2,0,1,1);
    layout->addWidget(combox,2,1,1,1);
    layout->addWidget(labelParam,3,0,1,1);
    layout->addWidget(scrollBar,3,1,1,1);
    layout->addWidget(checkBox,4,0,1,2);

    setWidget(widget);

    connect(button,SIGNAL(clicked()),this,SLOT(importImage()));
    connect(scrollBar,SIGNAL(valueChanged(int)),this,SLOT(paramChanged(int)));
    connect(combox,SIGNAL(currentIndexChanged(int)),this,SLOT(OperationTypeChanged(int)));
    connect(checkBox,SIGNAL(stateChanged(int)),this,SLOT(isColorfulChanged(int)));
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

    if(GlobalVariable::operationType == OperationType::Canney)
        labelParam->setText("参数值：" + QString::number(_scrollBarValue));
    else
        labelParam->setText("参数值：" + QString::number(_scrollBarValue*2-1));

    emit refresh();
}

void OperationView::OperationTypeChanged(int index)
{
    switch(index){
    case 0:
        scrollBar->setMaximum(60);

        GlobalVariable::nParam = 1;
        scrollBar->setValue(GlobalVariable::nParam);

        GlobalVariable::operationType = OperationType::Canney;
        break;
    case 1:
        scrollBar->setMinimum(1);
        scrollBar->setMaximum(4);

        GlobalVariable::nParam = 1;
        scrollBar->setValue(GlobalVariable::nParam);

        GlobalVariable::operationType = OperationType::Sobel;
        break;
    }

    emit refresh();
}

void OperationView::isColorfulChanged(int i)
{
    if(checkBox->isChecked())
        GlobalVariable::isColorful = true;
    else
        GlobalVariable::isColorful = false;

    emit refresh();
}
