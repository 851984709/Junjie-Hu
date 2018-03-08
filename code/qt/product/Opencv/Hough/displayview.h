#ifndef DISPLAYVIEW_H
#define DISPLAYVIEW_H

#include <QWidget>
#include <QScrollArea>
#include <QLabel>
#include <QImage>
#include <QDebug>

#include <opencv2/opencv.hpp>
#include <iostream>

#include "globalvariable.h"
#include "myopencv.h"

class DisplayView : public QScrollArea
{
    Q_OBJECT
public:
    explicit DisplayView(QWidget *parent = nullptr);

    QLabel *label;

    void processLine();
    void processCircle();

signals:
    void saveEnable();

public slots:
    void refresh();
};

#endif // DISPLAYVIEW_H
