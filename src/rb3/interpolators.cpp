#include "common.hpp"
#include "data.hpp"
#include "interpolator.hpp"
#include "linearinterpolator.hpp"
#include "expinterpolator.hpp"
#include "invexpinterpolator.hpp"
#include "ataninterpolator.hpp"
#include "std/math.h"

#pragma dont_inline on
// fn_802DCF50
Interpolator::Interpolator(){ }

// fn_802DCF60
LinearInterpolator::LinearInterpolator(){ }

// fn_802DCEDC
LinearInterpolator::LinearInterpolator(float f1, float f2, float f3, float f4){
    Reset(f1, f2, f3, f4);
}
#pragma dont_inline reset

// fn_802DCF9C
void LinearInterpolator::Reset(float f1, float f2, float f3, float f4){
    float f0 = f4 - f3;
    unk4 = f1;
    unkc = f3;
    unk10 = f4;
    unk8 = f2;
    if(AbsThunk(f0) < (float)0.000001) unk14 = 0.0;
    else unk14 = (f2 - f1) / f0;
    unk18 = -unkc * unk14 + unk4;
}

// fn_802DD05C
void LinearInterpolator::Reset(const DataArray* da){
    Reset(da->GetFloatAtIndex(1), da->GetFloatAtIndex(2), da->GetFloatAtIndex(3), da->GetFloatAtIndex(4));
}

// fn_802DD994
double LinearInterpolator::Eval(float f){
    return unk14 * f + unk18;
}

// fn_802DD0F0
ExpInterpolator::ExpInterpolator(float f1, float f2, float f3, float f4, float f5){
    Reset(f1, f2, f3, f4, f5);
}

// fn_802DD16C
void ExpInterpolator::Reset(float f1, float f2, float f3, float f4, float f5){
    float f0 = f4 - f3;
    unk4 = f1;
    unkc = f3;
    unk10 = f4;
    unk8 = f2;
    if(AbsThunk(f0) < (float)0.000001) unk1c = (float)1.0;
    else unk1c = (float)1.0 / f0;
    unk14 = f5;
    unk18 = f2 - f1;
}

// fn_802DD238
void ExpInterpolator::Reset(const DataArray* da){
    float f5;
    if(da->GetNodeCount() > 5){
        f5 = da->GetFloatAtIndex(5);
    }
    else f5 = 2.0;
    Reset(da->GetFloatAtIndex(1), da->GetFloatAtIndex(2), da->GetFloatAtIndex(3), da->GetFloatAtIndex(4), f5);
}

// fn_802DD32C
double ExpInterpolator::Eval(float f){
    float pow_res = PowThunk(unk1c * (f - unkc), unk14);
    return pow_res * unk18 + unk4;
}

#pragma dont_inline on
// fn_802DD378
float PowThunk(double d1, double d2){
    return PowFloat(d1, d2);
}
#pragma dont_inline reset

// fn_802DD37C
InvExpInterpolator::InvExpInterpolator(float f1, float f2, float f3, float f4, float f5){
    Reset(f1, f2, f3, f4, f5);
}

// fn_802DD3F8
void InvExpInterpolator::Reset(float f1, float f2, float f3, float f4, float f5){
    float f0 = f4 - f3;
    unk4 = f1;
    unkc = f3;
    unk10 = f4;
    unk8 = f2;
    if(AbsThunk(f0) < (float)0.000001) unk1c = (float)1.0;
    else unk1c = (float)1.0 / f0;
    unk14 = f5;
    unk18 = f2 - f1;
}

// fn_802DD4C4
void InvExpInterpolator::Reset(const DataArray* da){
    float f5;
    if(da->GetNodeCount() > 5){
        f5 = da->GetFloatAtIndex(5);
    }
    else f5 = 2.0;
    Reset(da->GetFloatAtIndex(1), da->GetFloatAtIndex(2), da->GetFloatAtIndex(3), da->GetFloatAtIndex(4), f5);
}

// fn_802DD5B8
double InvExpInterpolator::Eval(float f){
    float pow_res = PowThunk(-(unk1c * (f - unkc) - (float)1.0), unk14);
    return ((float)1.0 - pow_res) * unk18 + unk4;
}

// fn_802DD61C
ATanInterpolator::ATanInterpolator(float f1, float f2, float f3, float f4, float f5) :
    unk14((float)0.0, (float)0.0, (float)0.0, (float)0.0){
        Reset(f1, f2, f3, f4, f5);
}

// fn_802DD6F4
ATanInterpolator::ATanInterpolator(){

}

#pragma dont_inline on
// fn_802DD82C
float ATanFloat(double d){
    return atan(d);
}

// fn_802DD828
float ATanThunk(double d){
    return ATanFloat(d);
}
#pragma dont_inline reset

// fn_802DD738
void ATanInterpolator::Reset(float f1, float f2, float f3, float f4, float f5){
    unk14.Reset(-f5, f5, f3, f4);
    unkc = f3;
    unk10 = f4;
    unk4 = f1;
    unk8 = f2;
    float ftan = ATanThunk(f5);
    unk30 = (f2 - f1) / (-ftan - ftan);
    unk34 = (float)0.5 * (f2 - f1) + f1;
    unk38 = f5;
}

// fn_802DD850
void ATanInterpolator::Reset(const DataArray* da){
    float f5;
    if(da->GetNodeCount() > 5){
        f5 = da->GetFloatAtIndex(5);
    }
    else f5 = (float)10.0;
    Reset(da->GetFloatAtIndex(1), da->GetFloatAtIndex(2), da->GetFloatAtIndex(3), da->GetFloatAtIndex(4), f5);
}

// fn_802DD944
double ATanInterpolator::Eval(float f){
    return (ATanThunk(unk14.Eval(f)) * unk30) + unk34;
}