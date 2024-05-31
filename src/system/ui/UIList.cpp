#include "obj/Object.h"
#include "obj/ObjPtr_p.h"

#include "decomp.h"

// Here to test ObjPtrList
DECOMP_FORCEBLOCK(UIList, (ObjPtrList<Hmx::Object, class ObjectDir>* plist, BinStream& bs),
    bs >> *plist;
)
