#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include <QFileInfo>

#include "displayview.h"
#include "operationview.h"
#include "globalvariable.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    //菜单
    QMenuBar *mnBar;
    QMenu *mnFile;
    QAction *actOpen;
    QAction *actSave;

    //显示试图
    DisplayView *displayView;

    //操作视图
    OperationView *operationView;

signals:
    void getImage(QString);

public slots:
    void openImage();
    void saveImage();
    void saveEnable();
};

#endif // MAINWINDOW_H
