#include "common.hpp"
#include "data.hpp"
#include "interpolator.hpp"
#include "linearinterpolator.hpp"
#include "expinterpolator.hpp"
#include "invexpinterpolator.hpp"
#include "ataninterpolator.hpp"
#include "math.h"

#pragma dont_inline on
// fn_802DCEDC
LinearInterpolator::LinearInterpolator(float f1, float f2, float f3, float f4) {
    Reset(f1, f2, f3, f4);
}

// fn_802DCF50
Interpolator::Interpolator() {
}

// fn_802DCF60
LinearInterpolator::LinearInterpolator() {
}
#pragma dont_inline reset

// fn_802DCF9C
void LinearInterpolator::Reset(float f1, float f2, float f3, float f4) {
    float f0 = f4 - f3;
    unk4 = f1;
    unkc = f3;
    unk10 = f4;
    unk8 = f2;
    if (AbsThunk(f0) < (float)0.000001)
        unk14 = 0.0;
    else
        unk14 = (f2 - f1) / f0;
    unk18 = -unkc * unk14 + unk4;
}

// fn_802DD05C
void LinearInterpolator::Reset(const DataArray *da) {
    Reset(
        da->GetFloatAtIndex(1),
        da->GetFloatAtIndex(2),
        da->GetFloatAtIndex(3),
        da->GetFloatAtIndex(4)
    );
}

// fn_802DD0F0
ExpInterpolator::ExpInterpolator(float f1, float f2, float f3, float f4, float f5) {
    Reset(f1, f2, f3, f4, f5);
}

// fn_802DD16C
void ExpInterpolator::Reset(float f1, float f2, float f3, float f4, float f5) {
    float f0 = f4 - f3;
    unk4 = f1;
    unkc = f3;
    unk10 = f4;
    unk8 = f2;
    if (AbsThunk(f0) < 0.000001f)
        unk1c = 1.0f;
    else
        unk1c = 1.0f / f0;
    unk14 = f5;
    unk18 = f2 - f1;
}

// fn_802DD238
void ExpInterpolator::Reset(const DataArray *da) {
    float f5;
    if (da->GetNodeCount() > 5) {
        f5 = da->GetFloatAtIndex(5);
    } else
        f5 = 2.0;
    Reset(
        da->GetFloatAtIndex(1),
        da->GetFloatAtIndex(2),
        da->GetFloatAtIndex(3),
        da->GetFloatAtIndex(4),
        f5
    );
}

// fn_802DD32C
double ExpInterpolator::Eval(float f) {
    float pow_res = PowThunk(unk1c * (f - unkc), unk14);
    return pow_res * unk18 + unk4;
}

#pragma dont_inline on
// fn_802DD378
float PowThunk(double d1, double d2) {
    return PowFloat(d1, d2);
}
#pragma dont_inline reset

// fn_802DD37C
InvExpInterpolator::InvExpInterpolator(float f1, float f2, float f3, float f4, float f5) {
    Reset(f1, f2, f3, f4, f5);
}

// fn_802DD3F8
void InvExpInterpolator::Reset(float f1, float f2, float f3, float f4, float f5) {
    float f0 = f4 - f3;
    unk4 = f1;
    unkc = f3;
    unk10 = f4;
    unk8 = f2;
    if (AbsThunk(f0) < 0.000001f)
        unk1c = 1.0f;
    else
        unk1c = 1.0f / f0;
    unk14 = f5;
    unk18 = f2 - f1;
}

// fn_802DD4C4
void InvExpInterpolator::Reset(const DataArray *da) {
    float f5;
    if (da->GetNodeCount() > 5) {
        f5 = da->GetFloatAtIndex(5);
    } else
        f5 = 2.0;
    Reset(
        da->GetFloatAtIndex(1),
        da->GetFloatAtIndex(2),
        da->GetFloatAtIndex(3),
        da->GetFloatAtIndex(4),
        f5
    );
}

// fn_802DD5B8
double InvExpInterpolator::Eval(float f) {
    float pow_res = PowThunk(-(unk1c * (f - unkc) - 1.0f), unk14);
    return (1.0f - pow_res) * unk18 + unk4;
}

// fn_802DD61C
ATanInterpolator::ATanInterpolator(float f1, float f2, float f3, float f4, float f5)
    : unk14(0.0f, 0.0f, 0.0f, 0.0f) {
    Reset(f1, f2, f3, f4, f5);
}

// fn_802DD6F4
ATanInterpolator::ATanInterpolator() {
}

// fn_802DD738
void ATanInterpolator::Reset(float f1, float f2, float f3, float f4, float f5) {
    float f31 = -f5;
    unk14.Reset(f31, f5, f3, f4);
    unkc = f3;
    unk10 = f4;
    unk4 = f1;
    unk8 = f2;
    float ftan = ATanThunk(f31);
    unk30 = (f2 - f1) / (-ftan - ftan);
    unk34 = 0.5f * (f2 - f1) + f1;
    unk38 = f5;
}

#pragma dont_inline on
// fn_802DD828
float ATanThunk(double d) {
    return ATanFloat(d);
}

// fn_802DD82C
float ATanFloat(double d) {
    return atan(d);
}
#pragma dont_inline reset

// fn_802DD850
void ATanInterpolator::Reset(const DataArray *da) {
    float f5;
    if (da->GetNodeCount() > 5) {
        f5 = da->GetFloatAtIndex(5);
    } else
        f5 = 10.0f;
    Reset(
        da->GetFloatAtIndex(1),
        da->GetFloatAtIndex(2),
        da->GetFloatAtIndex(3),
        da->GetFloatAtIndex(4),
        f5
    );
}

// fn_802DD944
double ATanInterpolator::Eval(float f) {
    float ret = ATanThunk(unk14.Eval(f));
    ret *= unk30;
    return ret + unk34;
}

// fn_802DD994
double LinearInterpolator::Eval(float f) {
    return unk14 * f + unk18;
}