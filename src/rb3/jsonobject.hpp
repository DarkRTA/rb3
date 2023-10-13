#ifndef RB3_JSONOBJECT_HPP
#define RB3_JSONOBJECT_HPP
#include "json-c/json.h"

// this class is 0x8 big! according to fn_800A6D68
class JsonObject {
public:
	JsonObject(); // fn_800A6360
	virtual ~JsonObject(); // fn_800A6378

	json_object* json_object_struct; // pointer to some class
};

#endif
