#include "jsonobject.hpp"
#include "jsonarray.hpp"
#include "jsonstring.hpp"
#include "jsonint.hpp"
#include "jsondouble.hpp"

#pragma dont_inline on
// fn_800A6360
JsonObject::JsonObject()
{
	json_object_struct = 0;
}
#pragma dont_inline reset

// fn_800A6378
JsonObject::~JsonObject()
{
	json_object_put(json_object_struct);
}

// fn_800A63DC
const char *JsonObject::GetString()
{
	return json_object_get_string(json_object_struct);
}

// fn_800A63E4
enum json_type JsonObject::Type()
{
	return json_object_get_type(json_object_struct);
}

// fn_800A63EC
JsonArray::JsonArray()
{
	json_object_struct = json_object_new_array();
}

// fn_800A6430
JsonArray::~JsonArray()
{
	for (int len = json_object_array_length(json_object_struct) - 1; len >= 0;
		 len--) {
		json_object_put(json_object_array_get_idx(json_object_struct, len));
	}
}

// fn_800A64C4
void JsonArray::Append(JsonObject *obj)
{
	json_object_get(obj->GetJsonObjectStruct());
	json_object_array_add(json_object_struct, obj->GetJsonObjectStruct());
}

// fn_800A6518
int JsonArray::Length()
{
	return json_object_array_length(json_object_struct);
}

// fn_800A6520
JsonString::JsonString(const char *s)
{
	json_object_struct = json_object_new_string(s);
}

// fn_800A6574
JsonString::~JsonString()
{
}

#pragma force_active on
// fn_800A65CC
const char *JsonString::GetString()
{
	return json_object_get_string(json_object_struct);
}
#pragma force_active reset

// fn_800A65D4
JsonInt::JsonInt(int i)
{
	json_object_struct = json_object_new_int(i);
}

#pragma force_active on
// fn_800A6628
JsonInt::~JsonInt()
{
}
#pragma force_active reset

// fn_800A6680
int JsonInt::GetInt()
{
	return json_object_get_int(json_object_struct);
}

// fn_800A6688
JsonDouble::JsonDouble(double d)
{
	json_object_struct = json_object_new_double(d);
}

#pragma force_active on
// fn_800A66DC
JsonDouble::~JsonDouble()
{
}
#pragma force_active reset

// fn_800A6734
double JsonDouble::GetDouble()
{
	return json_object_get_double(json_object_struct);
}