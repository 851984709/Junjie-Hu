#ifndef MYMAT3_H
#define MYMAT3_H

#include "mymat.h"

class MyMat3:public MyMat
{
public:
    MyMat3();
    MyMat3(const int width, const int height,const int channel, const double *data);
    MyMat3(const int width, const int height,const int channel, const double all_value);
    ~MyMat3();

    void SetPointValue3(const int row,const int col,const int dep,const double value);
    double GetPointValue3(const int row,const int col,const int dep);

public:
    int m_width;
    int m_height;
    int m_channel;
};

#endif // MYMAT3_H
