#ifndef OBJ_DATAFUNC_H
#define OBJ_DATAFUNC_H
#include "obj/Data.h"
#include "obj/Object.h"
#include "obj/Dir.h"
#include "utl/MemMgr.h"
#include "obj/ObjPtr_p.h"
#include "obj/DataUtl.h"

extern Hmx::Object *gDataThis;

class DataFuncObj : public Hmx::Object {
public:
    DataArray* mFunc;

    DataFuncObj(DataArray* da) : mFunc(da) {
        da->AddRef();
        SetName(da->Str(1), ObjectDir::Main());
    }

    virtual ~DataFuncObj(){
        mFunc->Release();
    }
    virtual DataNode Handle(DataArray* _msg, bool _warn){
        return mFunc->ExecuteScript(2, gDataThis, _msg, 1);
    }

    NEW_POOL_OVERLOAD(DataFuncObj);
    DELETE_POOL_OVERLOAD(DataFuncObj);

    static DataNode New(DataArray*);
};

class DataThisPtr : public ObjPtr<Hmx::Object, class ObjectDir> {
public:
    DataThisPtr() : ObjPtr(0, 0) {}
    virtual ~DataThisPtr(){}
    virtual void Replace(Hmx::Object* from, Hmx::Object* to){
        ObjPtr<Hmx::Object, class ObjectDir>::operator=(to);
        if(gDataThis == from) DataSetThis(to);
    }
};

void DataRegisterFunc(Symbol s, DataFunc* func);
Symbol DataFuncName(DataFunc*);
bool FileListCallBack(char*);
void DataInitFuncs();
void DataTermFuncs();

#endif
