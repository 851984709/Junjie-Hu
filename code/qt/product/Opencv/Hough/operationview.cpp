#include "operationview.h"

OperationView::OperationView(QWidget *parent) : QDockWidget(parent)
{
    widget = new QWidget(this);
    layout = new QGridLayout(widget);
    labelImage = new QLabel("图片区域",widget);
    labelName = new QLabel("图片名",widget);
    button = new QPushButton("导入图片",widget);
    labelGraphicType = new QLabel("图形类型：",widget);
    combox = new QComboBox(widget);
    labelParam = new QLabel(widget);
    scrollBar = new QScrollBar(Qt::Horizontal,widget);

    combox->addItem("线段");
    combox->addItem("圆");

    layout->setSpacing(20);
    widget->setMaximumSize(250,250);

    labelParam->setText("参数值：" + QString::number(GlobalVariable::nParam));
    labelParam->setMinimumWidth(100);

    scrollBar->setMinimum(1);//设置滚动条最小值
    scrollBar->setMaximum(200);//设置滚动条最大值
    scrollBar->setMinimumWidth(100);//设置滚动条长度
    scrollBar->setValue(GlobalVariable::nParam);

    layout->addWidget(labelImage,0,0,2,1);
    layout->addWidget(labelName,0,1,1,1);
    layout->addWidget(button,1,1,1,1);
    layout->addWidget(labelGraphicType,2,0,1,1);
    layout->addWidget(combox,2,1,1,1);
    layout->addWidget(labelParam,3,0,1,1);
    layout->addWidget(scrollBar,3,1,1,1);

    setWidget(widget);

    connect(button,SIGNAL(clicked()),this,SLOT(importImage()));
    connect(scrollBar,SIGNAL(valueChanged(int)),this,SLOT(paramChanged(int)));
    connect(combox,SIGNAL(currentIndexChanged(int)),this,SLOT(graphicTypeChanged(int)));
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

void OperationView::graphicTypeChanged(int index)
{
    switch(index){
    case 0:
        GlobalVariable::graphicType = GraphicType::Line;
        break;
    case 1:
        GlobalVariable::graphicType = GraphicType::Circle;
        break;
    }

    emit refresh();
}
