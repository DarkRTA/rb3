#ifndef RB3_INVEXPINTERPOLATOR_HPP
#define RB3_INVEXPINTERPOLATOR_HPP
#include "interpolator.hpp"
#include "data.hpp"

class InvExpInterpolator : Interpolator {
public:
    InvExpInterpolator(float, float, float, float, float); // fn_802DD37C

    virtual double Eval(float); // fn_802DD5B8
    virtual void Reset(const DataArray *); // fn_802DD4C4
    virtual ~InvExpInterpolator(); // fn_800E0DEC

    void Reset(float, float, float, float, float); // fn_802DD3F8

    float unk4;
    float unk8;
    float unkc;
    float unk10;
    float unk14;
    float unk18;
    float unk1c;
};

#endif
