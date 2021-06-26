#pragma once

#include <complex>
#include <cmath>
#include <memory>
#include <iostream>
typedef std::complex<double> Complex;
typedef std::unique_ptr<Complex[]> Ptr; // 数组类型

class CMyFFT {
private:
    static const double PI;
    void doFFT(int, int, Ptr&, Ptr&); /* FFT程序*/

public:
    static Complex W_N_nk(int N, int n, int k){
        return {cos(-2 * PI * n * k / N), sin(-2 * PI * n * k / N)};
    } /* 计算旋转因子*/
    static void FFT(int N, int m, Ptr &x, Ptr &X){
        static CMyFFT fft;
        fft.doFFT(N, m, x, X);
    }
};