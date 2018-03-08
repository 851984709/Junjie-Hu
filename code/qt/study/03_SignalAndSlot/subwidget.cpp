#include "subwidget.h"
#include "mainwidget.h"

SubWidget::SubWidget(QWidget *parent) : QWidget(parent)
{
    this->setWindowTitle("子窗口");
    this->resize(QSize(300,350));

    b.setParent(this);
    b.setText("切换到主窗口");

    connect(&b,&QPushButton::clicked,this,&SubWidget::sendSlot);
}

SubWidget::~SubWidget()
{

}

void SubWidget::sendSlot()
{
    emit mySignal();
    emit mySignal(250,"我是子窗口");
}
