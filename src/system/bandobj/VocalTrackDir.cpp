#include "rndobj/Trans.h"

static void justheretotestobjptrlistlol(ObjPtrList<RndTransformable, ObjectDir>* plist, BinStream& bs){
    bs >> *plist;
}
