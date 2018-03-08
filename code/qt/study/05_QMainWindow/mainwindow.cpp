#include "mainwindow.h"
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QDebug>
#include <QToolBar>
#include <QPushButton>
#include <QStatusBar>
#include <QLabel>
#include <QTextEdit>
#include <QDockWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //1）菜单栏
    QMenuBar *mBar =  this->menuBar();
	setMenuBar(mBar);
	
    //添加菜单
    QMenu *pFile = mBar->addMenu("文件");
    QMenu *pEdit = mBar->addMenu("编辑");

    //添加菜单项，添加动作
    QAction *pNew = pFile->addAction("新建");

    connect(pNew,&QAction::triggered,
                [=]()
        {
            qDebug()<<"新建";
        }
        );

    pFile->addSeparator();//添加分割线

    QAction *pOpen = pFile->addAction("打开");

    connect(pOpen,&QAction::triggered,
            [](){
        qDebug()<<"打开";
    });

    //2）工具栏，菜单项的快捷方式
    QToolBar *toolBar = addToolBar("");

    //工具栏添加快捷键
    toolBar->addAction(pNew);

    QPushButton *b = new QPushButton(this);
    b->setText("^_^");

    //添加小控件
    toolBar->addWidget(b);

    connect(b,&QPushButton::clicked,
            [b](){
        b->setText("@_@");
    });

    //3）状态栏
    QStatusBar *sBar = statusBar();
    QLabel *label = new QLabel(this);
    label->setText("Normal text file");
    sBar->addWidget(label);
    //addWidget 从左往右添加
    sBar->addWidget(new QLabel("2",this));

    //addPermanentWidget 从右往左添加
    sBar->addPermanentWidget(new QLabel("右",this));

    //4）核心控件
    QTextEdit *textEdit = new QTextEdit(this);
    setCentralWidget(textEdit);//设置中间区域控件

    //5）浮动窗口
    QDockWidget *dock = new QDockWidget(this);
    addDockWidget(Qt::RightDockWidgetArea,dock);

    //为浮动窗口添加控件
    QTextEdit *dockEdit = new QTextEdit();
    dock->setWidget(dockEdit);

}

MainWindow::~MainWindow()
{

}
