#include "blendcomponent.h"

BlendComponent::BlendComponent(QWidget *parent) : QWidget(parent)
{
    //开辟内存
    labelImage1 = new QLabel(this);
    labelImage2 = new QLabel(this);

    button1 = new QPushButton("导入图片",this);
    button2 = new QPushButton("导入图片",this);

    labelName1 = new QLabel(this);
    labelName2 = new QLabel(this);

    scrollBar1 = new QScrollBar(Qt::Horizontal, this);//水平滚动条
    scrollBar2 = new QScrollBar(Qt::Horizontal, this);

    resourceSelectDialog = new ResourceSelectDialog(this);

    //设置位置和大小
    labelImage1->move(10,10);
    button1->move(20,50);
    labelName1->move(120,20);
    scrollBar1->move(120,80);

    labelImage2->move(10,120);
    button2->move(20,160);
    labelName2->move(120,130);
    scrollBar2->move(120,190);

    labelName1->setText("labelName1");
    labelName2->setText("labelName2");

    QPixmap *pixmap1 = new QPixmap(QPixmap::fromImage(QImage("D:/code/Qt/10_Opencv/Opencv/琪亚娜.bmp")));
    QPixmap *pixmap2 = new QPixmap(*pixmap1);

    *pixmap1 = pixmap1->scaled(QSize(100,100));
    *pixmap2 = pixmap2->scaled(QSize(100,100));

    labelImage1->setPixmap(*pixmap1);
    labelImage2->setPixmap(*pixmap2);

    //最开始影藏图片标签，显示按钮
    labelImage1->hide();
    labelImage2->hide();

    //固定窗体大小
    setMaximumSize(QSize(230,230));
    setMinimumSize(QSize(230,230));

    connect(button1,SIGNAL(clicked()),this,SLOT(resourceSelect()));
    connect(resourceSelectDialog,SIGNAL(okClicked()),this,SLOT(okClicked()));
}

void BlendComponent::resourceSelect()
{
    if(Globalvariable::imageObjectList.isEmpty())
    {
        QMessageBox::warning(this,"警告","当前资源视图中没有资源");
    }
    else{
        resourceSelectDialog->initListWidget();
        resourceSelectDialog->show();
    }
}

void BlendComponent::okClicked()
{
    labelImage1->setPixmap(QPixmap::fromImage(*Globalvariable::imageBlend1->image).scaled(QSize(100,100)));
    labelImage1->show();

    button1->hide();

    labelName1->setText(*Globalvariable::imageBlend1->imageName);
}
