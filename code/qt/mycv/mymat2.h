#ifndef MYMAT2_H
#define MYMAT2_H

#include "mymat.h"

class MyMat2:public MyMat
{
public:
    MyMat2();
    MyMat2(const int width, const int height, const double *data);
    MyMat2(const int width, const int height, const double all_value);
    ~MyMat2();

    int Sum(double &result);
    int DotMul(const MyMat2 &psv_mat,double &result);
    void SetPointValue2(const int row,const int col,const double value);
    double GetPointValue2(const int row,const int col) const;
    double GetPointValue2IncOut(const int row,const int col) const;

    static int CopyMyMat2(MyMat2 &src_mat,MyMat2 &dst_mat);

public:
    int m_width;
    int m_height;
};

#endif // MYMAT2_H
