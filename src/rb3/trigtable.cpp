#include "common.hpp"
#include "trigtable.hpp"

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
void TrigTableNOP() {
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