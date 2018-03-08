#ifndef OPERATIONVIEW_H
#define OPERATIONVIEW_H

#include <QWidget>
#include <QDockWidget>
#include <QGridLayout>
#include <QLabel>
#include <QImage>
#include <QComboBox>
#include <QPushButton>
#include <QScrollBar>
#include <QColorDialog>
#include <QPalette>

#include "onlynumlineedit.h"
#include "globalvariable.h"
#include "myopencv.h"

class OperationView : public QDockWidget
{
    Q_OBJECT
public:
    explicit OperationView(QWidget *parent = nullptr);

    QWidget *widget;
    QGridLayout *layout;
    QLabel *labelImage;
    QLabel *labelName;
    QPushButton *button;
    QLabel *labelParamLower;
    QScrollBar *scrollBarLower;
    QLabel *labelParamHigher;
    QScrollBar *scrollBarHigher;
    QLabel *labelColorText;
    QLabel *labelColorImage;
    OnlyNumLineEdit *textR;
    OnlyNumLineEdit *textG;
    OnlyNumLineEdit *textB;
    QPushButton *buttonMoreColor;

signals:
    void refresh();

public slots:
    void getImage(QString);
    void paramLowerChanged(int);
    void paramHigherChanged(int);
    void colorChanged();
    void moreColor();
};

#endif // OPERATIONVIEW_H
