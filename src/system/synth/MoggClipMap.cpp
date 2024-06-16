#include "synth/MoggClipMap.h"
#include "decomp.h"

int MoggClipMap::sRev = 0;

MoggClipMap::MoggClipMap(Hmx::Object* obj) : mMoggClip(obj, 0), mPan(0.0f), mPanWidth(0.0f), mVolume(0.0f), mIsStereo(false) {

}

BinStream& operator>>(BinStream& bs, MoggClipMap& mcmap){
    mcmap.myLoad(bs);
    return bs;
}

void MoggClipMap::myLoad(BinStream& bs){
    bs >> mMoggClip;
    if(sRev >= 11){
        bs >> mVolume >> mPan >> mPanWidth >> mIsStereo;
    }
}

// Force these to generate before ~MoggClipMap()
DECOMP_FORCEBLOCK(MoggClipMap, (ObjPtr<MoggClip, ObjectDir>* objPtr),
    objPtr->RefOwner();
    objPtr->Replace(nullptr, nullptr);
)
