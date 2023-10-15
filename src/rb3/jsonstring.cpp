#include "jsonstring.hpp"

// fn_800A6520
JsonString::JsonString(const char* s){ json_object_struct = json_object_new_string(s); }

// fn_800A6574
JsonString::~JsonString(){ }

// fn_800A65CC
const char* JsonString::GetString(){ return json_object_get_string(json_object_struct); }