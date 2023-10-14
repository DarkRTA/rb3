#ifndef RB3_JSONOBJECT_HPP
#define RB3_JSONOBJECT_HPP
#include "json-c/json.h"

// this class is 0x8 big! according to fn_800A6D68
class JsonObject {
public:
	JsonObject(); // fn_800A6360
	virtual ~JsonObject(); // fn_800A6378

	json_object* json_object_struct;
	json_object* GetJsonObjectStruct(); // fn_8000DF3C
	const char* GetString(); // fn_800A63DC
	enum json_type Type(); // fn_800A63E4
};

#endif
