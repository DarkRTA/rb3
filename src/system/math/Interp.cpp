#include "common.hpp"
#include "Data.h"
#include "Interp.h"
#include "math.h"


// fn_802DCEDC
LinearInterpolator::LinearInterpolator(float y0, float y1, float x0, float x1) {
    Reset(y0, y1, x0, x1);
}

// fn_802DCF50
Interpolator::Interpolator() {
}

// fn_802DCF60
LinearInterpolator::LinearInterpolator() {
}


// fn_802DCF9C
void LinearInterpolator::Reset(float y0, float y1, float x0, float x1) {
    float run = x1 - x0;
    mY0 = y0;
    mX0 = x0;
    mX1 = x1;
    mY1 = y1;
    if (AbsThunk(run) < (float)0.000001)
        mSlope = 0.0;
    else
        mSlope = (y1 - y0) / run;
    mB = -mX0 * mSlope + mY0;
}

// fn_802DD05C
void LinearInterpolator::Reset(const DataArray *data) {
    Reset(
        data->Float(1),
        data->Float(2),
        data->Float(3),
        data->Float(4)
    );
}

// fn_802DD0F0
ExpInterpolator::ExpInterpolator(float f1, float f2, float f3, float f4, float f5) {
    Reset(f1, f2, f3, f4, f5);
}

// fn_802DD16C
void ExpInterpolator::Reset(float f1, float f2, float f3, float f4, float f5) {
    float f0 = f4 - f3;
    mY0 = f1;
    mX0 = f3;
    mX1 = f4;
    mY1 = f2;
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
    if (da->Size() > 5) {
        f5 = da->Float(5);
    } else
        f5 = 2.0;
    Reset(
        da->Float(1),
        da->Float(2),
        da->Float(3),
        da->Float(4),
        f5
    );
}

// fn_802DD32C
float ExpInterpolator::Eval(float f) {
    float pow_res = PowThunk(unk1c * (f - mX0), unk14);
    return pow_res * unk18 + mY0;
}


// fn_802DD378
float PowThunk(double d1, double d2) {
    return PowFloat(d1, d2);
}


// fn_802DD37C
InvExpInterpolator::InvExpInterpolator(float f1, float f2, float f3, float f4, float f5) {
    Reset(f1, f2, f3, f4, f5);
}

// fn_802DD3F8
void InvExpInterpolator::Reset(float f1, float f2, float f3, float f4, float f5) {
    float f0 = f4 - f3;
    mY0 = f1;
    mX0 = f3;
    mX1 = f4;
    mY1 = f2;
    if (AbsThunk(f0) < 0.000001f)
        unk1c = 1.0f;
    else
        unk1c = 1.0f / f0;
    unk14 = f5;
    unk18 = f2 - f1;
}

// fn_802DD4C4
void InvExpInterpolator::Reset(const DataArray *data) {
    float f5;
    if (data->Size() > 5) {
        f5 = data->Float(5);
    } else
        f5 = 2.0;
    Reset(
        data->Float(1),
        data->Float(2),
        data->Float(3),
        data->Float(4),
        f5
    );
}

// fn_802DD5B8
float InvExpInterpolator::Eval(float f) {
    float pow_res = PowThunk(-(unk1c * (f - mX0) - 1.0f), unk14);
    return (1.0f - pow_res) * unk18 + mY0;
}

// fn_802DD61C
ATanInterpolator::ATanInterpolator(float y0, float y1, float x0, float x1, float severity)
    : mXMapping(0.0f, 0.0f, 0.0f, 0.0f) {
    Reset(y0, y1, x0, x1, severity);
}

// fn_802DD6F4
ATanInterpolator::ATanInterpolator() {
}

// fn_802DD738
void ATanInterpolator::Reset(float y0, float y1, float x0, float x1, float severity) {
    float f31 = -severity;
    mXMapping.Reset(f31, severity, x0, x1);
    mX0 = x0;
    mX1 = x1;
    mY0 = y0;
    mY1 = y1;
    float ftan = ATanThunk(f31);
    mScale = (y1 - y0) / (-ftan - ftan);
    mOffset = 0.5f * (y1 - y0) + y0;
    mSeverity = severity;
}


// fn_802DD828
float ATanThunk(double d) {
    return ATanFloat(d);
}

// fn_802DD82C
float ATanFloat(double d) {
    return atan(d);
}


// fn_802DD850
void ATanInterpolator::Reset(const DataArray *data) {
    float f5;
    if (data->Size() > 5) {
        f5 = data->Float(5);
    } else
        f5 = 10.0f;
    Reset(
        data->Float(1),
        data->Float(2),
        data->Float(3),
        data->Float(4),
        f5
    );
}

// fn_802DD944
float ATanInterpolator::Eval(float f) {
    float ret = ATanThunk(mXMapping.Eval(f));
    ret *= mScale;
    return ret + mOffset;
}
