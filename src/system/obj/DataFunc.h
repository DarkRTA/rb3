#ifndef OBJ_DATAFUNC_H
#define OBJ_DATAFUNC_H
#include "Object.h"

class DataFuncObj : public Hmx::Object {
public:
    DataArray* mFunc;

    DataFuncObj(DataArray*);
    virtual ~DataFuncObj();
    virtual DataNode Handle(DataArray*, bool);
    
    static DataNode New(DataArray*);
};

#endif
