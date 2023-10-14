#ifndef RB3_JSONCONVERTER_HPP
#define RB3_JSONCONVERTER_HPP
#include "jsonarray.hpp"
#include "string.hpp"

class Dummy {
public:
	~Dummy();
	int lol;
};

class UnknownJsonConverterMember {
public:
	int unk0;
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
};

#endif
