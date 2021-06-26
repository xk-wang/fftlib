#include "CMyFFT.h"

const double CMyFFT::PI = 3.141592654;

void CMyFFT::doFFT(int N, int m, Complex *x, Complex *X) {
    if (N != int(exp2(m + 1))) //检查输入参数
    {
        exit(0);
    }
    if (N == 2 || m == 0) {
        Complex tmp = x[0];
        X[0] = x[0] + x[1];
        X[1] = tmp - x[1];
        return;
    }

    Complex *ou = new Complex[N / 2];
    Complex *ji = new Complex[N / 2];
    Complex *Ak = new Complex[N / 2];
    Complex *Bk = new Complex[N / 2];

    for (int i = 0; i < N; i++) {
        if (i % 2 == 0) {
            ou[i / 2] = x[i];
        } else {
            ji[i / 2] = x[i];
        }
    }
    //求出Ak 和 Bk
    doFFT(N / 2, m - 1, ou, Ak);
    doFFT(N / 2, m - 1, ji, Bk);
    for (int k = 0; k < N / 2; k++) {
        Complex factor = W_N_nk(N, 1, k);
        Complex tmp = factor * Bk[k];
        X[k] = Ak[k] + tmp;
        X[k + N / 2] = Ak[k] - tmp;
    }

    delete[] ou;
    delete[] ji;
    delete[] Ak;
    delete[] Bk;
}