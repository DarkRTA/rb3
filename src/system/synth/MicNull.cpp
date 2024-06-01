#include "synth/MicNull.h"

Rand MicNull::sRand(0x1bca7);

MicNull::MicNull(){
    for(int i = 0; i < 10000U; i++){
        mBuf[i] = sRand.Int(-32000, 32000);
    }
}

void MicNull::GetRecentBuf(int& i){

}

void MicNull::GetContinuousBuf(int& i){
    
}