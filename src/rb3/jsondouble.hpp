#ifndef RB3_JSONDOUBLE_HPP
#define RB3_JSONDOUBLE_HPP
#include "jsonobject.hpp"

class JsonDouble : public JsonObject {
public:
	JsonDouble(double); // fn_800A6688
	virtual ~JsonDouble(); // fn_800A66DC

	double GetDouble(); // fn_800A6734
};

#endif
