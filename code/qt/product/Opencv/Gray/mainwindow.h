#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QFileDialog>
#include <QString>
#include <QImage>
#include <QPixmap>
#include <QLabel>
#include <QScrollArea>
#include <QWheelEvent>
#include <QDebug>
#include <QMessageBox>

#include <opencv2/opencv.hpp>

#include <myopencv.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QMenuBar *mnbar;

    QMenu *mnFile;
    QMenu *mnEdit;

    QAction *actOpen;
    QAction *actSave;
    QAction *actGray;

    QImage *imageResource;
    QImage *imageScreen;
    QLabel *label;

    double scaledrate;

    void wheelEvent(QWheelEvent*);

    void refresh();

private slots:
    void openImage();
    void saveImage();
    void toGray();

};
#endif // MAINWINDOW_H
