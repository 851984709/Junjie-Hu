#include "globalvariable.h"

GlobalVariable::GlobalVariable()
{

}

cv::Mat GlobalVariable::matSource;
cv::Mat GlobalVariable::matScreen;
OperationType GlobalVariable::operationType = OperationType::Canney;
int GlobalVariable::nParam = 1;
bool GlobalVariable::isColorful = false;
