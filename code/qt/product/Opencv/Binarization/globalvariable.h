#ifndef GLOBALVARIABLE_H
#define GLOBALVARIABLE_H

#include <QImage>

class GlobalVariable
{
public:
    GlobalVariable();

    static QImage *imageSource;
    static QImage *imageScreen;
    static bool binarizationClass;
    static int nThreshold;
};

#endif // GLOBALVARIABLE_H
