#ifndef RB3_JSONCONVERTER_HPP
#define RB3_JSONCONVERTER_HPP
#include "jsonarray.hpp"
#include "jsonstring.hpp"
#include "jsonint.hpp"
#include "jsondouble.hpp"
#include "jsonobject.hpp"
#include "string.hpp"

class Dummy {
public:
	~Dummy();
	int lol;
};

class UnknownJsonConverterMember {
public:
	JsonObject** unk0; // possibly a ptr to another class
	unsigned short unk4;
	unsigned short unk6;

	bool fn_800AFE60();
	unsigned short fn_800A6BD0();
	// void fn_801CEDFC(String*);
	// fn_800A6790 - dtor?
};

class JsonConverter : public JsonArray {
public:
	JsonConverter(); // fn_800A673C
	virtual ~JsonConverter(); // fn_800A6AF0

	UnknownJsonConverterMember mem;

	JsonArray* ToJsonArray(); // fn_800A6BD8
	JsonString* ToJsonString(const char*); // fn_800A6C34
	JsonInt* ToJsonInt(int); // fn_800A6C98
	JsonDouble* ToJsonDouble(double); // fn_800A6CFC

};

#endif
