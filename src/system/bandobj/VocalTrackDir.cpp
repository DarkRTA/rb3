#include "rndobj/Trans.h"

#include "decomp.h"

// Here to test ObjPtrList
DECOMP_FORCEBLOCK(VocalTrackDir, (ObjPtrList<RndTransformable, ObjectDir>* plist, BinStream& bs),
    bs >> *plist;
)
