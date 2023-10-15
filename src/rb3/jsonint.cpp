#include "jsonint.hpp"

// fn_800A65D4
JsonInt::JsonInt(int i){ json_object_struct = json_object_new_int(i); }

// fn_800A6628
JsonInt::~JsonInt(){ }

// fn_800A6680
int JsonInt::GetInt(){ return json_object_get_int(json_object_struct); }