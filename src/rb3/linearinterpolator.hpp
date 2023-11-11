#ifndef RB3_LINEARINTERPOLATOR_HPP
#define RB3_LINEARINTERPOLATOR_HPP
#include "interpolator.hpp"
#include "data.hpp"

class LinearInterpolator : Interpolator {
public:
	LinearInterpolator(float, float, float, float); // fn_802DCEDC
	LinearInterpolator(); // fn_802DCF60
	virtual double Eval(float); // fn_802DD994
	virtual void Reset(const DataArray *); // fn_802DD05C
	virtual ~LinearInterpolator(); // fn_800E0DEC

	void Reset(float, float, float, float); // fn_802DCF9C

	float unk4;
	float unk8;
	float unkc;
	float unk10;
	float unk14;
	float unk18;
};

#endif
