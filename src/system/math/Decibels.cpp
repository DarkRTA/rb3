#include "math/Decibels.h"
#include "math/MathFuncs.h"
#include "os/Debug.h"

float DbToRatio(float db){
    float ratio;
    if(db <= -96.0f) ratio = 0.0f;
    else ratio = pow_f(10.0, db / 20.0f);
    return ratio;
}

float RatioToDb(float ratio){
    if(ratio < 0.0f){
        ratio = 0.0f;
        MILO_LOG("Got a BAD Decibel ratio\n");
    }
    return (ratio <= 0.0f) ? -96.0f : log10_f(ratio) * 20.0f;
}
