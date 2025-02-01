#ifndef MATH_INTERP_H
#define MATH_INTERP_H
#include "obj/Data.h"

class Interpolator {
public:
    Interpolator() {}
    virtual float Eval(float) = 0;
    virtual void Reset(const DataArray *) = 0;
    virtual ~Interpolator() {} // generic dtor

    float Y0() const { return mY0; }
    float Y1() const { return mY1; }
    float X0() const { return mX0; }
    float X1() const { return mX1; }

    float mY0, mY1, mX0, mX1;
};

class LinearInterpolator : public Interpolator {
public:
    LinearInterpolator(float, float, float, float); // fn_802DCEDC
    LinearInterpolator(); // fn_802DCF60
    virtual float Eval(float f) { return mSlope * f + mB; } // fn_802DD994 - weak
    virtual void Reset(const DataArray *); // fn_802DD05C
    virtual ~LinearInterpolator() {} // fn_800E0DEC - weak

    void Reset(float, float, float, float); // fn_802DCF9C

    float mSlope, mB;
};

class ExpInterpolator : public Interpolator {
public:
    ExpInterpolator(float, float, float, float, float); // fn_802DD0F0

    virtual float Eval(float); // fn_802DD32C
    virtual void Reset(const DataArray *); // fn_802DD238
    virtual ~ExpInterpolator() {} // fn_800E0DEC

    void Reset(float, float, float, float, float); // fn_802DD16C

    float mPower;
    float mRise;
    float mInvRun;
};

class InvExpInterpolator : public Interpolator {
public:
    InvExpInterpolator(float, float, float, float, float); // fn_802DD37C

    virtual float Eval(float); // fn_802DD5B8
    virtual void Reset(const DataArray *); // fn_802DD4C4
    virtual ~InvExpInterpolator() {} // fn_800E0DEC

    void Reset(float, float, float, float, float); // fn_802DD3F8

    float mPower;
    float mRise;
    float mInvRun;
};

class ATanInterpolator : public Interpolator {
public:
    ATanInterpolator(float, float, float, float, float); // fn_802DD61C
    ATanInterpolator(); // fn_802DD6F4
    virtual float Eval(float); // fn_802DD944
    virtual void Reset(const DataArray *); // fn_802DD850
    virtual ~ATanInterpolator() {} // fn_800E0D84

    void Reset(float, float, float, float, float); // fn_802DD738

    LinearInterpolator mXMapping;
    float mScale;
    float mOffset;
    float mSeverity;
};

#endif
