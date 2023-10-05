#ifndef RB3_OBJREF_HPP
#define RB3_OBJREF_HPP
#include "binstream.hpp"
#include "string.hpp"
#include "asyncfilewii.hpp"

class ObjRef {
	ObjRef();
	virtual ~ObjRef(); //fn_8000DD10
	virtual void V_Unk2() = 0;
	virtual void V_Unk3() = 0;
	virtual int V_Unk4(); // links to fn_8077BAA0, which returns 0
};

#endif
