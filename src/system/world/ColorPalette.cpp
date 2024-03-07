#include "world/ColorPalette.h"

ColorPalette::ColorPalette(){

}

BinStream& operator>>(BinStream& bs, ColorSet& cset){
    bs >> cset.mPrimary >> cset.mSecondary;
    return bs;
}

SAVE_OBJ(ColorPalette, 0x29);

void ColorPalette::Load(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(1, 0);
    Hmx::Object::Load(bs);
}

BEGIN_COPYS(ColorPalette)
    GET_COPY_AND_ASSERT(ColorPalette, 0x4A);
    COPY_SUPERCLASS(Hmx::Object)
    COPY_MEMBER(mColors)
END_COPYS

BEGIN_HANDLERS(ColorPalette)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x53)
END_HANDLERS
