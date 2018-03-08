#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //初始化菜单
    mnBar = menuBar();
    setMenuBar(mnBar);
    mnFile = mnBar->addMenu("文件");
    actOpen = mnFile->addAction("打开");
    actSave = mnFile->addAction("保存");

    //初始化显示试图
    displayView = new DisplayView(this);
    setCentralWidget(displayView);

    //初始化操作视图
    operationView = new OperationView(this);
    addDockWidget(Qt::LeftDockWidgetArea,operationView);

    //有操作结果之前无法进行保存操作
    actSave->setEnabled(false);

    connect(actOpen,SIGNAL(triggered()),this,SLOT(openImage()));
    connect(operationView->button,SIGNAL(clicked()),this,SLOT(openImage()));
    connect(actSave,SIGNAL(triggered()),this,SLOT(saveImage()));
    connect(this,SIGNAL(getImage(QString)),operationView,SLOT(getImage(QString)));
    connect(operationView,SIGNAL(refresh()),displayView,SLOT(refresh()));
    connect(displayView,SIGNAL(saveEnable()),this,SLOT(saveEnable()));
}

MainWindow::~MainWindow()
{

}

void MainWindow::openImage()
{
    QString pathName = QFileDialog::getOpenFileName(this,
                                                        "打开图片",
                                                        "../",
                                                        "Image(*.bmp *.jpg *.png)");
    if(pathName.isEmpty())
    {
        QMessageBox::warning(this,"警告",
                             "图片加载失败");
        return;
    }
    else{//导入图片成功
        GlobalVariable::matSource = cv::imread((const char *)pathName.toLocal8Bit());
        // (const char *) 和 .toLocal8Bit() 使 OpenCV 能打开和保存中文件路径图片

        QString imageName = QFileInfo(pathName).baseName();

        emit getImage(imageName);
    }
}

void MainWindow::saveImage()
{
    QString pathName = QFileDialog::getSaveFileName(this,
                                                            "保存图片",
                                                            "../",
                                                            "Image(*.bmp *.jpg *.png)");
    QString fileSuffix = QFileInfo(pathName).suffix();

    if((fileSuffix == "bmp") ||
            (fileSuffix == "jpg") ||
            (fileSuffix == "png"))//文件后缀名正确
    {
        cv::imwrite((const char *)pathName.toLocal8Bit(),GlobalVariable::matScreen);
    }
    else{//文件后缀名不正确
        QMessageBox::warning(this,
                             "警告",
                             "文件后缀名不匹配");
    }
}

void MainWindow::saveEnable()
{
    actSave->setEnabled(true);
}
