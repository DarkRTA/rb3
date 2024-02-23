#include "math/Trig.h"
#include "math/Math_f.h"
#include "obj/Data.h"

float gBigSinTable[0x200];

extern void DataRegisterFunc(Symbol, DataNode (*)(DataArray *));

void TrigTableInit() {
    int i;
    for (i = 0; i < 256; i++) {
        gBigSinTable[i * 2] = sin_f(0.024543693f * i);
        if (i != 0) {
            gBigSinTable[i * 2 - 1] = gBigSinTable[i * 2] - gBigSinTable[i * 2 - 2];
        }
    }
    int tmp = (i - 1) * 2;
    *(gBigSinTable + tmp + 1) = sin_f(0.024543693f * i) - *(gBigSinTable + tmp);
}

void TrigTableTerminate() {
}

inline float Lookup(float arg8) {
    int temp_r5 = (int)arg8;
    int idx = (temp_r5 & 0xFF) * 2;
    float *offset = &gBigSinTable[idx];
    float res = arg8 - (float)temp_r5;
    return (res * offset[1]) + offset[0];
}

float Sine(float arg8) {
    if (arg8 < 0.0f) {
        return -Lookup(-arg8 * 40.743664f);
    } else
        return Lookup(arg8 * 40.743664f);
}

float FastSin(float f) {
    if (f < 0.0f) {
        return -gBigSinTable[((int)(-40.743664f * f + 0.49998999f) & 0xFF) * 2];
    } else
        return gBigSinTable[((int)(40.743664f * f + 0.49998999f) & 0xFF) * 2];
}

inline float DegreesToRadians(float deg) {
    return 0.017453292f * deg;
}

DataNode DataSin(DataArray *da) {
    return DataNode(sin_f(DegreesToRadians(da->Float(1))));
}

DataNode DataCos(DataArray *da) {
    return DataNode((float)cos(DegreesToRadians(da->Float(1))));
}

DataNode DataTan(DataArray *da) {
    return DataNode((float)tan(DegreesToRadians(da->Float(1))));
}

inline float RadiansToDegrees(float rad) {
    return 57.295776f * rad;
}

inline bool IsNan(float f) {
    return (f == f) ? false : true;
}

DataNode DataASin(DataArray *da) {
    float f = da->Float(1);
    if(IsNan(f)) return DataNode(0.0f);
    else return DataNode(RadiansToDegrees((float)asin(f)));
}

DataNode DataACos(DataArray *da) {
    float f = da->Float(1);
    if(IsNan(f)) return DataNode(0.0f);
    else return DataNode(RadiansToDegrees((float)acos(f)));
}

DataNode DataATan(DataArray *da) {
    float f = da->Float(1);
    if(IsNan(f)) return DataNode(0.0f);
    else return DataNode(RadiansToDegrees(atan_f(f)));
}

void TrigInit() {
    DataRegisterFunc("sin", DataSin);
    DataRegisterFunc("cos", DataCos);
    DataRegisterFunc("tan", DataTan);
    DataRegisterFunc("asin", DataASin);
    DataRegisterFunc("acos", DataACos);
    DataRegisterFunc("atan", DataATan);
}
