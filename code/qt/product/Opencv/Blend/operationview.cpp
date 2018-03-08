#include "operationview.h"

using namespace cv;

OperationView::OperationView(QWidget *parent) : QDockWidget(parent)
{
    setWindowTitle("操作视图");

    //分配内存
    widget = new QWidget(this);

    layout = new QGridLayout(widget);

    image1 = new QImage();
    stringName1 = new QString();
    labelImage1 = new QLabel(widget);
    buttonImageImport1 = new QPushButton("导入图片",widget);
    labelName1 = new QLabel("图片名1",widget);
    labelAlpha = new QLabel(widget);
    scrollBar1 = new QScrollBar(Qt::Horizontal,widget);
    labelImage1->setText("图片区域");
    scrollBar1->setMinimumWidth(100); //设置滚动条最小长度

    image2 = new QImage();
    stringName2 = new QString();
    labelImage2 = new QLabel(widget);
    buttonImageImport2 = new QPushButton("导入图片",widget);
    labelName2 = new QLabel("图片名2",widget);
    labelBeta = new QLabel(widget);
    scrollBar2 = new QScrollBar(Qt::Horizontal,widget);
    labelImage2->setText("图片区域");
    scrollBar2->setMinimumWidth(100); //设置滚动条最小长度

    labelWidth = new QLabel("目标图像宽度(pix):",widget);
    lineEditWidth = new QLineEdit(widget);
    buttonWidth = new QPushButton("确定",widget);
    labelHeight = new QLabel("目标图像高度(pix):",widget);
    lineEditHeight = new QLineEdit(widget);
    buttonHeight = new QPushButton("确定",widget);
    lineEditWidth->setMaximumWidth(50);
    lineEditHeight->setMaximumWidth(50);

    imageBlend = new QImage();

    //控件布局
    layout->addWidget(labelImage1,0,0,4,1);
    layout->addWidget(buttonImageImport1,0,1,1,1);
    layout->addWidget(labelName1,1,1,1,2);
    layout->addWidget(labelAlpha,2,1,1,2);
    layout->addWidget(scrollBar1,3,1,1,2);

    layout->addWidget(labelImage2,4,0,4,1);
    layout->addWidget(buttonImageImport2,4,1,1,1);
    layout->addWidget(labelName2,5,1,1,2);
    layout->addWidget(labelBeta,6,1,1,2);
    layout->addWidget(scrollBar2,6,1,1,2);

    layout->addWidget(labelWidth,8,0,1,1);
    layout->addWidget(lineEditWidth,8,1,1,1);
    layout->addWidget(buttonWidth,8,2,1,1);
    layout->addWidget(labelHeight,9,0,1,1);
    layout->addWidget(lineEditHeight,9,1,1,1);
    layout->addWidget(buttonHeight,9,2,1,1);

    //数值初始化
    alpha = 1.00;
    beta = 1.00 - alpha;
    widthBlend = 0;
    heightBlend = 0;

    labelAlpha->setText("alpha: " + QString::number(alpha,10,2));//进制，精度
    labelBeta->setText("beta: " + QString::number(beta,10,2));

    //qDebug("alpha %d",alpha);
    //qDebug("beta %d",beta);

    //设置滚动条长度和默认值
    scrollBar1->setMaximum(100);
    scrollBar2->setMaximum(100);
    scrollBar1->setValue(alpha*100);
    scrollBar2->setValue(beta*100);

    setWidget(widget);

    connect(buttonImageImport1,SIGNAL(clicked()),this,SLOT(openImage1()));
    connect(buttonImageImport2,SIGNAL(clicked()),this,SLOT(openImage2()));
    connect(scrollBar1,SIGNAL(valueChanged(int)),this,SLOT(scrollBar1ValueChanged(int)));
    connect(scrollBar2,SIGNAL(valueChanged(int)),this,SLOT(scrollBar2ValueChanged(int)));
    connect(buttonWidth,SIGNAL(clicked()),this,SLOT(widthChange()));
    connect(buttonHeight,SIGNAL(clicked()),this,SLOT(heightChange()));
}

void OperationView::scrollBar1ValueChanged(int value)
{
    alpha = (double)value / 100;
    beta = 1 - (double)alpha;

    scrollBar2->setValue(100 - value);

    //qDebug("alpha %f",alpha);
    //qDebug("beta %f",beta);

    labelAlpha->setText("alpha: " + QString::number(alpha,10,2));//进制，精度
    labelBeta->setText("beta: " + QString::number(beta,10,2));

    emit refresh();
}

