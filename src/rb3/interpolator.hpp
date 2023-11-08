#ifndef RB3_INTERPOLATOR_HPP
#define RB3_INTERPOLATOR_HPP
#include "data.hpp"

class Interpolator {
public:
	Interpolator(); // fn_802DCF50
	virtual double Eval(float) = 0;
	virtual void Reset(const DataArray*) = 0;
	virtual ~Interpolator(); // generic dtor
};

#endif
