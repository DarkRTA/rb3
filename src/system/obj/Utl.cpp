#include "obj/Utl.h"
#include "System.h"

void InitObject(Hmx::Object* obj){
    static DataArray* objects = SystemConfig("objects");
    static Symbol initSym("init");
    obj->ClassName();
    DataArray* found1 = objects->FindArray(initSym, true);
    DataArray* found2 = found1->FindArray(initSym, false);
    if(found2 != 0)
        found2->ExecuteScript(1, obj, 0, 1);
}

char* PathName(const Hmx::Object* obj){
    if(obj != 0) ((Hmx::Object*)obj)->FindPathName();
    else return "NULL Object";
}

const char* SafeName(Hmx::Object* obj){
    if(obj != 0) return obj->Name();
    else return "NULL";
}

bool IsASubclass(Symbol s1, Symbol s2){
    if((s2 == "Object") || (s1 == s2)) return true;
    else return RecurseSuperClassesSearch(s1, s2);
}
