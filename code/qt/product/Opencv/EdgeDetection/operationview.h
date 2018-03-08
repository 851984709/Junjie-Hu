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
#include <QCheckBox>

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
    QLabel *labelBlurType;
    QComboBox *combox;
    QLabel *labelParam;
    QScrollBar *scrollBar;
    QCheckBox *checkBox;

signals:
    void refresh();

public slots:
    void getImage(QString);
    void paramChanged(int);
    void OperationTypeChanged(int);
    void isColorfulChanged(int);
};

#endif // OPERATIONVIEW_H
