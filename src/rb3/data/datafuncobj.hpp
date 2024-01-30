#ifndef RB3_DATAFUNCOBJ_HPP
#define RB3_DATAFUNCOBJ_HPP
#include "hmx/object.hpp"

class DataFuncObj : public Hmx::Object {
public:
    DataArray* arr;

    DataFuncObj(DataArray*);
    virtual ~DataFuncObj();
    virtual DataNode Handle(DataArray*, bool);

    void PoolFree();
};

#endif
