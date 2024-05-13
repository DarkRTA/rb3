#include "math/Interp.h"
#include "math/MathFuncs.h"
#include "os/Debug.h"
#include <stdlib.h>

static const char* const unused1[] = {
    "exp", "atan", "unknown interpolator type: %s\nat %d in %s"
};

LinearInterpolator::LinearInterpolator(float y0, float y1, float x0, float x1) {
    Reset(y0, y1, x0, x1);
}

LinearInterpolator::LinearInterpolator() {
}

void LinearInterpolator::Reset(float y0, float y1, float x0, float x1) {
    float run = x1 - x0;
    mX0 = x0;
    mX1 = x1;
    mY0 = y0;
    mY1 = y1;
    if (fabs_f(run) < 0.000001f)
        mSlope = 0.0;
    else
        mSlope = (y1 - y0) / run;
    mB = -mX0 * mSlope + mY0;
}

void LinearInterpolator::Reset(const DataArray *data) {
    Reset(
        data->Float(1),
        data->Float(2),
        data->Float(3),
        data->Float(4)
    );
}

ExpInterpolator::ExpInterpolator(float f1, float f2, float f3, float f4, float f5) {
    Reset(f1, f2, f3, f4, f5);
}

void ExpInterpolator::Reset(float f1, float f2, float f3, float f4, float f5) {
    float f0 = f4 - f3;
    mX0 = f3;
    mX1 = f4;
    mY0 = f1;
    mY1 = f2;
    if (fabs_f(f0) < 0.000001f)
        mInvRun = 1.0f;
    else
        mInvRun = 1.0f / f0;
    mPower = f5;
    mRise = f2 - f1;
}

// fn_802DD238
void ExpInterpolator::Reset(const DataArray *data) {
    Reset(data->Float(1), data->Float(2), data->Float(3), data->Float(4), (data->Size() > 5) ? data->Float(5) : 2.0f);
}

// fn_802DD32C
float ExpInterpolator::Eval(float f) {
    double pow_res = pow((double)(mInvRun * (f - mX0)), (double)mPower);

    // mInvRun * (f - mX0) is an implicit cast from float to double?
    // mPower is also implicitly casted from float to double

    // float pow_f(double x, double y) => double pow(double x, double y)
    //pow_res = pow_f(mInvRun * (f - mX0), mPower);
    return (float)pow_res * mRise + mY0;
}


// fn_802DD37C
InvExpInterpolator::InvExpInterpolator(float f1, float f2, float f3, float f4, float f5) {
    Reset(f1, f2, f3, f4, f5);
}

// fn_802DD3F8
void InvExpInterpolator::Reset(float f1, float f2, float f3, float f4, float f5) {
    float f0 = f4 - f3;
    mX0 = f3;
    mX1 = f4;
    mY0 = f1;
    mY1 = f2;
    if (fabs_f(f0) < 0.000001f)
        mInvRun = 1.0f;
    else
        mInvRun = 1.0f / f0;
    mPower = f5;
    mRise = f2 - f1;
}

// fn_802DD4C4
void InvExpInterpolator::Reset(const DataArray *data) {
    Reset(data->Float(1), data->Float(2), data->Float(3), data->Float(4), (data->Size() > 5) ? data->Float(5) : 2.0f);
}

// fn_802DD5B8
float InvExpInterpolator::Eval(float f) {
    float pow_res;

    double a = -(mInvRun * (f - mX0) - 1);

    pow_res = pow(a, (double)mPower);
    return (1.0f - pow_res) * mRise + mY0;
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
    if(severity < 0.001f) MILO_FAIL("ATanInterpolator: severity (%f) too small.", severity);
    float ftan = atan_f(f31);
    mScale = (y1 - y0) / (-ftan - ftan);
    mOffset = 0.5f * (y1 - y0) + y0;
    mSeverity = severity;
}

// fn_802DD850
void ATanInterpolator::Reset(const DataArray *data) {
    Reset(data->Float(1), data->Float(2), data->Float(3), data->Float(4), (data->Size() > 5) ? data->Float(5) : 10.0f);
}

// fn_802DD944
float ATanInterpolator::Eval(float f) {
    float ret = atan_f(mXMapping.Eval(f));
    ret *= mScale;
    return ret + mOffset;
}

static const char* const unused2[] = {
    "Interp.cpp", "source", "numEntries > 1", "mTable", "source->Size() > startAt", "mDeltas"
};
