#include "touchablelabel.h"

TouchableLabel::TouchableLabel(QWidget *parent) : QLabel(parent)
{

}

void TouchableLabel::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        //qDebug()<<"鼠标左键被按下 "<<event->x()<<" "<<event->y();
        emit mouseLeftButtonPress(QPoint(event->x(),event->y()));
    }
}
