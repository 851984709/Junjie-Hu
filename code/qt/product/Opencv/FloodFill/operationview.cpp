#include "operationview.h"

OperationView::OperationView(QWidget *parent) : QDockWidget(parent)
{
    widget = new QWidget(this);
    layout = new QGridLayout(widget);
    labelImage = new QLabel("图片区域",widget);
    labelName = new QLabel("图片名",widget);
    button = new QPushButton("导入图片",widget);
    labelParamLower = new QLabel(widget);
    scrollBarLower = new QScrollBar(Qt::Horizontal,widget);
    labelParamHigher = new QLabel(widget);
    scrollBarHigher = new QScrollBar(Qt::Horizontal,widget);
    labelColorText = new QLabel("颜色(R.G.B)：",widget);
    labelColorImage = new QLabel(widget);
    textR = new OnlyNumLineEdit(widget);
    textG = new OnlyNumLineEdit(widget);
    textB = new OnlyNumLineEdit(widget);
    buttonMoreColor = new QPushButton("更多颜色",widget);

    //layout->setSpacing(20);
    widget->setMaximumSize(250,300);

    labelParamLower->setText("负差最大值：" + QString::number(GlobalVariable::lowerBrightnessDifference));
    labelParamLower->setMinimumWidth(100);

    scrollBarLower->setMaximum(40);//设置滚动条最大值
    scrollBarLower->setMinimumWidth(100);//设置滚动条长度
    scrollBarLower->setValue(GlobalVariable::lowerBrightnessDifference);

    labelParamHigher->setText("正差最大值：" + QString::number(GlobalVariable::higherBrightnessDifference));
    labelParamHigher->setMinimumWidth(100);

    scrollBarHigher->setMaximum(40);//设置滚动条最大值
    scrollBarHigher->setMinimumWidth(100);//设置滚动条长度
    scrollBarHigher->setValue(GlobalVariable::higherBrightnessDifference);

    textR->setMaximumWidth(25);
    textG->setMaximumWidth(25);
    textB->setMaximumWidth(25);
    textR->setText("0");
    textG->setText("255");
    textB->setText("0");

    QPalette palette;
    palette.setColor(QPalette::Background,
                     QColor(GlobalVariable::color[0], GlobalVariable::color[1], GlobalVariable::color[2]));//一开始是绿色
    labelColorImage->setAutoFillBackground(true);  //一定要这句，否则不行
    labelColorImage->setPalette(palette);

    layout->addWidget(labelImage,0,0,2,2);
    layout->addWidget(labelName,0,1,1,2);
    layout->addWidget(button,1,1,1,2);
    layout->addWidget(labelParamLower,2,0,1,1);
    layout->addWidget(scrollBarLower,2,1,1,3);
    layout->addWidget(labelParamHigher,3,0,1,1);
    layout->addWidget(scrollBarHigher,3,1,1,3);
    layout->addWidget(labelColorText,4,0,1,1);
    layout->addWidget(textR,4,1,1,1);
    layout->addWidget(textG,4,2,1,1);
    layout->addWidget(textB,4,3,1,1);
    layout->addWidget(buttonMoreColor,5,0,1,1);
    layout->addWidget(labelColorImage,5,2,1,1);

    setWidget(widget);

    connect(button,SIGNAL(clicked()),this,SLOT(importImage()));
    connect(scrollBarLower,SIGNAL(valueChanged(int)),this,SLOT(paramLowerChanged(int)));
    connect(scrollBarHigher,SIGNAL(valueChanged(int)),this,SLOT(paramHigherChanged(int)));
    connect(textR,SIGNAL(textExactlyChanged()),this,SLOT(colorChanged()));
    connect(textG,SIGNAL(textExactlyChanged()),this,SLOT(colorChanged()));
    connect(textB,SIGNAL(textExactlyChanged()),this,SLOT(colorChanged()));
    connect(buttonMoreColor,SIGNAL(clicked()),this,SLOT(moreColor()));
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


void OperationView::paramLowerChanged(int _scrollBarValue)
{
    GlobalVariable::lowerBrightnessDifference = _scrollBarValue;

    labelParamLower->setText("负差最大值：" + QString::number(_scrollBarValue));

    emit refresh();
}

void OperationView::paramHigherChanged(int _scrollBarValue)
{
    GlobalVariable::higherBrightnessDifference = _scrollBarValue;

    labelParamHigher->setText("正差最大值：" + QString::number(_scrollBarValue));

    emit refresh();
}

void OperationView::colorChanged()
{
    int nR = textR->text().toInt();
    int nG = textG->text().toInt();
    int nB = textB->text().toInt();

    //opencv 为 GBR，和 Qt 的顺序相反
    GlobalVariable::color[2] = nR;
    GlobalVariable::color[1] = nG;
    GlobalVariable::color[0] = nB;

    QPalette palette;
    palette.setColor(QPalette::Background,QColor(nR, nG, nB));//一开始是绿色
    labelColorImage->setPalette(palette);
}

void OperationView::moreColor()
{
    int nR = GlobalVariable::color[2];
    int nG = GlobalVariable::color[1];
    int nB = GlobalVariable::color[0];

    //默认将当前颜色作为用户首选颜色
    QColor color = QColorDialog::getColor(QColor(nR,nG,nB),this);

    textR->setText(QString::number(color.red()));
    textG->setText(QString::number(color.green()));
    textB->setText(QString::number(color.blue()));

    colorChanged();
}
