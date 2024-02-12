#ifndef RB3_DATAFUNCOBJ_HPP
#define RB3_DATAFUNCOBJ_HPP
#include "obj/Object.h"

class DataFuncObj : public Hmx::Object {
public:
    DataArray* arr;

    DataFuncObj(DataArray*);
    virtual ~DataFuncObj();
    virtual DataNode Handle(DataArray*, bool);

    void PoolFree();
};

#endif
