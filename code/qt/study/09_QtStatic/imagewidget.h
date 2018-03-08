#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QWidget>
#include <QLabel>

class ImageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ImageWidget(QWidget *parent = 0);
    ~ImageWidget();

    QLabel label;

signals:

public slots:
};

#endif // IMAGEWIDGET_H
