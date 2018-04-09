#ifndef MYKERNEL2_H
#define MYKERNEL2_H

#include <QDebug>

#include <iostream>
#include <string.h>
#include "mymat2.h"

class MyKernel2:public MyMat2
{
public:
    enum kerneltype{
        MEAN,
        BILINEAR,
        NONE
    };

    MyKernel2();
    MyKernel2(const MyKernel2 &scr_kernel);
    MyKernel2(const int width,const int height,const enum kerneltype kernelType);

    MyMat2 ToMat2() const;
    static double* Normalize(double* data,int size);

    enum kerneltype m_kernulType;

};

#endif // MYKERNEL2_H
