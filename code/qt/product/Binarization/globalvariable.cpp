#include "globalvariable.h"

GlobalVariable::GlobalVariable()
{

}

QImage *GlobalVariable::imageSource = new QImage();
QImage *GlobalVariable::imageScreen = new QImage();
bool GlobalVariable::binarizationClass = true;
int GlobalVariable::nThreshold = 127;
