#include "mycv.h"

MyCV::MyCV()
{

}

// 将图像转换为灰度图像
MyImage MyCV::Gray(MyImage const &scr)
{
    if(scr.m_format == MyImage::format::GRAY8)
         return MyImage(scr);

    else if(scr.m_format == MyImage::format::RGB32)
    {
        int width = scr.m_width;
        int height = scr.m_height;
        int bytesPerLine = (width*8 +31)/32*4;
        unsigned char* scrdata = scr.m_data;

        unsigned char *data = new unsigned char[bytesPerLine*height];

        for(int i=0;i<height;i++)
            for(int j=0;j<width;j++)
            {
                // 灰度公式
                int gray = (int)(scrdata[2] * 0.3 + scrdata[1] * 0.59 + scrdata[0] * 0.11);

                data[i*bytesPerLine+j]  = gray;

                scrdata+=4;
            }

        return MyImage(data,width,height,MyImage::format::GRAY8);
    }
}

MyImage MyCV::Dft22MyImage(MyComplexNumber *scr, int const width, int const height)
{
    // 将傅里叶数组归一化
    // 取模
    double mold[width*height];
    for(int i = 0 ;i<width*height;i++)
    {
        mold[i] = scr[i].get_mold();
    }

    // 获取最小值
    double min = mold[0];
    for(int i = 0;i<width*height;i++)
    {
        if(mold[i]<min)
            min = mold[i];
    }

    // 获取去掉前几大值的最大值
    double maxqueue[20] = {0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.},max;
    for(int i = 0;i<width*height;i++){
        if(mold[i]>maxqueue[0])
            maxqueue[0] = mold[i];
    }
    for(int j =1;j<20;j++){
        for(int i = 0;i<width*height;i++){
            if(mold[i]>maxqueue[j]&&mold[i]<maxqueue[j-1])
                maxqueue[j] = mold[i];
        }
    }
    max = maxqueue[19];

    unsigned char *normalized_data = new unsigned char[width*height];

    for(int i=0;i<height;i++)
        for(int j=0;j<width;j++)
        {
            unsigned char t = (unsigned char)((mold[i*width+j]-min)/(max-min)*255);
            if(t>255)
                t = 255;
            normalized_data[i*width+j]=t;
        }



    // 将图像中心化
    unsigned char* center_data = new unsigned char[width*height];

    for (int u = 0; u<height; u++)
        {
        for (int v = 0; v<width; v++) {
            if ((u<(height / 2)) && (v<(width / 2))) {
                center_data[v + u*width] =
                    normalized_data[width / 2 + v + (height / 2 + u)*width];
            }
            else if ((u<(height / 2)) && (v >= (width / 2))) {
                center_data[v + u*width] =
                    normalized_data[(v - width / 2) + (height / 2 + u)*width];
            }
            else if ((u >= (height / 2)) && (v<(width / 2))) {
                center_data[v + u*width] =
                    normalized_data[(width / 2 + v) + (u - height / 2)*width];
            }
            else if ((u >= (height / 2)) && (v >= (width / 2))) {
                center_data[v + u*width] =
                    normalized_data[(v - width / 2) + (u - height / 2)*width];
            }
        }
    }

    // 向中心化的数组填充空间
    int bytesPerLine = (width*8+31)/32*4;
    unsigned char *dst_data = new unsigned char[bytesPerLine*height];

    for(int i=0;i<height;i++)
        for(int j=0;j<width;j++)
        {
            dst_data[i*bytesPerLine+j] = center_data[i*width+j];
        }

    return MyImage(dst_data,width,height,MyImage::format::GRAY8);
}

//MyMat* MyCV::Conv(MyMat const &scr, const MyKernel &kernel,int span)
//{
//    // 被卷积矩阵和卷积和通道数不匹配
//    if(scr.m_channel != kernel.m_channel)
//        return NULL;

//    // 二维
//    if(scr.m_channel == 1)
//    {
//        int scr_width = scr.m_width;
//        int scr_height = scr.m_height;

//        int ker_width = kernel.m_width;
//        int ker_height = kernel.m_height;

//        int temp_width = scr_width + ker_width -1;
//        int temp_height = scr_height + ker_height -1;

//        int edge_width = (ker_width-1)/2;
//        int edge_height = (ker_height-1)/2;

//        double* temp_data = new double[temp_width*temp_height];

