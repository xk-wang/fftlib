//
// Created by HUAWEI on 2021/7/1.
//

#include "stft.h"

std::vector<double> _hamming(int M){
    std::vector<double>ans(M);
    for(int i=0;i<M;++i){
        ans[i]=0.54-0.46*cos(2*PI*i/(M-1));
    }
    return ans;
}

std::vector<double> hamming(int M, bool sym){
    if(sym) return _hamming(M);
    std::vector<double>ans=_hamming(M+1);
    return {ans.begin(), ans.end()-1};
}

std::vector<double> _blackman(int M){
    std::vector<double>ans(M);
    for(int i=0;i<M;++i){
        ans[i]=0.42-0.5*cos(2*PI*i/(M-1))+0.08*cos(4*PI*i/(M-1));
    }
    return ans;
}

std::vector<double> blackman(int M, bool sym){
    if(sym) return _blackman(M);
    std::vector<double>ans=_blackman(M+1);
    return {ans.begin(), ans.end()-1};
}

std::vector<double> _hann(int M){
    std::vector<double> ans(M);
    for(int i=0;i<M;++i){
        ans[i]=0.5-0.5*cos(2*PI*i/(M-1));
    }
    return ans;
}

std::vector<double> hann(int M, bool sym){
    if(sym) return _hann(M);
    std::vector<double> ans=_hann(M+1);
    return {ans.begin(), ans.end()-1};
}

std::vector<double> get_window(std::string win, int M, bool fftbins){
    bool sym=!fftbins;
    if("hamming"==win) return hamming(M, sym);
    if("blackman"==win) return blackman(M, sym);
    if("hann"==win) return hann(M, sym);
    std::cerr<<"wrong win name!"<<std::endl;
    exit(1);
}

std::vector<double>& pad_center(std::vector<double>&data, int len){
    size_t nums=data.size();
    int pad_front = (len-nums)/2;
    int pad_end = len-nums-pad_front;

    data.insert(data.begin(), pad_front, 0);
    data.insert(data.end(), pad_end,0);
    return data;

}

std::vector<double>& pad_center(std::vector<double>&data, int len, std::string padmode){
    size_t nums=data.size();
    int pad_front = len/2;
    int pad_end = len-pad_front;

    if("reflect"==padmode){
        for(int i=0;i<pad_front;++i){
            data.insert(data.begin(), data[2*i+1]);
        }
        for(int i=0;i<pad_end;++i){
            data.insert(data.end(), *(data.end()-2*(i+1)));
        }
    }
    else if("constant"==padmode){
        // 放最后来实现默认的值
        data.insert(data.begin(), pad_front, 0);
        data.insert(data.end(), pad_end,0);
    }
    else{
        std::cerr<<"wrong padmode!"<<std::endl;
        exit(1);
    }
    return data;

}

bool check_power2(int n){
    return n==pow(2, int(log2(n)));
}

stft_maxtrix stft(std::vector<double>y, int n_fft, int hop_len, int win_len,
                  std::string win, bool center, std::string padmode){
    size_t len = y.size();
    assert(n_fft<=len);
    if(win_len==-1) win_len=n_fft;
    if(hop_len==-1) hop_len=win_len/4;
    // 需要进行判断是否n_fft和win_len是2的幂
    assert(check_power2(n_fft)&&check_power2(win_len));

    std::vector<double>fft_win=get_window(win, win_len);
    fft_win = pad_center(fft_win, win_len);
    y = pad_center(y, n_fft, padmode);
    len = y.size();

    // 分帧计算
    int frame_len = (len-n_fft)/hop_len+1;
    int freq_len = n_fft/2+1;
    stft_maxtrix stfmatrix(frame_len, stft_vec(freq_len));
    std::vector<double>::iterator begin = y.begin();
    std::vector<std::complex<double>>segment(n_fft);
    for(int i=0;i<frame_len;++i){
        auto offset = begin+i*hop_len;
        for(int k=0;k<n_fft;++k){
            segment[k]={*(offset+k)*fft_win[k],0};
        }
        stfmatrix[i]=rfft(segment);
    }
    return stfmatrix;
}