#include "jsonarray.hpp"

// fn_800A63EC
JsonArray::JsonArray(){ json_object_struct = json_object_new_array(); }

// fn_800A6430
JsonArray::~JsonArray(){
	for(int len = json_object_array_length(json_object_struct) - 1; len >= 0; len--){
		json_object_put(json_object_array_get_idx(json_object_struct, len));
	}
}

// fn_800A64C4
void JsonArray::Append(JsonObject* obj){
	json_object_get(obj->GetJsonObjectStruct());
	json_object_array_add(json_object_struct, obj->GetJsonObjectStruct());
}

// fn_800A6518
int JsonArray::Length(){ return json_object_array_length(json_object_struct); }