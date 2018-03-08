#include "displayview.h"

DisplayView::DisplayView(QWidget *parent) : QScrollArea(parent)
{
    setBackgroundRole(QPalette::Dark);
    label = new QLabel(this);

    setWidget(label);
}

void DisplayView::refresh()
{
    //判断是否有可供处理的图片
    if(GlobalVariable::matSource.empty())
    {
        qDebug()<<"不满足显示条件";
        return;
    }

    emit saveEnable();

    switch(GlobalVariable::operationType){
    case 0:
        processCanney();
        break;
    case 1:
        processSobel();
        break;
    }

    QPixmap pixmap = QPixmap(QPixmap::fromImage(MyOpenCV::cvMat2QImage(GlobalVariable::matScreen)));

    label->setPixmap(pixmap);

    label->resize(pixmap.size());
}

void DisplayView::processCanney()
{

    if(GlobalVariable::isColorful == false)//黑白
    {
        cv::Mat matGray;

        cv::cvtColor(GlobalVariable::matSource, matGray, CV_RGB2GRAY);//转成灰度

        cv::blur(matGray, matGray, cv::Size(3, 3));//降噪

        cv::Canny(matGray, GlobalVariable::matScreen, GlobalVariable::nParam, GlobalVariable::nParam*3, 3);
    }
    else{//彩色
        cv::Mat matGray;
        cv::Mat matEdge;

        cv::cvtColor(GlobalVariable::matSource, matGray, CV_RGB2GRAY);//转成灰度

        cv::blur(matGray, matGray, cv::Size(3, 3));//降噪

        cv::Canny(matGray, matEdge, GlobalVariable::nParam, GlobalVariable::nParam*3, 3);//边缘检测

        // copyto 函数只是将 scr 添加到 dst 上，dst 图像上原有内容不会被清空
        //因此使用 copyto 函数之前要先使用 release 函数释放 dst
        GlobalVariable::matScreen.release();
        GlobalVariable::matSource.copyTo(GlobalVariable::matScreen, matEdge);
    }
}

void DisplayView::processSobel()
{
    if(GlobalVariable::isColorful == false)//黑白
    {
        cv::Mat matX, matY;
        cv::Mat abs_matX, abs_matY;

        //求 X方向梯度
        cv::Sobel(GlobalVariable::matSource, matX, CV_16S, 1, 0, GlobalVariable::nParam*2-1, 1, 1, cv::BORDER_DEFAULT );
        cv::convertScaleAbs( matX, abs_matX );

        //求Y方向梯度
        cv::Sobel( GlobalVariable::matSource, matY, CV_16S, 0, 1, GlobalVariable::nParam*2-1, 1, 1, cv::BORDER_DEFAULT );
        cv::convertScaleAbs( matY, abs_matY );

        //合并梯度(近似)
        cv::addWeighted( abs_matX, 0.5, abs_matY, 0.5, 0, GlobalVariable::matScreen );

        cvtColor(GlobalVariable::matScreen, GlobalVariable::matScreen, CV_RGB2GRAY);//转成灰度
    }
    else{//彩色
        cv::Mat matX, matY;
        cv::Mat abs_matX, abs_matY,dst;


        //求 X方向梯度
        cv::Sobel(GlobalVariable::matSource, matX, CV_16S, 1, 0, GlobalVariable::nParam*2-1, 1, 1, cv::BORDER_DEFAULT );
        cv::convertScaleAbs( matX, abs_matX );

        //求Y方向梯度
        cv::Sobel( GlobalVariable::matSource, matY, CV_16S, 0, 1, GlobalVariable::nParam*2-1, 1, 1, cv::BORDER_DEFAULT );
        cv::convertScaleAbs( matY, abs_matY );

        //合并梯度(近似)
        cv::addWeighted( abs_matX, 0.5, abs_matY, 0.5, 0, GlobalVariable::matScreen );
    }
}
