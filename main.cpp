#include "CComplex.h"
#include "CMyFFT.h "
using namespace std;
int main()
{
    int m = 3;
    int N = int(exp2(m));
    CComplex x[8];
    CComplex X[8];

     for (int i = 0; i < N;i++) {
         x[i].setReal(i);
         x[i].setImg(i);
     }
     CMyFFT::FFT(N, m-1, x, X);

     for(int i=0;i<8;i++)
         cout<<X[i].getReal()<<", "<< X[i].getImg()<<"i"<<endl;

     return 0;
 }