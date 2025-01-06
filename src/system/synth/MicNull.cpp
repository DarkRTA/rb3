#include "synth/MicNull.h"

Rand MicNull::sRand(0x1bca7);

MicNull::MicNull(){
    for(int i = 0; i < 10000U; i++){
        mBuf[i] = sRand.Int(-32000, 32000);
    }
}

char* MicNull::GetRecentBuf(int& i){
    i = 0x600;
    memcpy(buf_0xC, mBuf, 0xC00);
    return buf_0xC;
}

char* MicNull::GetContinuousBuf(int& i){
    mTimer.Restart();
    i = ((int)GetSampleRate() / 1000) * mTimer.GetLastMs();
    MinEq(i, 10000);
    int num = i % 8;
    if(num != 0) i += num;
    memcpy(filler, mBuf, i * 2);
    return filler;
}

int MicNull::GetSampleRate() const { return 48000; }