//        double* scr_data = scr.m_data;
//        double* ker_data = kernel.m_data;

//        // 给临时模板复制
//        for(int i=0;i<scr_height;i++)
//            for(int j=0;j<scr_width;j++)
//            {
//                temp_data[(edge_height+i)*temp_width+edge_width+j] = scr_data[i*scr_width+j];
//            }

//        // 填充边缘
//        for(int i=0;i<temp_height;i++)
//            for(int j=0;j<temp_width;j++)
//            {
//                // 左上角
//                if(i<edge_height && j<edge_width)
//                {
//                    temp_data[i*temp_width+j] = scr_data[0];
//                }
//                // 左下角
//                else if(i>=(edge_height+scr_height) && j<edge_width)
//                {
//                    temp_data[i*temp_width+j] = scr_data[(scr_height-1)*scr_width];
//                }
//                // 右上角
//                else if(i<edge_height && j>=(edge_width+scr_width))
//                {
//                    temp_data[i*temp_width+j] = scr_data[scr_width-1];
//                }
//                // 右下角
//                else if(i>=(edge_height+scr_height) && j>=(edge_width+scr_width))
//                {
//                    temp_data[i*temp_width+j] = scr_data[scr_height*scr_width-1];
//                }
//                // 上边
//                else if(i<edge_height && j>=edge_width && j<(edge_width+scr_width))
//                {
//                    temp_data[i*temp_width+j] = scr_data[(j-edge_width)];
//                }
//                // 下边
//                else if(i>=(edge_height+scr_height) && j>=edge_width && j<(edge_width+scr_width))
//                {
//                    temp_data[i*temp_width+j] = scr_data[(scr_height-1)*scr_width+(j-edge_width)];
//                }
//                // 左边
//                else if(i>=edge_height && i<(edge_height+scr_height) && j<edge_width)
//                {
//                    temp_data[i*temp_width+j] = scr_data[i*scr_width];
//                }
//                // 右边
//                else if(i>=edge_height && i<(temp_height-edge_height) && j>=(temp_width-edge_width))
//                {
//                    temp_data[i*temp_width+j] = scr_data[i*scr_width+scr_width-1-edge_width];
//                }
//            }

//        // 目标矩阵
//        int dst_width = scr_width/span;
//        int dst_height = scr_height/span;

//        double* dst_data = new double[dst_width*dst_height];

//        for(int i=0;i<dst_height;i++)
//            for(int j=0;j<dst_width;j++)
//            {
//                double kernel_center = 0;

//                for(int u=0;u<ker_height;u++)
//                    for(int v=0;v<ker_width;v++)
//                    {
//                        // 利用卷积求目标点值
////                        kernel_center += temp_data[(i+u)*temp_width + (j+v)] * ker_data[u*ker_width+v];
//                        kernel_center += temp_data[(i*span+u)*temp_width + (j*span+v)] * ker_data[u*ker_width+v];
//                    }

//                // 将得到的值赋给目标数据
//                dst_data[i*dst_width+j] = kernel_center;


//            }

//        return new MyMat(dst_width,dst_height,1,dst_data);
//    }
//    else
//    {
//        int scr_width = scr.m_width;
//        int scr_height = scr.m_height;

//        int ker_width = kernel.m_width;
//        int ker_height = kernel.m_height;

//        int channel = scr.m_channel;

//        int temp_width = scr_width + ker_width -1;
//        int temp_height = scr_height + ker_height -1;

//        int span_width = (ker_width-1)/2;
//        int span_height = (ker_height-1)/2;

//        double* temp_data = new double[temp_width*temp_height*channel];

//        double* scr_data = scr.m_data;
//        double* ker_data = kernel.m_data;

//        // 给临时模板复制
//        for(int i=0;i<scr_height;i++)
//            for(int j=0;j<scr_width;j++)
//                for(int k=0;k<channel;k++)
//                {
//                    temp_data[((span_height+i)*temp_width+span_width+j)*channel +k] =
//                            scr_data[(i*scr_width+j)*channel+k];
//                }

//        // 目标矩阵
//        double* dst_data = new double[scr_width*scr_height*channel];

//        for(int i=0;i<scr_height;i++)
//            for(int j=0;j<scr_width;j++)
//                for(int k=0;k<channel;k++)
//                {
//                    double kernel_center =0.0;

