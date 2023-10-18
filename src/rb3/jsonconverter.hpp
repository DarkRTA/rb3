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
	JsonObject** unk0;
	unsigned short unk4;
	unsigned short unk6;


	~UnknownJsonConverterMember(); // fn_800A6790
	bool fn_800AFE60();
	unsigned short GetUnk4(); // fn_800A6BD0
	JsonObject** fn_800A6A24(); // fn_800A6A24
	void fn_800A6FA4(unsigned short); // fn_800A6FA4
	// void fn_801CEDFC(String*);
	
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
