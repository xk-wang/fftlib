//
// Created by HUAWEI on 2021/6/27.
//

#ifndef MYLIB_FFT_H
#define MYLIB_FFT_H
#include <vector>
#include <complex>
#include <cmath>
#define PI 3.141592654

typedef std::complex<double> value_type;
typedef std::vector<value_type> Vec;

inline value_type W_N_nk(int N, int n, int k);

inline double amplitude(value_type x);

inline std::vector<double> amplitude(Vec x);

inline double phase(value_type x);

inline std::vector<double> phase(Vec x);

Vec& fft(Vec& x);

Vec rfft(Vec& x);

#endif //MYLIB_FFT_H