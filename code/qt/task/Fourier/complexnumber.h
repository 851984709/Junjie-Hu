#ifndef COMPLEXNUMBER_H
#define COMPLEXNUMBER_H

#include <QDebug>

class ComplexNumber
{
public:
    ComplexNumber(double rl,double im);
    ComplexNumber();

public:
    // 重载四则运算符号
    ComplexNumber operator +(const ComplexNumber &c){
        return ComplexNumber(m_rl+c.m_rl,m_im+c.m_im);
    }
    ComplexNumber operator -(const ComplexNumber &c){
        return ComplexNumber(m_rl-c.m_rl,m_im-c.m_im);
    }
    ComplexNumber operator *(const ComplexNumber &c){
        return ComplexNumber(m_rl*c.m_rl-m_im*c.m_im,
                             m_rl*c.m_im+m_im*c.m_rl);
    }
    ComplexNumber operator /(const ComplexNumber &c) {
            if ((0==c.m_rl) && (0==c.m_im)) {
                qDebug()<<"ERROR: divider is 0!";
                return ComplexNumber(m_rl, m_im);
            }
            return ComplexNumber((m_rl*c.m_rl + m_im*c.m_im) / (c.m_rl*c.m_rl + c.m_im*c.m_im),
                (m_im*c.m_rl - m_rl*c.m_im) / (c.m_rl*c.m_rl + c.m_im*c.m_im));
        }
    void SetValue(double rl, double im);
    double get_mold();

public:
    double m_rl,m_im;
};

#endif // COMPLEXNUMBER_H
