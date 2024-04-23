#include "EventTrigger.h"
#include "obj/Object.h"
#include "rndobj/Draw.h"
#include "obj/ObjPtr_p.h"

#pragma dont_inline on
static void thisisheretotestobjptrlist(Hmx::Object* obj){
    ObjPtrList<RndDrawable, ObjectDir> lol(obj, kObjListNoNull);
    lol.pop_back();
    lol.back();
    lol.empty();
    lol.push_back(0);
}

static void test2(ObjPtrList<EventTrigger, ObjectDir>* l1, ObjPtrList<EventTrigger, ObjectDir>* l2){
    *l1 = *l2;
}
#pragma dont_inline reset

SAVE_OBJ(EventTrigger, 406)
