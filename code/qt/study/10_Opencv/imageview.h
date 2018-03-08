#ifndef DISPLAYWIDGET_H
#define DISPLAYWIDGET_H

#include <QWidget>
#include <QScrollArea>
#include <QLabel>
#include <QGridLayout>
#include <QMdiSubWindow>

#include <opencv2/opencv.hpp>

#include "globalvariable.h"
#include "myopencv.h"

class ImageView : public QWidget
{
    Q_OBJECT
public:
    explicit ImageView(QWidget *parent = nullptr);

    QGridLayout *layout;//窗口布局
    QScrollArea *scrollArea;
    QLabel *label;


signals:

public slots:
    void refresh();
    void showImage();
    void toGray();
};

#endif // DISPLAYWIDGET_H
