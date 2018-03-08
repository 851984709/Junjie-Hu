#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    int ret = QMessageBox::question(this,"问题","你有问题吗？");

    switch(ret)
    {
    case QMessageBox::Yes:
        qDebug()<<"是";
        break;
    case QMessageBox::No:
        qDebug()<<"否";
        break;
    default:
        break;
    }
}
