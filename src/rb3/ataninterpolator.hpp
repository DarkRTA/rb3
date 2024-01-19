#ifndef RB3_ATANINTERPOLATOR_HPP
#define RB3_ATANINTERPOLATOR_HPP
#include "linearinterpolator.hpp"
#include "interpolator.hpp"
#include "data.hpp"

class ATanInterpolator : public Interpolator {
public:
    ATanInterpolator(float, float, float, float, float); // fn_802DD61C
    ATanInterpolator(); // fn_802DD6F4
    virtual double Eval(float); // fn_802DD944
    virtual void Reset(const DataArray *); // fn_802DD850
    virtual ~ATanInterpolator(){} // fn_800E0D84

    void Reset(float, float, float, float, float); // fn_802DD738

    float unk4;
    float unk8;
    float unkc;
    float unk10;
    LinearInterpolator unk14;
    float unk30;
    float unk34;
    float unk38;
};

#endif
