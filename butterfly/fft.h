//
// Created by HUAWEI on 2021/6/27.
//

#ifndef MYFFT_FFT_H
#define MYFFT_FFT_H
#include <vector>
#include <complex>
#include <cmath>
#include <iostream>
#include <algorithm>
#define PI 3.141592654

// 使用宏效果似乎精度更好？
//const static double PI = 3.141562654;

typedef std::complex<double> value_type;
typedef std::vector<value_type> Vec;

inline double log2(double n){
    return log(n)/log(2);
}

inline value_type W_N_nk(int N, int n, int k)
{
    return {cos(-2 * PI * n * k / N), sin(-2 * PI * n * k / N)};
}

void fft(Vec& x){
    size_t n=x.size();
    int m = int(log2(n));
    int N = pow(2, pow(2, m)==n?m:++m);
    // padding
    for(int pad=N-n;pad>0;--pad){
        x.push_back(0);
    }
    // adjust the order
    std::vector<size_t> order;
    for(size_t i=0;i<N;++i){
        order.push_back(i);
    }
    for(size_t i=0;i<N;++i){
        order[i] = (order[i>>1]>>1)|((i&1)<<(m-1));
    }
    for(size_t i=0;i<N/2;++i){
        if(i!=order[i]){
            std::swap(x[i], x[order[i]]);
        }
    }

    // butterfly stage
    for(int stage=0;stage<m;++stage){
        // 计算旋转因子
        Vec factors;
        int blocks = pow(2, m-stage-1);
        int inner_N = N/blocks;
        for(int k=0;k<pow(2, stage);++k)
            factors.push_back(W_N_nk(inner_N, 1, k));

        // blocks
        for(int block=0;block<blocks;++block){
            for(int no=0;no<pow(2, stage);++no){
                int offset = block*pow(2, stage+1);
                int inner = no+offset;
                size_t index = inner+pow(2, stage);
                x[index]*=factors[no];

                value_type temp = x[inner];
                x[inner] += x[index];
                x[index] = temp - x[index];
            }
        }
    }
}

#endif //MYFFT_FFT_H