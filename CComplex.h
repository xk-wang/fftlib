#pragma once

#include <math.h>

class CComplex/*复数运算类*/
{
private:
    double m_real;   /*实部*/
    double m_img;   /*虚部*/

public:
    /*构造函数和析构函数*/
    CComplex() : m_real(0), m_img(0) {};

    CComplex(double real, double img) : m_real(real), m_img(img) {};

    /* setters & getters */
    void setReal(double value) { m_real = value; };

    double getReal() const { return m_real; };

    void setImg(double value) { m_img = value; };

    double getImg() const { return m_img; }

    friend CComplex operator+(const CComplex &c1, const CComplex &c2) {
        return CComplex(c1.m_real + c2.m_real, c1.m_img + c2.m_img);
    }

    CComplex & operator+=(const CComplex &rhs){
        setReal(m_real+rhs.m_real);
        setImg(m_img+rhs.m_img);
        return *this;
    }

    friend CComplex operator-(const CComplex &c1, const CComplex &c2) {
        return CComplex(c1.m_real - c2.m_real, c1.m_img - c2.m_img);
    }

    friend CComplex operator*(const CComplex &c1, const CComplex &c2) {
        double a = c1.m_real;
        double b = c1.m_img;
        double c = c2.m_real;
        double d = c2.m_img;
        double _real = a * c - b * d;
        double _img = a * d + b * c;
        return CComplex(_real, _img);
    }

    double getModulus() { return sqrt(m_real * m_real + m_img * m_img); };    //模长计算
    double getAngle() {
        double modulus = getModulus();
        if (modulus == 0) {
            return 0;
        } else {
            return acos(m_real / modulus);
        }
    };
};