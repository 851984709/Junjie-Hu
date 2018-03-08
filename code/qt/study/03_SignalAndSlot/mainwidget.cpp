#include "mainwidget.h"
#include <QPushButton>
#include <QDebug>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    this->setWindowTitle("主窗口");
    this->resize(QSize(300,350));

    b1.setParent(this);
    b1.setText("close");
    b1.move(QPoint(0,300));

    b2 = new QPushButton(this);
    b2->setText("^_^");
    b2->move(QPoint(200,300));

    b3.setParent(this);
    b3.setText("切换到子窗口");

    connect(&b1,&QPushButton::pressed,this,&MainWidget::close);
    /* &b1:信号发出者，指针类型
     * &QPushButton::pressed：处理的信号 &发出者的类名::信号名字
     * this：信号接收者
     * &MainWidget::close：槽函数，信号处理函数 &信号接收者的类名::槽函数名字
    */

    /*自定义槽，普通函数的用法
     * Qt5:任意的成员函数，普通全局函数，静态函数
     * 槽函数需要和信号一致（参数，返回值）
     * 由于信号都是没有返回值，所以，槽函数一定没有返回值
    */
    connect(b2,&QPushButton::released,this,&MainWidget::mySlot);

    connect(b2,SIGNAL(released()),&b1,SLOT(hide()));
    // SIGNAL 和 SLOT 要同时使用

    connect(&b3,&QPushButton::clicked,this,&MainWidget::gotoSubwidget);

//    //处理子窗口信息
//    void (SubWidget::*mySignal1)() = &SubWidget::mySignal;
//    connect(&sw,mySignal1,this,&MainWidget::dealSubwidgetSignal1);

//    void (SubWidget::*mySignal2)(int,QString) = &SubWidget::mySignal;
//    connect(&sw,mySignal2,this,&MainWidget::dealSubwidgetSignal2);

    //Qt4信号连接
    //Qt4槽函数必须有slots关键字来修饰
    connect(&sw,SIGNAL(mySignal()),this,SLOT(dealSubwidgetSignal()));
    connect(&sw,SIGNAL(mySignal(int,QString)),this,SLOT(dealSubwidgetSignal(int,QString)));
    // SIGNAL SLOT 将函数名字 -> 字符串 不进行错误检查

    //lamda表达式,匿名函数对象
    //C++11增加的新特性， 项目文件： CONFIG += C
    //Qt配合信号一起使用，非常方便

    QPushButton *b4 = new QPushButton(this);
    b4->move(150,150);
    b4->setText("Lamda表达式");
    int a=3,b=4;
    connect(b4,&QPushButton::clicked,
            // [] ：里面填写需要传入的参数，默认为只读
            // = ：把外部所有局部变量、类中所有成员以值传递方式
            // this ：类中所有成员以值传递方式
            // mutable ：使传入的参数值可以被改变
            [=](bool ischeck) mutable
    {
        b4->setText(QString::number(a+b));
        qDebug()<<ischeck;
    }
    );
}

MainWidget::~MainWidget()
{

}

void MainWidget::mySlot()
{
    b2->setText("@_@");
}

void MainWidget::gotoSubwidget()
{
    //子窗口显示
    sw.show();
    //本窗口隐藏
    this->hide();
}

void MainWidget::dealSubwidgetSignal()
{
    sw.hide();
    this->show();
}

void MainWidget::dealSubwidgetSignal(int a,QString str)
{
    //str.toUtf8() -> 字节数组QByteArray
    //data() -> QByteArray -> char *
    qDebug()<<a<<str.toUtf8().data();
}
