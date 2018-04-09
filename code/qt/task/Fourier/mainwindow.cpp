#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    label = new QLabel(this);
    label->move(0,30);

    mnbar = menuBar();
    setMenuBar(mnbar);

    fileMenu = mnbar->addMenu("File");
    editMenu = mnbar->addMenu("Edit");

    openAction = fileMenu->addAction("Open");
    saveAction = fileMenu->addAction("Save");
    grayAction = editMenu->addAction("Gray");
    fourierAction = editMenu->addAction("Fourier");
    ifourierAction = editMenu->addAction("iFourier");

    connect(openAction,SIGNAL(triggered()),this,SLOT(openSlot()));
    connect(saveAction,SIGNAL(triggered()),this,SLOT(saveSlot()));
    connect(grayAction,SIGNAL(triggered()),this,SLOT(graySlot()));
    connect(fourierAction,SIGNAL(triggered()),this,SLOT(fourierSlot()));
    connect(ifourierAction,SIGNAL(triggered()),this,SLOT(ifourierSlot()));
    connect(this,SIGNAL(freshSignal()),this,SLOT(freshSlot()));
}

MainWindow::~MainWindow()
{

}

void MainWindow::openSlot()
{
    QString path = QFileDialog::getOpenFileName(
                            this,
                            "文件对话框",
                            "../",//上一级路径
                            "Image(*.bmp *.jpg *.png)"
                           );
    image = new QImage(path);// RGB32

    emit freshSignal();
}

void MainWindow::graySlot()
{
    MyImage *scrimage = new MyImage(*image);

    MyImage *dstimage = MyCV::Gray(*scrimage);

    image = MyImage::MyImage2QImage(*dstimage);

    emit freshSignal();
}

void MainWindow::fourierSlot()
{
    MyImage *scrimage = new MyImage(*image);

    MyMat2 *mymat2 = MyImage::MyImage2MyMat2(*scrimage);

    dft2_data = MyMath::Dft2(*mymat2);

    MyImage *dstimage = MyCV::Dft22MyImage(dft2_data,
                                           image->width(),
                                           image->height());

    image = MyImage::MyImage2QImage(*dstimage);

    emit freshSignal();
}

void MainWindow::ifourierSlot()
{
    MyMat2* dstmat2 = MyMath::Idft2(dft2_data,
                                    image->width(),
                                    image->height());

    MyImage* dstimage = new MyImage(*dstmat2);

    image = MyImage::MyImage2QImage(*dstimage);

    emit freshSignal();
}


void MainWindow::freshSlot()
{
    label->setPixmap(QPixmap::fromImage(*image));
    label->resize(image->size());
//    this->resize(image->size());
}

void MainWindow::saveSlot()
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
        image->save(pathName);
    }
    else{//文件后缀名不正确
        QMessageBox::warning(this,
                             "警告",
                             "文件后缀名不匹配");
    }
}
