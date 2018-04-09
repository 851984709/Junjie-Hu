#include "mymat2.h"

MyMat2::MyMat2()
{
    m_width =0;
    m_height=0;
    m_data = NULL;
}

MyMat2::MyMat2(int width,int height,double const *data)
{
    m_width = width;
    m_height = height;
    m_data = new double[width*height];

    for(int i=0;i<width*height;i++)
    {
        m_data[i] = data[i];
    }
}

MyMat2::MyMat2(int width, int height, double all_value)
{
    m_width = width;
    m_height = height;
    m_data = new double[width*height];
    for(int i=0;i<width*height;i++)
        m_data[i] = all_value;
}

MyMat2::~MyMat2()
{

}

int MyMat2::Sum(double &result)
{
    if(this->m_data == NULL)
        return 0;

    int size = m_width*m_height;
    result=0;

    for(int i=0;i<size;i++)
        result += this->m_data[i];

    return 1;
}

int MyMat2::DotMul(const MyMat2 &mat2,double &result)
{
    // 两个被乘矩阵形状不同
    if(mat2.m_height != m_height || mat2.m_width != m_width)
        return 0;

    MyMat2 result_mat;

    result_mat.m_width = m_width;
    result_mat.m_height = m_height;

    int size = m_width*m_height;
    double* dst_data = new double[size];
    double* data1 = this->m_data;
    double* data2 = mat2.m_data;

    for(int i=0;i<size;i++)
    {
        dst_data[i] = data1[i]*data2[i];
    }

    result_mat.m_data = dst_data;

    result_mat.Sum(result);

    return 1;
}

void MyMat2::SetPointValue2(const int row, const int col, const double value)
{
    m_data[row*m_width+col] = value;
}

double MyMat2::GetPointValue2(const int row, const int col) const
{
    return m_data[row*m_width+col];
}

double MyMat2::GetPointValue2IncOut(const int row, const int col) const
{
    // 范围内
    if(row>=0 && row<m_height && col>=0 && col<m_width)
        return m_data[row*m_width+col];
    // 左上角
    else if(row<0 && col<0)
        return m_data[0];
    // 左下角
    else if(row>=m_height && col<0)
        return m_data[(m_height-1)*m_width];
    // 右上角
    else if(row<0 && col>=m_width)
        return m_data[m_width-1];
    // 右下角
    else if(row>=m_height && col>=m_width)
        return m_data[m_width*m_height-1];
    // 上边
    else if(row<0 && col>=0 && col<m_width)
        return m_data[col];
    // 下边
    else if(row>=m_height && col>=0 && col<m_width)
        return m_data[(m_height-1)*m_width + col];
    // 左边
    else if(row>=0 && row<m_height && col<0)
        return m_data[row*m_width];
    // 右边
    else if(row>=0 && row<m_height && col>=m_width)
        return m_data[(row+1)*m_width-1];
}

int MyMat2::CopyMyMat2(MyMat2 &src_mat, MyMat2 &dst_mat)
{
    if(src_mat.m_data == NULL)
        return 0;

    int width = src_mat.m_width;
    int height = src_mat.m_height;

    dst_mat.m_width = width;
    dst_mat.m_height = height;
    dst_mat.m_data = new double[width*height];
    for(int i=0;i<width*height;i++)
        dst_mat.m_data[i] = src_mat.m_data[i];
}
