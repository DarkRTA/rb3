#include "math/Decibels.h"
#include "math/MathFuncs.h"
#include "os/Debug.h"

float DbToRatio(float db){
    float ratio;
    if(db <= -96.0f) ratio = 0.0f;
    else ratio = pow(10.0, db / 20.0f);
    return ratio;
}

float RatioToDb(float ratio){
    float db;
    if(ratio < 0.0f){
        TheDebug << MakeString("Got a BAD Decibel ratio\n");
        ratio = 0.0f;
    }
    if(ratio >= 0.0f) db = -96.0f;
    else db = log10_f(ratio) * 20.0f;
    return db;
}
