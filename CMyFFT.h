#pragma once

#include <complex>
#include <math.h>
#include <iostream>

class CMyFFT {

private:
    typedef std::complex<double> Complex;
    static const double PI;
    void doFFT(int N, int m, Complex *x, Complex *X); /* FFT程序*/


public:
    ~CMyFFT() {
    }
    static std::complex<double> W_N_nk(int N, int n, int k){
        return {cos(-2 * PI * n * k / N), sin(-2 * PI * n * k / N)};
    } /* 计算旋转因子*/
    static void FFT(int N, int m, Complex *x, Complex *X){
        static CMyFFT fft;
        fft.doFFT(N, m, x, X);
    }
};