//                    for(int u=0;u<ker_height;u++)
//                        for(int v=0;u<ker_width;v++)
//                        {
//                            // 利用卷积求目标点值
//                            kernel_center +=
//                                    temp_data[((i+u)*temp_width + (j+v))*channel + k] *
//                                    ker_data[(u*ker_width+v)*channel + k];
//                        }

//                    // 将得到的值赋给目标数据
//                    dst_data[(i*scr_width+j)*channel+k] = kernel_center;
//                }

//        return new MyMat(scr_width,scr_height,channel,dst_data);
//    }
//}

int MyCV::Resize2NearPoint(const MyImage &scr, MyImage &dst, const int dst_width, const int dst_height)
{
    if(scr.m_data == NULL)
        return 0;

    MyMat2 scr_mat = MyImage::MyImage2MyMat2(scr);
    MyMat2 dst_mat = MyMat2(dst_width,dst_height,0.0);

    for(int i=0;i<dst_height;i++)
        for(int j=0;j<dst_width;j++)
        {
            int temp_row = i*scr.m_height/dst_height;
            int temp_col = j*scr.m_width/dst_width;

            double temp_value = scr_mat.GetPointValue2(temp_row,temp_col);

            dst_mat.SetPointValue2(i,j,temp_value);
        }

    MyImage::CopyMyImage(MyImage(dst_mat),dst);

    return 1;
}


int MyCV::Resize2BiLinear(const MyImage &scr, MyImage &dst, const int dst_width, const int dst_height)
{
    if(scr.m_data == NULL)
        return 0;

    MyMat2 scr_mat = MyImage::MyImage2MyMat2(scr);
    MyMat2 dst_mat = MyMat2(dst_width,dst_height,0.0);

    int src_width = scr.m_width;
    int src_height = scr.m_height;

    double w_mul = dst_width/(double)src_width;
    double h_mul = dst_height/(double)src_height;

    // 整体缩小
    if(w_mul<1 && h_mul<1)
        for(int i=0;i<dst_height;i++)
            for(int j=0;j<dst_width;j++)
            {
                // 对应坐标整数部分
                // 0.5 是防止数据左偏
                int row = (int)((i+0.5)*src_height/dst_height-0.5);
                int col = (int)((j+0.5)*src_width/dst_width -0.5);
                //对应坐标小数部分
                double row_p = (i+0.5)*src_height/(double)dst_height-0.5 - row;
                double col_p = (j+0.5)*src_width/(double)dst_width-0.5 - col;

                double a = scr_mat.GetPointValue2(row,col);
                double b = scr_mat.GetPointValue2(row,col+1);
                double c = scr_mat.GetPointValue2(row+1,col);
                double d = scr_mat.GetPointValue2(row+1,col+1);

                double a_weight = (1-row_p)*(1-col_p);
                double b_weight = (1-row_p)*col_p;
                double c_weight = row_p*(1-col_p);
                double d_weight = row_p*col_p;

                double temp_value = a*a_weight + b*b_weight + c*c_weight + d*d_weight;

                dst_mat.SetPointValue2(i,j,temp_value);
            }

    // 存在放大
    else
        for(int i=0;i<dst_height;i++)
            for(int j=0;j<dst_width;j++)
            {
                // 对应坐标整数部分
                // 0.5 是防止数据左偏
                int row = (int)((i+0.5)*src_height/dst_height-0.5);
                int col = (int)((j+0.5)*src_width/dst_width -0.5);
                //对应坐标小数部分
                double row_p = (i+0.5)*src_height/(double)dst_height-0.5 - row;
                double col_p = (j+0.5)*src_width/(double)dst_width-0.5 - col;

                double a = scr_mat.GetPointValue2IncOut(row,col);
                double b = scr_mat.GetPointValue2IncOut(row,col+1);
                double c = scr_mat.GetPointValue2IncOut(row+1,col);
                double d = scr_mat.GetPointValue2IncOut(row+1,col+1);

                double a_weight = (1-row_p)*(1-col_p);
                double b_weight = (1-row_p)*col_p;
                double c_weight = row_p*(1-col_p);
                double d_weight = row_p*col_p;

                double temp_value = a*a_weight + b*b_weight + c*c_weight + d*d_weight;

                dst_mat.SetPointValue2(i,j,temp_value);
            }

    MyImage::CopyMyImage(MyImage(dst_mat),dst);

    return 1;
}

