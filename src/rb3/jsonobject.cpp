#include "jsonobject.hpp"

// fn_800A6360
JsonObject::JsonObject() { json_object_struct = 0; }

// fn_800A6378
JsonObject::~JsonObject() { json_object_put(json_object_struct); }

// fn_800A63DC
const char* JsonObject::GetString(){ return json_object_get_string(json_object_struct); }

// fn_800A63E4
enum json_type JsonObject::Type(){ return json_object_get_type(json_object_struct); }
