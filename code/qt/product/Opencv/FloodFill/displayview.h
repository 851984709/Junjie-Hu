#ifndef DISPLAYVIEW_H
#define DISPLAYVIEW_H

#include <QWidget>
#include <QScrollArea>
#include <QImage>
#include <QDebug>

#include <opencv2/opencv.hpp>

#include "touchablelabel.h"
#include "globalvariable.h"
#include "myopencv.h"

class DisplayView : public QScrollArea
{
    Q_OBJECT
public:
    explicit DisplayView(QWidget *parent = nullptr);

    TouchableLabel *label;

signals:
    void saveEnable();
    void floodFilled();

public slots:
    void refresh();
    void floodFill(QPoint);
};

#endif // DISPLAYVIEW_H
