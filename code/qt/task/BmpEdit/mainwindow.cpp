#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    button = new QPushButton(this);
    label = new QLabel(this);

    button->setText("button");
    label->setText("label");

    button->move(50,50);
    label->move(50,20);

    //给button装在事件过滤器
    button->installEventFilter(this);

    connect(button,SIGNAL(clicked()),this,SLOT(buttonClicked()));
}

MainWindow::~MainWindow()
{

}

void MainWindow::buttonClicked()
{
    //安装上按钮的事件过滤器后，这个函数就不再会被执行
    label->setText("按钮被按下");
}

//实现事件过滤
bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == button)
    {
        //过滤鼠标在按钮上的单击和双击事件
        if(event->type() == QEvent::MouseButtonPress ||
                event->type() == QEvent::MouseButtonDblClick)
            {
            //对过滤的事件的处理
            label->setText("按钮事件被过滤");

            return true;//处理完毕，整个程序不在对该消息进行处理
        }
        else
            return false;//其他事件还要继续处理
    }
    else
        //其它部件产生的事件则交给基类处理
        return MainWindow::eventFilter(watched,event);//
}
