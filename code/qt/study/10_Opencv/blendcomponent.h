#ifndef BLENDVIEW_H
#define BLENDVIEW_H

#include <QWidget>
#include <QLabel>
#include <QScrollBar>
#include <QPixmap>
#include <QImage>
#include <QDebug>
#include <QPushButton>

#include "globalvariable.h"
#include "resourceselectdialog.h"

class BlendComponent : public QWidget
{
    Q_OBJECT
public:
    explicit BlendComponent(QWidget *parent = nullptr);

    QLabel *labelImage1;
    QLabel *labelImage2;

    QPushButton *button1;
    QPushButton *button2;

    QLabel *labelName1;
    QLabel *labelName2;

    QScrollBar *scrollBar1;
    QScrollBar *scrollBar2;

    ResourceSelectDialog *resourceSelectDialog;

signals:

public slots:
    void resourceSelect();
    void okClicked();
};

#endif // BLENDVIEW_H
