#ifndef MYCV_H
#define MYCV_H

#include "myimage.h"
#include "mycomplexnumber.h"
#include "mykernel2.h"
#include "mymat.h"
#include "mymath.h"

#define PI 3.141592653

class MyCV
{
public:
    MyCV();

    // 灰度变换
    static MyImage Gray(MyImage const &scr);

    // 傅里叶数组转图像
    static MyImage Dft22MyImage(MyComplexNumber *scr,int width,int height);

    static int Resize2NearPoint(const MyImage &scr,MyImage &dst, const int dst_width,const int dst_height);
    static int Resize2BiLinear(const MyImage &scr,MyImage &dst,const int dst_width,const int dst_height);

    //图像 卷积运算
//    static MyMat* Conv(MyMat const &scr,MyKernel const &kernel,int span);
};

#endif // MYCV_H
