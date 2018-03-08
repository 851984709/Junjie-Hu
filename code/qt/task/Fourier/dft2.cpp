#include "dft2.h"


Dft2::Dft2(QImage image)
{
    if(image.format()!=QImage::Format_Grayscale8)
        qDebug()<<"Image is not gray!";

    m_scrimage = image;
    m_width = image.width();
    m_height = image.height();
    m_data = image.bits();
    m_bytesPerLine = image.bytesPerLine();

    m_scrmatrix = new double[m_width*m_height];

    // 将data转化为double型
    for(int i=0;i<m_height;i++)
        for(int j=0;j<m_width;j++)
        {
            m_scrmatrix[i*m_width+j]=(double)m_data[i*m_bytesPerLine+j];
        }

    m_dft2_matrix = get_dft2_matrix();
    m_normalized_data = get_normalized_matrix();
    m_center_matrix = get_center_matrix();
    m_dst_image = get_dst_image();
}

ComplexNumber* Dft2::get_dft2_matrix()
{
    ComplexNumber *dft2_matrix = new ComplexNumber[m_width*m_height];
    double fixed_factor_for_axisX = (-2 * PI) / m_height;
    // evaluate -i2π/N of -i2πux/N, and store the value for computing efficiency
    double fixed_factor_for_axisY = (-2 * PI) / m_width;
    // evaluate -i2π/N of -i2πux/N, and store the value for computing efficiency

    for (int u = 0; u<m_height; u++) {
            for (int v = 0; v<m_width; v++) {
                for (int x = 0; x<m_height; x++) {
                    for (int y = 0; y<m_width; y++) {
                        double powerX = u * x * fixed_factor_for_axisX; // evaluate -i2πux/N
                        double powerY = v * y * fixed_factor_for_axisY; // evaluate -i2πux/N
                        ComplexNumber cplTemp;
                        cplTemp.m_rl = m_scrmatrix[y + x*m_width] * cos(powerX + powerY);
                        // evaluate f(x) * e^(-i2πux/N), which is equal to f(x) * (cos(-i2πux/N)+sin(-i2πux/N)i) according to Euler's formula
                        cplTemp.m_im = m_scrmatrix[y + x*m_width] * sin(powerX + powerY);
                        dft2_matrix[v + u*m_width] = dft2_matrix[v + u*m_width] + cplTemp;
                    }
                }
            }
        }

    return dft2_matrix;
}

unsigned char* Dft2::get_normalized_matrix()
{
    // 取模
    double mold[m_width*m_height];
    for(int i = 0 ;i<m_width*m_height;i++){
        mold[i] = m_dft2_matrix[i].get_mold();
    }

    double max=getmax(mold,m_width*m_height);
    double min=getmin(mold,m_width*m_height);

    qDebug()<<(int)max;
    qDebug()<<(int)min;

    unsigned char *normalized_data = new unsigned char[m_width*m_height];//存储处理后的数据

    for(int i=0;i<m_height;i++)
        for(int j=0;j<m_width;j++)
        {
            unsigned char t = (unsigned char)((mold[i*m_width+j]-min)/(max-min)*255);
            if(t>255)
                t = 255;
            normalized_data[i*m_width+j]=t;
//            qDebug()<<t;
        }

    return normalized_data;
}


unsigned char* Dft2::get_center_matrix()
{
    unsigned char* data = new unsigned char[m_bytesPerLine*m_height];

    for (int u = 0; u<m_height; u++)
        {
        for (int v = 0; v<m_width; v++) {
            if ((u<(m_height / 2)) && (v<(m_width / 2))) {
                data[v + u*m_width] =
                    m_normalized_data[m_width / 2 + v + (m_height / 2 + u)*m_width];
            }
            else if ((u<(m_height / 2)) && (v >= (m_width / 2))) {
                data[v + u*m_width] =
                    m_normalized_data[(v - m_width / 2) + (m_height / 2 + u)*m_width];
            }
            else if ((u >= (m_height / 2)) && (v<(m_width / 2))) {
                data[v + u*m_width] =
                    m_normalized_data[(m_width / 2 + v) + (u - m_height / 2)*m_width];
            }
            else if ((u >= (m_height / 2)) && (v >= (m_width / 2))) {
                data[v + u*m_width] =
                    m_normalized_data[(v - m_width / 2) + (u - m_height / 2)*m_width];
            }
        }
    }

    unsigned char *center_data = new unsigned char[m_bytesPerLine*m_height];//存储处理后的数据

    for(int i=0;i<m_height;i++)
        for(int j=0;j<m_width;j++)
        {
            center_data[i*m_bytesPerLine+j] = data[i*m_width+j];
        }

    return center_data;
}

QImage* Dft2::get_dst_image()
{
    QImage *dst_image = new QImage(m_center_matrix,m_width,m_height,m_bytesPerLine,QImage::Format_Grayscale8);

    return dst_image;
}

double Dft2::getmax(double mold[], int size)
{
    double maxqueue[5] = {0.,0.,0.,0.,0.},max;

    // 获取最大值
    for(int i = 0;i<size;i++){
        if(mold[i]>maxqueue[0])
            maxqueue[0] = mold[i];
    }
    // 重小到大排序
    for(int j =1;j<5;j++){
        for(int i = 0;i<size;i++){
            if(mold[i]>maxqueue[j]&&mold[i]<maxqueue[j-1])
                maxqueue[j] = mold[i];
        }
    }
    // 忽略前几个个最大值
    max = maxqueue[4];

    return max;
}

double Dft2::getmin(double mold[], int size)
{
    double min;
    // 获取最小值
    min = mold[0];
    for(int i = 0;i<size;i++){
        if(mold[i]<min)
            min = mold[i];
    }

    return min;
}
