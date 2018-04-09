#include "mymath.h"

MyMath::MyMath()
{

}

// 将矩阵转化为傅里叶数组
MyComplexNumber* MyMath::Dft2(MyMat2 const &scr)
{
    int width = scr.m_width;
    int height = scr.m_height;
    double *double_data = scr.m_data;

    // 对 double_data 进行傅里叶变换
    MyComplexNumber *dft2_data = new MyComplexNumber[width*height];
    double fixed_factor_for_axisX = (-2 * PI) / height;
    // evaluate -i2π/N of -i2πux/N, and store the value for computing efficiency
    double fixed_factor_for_axisY = (-2 * PI) / width;
    // evaluate -i2π/N of -i2πux/N, and store the value for computing efficiency

    for (int u = 0; u<height; u++) {
            for (int v = 0; v<width; v++) {
                for (int x = 0; x<height; x++) {
                    for (int y = 0; y<width; y++) {
                        double powerX = u * x * fixed_factor_for_axisX; // evaluate -i2πux/N
                        double powerY = v * y * fixed_factor_for_axisY; // evaluate -i2πux/N
                        MyComplexNumber cplTemp;
                        cplTemp.m_rl = double_data[y + x*width] * cos(powerX + powerY);
                        // evaluate f(x) * e^(-i2πux/N), which is equal to f(x) * (cos(-i2πux/N)+sin(-i2πux/N)i) according to Euler's formula
                        cplTemp.m_im = double_data[y + x*width] * sin(powerX + powerY);
                        dft2_data[v + u*width] = dft2_data[v + u*width] + cplTemp;
                    }
                }
            }
        }

    // 返回傅里叶数组
    return dft2_data;
}

MyMat2 MyMath::Idft2(MyComplexNumber *scr, const int width, const int height)
{
    double* dst_data = new double[width*height];
    // 全部赋值为0
    for(int i=0;i<width*height;i++)
        dst_data[i] = 0;

    double fixed_factor_for_axisX = (2 * PI) / height;                  // evaluate i2π/N of i2πux/N, and store the value for computing efficiency
    double fixed_factor_for_axisY = (2 * PI) / width;                   // evaluate i2π/N of i2πux/N, and store the value for computing efficiency
    for (int x = 0; x<height; x++) {
        for (int y = 0; y<width; y++) {
            for (int u = 0; u<height; u++) {
                for (int v = 0; v<width; v++) {
                    double powerU = u * x * fixed_factor_for_axisX;         // evaluate i2πux/N
                    double powerV = v * y * fixed_factor_for_axisY;         // evaluate i2πux/N
                    MyComplexNumber cplTemp;
                    cplTemp.SetValue(cos(powerU + powerV), sin(powerU + powerV));
                    dst_data[y + x*width] = dst_data[y + x*width] +
                            ((scr[v + u*width] * cplTemp).m_rl
                            /(height*width));
                }
            }
        }
    }

    return MyMat2(width,height,dst_data);
}

MyMat2 MyMath::Conv2(MyMat2 const &scr, const MyKernel2 &kernel,int span_row,int span_col)
{
    int scr_width = scr.m_width;
    int scr_height = scr.m_height;

    int ker_width = kernel.m_width;
    int ker_height = kernel.m_height;

    int temp_width = scr_width + ker_width -1;
    int temp_height = scr_height + ker_height -1;

    int edge_width = (ker_width-1)/2;
    int edge_height = (ker_height-1)/2;

    MyMat2 temp_mat = MyMat2(temp_width,temp_height,0.0);
//    double* temp_data = new double[temp_width*temp_height];

//    double* scr_data = scr.m_data;
//    double* ker_data = kernel.m_data;

    // 给临时模板复制
    for(int i=0;i<scr_height;i++)
        for(int j=0;j<scr_width;j++)
        {
            double value = scr.GetPointValue2(i,j);
            temp_mat.SetPointValue2(edge_height+i,edge_width+j,value);
//            temp_data[(edge_height+i)*temp_width+edge_width+j] = scr_data[i*scr_width+j];
        }

    // 填充边缘
    for(int i=0;i<temp_height;i++)
        for(int j=0;j<temp_width;j++)
        {
            // 左上角
            if(i<edge_height && j<edge_width)
            {
                temp_mat.SetPointValue2(i,j,scr.GetPointValue2(0,0));
//                temp_data[i*temp_width+j] = scr_data[0];
            }
            // 左下角
            else if(i>=(edge_height+scr_height) && j<edge_width)
            {
                temp_mat.SetPointValue2(i,j,scr.GetPointValue2(scr_height-1,0));
//                temp_data[i*temp_width+j] = scr_data[(scr_height-1)*scr_width];
            }
            // 右上角
            else if(i<edge_height && j>=(edge_width+scr_width))
            {
                temp_mat.SetPointValue2(i,j,scr.GetPointValue2(0,scr_width-1));
//                temp_data[i*temp_width+j] = scr_data[scr_width-1];
            }
            // 右下角
            else if(i>=(edge_height+scr_height) && j>=(edge_width+scr_width))
            {
                temp_mat.SetPointValue2(i,j,scr.GetPointValue2(scr_height-1,scr_width-1));
//                temp_data[i*temp_width+j] = scr_data[scr_height*scr_width-1];
            }
            // 上边
            else if(i<edge_height && j>=edge_width && j<(edge_width+scr_width))
            {
                temp_mat.SetPointValue2(i,j,scr.GetPointValue2(0,j-edge_width));
//                temp_data[i*temp_width+j] = scr_data[(j-edge_width)];
            }
            // 下边
            else if(i>=(edge_height+scr_height) && j>=edge_width && j<(edge_width+scr_width))
            {
                temp_mat.SetPointValue2(i,j,scr.GetPointValue2(scr_height-1,j-edge_width));
//                temp_data[i*temp_width+j] = scr_data[(scr_height-1)*scr_width+(j-edge_width)];
            }
            // 左边
            else if(i>=edge_height && i<(edge_height+scr_height) && j<edge_width)
            {
                temp_mat.SetPointValue2(i,j,scr.GetPointValue2(i,0));
//                temp_data[i*temp_width+j] = scr_data[i*scr_width];
            }
            // 右边
            else if(i>=edge_height && i<(temp_height-edge_height) && j>=(temp_width-edge_width))
            {
                temp_mat.SetPointValue2(i,j,scr.GetPointValue2(i,scr_width-1-edge_width));
//                temp_data[i*temp_width+j] = scr_data[i*scr_width+scr_width-1-edge_width];
            }
        }

    // 目标矩阵
    int dst_width = scr_width/span_col;
    int dst_height = scr_height/span_row;

//    double* dst_data = new double[dst_width*dst_height];
    MyMat2 dst_mat = MyMat2(dst_width,dst_height,0.0);

    // 给目标矩阵赋值
    for(int i=0;i<dst_height;i++)
        for(int j=0;j<dst_width;j++)
        {
            double kernel_center = 0;

            for(int u=0;u<ker_height;u++)
                for(int v=0;v<ker_width;v++)
                {
                    // 利用卷积求目标点值
//                        kernel_center += temp_data[(i+u)*temp_width + (j+v)] * ker_data[u*ker_width+v];
//                    kernel_center += temp_data[(i*span+u)*temp_width + (j*span+v)] * ker_data[u*ker_width+v];
                    kernel_center += temp_mat.GetPointValue2(i*span_row+u,j*span_col+v)*kernel.GetPointValue2(u,v);
                }

            // 将得到的值赋给目标数据
            dst_mat.SetPointValue2(i,j,kernel_center);
//            dst_data[i*dst_width+j] = kernel_center;


        }

//    return new MyMat2(dst_width,dst_height,dst_data);
    return dst_mat;
}

