#include "imageobject.h"


ImageObject::ImageObject(QImage Image, QString ImageName)
{
    image = new QImage(Image);
    imageName = new QString(ImageName);
}

ImageObject::ImageObject(const ImageObject &imageObejct)
{
    image = new QImage(*imageObejct.image);
    imageName = new QString(*imageObejct.imageName);
}
