#include "rand.hpp"
#include "common.hpp"
#include "data.hpp"
#include "interpolator.hpp"
#include "linearinterpolator.hpp"

#pragma dont_inline on
// fn_802DCF50
Interpolator::Interpolator(){ }
#pragma dont_inline reset

// fn_802DCF60
LinearInterpolator::LinearInterpolator(){ }

// fn_802DCEDC
LinearInterpolator::LinearInterpolator(float f1, float f2, float f3, float f4){
    Reset(f1, f2, f3, f4);
}

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