void OperationView::scrollBar2ValueChanged(int value)
{
    beta = (double)value / 100;
    alpha = 1 - (double)beta;

    scrollBar1->setValue(100 - value);

    //qDebug("alpha %f",alpha);
    //qDebug("beta %f",beta);

    labelAlpha->setText("alpha: " + QString::number(alpha,10,2));
    labelBeta->setText("beta: " + QString::number(beta,10,2));

    emit refresh();
}

void OperationView::openImage1()
{
    QString pathName = QFileDialog::getOpenFileName(this,
                                       "打开图片",
                                       "../",
                                       "Image(*.bmp *.jpg *.png)");

    if(pathName.isEmpty())
    {
        QMessageBox::warning(this,"警告","图片加载失败");
        return;
    }

    //数据读入
    image1->load(pathName);
    *stringName1 = "图片名: " + QFileInfo(pathName).baseName();

    buttonImageImport1->setText("重新导入图片");
    labelImage1->setPixmap(QPixmap::fromImage(image1->scaled(QSize(100,100))));
    labelImage1->show();
    labelName1->setText(*stringName1);

    refresh();
}

void OperationView::openImage2()
{
    QString pathName = QFileDialog::getOpenFileName(this,
                                       "打开图片",
                                       "../",
                                       "Image(*.bmp *.jpg *.png)");

    if(pathName.isEmpty())
    {
        QMessageBox::warning(this,"警告","图片加载失败");
        return;
    }

    //数据读入
    image2->load(pathName);
    *stringName2 = "图片名: " + QFileInfo(pathName).baseName();

    buttonImageImport2->setText("重新导入图片");
    labelImage2->setPixmap(QPixmap::fromImage(image2->scaled(QSize(100,100))));
    labelImage2->show();
    labelName2->setText(*stringName2);

    refresh();
}

void OperationView::widthChange()
{
    if(widthBlend == 0)//初始化
    {
        if(!lineEditWidth->text().toInt())//输入框中的长度有问题
        {
            lineEditWidth->setText("");
            QMessageBox::warning(this,"警告","请输入正确的宽度");
            return;
        }
        else{
            widthBlend = lineEditWidth->text().toInt();
            buttonWidth->setText("改变");
        }
    }
    else{
        if(!lineEditWidth->text().toInt())//输入框中的长度有问题
        {
            lineEditWidth->setText(QString::number(widthBlend));
            QMessageBox::warning(this,"警告","请输入正确的宽度");
            return;
        }
        else{
            widthBlend = lineEditWidth->text().toInt();
        }
    }

    refresh();
}

void OperationView::heightChange()
{
    if(heightBlend == 0)
    {
        if(!lineEditHeight->text().toInt())
        {
            lineEditHeight->setText("");
            QMessageBox::warning(this,"警告","请输入正确的高度");
            return;
        }
        else{
            heightBlend = lineEditHeight->text().toInt();
            buttonHeight->setText("改变");
        }
    }
    else{
        if(!lineEditHeight->text().toInt())
        {
            lineEditHeight->setText(QString::number(heightBlend));
            QMessageBox::warning(this,"警告","请输入正确的高度");
            return;
        }
        else{
            heightBlend = lineEditHeight->text().toInt();

        }
    }

    refresh();
}

void OperationView::refresh()
{
    if(image1->isNull() || image2->isNull() ||
            widthBlend == 0 ||heightBlend == 0)
        {
        qDebug()<<"不满足显示条件";
        return;
    }
    else{
        Mat mat1 = MyOpenCV::QImage2cvMat(*image1);
        Mat mat2 = MyOpenCV::QImage2cvMat(*image2);

        Mat matBlend;

        //不要用Qt自带的图像处理函数，否则可能会发生很严重的问题！！！！！！！！！！！！！！！
        cv::resize(mat1,mat1,Size(widthBlend, heightBlend));
        cv::resize(mat2,mat2,Size(widthBlend, heightBlend));

        //imshow("mat1",mat1);
        //imshow("mat2",mat2);

        addWeighted(mat1,alpha,mat2,beta,0.0,matBlend);

        //imshow("matBlend",matBlend);

        *imageBlend = MyOpenCV::cvMat2QImage(matBlend);

        //给主窗口发送消息，显示混合后的图像
        emit blendImageChange();
    }
}
