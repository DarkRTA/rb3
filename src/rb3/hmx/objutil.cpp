#include "hmx/objutil.hpp"
#include "system.hpp"

void InitObject(Hmx::Object* obj){
    static DataArray* objects = SystemConfig("objects");
    static Symbol initSym("init");
    obj->ClassName();
    DataArray* found1 = objects->FindArray(initSym, true);
    DataArray* found2 = found1->FindArray(initSym, false);
    if(found2 != nullptr)
        found2->ExecuteScript(1, obj, nullptr, 1);
}

char* PathName(const Hmx::Object* obj){
    if(obj != nullptr) ((Hmx::Object*)obj)->FindPathName();
    else return "NULL Object";
}

const char* SafeName(Hmx::Object* obj){
    if(obj != nullptr) return obj->Name();
    else return "NULL";
}