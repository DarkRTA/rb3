#ifndef RB3_DATAFUNCOBJ_HPP
#define RB3_DATAFUNCOBJ_HPP
#include "hmx/object.hpp"

class DataFuncObj : Hmx::Object {
public:
    DataArray* arr;

    DataFuncObj(DataArray*);
    
};

#endif
