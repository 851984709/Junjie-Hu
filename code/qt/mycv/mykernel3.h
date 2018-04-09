#ifndef MYKERNEL3_H
#define MYKERNEL3_H

#include <QDebug>

#include <iostream>
#include <string.h>
#include "mymat3.h"

class MyKernel3:public MyMat3
{
public:
    enum kerneltype{
        MEAN
    };

    MyKernel3();
    MyKernel3(int width,int height, int channel,enum kerneltype kernelType);

    enum kerneltype m_kernulType;

};

#endif // MYKERNEL_H
