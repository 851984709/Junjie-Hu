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
    labelStructElementSize = new QLabel(widget);
    scrollBarStructElementSize = new QScrollBar(Qt::Horizontal,widget);
    labelIteration = new QLabel(widget);
    scrollBarIteration = new QScrollBar(Qt::Horizontal,widget);

    combox->addItem("膨胀");
    combox->addItem("腐蚀");

    layout->setSpacing(20);
    widget->setMaximumSize(250,250);

    labelStructElementSize->setText("内核尺寸：" + QString::number(GlobalVariable::nStructElementSize));
    labelStructElementSize->setMinimumWidth(100);

    labelIteration->setText("迭代次数：" + QString::number(GlobalVariable::niteration));
    labelIteration->setMinimumWidth(100);

    scrollBarStructElementSize->setMaximum(20);//设置内核尺寸最大值
    scrollBarStructElementSize->setMinimumWidth(100);//设置滚动条长度
    scrollBarStructElementSize->setValue(GlobalVariable::nStructElementSize);

    scrollBarIteration->setMaximum(10);//设置迭代次数最大值
    scrollBarIteration->setMinimumWidth(100);//设置滚动条长度
    scrollBarIteration->setValue(GlobalVariable::niteration);

    layout->addWidget(labelImage,0,0,2,1);
    layout->addWidget(labelName,0,1,1,1);
    layout->addWidget(button,1,1,1,1);
    layout->addWidget(labelBlurType,2,0,1,1);
    layout->addWidget(combox,2,1,1,1);
    layout->addWidget(labelStructElementSize,3,0,1,1);
    layout->addWidget(scrollBarStructElementSize,3,1,1,1);
    layout->addWidget(labelIteration,4,0,1,1);
    layout->addWidget(scrollBarIteration,4,1,1,1);

    setWidget(widget);

    connect(button,SIGNAL(clicked()),this,SLOT(importImage()));
    connect(scrollBarStructElementSize,SIGNAL(valueChanged(int)),this,SLOT(structElementSizeChanged(int)));
    connect(scrollBarIteration,SIGNAL(valueChanged(int)),this,SLOT(iterationChanged(int)));
    connect(combox,SIGNAL(currentIndexChanged(int)),this,SLOT(operationTypeChanged(int)));
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


void OperationView::structElementSizeChanged(int _scrollBarValue)
{
    GlobalVariable::nStructElementSize = _scrollBarValue;

    labelStructElementSize->setText("参数值：" + QString::number(_scrollBarValue));

    emit refresh();
}

void OperationView::iterationChanged(int _scrollBarValue)
{
    GlobalVariable::niteration = _scrollBarValue;

    labelIteration->setText("参数值：" + QString::number(_scrollBarValue));

    emit refresh();
}

void OperationView::operationTypeChanged(int index)
{
    switch(index){
    case 0:
        GlobalVariable::operationType = OperationType::Dilation;
        break;
    case 1:
        GlobalVariable::operationType = OperationType::Erosion;
        break;
    }

    emit refresh();
}
