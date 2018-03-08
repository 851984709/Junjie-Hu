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

    connect(openAction,SIGNAL(triggered()),this,SLOT(openSlot()));
    connect(saveAction,SIGNAL(triggered()),this,SLOT(saveSlot()));
    connect(grayAction,SIGNAL(triggered()),this,SLOT(graySlot()));
    connect(fourierAction,SIGNAL(triggered()),this,SLOT(fourierSlot()));
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
    if(image->format()==QImage::Format_Grayscale8)
        return;

    unsigned char *scrdata = image->bits();
    int width = image->width();
    int height = image->height();
    int bytesPerLine = (width*8+31)/32*8;//图像每行字节对齐
    unsigned char *dstdata = new unsigned char[bytesPerLine*height];//存储处理后的数据

    for(int i=0;i<height;i++)
        for(int j=0;j<width;j++)
        {
            // 灰度公式
            int gray = (int)(scrdata[2] * 0.3 + scrdata[1] * 0.59 + scrdata[0] * 0.11);

            dstdata[i*bytesPerLine+j]  = gray;

            scrdata+=4;
        }

    image= new QImage(dstdata,width,height,bytesPerLine,QImage::Format_Grayscale8);

    emit freshSignal();
}

void MainWindow::fourierSlot()
{
    Dft2 dft(*image);

    image= dft.m_dst_image;

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
