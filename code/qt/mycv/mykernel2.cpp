#include "mykernel2.h"

MyKernel2::MyKernel2()
{
    m_width =0;
    m_height =0;
    m_data = NULL;
    m_kernulType = kerneltype::NONE;
}

MyKernel2::MyKernel2(const MyKernel2 &scr_kernel)
{
    m_width = scr_kernel.m_width;
    m_height = scr_kernel.m_height;

    int size = m_width*m_height;
    m_data = new double[size];

    for(int i=0;i<size;i++)
        m_data[i] = scr_kernel.m_data[i];

    m_kernulType = scr_kernel.m_kernulType;
}

MyKernel2::MyKernel2(int width, int height,enum kerneltype kernelType)
{
    m_width = width;
    m_height = height;
    m_data = new double[width*height];

    switch(kernelType)
    {

    // 均值核
    case kerneltype::MEAN:
    {
        double mean_value = 1.0/(width*height);

        for(int i=0;i<width*height;i++)
            m_data[i] = mean_value;
//        memset(m_data,mean_value,width*height*channel);
//        memset 只能对8位数据赋值
    }
        break;
    // 线性核
    case kerneltype::BILINEAR:
    {
        int med_w = (width-1)/2;
        int med_h = (height-1)/2;

        for(int i=0;i<height;i++)
            for(int j=0;j<height;j++)
            {
                if(i==med_h && j==med_w)
                    m_data[i*width+j] = 2;
                else
                {
                    m_data[i*width+j] = 1/sqrt((med_h-i)*(med_h-i)+(med_w-j)*(med_w-j));
                }
                m_data = Normalize(m_data,width*height);
            }
    }
        break;

    }
}

MyMat2 MyKernel2::ToMat2() const
{
    MyMat2 mat = MyMat2(m_width,m_height,m_data);
    return mat;
}

// 将输入的数据归一化，和为一
double* MyKernel2::Normalize(double *data,int size)
{
    double sum=0;

    // 求和
    for(int i=0; i<size;i++)
        sum += data[i];

    double* dst_data = new double[size];
    // 归一
    for(int i=0; i<size;i++)
        dst_data[i] = data[i]/sum;

    delete data;

    return dst_data;
}
