#include "rndobj/Anim.h"

#include "decomp.h"

// Here to test ObjPtrList
DECOMP_FORCEBLOCK(BandCamShot, (ObjPtrList<RndAnimatable, ObjectDir>* plist, BinStream& bs),
    bs >> *plist;
)
