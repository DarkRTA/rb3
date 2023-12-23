#ifndef RB3_EXPINTERPOLATOR_HPP
#define RB3_EXPINTERPOLATOR_HPP
#include "interpolator.hpp"
#include "data.hpp"

class ExpInterpolator : Interpolator {
public:
    ExpInterpolator(float, float, float, float, float); // fn_802DD0F0

    virtual double Eval(float); // fn_802DD32C
    virtual void Reset(const DataArray *); // fn_802DD238
    virtual ~ExpInterpolator(); // fn_800E0DEC
    virtual void V_Unk() = 0;

    void Reset(float, float, float, float, float); // fn_802DD16C

    float unk4;
    float unk8;
    float unkc;
    float unk10;
    float unk14;
    float unk18;
    float unk1c;
};

#endif
