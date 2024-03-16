#include "obj/ObjPtr_p.h"
#include "rndobj/Trans.h"

#pragma dont_inline on
static void objptrlistctortest(Hmx::Object* obj){
    ObjPtrList<RndTransformable, ObjectDir> asdf(obj, kObjListNoNull);
}
#pragma dont_inline reset
