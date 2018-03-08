#include "mainwindow.h"

using namespace cv;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    mnbar = menuBar();
    setMenuBar(mnbar);

    mnFile = mnbar->addMenu("文件");
    mnEdit = mnbar->addMenu("编辑");

    actOpen = mnFile->addAction("打开");
    actSave = mnFile->addAction("保存");
    actGray = mnEdit->addAction("灰度");

    label = new QLabel(this);

    setCentralWidget(label);

    scaledrate = 1;

    actSave->setEnabled(false);

    connect(actOpen,SIGNAL(triggered()),this,SLOT(openImage()));
    connect(actSave,SIGNAL(triggered()),this,SLOT(saveImage()));
    connect(actGray,SIGNAL(triggered()),this,SLOT(toGray()));
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

    actSave->setEnabled(true);

    imageResource = new QImage(pathName);

    refresh();
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
        imageResource->save(pathName);
    }
    else{//文件后缀名不正确
        QMessageBox::warning(this,
                             "警告",
                             "文件后缀名不匹配");
    }
}

void MainWindow::toGray()
{
    Mat mat = MyOpenCV::QImage2cvMat((*imageResource));

    cvtColor(mat,mat,CV_RGB2GRAY);

    *imageResource = MyOpenCV::cvMat2QImage(mat);

    refresh();
}

void MainWindow::refresh()
{
    *imageScreen = imageResource->scaled(QSize(imageResource->width()*scaledrate,
                                              imageResource->height()*scaledrate));

    QPixmap *pixmap = new QPixmap(QPixmap::fromImage(*imageScreen));

    label->setPixmap(*pixmap);

    label->resize(pixmap->width(),pixmap->height());
}


void MainWindow::wheelEvent(QWheelEvent *event)
{
    if(imageResource)
    {
        if(event->delta()>0)//放大
        {
            scaledrate *= 1.1;
        }
        else{//缩小
            scaledrate /= 1.1;
        }
        refresh();
    }

    event->ignore();
}
