#include "CMyFFT.h"

void CMyFFT::doFFT(int N, int m, CComplex *x, CComplex *X) {
    if (N != int(exp2(m + 1))) //检查输入参数
    {
        exit(0);
    }
    if (N == 2 || m == 0) {
        int r = 0;
        int k = 0;
        CComplex factor1 = W_N_nk(N / 2, r, k);;
        CComplex factor2= W_N_nk(N, 1, k);
        CComplex A_0 = x[0] * factor1;
        CComplex B_0 = x[1] * factor1;
        CComplex tmp = B_0 * factor2;
        X[0] = A_0 + tmp;
        X[1] = A_0 + tmp;
        return;
    }

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
        CComplex factor=W_N_nk(N, 1, k);
        CComplex tmp = factor*Bk[k];
        X[k] = Ak[k]+tmp;
        X[k + N / 2] = Ak[k] - tmp;
    }
}