#include "Trig.h"

#include <math.h>
#include "utl/Symbol.h"
#include "common.hpp"

float gBigSinTable[0x200];

// fn_802E2E28
void TrigTableInit() {
    int i;
    for (i = 0; i < 256; i++) {
        gBigSinTable[i * 2] = SinFloat(0.024543693f * i);
        if (i != 0) {
            gBigSinTable[i * 2 - 1] = gBigSinTable[i * 2] - gBigSinTable[i * 2 - 2];
        }
    }
    int tmp = (i - 1) * 2;
    *(gBigSinTable + tmp + 1) = SinFloat(0.024543693f * i) - *(gBigSinTable + tmp);
}

#pragma force_active on
// fn_802E2F34
void TrigTableTerminate() {
}
#pragma force_active reset

// fn_802E2F38
float Sine(float arg8) {
    if (arg8 < 0.0f) {
        return -Lookup(-arg8 * 40.743664f);
    } else
        return Lookup(arg8 * 40.743664f);
}

// fn_802E2F90
float Lookup(float arg8) {
    int temp_r5 = (int)arg8;
    int idx = (temp_r5 & 0xFF) * 2;
    float *offset = &gBigSinTable[idx];
    float res = arg8 - (float)temp_r5;
    return (res * offset[1]) + offset[0];
}

// fn_802E2FE8
float FastSin(float f) {
    if (f < 0.0f) {
        return -gBigSinTable[((int)(-40.743664f * f + 0.49998999f) & 0xFF) * 2];
    } else
        return gBigSinTable[((int)(40.743664f * f + 0.49998999f) & 0xFF) * 2];
}

extern void DataRegisterFunc(Symbol, DataNode (*)(DataArray *));

// fn_802E306C
DataNode DataSin(DataArray *da) {
    return DataNode(SinThunk(DegreesToRadians(da->Float(1))));
}

// fn_802E30B0
float DegreesToRadians(float deg) {
    return 0.017453292f * deg;
}

// fn_802E30C0
DataNode DataCos(DataArray *da) {
    return DataNode(CosThunk(DegreesToRadians(da->Float(1))));
}

// fn_802E3104
DataNode DataTan(DataArray *da) {
    return DataNode(TanThunk(DegreesToRadians(da->Float(1))));
}


// fn_802E3148
float TanThunk(double d) {
    return TanFloat(d);
}


// fn_802E314C
float TanFloat(double d) {
    return tan(d);
}

// fn_802E3170
DataNode DataASin(DataArray *da) {
    float f = da->Float(1);
    if (!IsNan(f)) {
        return DataNode(RadiansToDegrees(ASinThunk(f)));
    } else
        return DataNode(0.0f);
}

// fn_802E31EC
float RadiansToDegrees(float rad) {
    return 57.295776f * rad;
}

// fn_802E31FC
float ASinThunk(double d) {
    return ASinFloat(d);
}

// fn_802E3200
bool IsNan(float f) {
    return (f == f) ? false : true;
}

// fn_802E3214
DataNode DataACos(DataArray *da) {
    float f = da->Float(1);
    if (!IsNan(f)) {
        return DataNode(RadiansToDegrees(ACosThunk(f)));
    } else
        return DataNode(0.0f);
}

// fn_802E3290
float ACosThunk(double d) {
    return ACosFloat(d);
}

// fn_802E3294
DataNode DataATan(DataArray *da) {
    float f = da->Float(1);
    if (!IsNan(f)) {
        return DataNode(RadiansToDegrees(ATanThunk(f)));
    } else
        return DataNode(0.0f);
}

// fn_802E3310
void DataInitTrigFuncs() {
    DataRegisterFunc("sin", DataSin);
    DataRegisterFunc("cos", DataCos);
    DataRegisterFunc("tan", DataTan);
    DataRegisterFunc("asin", DataASin);
    DataRegisterFunc("acos", DataACos);
    DataRegisterFunc("atan", DataATan);
}
