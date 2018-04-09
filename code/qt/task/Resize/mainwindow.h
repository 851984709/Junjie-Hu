#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <Qlabel>
#include <QPixmap>
#include <QImage>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QFileDialog>
#include <QString>
#include <QPoint>
#include <QDebug>
#include <QScrollArea>
#include <QTime>

#include "editdialog.h"
#include "D:\code\Qt\MyCV\mycv.h"
#include "D:\code\Qt\MyCV\mymath.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QScrollArea *scrollarea;
    QLabel *label;
    QMenuBar *menubar;
    QMenu *fileMenu;
    QMenu *editMenu;

    QAction *grayAction;
    QAction *openAction;
    QAction *editAction;

    EditDialog *editDialog;

    QImage *image; // 全局image
    QImage *image_screen;

    int method=0;

signals:
    void freshSignal();

private slots:
    void openFileSlot();
    void freshSlot();
    void graySlot();
    void editDialogSlot();
    void ResizeSlot(int width,int height);
    void MethodChangeSlot(int method_index);
};

#endif // MAINWINDOW_H
