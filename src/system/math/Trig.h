#ifndef MATH_TRIG_H
#define MATH_TRIG_H
#include "obj/Data.h"

void TrigTableInit(); // fn_802E2E28
void TrigTableTerminate();
float Lookup(float); // fn_802E2F90
float Sine(float); // fn_802E2F38
float FastSin(float); // fn_802E2FE8
float Cosine(float); // fn_802DE4D4

RETAIL_DONT_INLINE_FUNC float DegreesToRadians(float deg) {
    return 0.017453292f * deg;
}

RETAIL_DONT_INLINE_FUNC float RadiansToDegrees(float rad) {
    return 57.295776f * rad;
}

float NormalizeAngle(float);

DataNode DataSin(DataArray*);
DataNode DataCos(DataArray*);
DataNode DataTan(DataArray*);
DataNode DataASin(DataArray*);
DataNode DataACos(DataArray*);
DataNode DataATan(DataArray*);
void TrigInit();

#endif
