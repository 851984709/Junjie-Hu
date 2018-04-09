#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    scrollarea = new QScrollArea(this);
    label = new QLabel(this);
    menubar = this->menuBar();

    setBackgroundRole(QPalette::Dark);
    scrollarea->setWidget(label);
    setCentralWidget(scrollarea);

    fileMenu = menubar->addMenu("file");
    editMenu = menubar->addMenu("edit");

    grayAction = editMenu->addAction("Gray");
    openAction = fileMenu->addAction("openfile");
    editAction = editMenu->addAction("edit");

    editDialog = new EditDialog();

    connect(grayAction,SIGNAL(triggered()),this,SLOT(graySlot()));
    connect(openAction,SIGNAL(triggered()),this,SLOT(openFileSlot()));
    connect(editAction,SIGNAL(triggered()),this,SLOT(editDialogSlot()));
    connect(editDialog,SIGNAL(resultSignal(int,int)),SLOT(ResizeSlot(int,int)));
    connect(editDialog->combobox,SIGNAL(currentIndexChanged(int)),this,SLOT(MethodChangeSlot(int)));
    connect(this,SIGNAL(freshSignal()),this,SLOT(freshSlot()));
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
    image_screen = new QImage(path);

    editDialog->widthText->setText(QString::number(image_screen->width()));
    editDialog->heightText->setText(QString::number(image_screen->height()));

    emit freshSignal();
}

void MainWindow::freshSlot()
{
    label->setPixmap(QPixmap::fromImage(*image_screen));

    label->resize(image_screen->size());
}

void MainWindow::editDialogSlot()
{
    editDialog->show();
}

void MainWindow::graySlot()
{
    MyImage scrimage = MyImage(*image);

    MyImage dstimage = MyCV::Gray(scrimage);

    image = new QImage(MyImage::MyImage2QImage(dstimage));
    image_screen =  new QImage(MyImage::MyImage2QImage(dstimage));

    emit freshSignal();
}

void MainWindow::ResizeSlot(int width, int height)
{
    MyImage scr_myimage = MyImage(*image);
    MyImage dst_myimage;

    QTime time;
    time.start();

    switch(method)
    {
    case 0:
        MyCV::Resize2NearPoint(scr_myimage,dst_myimage,width,height);
        break;
    case 1:
        MyCV::Resize2BiLinear(scr_myimage,dst_myimage,width,height);
        break;
    }

    qDebug()<<time.elapsed()<<" ms";

    image_screen = new QImage(MyImage::MyImage2QImage(dst_myimage));

    emit freshSignal();
}

void MainWindow::MethodChangeSlot(int method_index)
{
    method = method_index;
}
