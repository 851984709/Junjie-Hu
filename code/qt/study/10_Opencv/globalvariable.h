#ifndef GLOBALVARIABLE_H
#define GLOBALVARIABLE_H

#include <QList>
#include <QImage>

#include "imageobject.h"

class Globalvariable
{
public:
    Globalvariable();

    static QList<ImageObject> imageObjectList;

    static ImageObject *imageObjectCurrent;

    static ImageObject *imageBlend1;
    static ImageObject *imageBlend2;
};

#endif // GLOBALVARIABLE_H
