#pragma once

#include "CComplex.h"
#include <math.h>
#include <iostream>

class CMyFFT {
private:
    static const double PI;
    void doFFT(int N, int m, CComplex *x, CComplex *X); /* FFT程序*/


public:
    ~CMyFFT() {
    }
    static::CComplex W_N_nk(int N, int n, int k){
        return CComplex(cos(-2 * PI * n * k / N), sin(-2 * PI * n * k / N));
    } /* 计算旋转因子*/
    static void FFT(int N, int m, CComplex *x, CComplex *X){
        static CMyFFT fft;
        fft.doFFT(N, m, x, X);
    }
};