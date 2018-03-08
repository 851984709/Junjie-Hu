#include "globalvariable.h"

GlobalVariable::GlobalVariable()
{

}

cv::Mat GlobalVariable::matSource;
cv::Mat GlobalVariable::matScreen;
GraphicType GlobalVariable::graphicType = GraphicType::Line;
int GlobalVariable::nParam = 1;
