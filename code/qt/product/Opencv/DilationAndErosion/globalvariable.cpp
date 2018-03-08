#include "globalvariable.h"

GlobalVariable::GlobalVariable()
{

}

cv::Mat GlobalVariable::matSource;
cv::Mat GlobalVariable::matScreen;
OperationType GlobalVariable::operationType = OperationType::Dilation;
int GlobalVariable::nStructElementSize = 0;
int GlobalVariable::niteration = 0;
