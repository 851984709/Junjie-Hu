#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //创建菜单栏
    QMenuBar *mnbBar = menuBar();
    setMenuBar(mnbBar);

    //给菜单栏添加菜单
    QMenu *mnFile = mnbBar->addMenu("文件");

    //给菜单添加行为
    QAction *actOpen = mnFile->addAction("打开");

    connect(actOpen,SIGNAL(triggered()),this,SLOT(openPicture()));
}

MainWindow::~MainWindow()
{

}

bool MainWindow::openPicture()
{
    QString pathName = QFileDialog::getOpenFileName(this,
                                   "打开图片",
                                   "../",
                                   "Image(*.bmp *.jpg *.png)");

    if(pathName.isEmpty())
    {
        qDebug()<<"加载图片失败";
        return false;
    }

    ImageWidget *imagewidget = new ImageWidget();

    imagewidget->setAttribute(Qt::WA_DeleteOnClose);

    QPixmap pixmap(pathName);

    imagewidget->setWindowTitle(QFileInfo(pathName).fileName());

    imagewidget->label.setPixmap(pixmap);

    imagewidget->label.setScaledContents(true);

    imagewidget->label.resize(pixmap.width(),pixmap.height());

    imagewidget->resize(pixmap.width(),pixmap.height());

    imagewidget->show();

    return true;
}
