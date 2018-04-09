#include "mykernel3.h"

MyKernel3::MyKernel3()
{

}

MyKernel3::MyKernel3(int width, int height, int channel,enum kerneltype kernelType)
{
    m_width = width;
    m_height = height;
    m_channel = channel;
    m_data = new double[width*height*channel];

    switch(kernelType)
    {
    case kerneltype::MEAN:
        double mean_value = 1.0/(width*height*channel);

        for(int i=0;i<width*height*channel;i++)
            m_data[i] = mean_value;
//        memset(m_data,mean_value,width*height*channel);
//        memset 只能对8位数据赋值

        break;
    }
}
