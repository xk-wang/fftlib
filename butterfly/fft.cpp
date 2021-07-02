//
// Created by HUAWEI on 2021/7/2.
//

# include "fft.h"

inline value_type W_N_nk(int N, int n, int k)
{
    return {cos(-2 * PI * n * k / N), sin(-2 * PI * n * k / N)};
}

inline double amplitude(value_type x){
    double real=x.real();
    double img=x.imag();
    return sqrt(real*real+img*img);
}

inline std::vector<double> amplitude(Vec x){
    size_t nums = x.size();
    std::vector<double>ans(nums);
    for(size_t i=0;i<nums;++i){
        ans[i]=amplitude(x[i]);
    }
    return ans;
}

inline double phase(value_type x){
    double real=x.real();
    double am = amplitude(x);
    if(abs(am)<1e-7) return 0;
    return acos(real/am);
}

inline std::vector<double> phase(Vec x){
    size_t nums = x.size();
    std::vector<double>ans(nums);
    for(size_t i=0;i<nums;++i){
        ans[i]=phase(x[i]);
    }
    return ans;
}

Vec& fft(Vec& x){
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
    return x;
}

Vec rfft(Vec& x){
    size_t nums = x.size();
    Vec data_fft = fft(x);
    return {data_fft.begin(), data_fft.begin()+nums/2+1};
}