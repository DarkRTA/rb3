#pragma once
#include "obj/Object.h"
#include "obj/ObjPtr_p.h"

class ObjVersion {
public:
    ObjVersion(int i, Hmx::Object* o) : obj(0, o), revs(i) {}
    ObjPtr<Hmx::Object, ObjectDir> obj;
    int revs;
};

extern std::vector<ObjVersion> sRevStack;
inline void PushRev(int i, Hmx::Object* o){
    sRevStack.push_back(ObjVersion(i, o));
}

inline int PopRev(Hmx::Object* o){
    ObjVersion* back = &sRevStack.back();
    while(back->obj == 0){
        sRevStack.pop_back();
        back = &sRevStack.back();
    }
    int revs = back->revs;
    if(o != back->obj){
        MILO_LOG("rev stack $this mismatch (%08x != %08x\n", o, back->obj);
        MILO_LOG("curr obj: %s %s\n", o->ClassName(), PathName(o));
        MILO_LOG("stack obj: %s %s\n", back->obj->ClassName(), PathName(back->obj));
        MILO_FAIL("rev stack (%08x %s %s != %08x %s %s)\n", o, o->ClassName(), PathName(o), back->obj, back->obj->ClassName(), PathName(back->obj));
    }
    sRevStack.pop_back();
    return revs;
}
