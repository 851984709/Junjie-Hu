#ifndef MYMATH_H
#define MYMATH_H

#include "mymat.h"
#include "mymat2.h"
#include "mymat3.h"
#include "mycomplexnumber.h"
#include "mykernel2.h"
#include "mykernel3.h"

#define PI 3.141592653

class MyMath
{
public:
    MyMath();

    // 离散傅里叶变换
    static MyComplexNumber* Dft2(MyMat2 const &scr);

    // 离散傅里叶逆变换
    static MyMat2 Idft2(MyComplexNumber *scr,int const width,int const height);

    // 二维矩阵卷积运算
    static MyMat2 Conv2(MyMat2 const &scr,MyKernel2 const &kernel,int span_row,int span_col);

    // 三维矩阵卷积运算
    static MyMat3 Conv3(MyMat3 const &scr,MyKernel3 const &kernel,int span);


    // 二维矩阵向上取样
    static MyMat2 SampleUp2(const MyMat2 &scr,const int width_mul,const int height_mul);

    // 二维矩阵向下取样
    static MyMat2 SampleDown2(const MyMat2 &scr,const int width_mul,const int height_mul);

    // 对指定点进行卷积
    static double GetPointConv(const MyMat2 &scr_mat,const int row,const int col,const MyKernel2 kernel);
};

#endif // MYMATH_H
