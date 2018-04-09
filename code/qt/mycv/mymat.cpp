#include "mymat.h"

MyMat::MyMat()
{

}

//MyMat::MyMat(int width,int height,int channel,double const *data)
//{
//    m_width = width;
//    m_height = height;
//    m_channel = channel;
//    m_data = new double[width*height*channel];

//    for(int i=0;i<width*height*channel;i++)
//    {
//        m_data[i] = data[i];
//    }
//}

//MyMat::MyMat(int width, int height, int channel, double all_value)
//{
//    m_width = width;
//    m_height = height;
//    m_channel = channel;
//    m_data = new double[width*height*channel];
//    for(int i=0;i<width*height*channel;i++)
//        m_data[i] = all_value;
//}

MyMat::~MyMat()
{
    if(m_data != NULL)
        delete m_data;
}
