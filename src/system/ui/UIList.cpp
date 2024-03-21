#include "obj/Object.h"
#include "obj/ObjPtr_p.h"

static void justheretotestobjptrlistlol(ObjPtrList<Hmx::Object, class ObjectDir>* plist, BinStream& bs){
    bs >> *plist;
}
