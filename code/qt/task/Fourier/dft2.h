#ifndef DFT2_H
#define DFT2_H

#define PI 3.141592653
#define MAX_MATRIX_SIZE 4194304 // 2048 * 2048

#include <QImage>
#include <QDebug>

#include "complexnumber.h"

class Dft2
{
public:
    Dft2(QImage image);

public:
    QImage m_scrimage;
    int m_width;
    int m_height;
    unsigned char* m_data;
    int m_bytesPerLine;
    double *m_scrmatrix;
    ComplexNumber* m_dft2_matrix;
    unsigned char* m_normalized_data;
    unsigned char* m_center_matrix;
    QImage *m_dst_image;

public:
    ComplexNumber* get_dft2_matrix();
    unsigned char* get_normalized_matrix();
    unsigned char* get_center_matrix();
    QImage *get_dst_image();
//    static ComplexNumber* dft2(double const matrix[],int const width,int const height); // 二维离散傅里叶变换
//    static unsigned char* normalized(ComplexNumber const matrix[],int const width,int const height);
    static double getmax(double mold[],int size);
    static double getmin(double mold[],int size);
};

#endif // DFT2_H
