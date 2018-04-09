#ifndef MYCOMPLEXNUMBER_H
#define MYCOMPLEXNUMBER_H

#include <math.h>

class MyComplexNumber
{
public:
    MyComplexNumber(double rl,double im);
    MyComplexNumber();

public:
    // 重载四则运算符号
    MyComplexNumber operator +(const MyComplexNumber &c){
        return MyComplexNumber(m_rl+c.m_rl,m_im+c.m_im);
    }
    MyComplexNumber operator -(const MyComplexNumber &c){
        return MyComplexNumber(m_rl-c.m_rl,m_im-c.m_im);
    }
    MyComplexNumber operator *(const MyComplexNumber &c){
        return MyComplexNumber(m_rl*c.m_rl-m_im*c.m_im,
                             m_rl*c.m_im+m_im*c.m_rl);
    }
    MyComplexNumber operator /(const MyComplexNumber &c) {
            if ((0==c.m_rl) && (0==c.m_im)) {
                return MyComplexNumber(m_rl, m_im);
            }
            return MyComplexNumber((m_rl*c.m_rl + m_im*c.m_im) / (c.m_rl*c.m_rl + c.m_im*c.m_im),
                (m_im*c.m_rl - m_rl*c.m_im) / (c.m_rl*c.m_rl + c.m_im*c.m_im));
        }
    void SetValue(double rl, double im);
    double get_mold();

public:
    double m_rl,m_im;
};

#endif // MYCOMPLEXNUMBER_H
