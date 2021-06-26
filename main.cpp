#include "CMyFFT.h "
#include <complex>
using namespace std;
int main()
{
    int m = 3;
    int N = int(exp2(m));
    complex<double> x[8];
    complex<double> X[8];

     for (int i = 0; i < N;i++) {
         x[i].real(i);
         x[i].imag(i);
     }
     CMyFFT::FFT(N, m-1, x, X);

     cout<<"right"<<endl;

     for(int i=0;i<8;i++)
         cout<<X[i].real()<<", "<< X[i].imag()<<"i"<<endl;

     // 使用基本计算方法来进行计算
     complex<double> Y[8];
     for(int k=0;k<8;++k)
         for(int n=0;n<8;++n)
             Y[k]=Y[k]+x[n]*CMyFFT::W_N_nk(8, n ,k);

     cout<<"my"<<endl;

     for(int i=0;i<8;++i)
         cout<<Y[i].real()<<", "<<Y[i].imag()<<"i"<<endl;

     return 0;
 }