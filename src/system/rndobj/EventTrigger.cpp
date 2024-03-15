#include "rndobj/Draw.h"
#include "obj/ObjPtr_p.h"

#pragma dont_inline on
static void thisisheretotestobjptrlist(Hmx::Object* obj){
    ObjPtrList<RndDrawable, ObjectDir> lol(obj, kObjListNoNull);
    lol.pop_back();
    lol.back();
    lol.empty();
}
#pragma dont_inline reset
