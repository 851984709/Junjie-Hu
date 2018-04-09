#ifndef MYIMAGE_H
#define MYIMAGE_H

#include <iostream>
#include <QImage>
#include <QDebug>

#include "mymat.h"
#include "mymat2.h"

class MyImage
{
public:
    enum format{
        GRAY8,
        RGB32,
        EMPTY
    };

public:
    MyImage();
    MyImage(unsigned char* data,int width,int height,enum format fmt);
    MyImage(const MyImage &Scr);
    MyImage(const QImage &qimage);
//    MyImage(const MyMat &mymat);
    MyImage(const MyMat2 &mymat2);
    ~MyImage();

    static QImage MyImage2QImage(const MyImage &myimage);
//    static MyMat* MyImage2MyMat(const MyImage &myimage);
    static MyMat2 MyImage2MyMat2(const MyImage &myimage);
    static int CopyMyImage(const MyImage &src,MyImage &dst);

public:
    int m_width;
    int m_height;
    int m_nBitCount;
    int m_bytesPerLine;
    enum format m_format;
    unsigned char* m_data;
};

#endif // MYIMAGE_H
