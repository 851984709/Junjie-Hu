#ifndef TOUCHABLELABEL_H
#define TOUCHABLELABEL_H

#include <QLabel>
#include <QMouseEvent>
#include <QDebug>

class TouchableLabel : public QLabel
{
    Q_OBJECT
public:
    explicit TouchableLabel(QWidget *parent = nullptr);

    void mousePressEvent(QMouseEvent *event);

signals:
    void mouseLeftButtonPress(QPoint);

public slots:
};

#endif // TOUCHABLELABEL_H