// 三维矩阵的卷积运算还未完全实现
// 请勿使用！！！
MyMat3 MyMath::Conv3(const MyMat3 &scr, const MyKernel3 &kernel, int span)
{
//    // 被卷积矩阵和卷积和通道数不匹配
//    if(scr.m_channel != kernel.m_channel)
//        return ;

    // 三维
    int scr_width = scr.m_width;
    int scr_height = scr.m_height;

    int ker_width = kernel.m_width;
    int ker_height = kernel.m_height;

    int channel = scr.m_channel;

    int temp_width = scr_width + ker_width -1;
    int temp_height = scr_height + ker_height -1;

    int span_width = (ker_width-1)/2;
    int span_height = (ker_height-1)/2;

    double* temp_data = new double[temp_width*temp_height*3];

    double* scr_data = scr.m_data;
    double* ker_data = kernel.m_data;

    // 给临时模板复制
    for(int i=0;i<scr_height;i++)
        for(int j=0;j<scr_width;j++)
            for(int k=0;k<channel;k++)
            {
                temp_data[((span_height+i)*temp_width+span_width+j)*channel +k] =
                        scr_data[(i*scr_width+j)*channel+k];
            }

    // 目标矩阵
    double* dst_data = new double[scr_width*scr_height*channel];

    for(int i=0;i<scr_height;i++)
        for(int j=0;j<scr_width;j++)
            for(int k=0;k<channel;k++)
            {
                double kernel_center =0.0;

                for(int u=0;u<ker_height;u++)
                    for(int v=0;u<ker_width;v++)
                    {
                        // 利用卷积求目标点值
                        kernel_center +=
                                temp_data[((i+u)*temp_width + (j+v))*channel + k] *
                                ker_data[(u*ker_width+v)*channel + k];
                    }

                // 将得到的值赋给目标数据
                dst_data[(i*scr_width+j)*channel+k] = kernel_center;
            }

    return MyMat3(scr_width,scr_height,channel,dst_data);
}

MyMat2 MyMath::SampleUp2(const MyMat2 &scr_mat, const int width_mul, const int height_mul)
{
    int scr_width = scr_mat.m_width;
    int scr_height = scr_mat.m_height;

    int dst_width = scr_width*width_mul;
    int dst_height = scr_height*height_mul;

    MyMat2 temp_mat = MyMat2(dst_width,dst_height,0.0);

    for(int i=0;i<dst_height;i++)
        for(int j=0;j<dst_width;j++)
        {
            int temp_value = scr_mat.GetPointValue2(i/height_mul,j/width_mul);
            temp_mat.SetPointValue2(i,j,temp_value);
        }

    MyKernel2 kernel = MyKernel2(3,3,MyKernel2::kerneltype::MEAN);

    return Conv2(temp_mat,kernel,1,1);
}

//MyMat2* MyMath::

double MyMath::GetPointConv(const MyMat2 &scr_mat, const int row, const int col, const MyKernel2 kernel)
{
    int ker_width = kernel.m_width;
    int ker_height = kernel.m_height;

//    int src_width = scr_mat.m_width;
//    int src_height = scr_mat.m_height;

    int edge_width = (ker_width-1)/2;
    int edge_height = (ker_height-1)/2;

    MyMat2 temp_mat = MyMat2(ker_width,ker_height,0.0);
    double* temp_data = temp_mat.m_data;

    for(int i=0;i<ker_height;i++)
        for(int j=0;j<ker_width;j++)
        {
            int src_row = row - edge_height+i;
            int src_col = col - edge_width +j;
            temp_data[i*ker_width+j] = scr_mat.GetPointValue2IncOut(src_row,src_col);
        }

    double result;
    temp_mat.DotMul(kernel.ToMat2(),result);

    return result;
}
