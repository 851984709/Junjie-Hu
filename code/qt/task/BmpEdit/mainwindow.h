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

#include "editdialog.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QLabel *label;
    QImage *image; // 全局image
    QMenuBar *menubar;
    QMenu *fileMenu;
    QMenu *editMenu;
    QAction *openAction;
    QAction *rectAction;

    EditDialog *editDialog;

signals:
    void freshSignal();

private slots:
    void openFileSlot();
    void freshSlot();
    void editDialogSlot();
    void rectChangeSlot(QPoint,QPoint,QColor);
};

#endif // MAINWINDOW_H
