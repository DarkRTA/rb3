#include "jsondouble.hpp"

// fn_800A6688
JsonDouble::JsonDouble(double d){ json_object_struct = json_object_new_double(d); }

// fn_800A66DC
JsonDouble::~JsonDouble(){ }

// fn_800A6734
double JsonDouble::GetDouble(){ return json_object_get_double(json_object_struct); }