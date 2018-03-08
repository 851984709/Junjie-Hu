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
    QLabel *labelStructElementSize;
    QScrollBar *scrollBarStructElementSize;
    QLabel *labelIteration;
    QScrollBar *scrollBarIteration;

signals:
    void refresh();

public slots:
    void getImage(QString);
    void structElementSizeChanged(int);
    void iterationChanged(int);
    void operationTypeChanged(int);
};

#endif // OPERATIONVIEW_H
