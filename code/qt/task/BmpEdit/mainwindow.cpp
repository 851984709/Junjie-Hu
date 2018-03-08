#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    label = new QLabel(this);
    label->move(0,30);
    menubar = this->menuBar();

    fileMenu = menubar->addMenu("file");
    editMenu = menubar->addMenu("edit");

    openAction = fileMenu->addAction("openfile");
    rectAction = editMenu->addAction("rect");

    editDialog = new EditDialog();

    connect(openAction,SIGNAL(triggered()),this,SLOT(openFileSlot()));
    connect(this,SIGNAL(freshSignal()),this,SLOT(freshSlot()));
    connect(rectAction,SIGNAL(triggered()),this,SLOT(editDialogSlot()));
    connect(editDialog,SIGNAL(resultSignal(QPoint,QPoint,QColor)),this,SLOT(rectChangeSlot(QPoint,QPoint,QColor)));
}

MainWindow::~MainWindow()
{

}


void MainWindow::openFileSlot()
{
    QString path = QFileDialog::getOpenFileName(
                        this,
                        "文件对话框",
                        "../",//上一级路径
                        "Image(*.bmp *.jpg *.png)"
                       );
    image = new QImage(path);

    emit freshSignal();
}

void MainWindow::freshSlot()
{
    label->setPixmap(QPixmap::fromImage(*image));

    label->resize(image->size());
}

void MainWindow::editDialogSlot()
{
    editDialog->show();
}

void MainWindow::rectChangeSlot(QPoint startPoint,QPoint endPoint,QColor color)
{
    // Qt 打开的 bmp、jpg 图像格式为 Format_RGB32，在内存中的顺序为 B G R 0
    //    打开的 png 图像的格式为 Format_ARGB32，在内存中的顺序为 B G R A
    unsigned char *scrdata = image->bits();
    int width = image->width();
    int height = image->height();
    int bytesPerLine = image->bytesPerLine();//图像每行字节对齐
    unsigned char *dstdata = new unsigned char[bytesPerLine*height];//存储处理后的数据

    int r = color.red();
    int g = color.green();
    int b = color.blue();

    for(int i=0;i<height;i++)
        for(int j=0;j<width;j++)
        {
            if((i>=startPoint.x())&&i<endPoint.x()&&
                    (j>=startPoint.y())&&j<endPoint.y())
            {
                dstdata[i*bytesPerLine+j*4]  = b;
                dstdata[i*bytesPerLine+j*4+1]= g;
                dstdata[i*bytesPerLine+j*4+2]= r;
            }
            else{
                dstdata[i*bytesPerLine+j*4]  = scrdata[0];
                dstdata[i*bytesPerLine+j*4+1]= scrdata[1];
                dstdata[i*bytesPerLine+j*4+2]= scrdata[2];
            }
            scrdata+=4;
        }
    image= new QImage(dstdata,width,height,bytesPerLine,QImage::Format_RGB32);

    emit freshSignal();
}
