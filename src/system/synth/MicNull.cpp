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
    float f = GetSampleRate();
    memcpy(filler, mBuf, i * 2);
    return filler;
}