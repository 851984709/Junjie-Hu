#include "myimage.h"

MyImage::MyImage()
{
    m_width = 0;
    m_height = 0;
    m_nBitCount = 0;
    m_bytesPerLine = 0;
    m_data = NULL;
    m_format = format::EMPTY;
}

MyImage::MyImage(unsigned char *data, int width, int height, enum format fmt)
{
    m_width = width;
    m_height = height;
    m_format = fmt;

    switch(fmt)
    {
    case format::GRAY8:
        m_nBitCount = 8;
        break;
    case format::RGB32:
        m_nBitCount = 32;
        break;
    }

    m_bytesPerLine = (width*m_nBitCount +31)/32*4;

    m_data = new unsigned char[m_bytesPerLine*height];
    memcpy(m_data,data,m_bytesPerLine*height);
}

MyImage::MyImage(const MyImage &Scr)
{
    m_width = Scr.m_width;
    m_height = Scr.m_height;
    m_nBitCount = Scr.m_nBitCount;
    m_bytesPerLine = Scr.m_bytesPerLine;
    m_format = Scr.m_format;

    m_bytesPerLine = (m_width*m_nBitCount +31)/32*4;

    m_data = new unsigned char[m_bytesPerLine*m_height];
    memcpy(m_data,Scr.m_data,m_bytesPerLine*m_height);
}

MyImage::MyImage(const QImage &qimage)
{
    m_width = qimage.width();
    m_height = qimage.height();
    m_nBitCount = qimage.byteCount();
    m_bytesPerLine = qimage.bytesPerLine();

    if(qimage.format()==QImage::Format_RGB32)
        m_format = format::RGB32;
    else if(qimage.format()==QImage::Format_Grayscale8)
        m_format = format::GRAY8;

    m_data = new unsigned char[m_bytesPerLine*m_height];

    memcpy(m_data,qimage.bits(),m_bytesPerLine*m_height);

}

//MyImage::MyImage(const MyMat &mymat)
//{
//    m_width= mymat.m_width;
//    m_height = mymat.m_height;

//    switch(mymat.m_channel)
//    {
//    case 1:
//        // 灰度图
//        m_nBitCount = 8;
//        m_format = format::GRAY8;
//        break;
//    case 3:
//        // RGB
//        m_nBitCount = 32;
//        m_format = format::RGB32;
//        break;

//    }

//    m_bytesPerLine = (m_width*m_nBitCount +31)/32*4;

//    m_data = new unsigned char[m_bytesPerLine*m_height];
//    double* mat_data = mymat.m_data;

//    for(int i=0;i<m_height;i++)
//        for(int j=0;j<m_width;j++)
//        {
//            m_data[i*m_bytesPerLine+j] = (unsigned char)mat_data[i*m_width+j];
//        }
//}

MyImage::MyImage(const MyMat2 &mymat2)
{
    m_width= mymat2.m_width;
    m_height = mymat2.m_height;

    // 灰度图
    m_nBitCount = 8;
    m_format = format::GRAY8;

    m_bytesPerLine = (m_width*m_nBitCount +31)/32*4;

    m_data = new unsigned char[m_bytesPerLine*m_height];
    double* mat_data = mymat2.m_data;

    for(int i=0;i<m_height;i++)
        for(int j=0;j<m_width;j++)
        {
            m_data[i*m_bytesPerLine+j] = (unsigned char)mat_data[i*m_width+j];
        }
}

MyImage::~MyImage()
{
    if(m_data != NULL)
        delete m_data;
}

QImage MyImage::MyImage2QImage(const MyImage &myimage)
{
    int width = myimage.m_width;
    int height = myimage.m_height;
    int bytesPerLine = myimage.m_bytesPerLine;
    QImage::Format format;

    if(myimage.m_format == MyImage::format::GRAY8)
        format = QImage::Format_Grayscale8;
    else if(myimage.m_format == MyImage::format::RGB32)
        format = QImage::Format_RGB32;

    unsigned char* dst_data = new unsigned char[bytesPerLine*height];
    memcpy(dst_data,myimage.m_data,bytesPerLine*height);

    QImage qimage = QImage(dst_data,width,height,bytesPerLine,format);

    return qimage;
}

//MyMat* MyImage::MyImage2MyMat(const MyImage &myimage)
//{
//    int width = myimage.m_width;
//    int height = myimage.m_height;

//    int bytesPerLine = myimage.m_bytesPerLine;
//    unsigned char* scr_data = myimage.m_data;

//    if(myimage.m_format == format::GRAY8)
//    {
//        double* dst_data = new double[width*height];

//        for(int i=0;i<height;i++)
//            for(int j=0;j<width;j++)
//            {
//                dst_data[i*width+j] =
//                        (double)scr_data[i*bytesPerLine+j];
//            }

//        return new MyMat(width,height,1,dst_data);
//    }
//    else if(myimage.m_format == format::RGB32)
//    {
//        int channel = 3;
//        double* dst_data = new double[width*height*channel];

//        for(int i=0;i<height;i++)
//            for(int j=0;j<width;j++)
//                for(int k=0;k<3;k++)
//                {
//                    dst_data[(i*height+j)*3 + k] =
//                            scr_data[i*bytesPerLine+j*4 + k];
//                }

//        return new MyMat(width,height,1,dst_data);
//    }
//}

MyMat2 MyImage::MyImage2MyMat2(const MyImage &myimage)
{
    int width = myimage.m_width;
    int height = myimage.m_height;

    int bytesPerLine = myimage.m_bytesPerLine;
    unsigned char* scr_data = myimage.m_data;

    double* dst_data = new double[width*height];

    for(int i=0;i<height;i++)
        for(int j=0;j<width;j++)
        {
            dst_data[i*width+j] =
                    (double)scr_data[i*bytesPerLine+j];
        }

    return MyMat2(width,height,dst_data);
}

int MyImage::CopyMyImage(const MyImage &src, MyImage &dst)
{
    dst.m_width = src.m_width;
    dst.m_height = src.m_height;
    dst.m_nBitCount = src.m_nBitCount;
    dst.m_bytesPerLine = src.m_bytesPerLine;
    dst.m_format = src.m_format;

    dst.m_data = new unsigned char[dst.m_bytesPerLine*dst.m_height];

    memcpy(dst.m_data,src.m_data,dst.m_bytesPerLine*dst.m_height);
}
