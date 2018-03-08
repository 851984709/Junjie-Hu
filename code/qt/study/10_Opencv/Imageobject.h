#ifndef IMAGE_H
#define IMAGE_H

#include <QImage>
#include <QString>

class ImageObject
{
public:
    ImageObject(QImage,QString);
    ImageObject(const ImageObject&);

    QImage *image;
    QString *imageName;
};

#endif // IMAGE_H
