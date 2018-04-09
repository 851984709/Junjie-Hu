#include "mymat3.h"

MyMat3::MyMat3()
{

}

MyMat3::MyMat3(const int width,const int height,const int channel,double const *data)
{
    m_width = width;
    m_height = height;
    m_channel = channel;
    m_data = new double[width*height*channel];

    for(int i=0;i<width*height*channel;i++)
    {
        m_data[i] = data[i];
    }
}

MyMat3::MyMat3(int width, int height,const int channel, double all_value)
{
    m_width = width;
    m_height = height;
    m_channel = channel;
    m_data = new double[width*height*channel];
    for(int i=0;i<width*height*channel;i++)
        m_data[i] = all_value;
}

MyMat3::~MyMat3()
{
}

void MyMat3::SetPointValue3(const int row, const int col, const int dep, const double value)
{
    this->m_data[(row*m_width+col)*m_channel+dep] = value;
}

double MyMat3::GetPointValue3(const int row, const int col, const int dep)
{
    return this->m_data[(row*m_width+col)*m_channel+dep];
}
