#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QWidget>
#include <QPixmap>
#include <QDebug>
#include <QFileDialog>
#include <QDockWidget>
#include <QListWidget>
#include <QList>
#include <QFileInfo>
#include <QTabWidget>

#include <opencv2/opencv.hpp>

#include "resourceview.h"
#include "imageview.h"
#include "operationview.h"
#include "globalvariable.h"

#include "myopencv.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    //菜单栏
    QMenuBar *mnbBar;

    //给菜单栏添加菜单
    QMenu *mnFile;
    QMenu *mnEdit;
    QMenu *mnProcess;

    QAction *actOpen;
    QAction *actSave;
    QAction *actToGray;
    QAction *actToBlend;

    ImageView *imageView;//编辑视图

    ResourceView *resourceView;//资源视图

    OperationView *operationView;//操作视图
signals:
    void addImage();

private slots:
    void openImage();
    void saveImage();
    void saveEnable();
    void toGray();
    void toBlend();
};

#endif // MAINWINDOW_H
