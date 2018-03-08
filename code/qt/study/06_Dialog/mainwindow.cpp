#include "mainwindow.h"
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QDialog>
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QMenuBar *mBar = menuBar();
    setMenuBar(mBar);
    QMenu *pDialog = mBar->addMenu("对话框");

    QAction *p1 = pDialog->addAction("模态对话框");

    connect(p1,&QAction::triggered,
            [=](){
        QDialog dlg;
        dlg.exec();
        qDebug()<<"模态对话框";
    });

    QAction *p2 = pDialog->addAction("非模态对话框");

    connect(p2,&QAction::triggered,
            [=](){
//        dlg.show();
//        //设置对话框为 MainWindow 的成员变量，只会生成1个对话框

//        QDialog *p = new QDialog(this);
//        p->show();
//        //可以生成多个对话框
//        //对话框关闭时，内存没有释放，只有当程序结束时内存才释放
//        //可能造成内存越用越少和内存泄漏

        QDialog *p = new QDialog();
        p->setAttribute(Qt::WA_DeleteOnClose);//关闭时释放内存
        p->show();
        //可以生成多个对话框

        qDebug()<<"非模态对话框";
    });

    QAction *p3 = pDialog->addAction("关于对话框");

    connect(p3,&QAction::triggered,
            [=](){
        QMessageBox::about(this,"关于对话框","关于Qt");

        qDebug()<<"关于对话框";
    });

    QAction *p4 = pDialog->addAction("问题对话框");

    connect(p4,&QAction::triggered,
            [=](){
        int ret = QMessageBox::question(this,
                                        "问题对话框","你有没有问题？"
                                        ,QMessageBox::Ok |QMessageBox::No | QMessageBox::Cancel);

        switch(ret)
        {
        case QMessageBox::Ok:
            qDebug()<<"是";
            break;
        case QMessageBox::No:
            qDebug()<<"否";
            break;
        case QMessageBox::Cancel:
            qDebug()<<"退出";
            break;
        default:
            break;
        }

        qDebug()<<"关于对话框";
    });

    QAction *p5 = pDialog->addAction("文件对话框");

    connect(p5,&QAction::triggered,
            [=](){
        QString path = QFileDialog::getOpenFileName(
                    this,
                    "文件对话框",
                    "../",//上一级路径
                    "Source(*.cpp *.h);;"
                    "Text(*.txt);;"
                    "All(*.*)"
                   );
        qDebug()<<path;

        qDebug()<<"文件对话框";
    });
}

MainWindow::~MainWindow()
{

}
