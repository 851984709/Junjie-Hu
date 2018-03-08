#include "mainwindow.h"

using namespace cv;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("图片混合");

    mnbar = menuBar();
    setMenuBar(mnbar);

    mnFile = mnbar->addMenu("文件");

    actSave = mnFile->addAction("保存");

    actSave->setEnabled(false);//默认在混合图像产生前没有保存功能

    scrollArea = new QScrollArea(this);

    label = new QLabel(this);

    setCentralWidget(scrollArea);

    scrollArea->setWidget(label);

    operationView = new OperationView(this);

    addDockWidget(Qt::LeftDockWidgetArea,operationView);

    connect(operationView,SIGNAL(blendImageChange()),this,SLOT(blendImageChange()));
    connect(actSave,SIGNAL(triggered()),this,SLOT(saveImage()));
}

MainWindow::~MainWindow()
{

}

void MainWindow::blendImageChange()
{
    if(!actSave->isEnabled())
        actSave->setEnabled(true);

    label->setPixmap(QPixmap::fromImage(*operationView->imageBlend));

    label->resize(operationView->widthBlend,operationView->heightBlend);
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
        operationView->imageBlend->save(pathName);
    }
    else{//文件后缀名不正确
        QMessageBox::warning(this,
                             "警告",
                             "文件后缀名不匹配");
    }
}
