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
    QLabel *labelBinarizationClass;
    QComboBox *combox;
    QLabel *labelThreshold;
    QScrollBar *scrollBar;

signals:
    void refresh();

public slots:
    void getImage(QString);
    void thresholdChanged(int);
    void binarizationClassChanged(int);
};

#endif // OPERATIONVIEW_H
