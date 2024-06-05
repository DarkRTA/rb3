#ifndef OBJ_OBJVERSION_H
#define OBJ_OBJVERSION_H
#include "obj/Object.h"
#include "obj/ObjPtr_p.h"

class ObjVersion {
public:
    ObjVersion(Hmx::Object* o, int i) : obj(0, o), revs(i) {}
    ObjPtr<Hmx::Object, ObjectDir> obj;
    int revs;
};

extern std::vector<ObjVersion> sRevStack;
inline void PushRev(int i, Hmx::Object* o){
    sRevStack.push_back(ObjVersion(o, i));
}

inline int PopRev(Hmx::Object* o){
    ObjVersion* back = &sRevStack.back();
    while(back->obj == 0){
        sRevStack.pop_back();
        back = &sRevStack.back();
    }
    int revs = back->revs;
    if(o != back->obj){
        TheDebug << MakeString("rev stack $this mismatch (%08x != %08x\n", o, back->obj);
        TheDebug << MakeString("curr obj: %s %s\n", o->ClassName(), PathName(o));
        TheDebug << MakeString("stack obj: %s %s\n", back->obj->ClassName(), PathName(back->obj));
        MILO_FAIL("rev stack (%08x %s %s != %08x %s %s)\n", o, o->ClassName(), PathName(o), back->obj, back->obj->ClassName(), PathName(back->obj));
    }
    sRevStack.pop_back();
    return revs;
}

#endif
