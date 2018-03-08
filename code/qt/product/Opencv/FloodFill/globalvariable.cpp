#include "globalvariable.h"

GlobalVariable::GlobalVariable()
{

}

cv::Mat GlobalVariable::matSource;
cv::Mat GlobalVariable::matScreen;
int GlobalVariable::lowerBrightnessDifference = 0;
int GlobalVariable::higherBrightnessDifference = 0;
cv::Scalar GlobalVariable::color = cv::Scalar(0,255,0);
