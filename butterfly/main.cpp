#include <iostream>
#include <complex>
#include "fft.h"
#include "stft.h"

int main() {
//    Vec x;
    int m=5, N=32;
//    for(size_t i=0;i<N;++i)
//        x.push_back({double(i+1),0}); // 必须要包装成复数
//    x = rfft(x);
//    for(int i=0;i<x.size();++i)
//        std::cout<<x[i]<<std::endl;

    std::vector<double>y;
    for(size_t i=0;i<N;++i)
        y.push_back(i);

    auto output=stft(y,4, 2);
    int row = output.size();
    int col = output[0].size();
    for(int i=0;i<row;++i){
        for(int j=0;j<col;++j){
            std::cout<<output[i][j]<<" ";
        }
        std::cout<<std::endl;
    }

    return 0;
}
