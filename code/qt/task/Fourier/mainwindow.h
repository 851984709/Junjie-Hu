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
#include <QDebug>
#include <QMessageBox>

#include <dft2.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QMenuBar *mnbar;

    QMenu *fileMenu;
    QMenu *editMenu;

    QAction *openAction;
    QAction *saveAction;
    QAction *grayAction;
    QAction *fourierAction;

    QImage *image;
    QLabel *label;

signals:
    void freshSignal();

private slots:
    void openSlot();
    void saveSlot();
    void graySlot();
    void fourierSlot();
    void freshSlot();
};
#endif // MAINWINDOW_H
