#include "globalvariable.h"

GlobalVariable::GlobalVariable()
{

}

cv::Mat GlobalVariable::matSource;
cv::Mat GlobalVariable::matScreen;
BlurType GlobalVariable::blurType = BlurType::MeanBlur;
int GlobalVariable::nParam = 0;
