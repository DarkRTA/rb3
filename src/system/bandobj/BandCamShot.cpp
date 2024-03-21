#include "rndobj/Anim.h"

static void justheretotestobjptrlistlol(ObjPtrList<RndAnimatable, ObjectDir>* plist, BinStream& bs){
    bs >> *plist;
}
