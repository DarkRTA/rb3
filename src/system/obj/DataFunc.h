#ifndef OBJ_DATAFUNC_H
#define OBJ_DATAFUNC_H
#include "obj/Data.h"
#include "obj/Object.h"
#include "obj/Dir.h"
#include "utl/MemMgr.h"
#include "obj/ObjPtr_p.h"

extern Hmx::Object *gDataThis;

class DataFuncObj : public Hmx::Object {
public:
    DataArray* mFunc;

    DataFuncObj(DataArray* da) : mFunc(da) {
        da->AddRef();
        SetName(da->Str(1), ObjectDir::sMainDir);
    }
    
    virtual ~DataFuncObj(){
        mFunc->Release();
    }
    virtual DataNode Handle(DataArray* _msg, bool _warn){
        return mFunc->ExecuteScript(2, gDataThis, _msg, 1);
    }
    
    void operator delete(void* v){
        _PoolFree(sizeof(DataFuncObj), FastPool, v);
    }

    static DataNode New(DataArray*);
};

class DataThisPtr : public ObjPtr<Hmx::Object, ObjectDir> {
public:
    DataThisPtr() : ObjPtr(0, 0) {}
    virtual ~DataThisPtr(){}
    virtual void Replace(Hmx::Object*, Hmx::Object*);
};

void DataRegisterFunc(Symbol s, DataFunc* func);
Symbol DataFuncName(DataFunc*);

#endif
