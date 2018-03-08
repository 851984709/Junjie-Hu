#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QScrollArea>
#include <QFileDialog>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp> // resize()

#include "operationview.h"
#include "myopencv.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QMenuBar *mnbar;
    QMenu *mnFile;

    QAction *actSave;

    QScrollArea *scrollArea;
    QLabel *label;

    OperationView *operationView;

public slots:
    void blendImageChange();
    void saveImage();
};

#endif // MAINWINDOW_H
