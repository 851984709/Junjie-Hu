#ifndef OPERATIONVIEW_H
#define OPERATIONVIEW_H

#include <QWidget>
#include <QDockWidget>
#include <QImage>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QScrollBar>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QFileInfo>
#include <QLineEdit>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp> // resize()

#include "myopencv.h"

class OperationView : public QDockWidget
{
    Q_OBJECT
public:
    explicit OperationView(QWidget *parent = nullptr);

    QWidget *widget;

    QGridLayout *layout;

    QImage *image1;
    QString *stringName1;
    QLabel *labelImage1;
    QPushButton *buttonImageImport1;
    QLabel *labelName1;
    QLabel *labelAlpha;
    QScrollBar *scrollBar1;

    QImage *image2;
    QString *stringName2;
    QLabel *labelImage2;
    QPushButton *buttonImageImport2;
    QLabel *labelName2;
    QLabel *labelBeta;
    QScrollBar *scrollBar2;

    QLabel *labelWidth;
    QLineEdit *lineEditWidth;
    QPushButton *buttonWidth;
    QLabel *labelHeight;
    QLineEdit *lineEditHeight;
    QPushButton *buttonHeight;

    QImage *imageBlend;
    int widthBlend;
    int heightBlend;

    double alpha;
    double beta;

    void refresh();

signals:
    void blendImageChange();

public slots:
    void openImage1();
    void openImage2();
    void scrollBar1ValueChanged(int);
    void scrollBar2ValueChanged(int);
    void widthChange();
    void heightChange();
};

#endif // OPERATIONVIEW_H
