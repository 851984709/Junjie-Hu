#include "complexnumber.h"

ComplexNumber::ComplexNumber()
{
    m_rl = 0;
    m_im = 0;
}

ComplexNumber::ComplexNumber(double rl, double im)
{
    m_rl = rl;
    m_im = im;
}

void ComplexNumber::SetValue(double rl, double im)
{
    m_rl = rl;
    m_im = im;
}

double ComplexNumber::get_mold()
{
    double mold;
    mold = sqrt(m_rl*m_rl+m_im*m_im);

    return mold;
}
