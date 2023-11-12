#include "data.hpp"
#include "symbol.hpp"
#include "common.hpp"
#include "std/math.h"

extern "C" void DataRegisterFunc(Symbol, DataNode (*)(DataArray *));

// fn_802E30B0
float DegreesToRadians(float f){
    return 0.017453292f * f;
}

// fn_802E306C
DataNode DataSin(DataArray* da){
    return DataNode(SinThunk(DegreesToRadians(da->GetFloatAtIndex(1))));
}

// fn_802E30C0
DataNode DataCos(DataArray* da){
    return DataNode(CosThunk(DegreesToRadians(da->GetFloatAtIndex(1))));
}

// fn_802E314C
float TanFloat(double d){
    return tan(d);
}

#pragma dont_inline on
// fn_802E3148
float TanThunk(double d){
    return TanFloat(d);
}
#pragma dont_inline reset

// fn_802E3104
DataNode DataTan(DataArray* da){
    return DataNode(TanThunk(DegreesToRadians(da->GetFloatAtIndex(1))));
}

// fn_802E3170
extern DataNode DataASin(DataArray*);
// fn_802E3214
extern DataNode DataACos(DataArray*);
// fn_802E3294
extern DataNode DataATan(DataArray*);

// fn_802E3310
void DataInitTrigFuncs(){
    DataRegisterFunc(Symbol("sin"), DataSin);
    DataRegisterFunc(Symbol("cos"), DataCos);
    DataRegisterFunc(Symbol("tan"), DataTan);
    DataRegisterFunc(Symbol("asin"), DataASin);
    DataRegisterFunc(Symbol("acos"), DataACos);
    DataRegisterFunc(Symbol("atan"), DataATan);
}