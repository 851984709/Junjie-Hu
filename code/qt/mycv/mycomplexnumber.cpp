#include "mycomplexnumber.h"

MyComplexNumber::MyComplexNumber()
{
    m_rl = 0;
    m_im = 0;
}

MyComplexNumber::MyComplexNumber(double rl, double im)
{
    m_rl = rl;
    m_im = im;
}

void MyComplexNumber::SetValue(double rl, double im)
{
    m_rl = rl;
    m_im = im;
}

double MyComplexNumber::get_mold()
{
    double mold;
    mold = sqrt(m_rl*m_rl+m_im*m_im);

    return mold;
}

