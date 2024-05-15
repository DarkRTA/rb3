#include "char/CharClipGroup.h"

INIT_REVS(CharClipGroup)

CharClipGroup::CharClipGroup() : mClips(this), mWhich(0), mFlags(0) {

}

SAVE_OBJ(CharClipGroup, 0x127)

void CharClipGroup::Load(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(2, 0);
    Hmx::Object::Load(bs);
    bs >> mClips;
    bs >> mWhich;
    if(gRev > 1) bs >> mFlags;
    else mFlags = 0;
}