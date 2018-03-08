#include "mainwindow.h"

using namespace cv;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowState(Qt::WindowMaximized);

    //创建菜单栏
    mnbBar = menuBar();
    setMenuBar(mnbBar);

    //给菜单栏添加菜单
    mnFile = mnbBar->addMenu("文件");
    mnEdit = mnbBar->addMenu("编辑");
    mnProcess = mnbBar->addMenu("处理");

    actOpen = mnFile->addAction("打开");
    actSave = mnFile->addAction("保存");
    actToGray = mnProcess->addAction("灰度");
    actToBlend = mnProcess->addAction("混合");

    //当当前图像为空时设置保存键为不可用
    actSave->setDisabled(true);

    //编辑视图
    imageView = new ImageView(this);

    setCentralWidget(imageView);

    //操作视图
    operationView = new OperationView(this);

    addDockWidget(Qt::LeftDockWidgetArea, operationView );
    //操作视图默认关闭
    operationView->hide();

    //资源视图
    resourceView = new ResourceView(this);

    addDockWidget(Qt::LeftDockWidgetArea, resourceView);


    //信息与槽

    //主窗口

    //文件菜单
    //打开
    connect(actOpen,SIGNAL(triggered()),this,SLOT(openImage()));
    //保存
    connect(actSave,SIGNAL(triggered()),this,SLOT(saveImage()));

    //处理菜单
    connect(actToGray,SIGNAL(triggered()),imageView,SLOT(toGray()));
    connect(actToGray,SIGNAL(triggered()),this,SLOT(toGray()));

    connect(actToBlend,SIGNAL(triggered()),this,SLOT(toBlend()));

    //资源视图
    connect(this,SIGNAL(addImage()),resourceView,SLOT(addImage()));

    connect(resourceView->listWidget,SIGNAL(customContextMenuRequested(QPoint)),
            resourceView,SLOT(customContextMenuRequested(QPoint)));

    connect(resourceView->actEdit,SIGNAL(triggered()),resourceView,SLOT(editImage()));

    connect(resourceView,SIGNAL(refresh()),imageView,SLOT(refresh()));

    connect(resourceView,SIGNAL(saveEnable()),this,SLOT(saveEnable()));

    //图像试图
    connect(resourceView->actEdit,SIGNAL(triggered(bool)),imageView,SLOT(showImage()));

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
        qDebug()<<"加载图片失败";
    }

    QString imageName = QFileInfo(pathName).baseName();

    //向全局图像列表加入图像
    Globalvariable::imageObjectList.append(ImageObject(QImage(pathName),imageName));

    emit addImage();
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
        Globalvariable::imageObjectCurrent->image->save(pathName);
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

void MainWindow::toGray()
{
    //隐藏操作视图
    operationView->hide();

    //图像视图
    if(!Globalvariable::imageObjectCurrent)
    {
        QMessageBox::warning(this,
                             "警告",
                             "当前画板没有可编辑的图像");
    }
    else
    {
        Mat mat = MyOpenCV::QImage2cvMat(*Globalvariable::imageObjectCurrent->image);

        cvtColor(mat,mat,CV_RGB2GRAY);

        *Globalvariable::imageObjectCurrent->image = MyOpenCV::cvMat2QImage(mat);

        imageView->refresh();
    }
}

void MainWindow::toBlend()
{
    //给操作窗口加载混合组件
    operationView->show();

    operationView->setWidget(operationView->blendComponent);
}
