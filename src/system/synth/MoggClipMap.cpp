#include "synth/MoggClipMap.h"

#include "decomp.h"

int MoggClipMap::sRev = 0;

MoggClipMap::MoggClipMap(Hmx::Object* obj) : mClipPtr(obj, 0), unk28(0.0f), unk2c(0.0f), unk30(0.0f), unk34(false) {

}

BinStream& operator>>(BinStream& bs, MoggClipMap& mcmap){
    mcmap.myLoad(bs);
    return bs;
}

void MoggClipMap::myLoad(BinStream& bs){
    bs >> mClipPtr;
    if(sRev >= 11){
        bs >> unk30 >> unk28 >> unk2c >> unk34;
    }
}

// Force these to generate before ~MoggClipMap()
DECOMP_FORCEBLOCK(MoggClipMap, (ObjPtr<MoggClip, ObjectDir>* objPtr),
    objPtr->RefOwner();
    objPtr->Replace(nullptr, nullptr);
)
