//
// Created by HUAWEI on 2021/7/1.
//

#ifndef MYLIB_STFT_H
#define MYLIB_STFT_H

#include <vector>
#include <string>
#include <complex>

#include "fft.h"
#include <cmath>
#include <string>
#include <iostream>
#include <cassert>
#define PI 3.141592654

typedef std::complex<double> stft_value_type;
typedef std::vector<stft_value_type> stft_vec;
typedef std::vector<stft_vec> stft_maxtrix;

std::vector<double> get_window(std::string win, int M, bool fftbins=true);

// 默认周期窗口，给dft偶数情况使用, 改成false是对称窗口
std::vector<double> hamming(int M, bool sym=true);
std::vector<double> blackman(int M, bool sym=true);
std::vector<double> hann(int M, bool sym=true);

stft_maxtrix stft(std::vector<double>y, int n_fft=2048, int hop_len=-1, int win_len=-1,
                  std::string win="hann", bool center=true, std::string padmode="reflect");
std::vector<double>& pad_center(std::vector<double>&data, int len, std::string padmode);

#endif //MYLIB_STFT_H
