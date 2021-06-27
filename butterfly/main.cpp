#include <iostream>
#include <complex>
#include "fft.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    Vec x;
    int m=3, N=8;
    for(size_t i=0;i<N;++i)
        x.push_back({double(i), double(i)});
    fft(x);
    for(int i=0;i<N;++i)
        std::cout<<x[i]<<std::endl;
    return 0;
}
