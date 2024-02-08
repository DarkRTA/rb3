#include "Data.h"
#include "symbol.hpp"
#include "common.hpp"
#include "math.h"

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
