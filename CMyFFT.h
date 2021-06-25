#pragma once

#include "CComplex.h"
#include <math.h>
#include <iostream>

// 构成仿函数，
class CMyFFT {
private:
    CComplex *ou = nullptr;
    CComplex *ji = nullptr;
    CComplex *Ak = nullptr;
    CComplex *Bk = nullptr;
    const double PI = 3.141592654;

    CMyFFT(int N=1024): ou(new CComplex[N / 2]), ji(new CComplex[N / 2]),
        Ak(new CComplex[N / 2]), Bk(new CComplex[N / 2]){ };

    void doFFT(int N, int m, CComplex *x, CComplex *X); /* FFT程序*/

    CComplex W_N_nk(int N, int n, int k){
        return CComplex(cos(-2 * PI * n * k / N), sin(-2 * PI * n * k / N));
    } /* 计算旋转因子*/

public:
    ~CMyFFT() {
        delete[] ou;
        delete[] ji;
        delete[] Ak;
        delete[] Bk;
    }
    static void FFT(int N, int m, CComplex *x, CComplex *X){
        static CMyFFT fft(N);
        fft.doFFT(N, m, x, X);
    }
};