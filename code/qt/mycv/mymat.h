#ifndef MYMAT_H
#define MYMAT_H

#include <qDebug>

#include <string.h>

class MyMat
{
public:
    MyMat();
    ~MyMat();
//    MyMat(const int width, const int height, const int channel, const double *data);
//    MyMat(const int width, const int height, const int channel, const double all_value);

public:
    int* dimension;
    int* size;
    double* m_data;
};

#endif // MYMAT_H
