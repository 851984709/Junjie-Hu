#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QPushButton>
#include "subwidget.h"//子窗口头文件

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = 0);
    ~MainWidget();

    void mySlot();
    void gotoSubwidget();
public slots:
    void dealSubwidgetSignal();
    void dealSubwidgetSignal(int,QString);
private:
    QPushButton b1;
    QPushButton *b2;
    QPushButton b3;

    SubWidget sw;
};

#endif // MAINWIDGET_H
