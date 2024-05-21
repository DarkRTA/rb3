#include "world/ColorPalette.h"
#include "utl/Symbols.h"

INIT_REVS(ColorPalette)

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
    if(gRev < 1){
        std::vector<ColorSet> setvec;
        bs >> setvec;
        mColors.resize(setvec.size());
        for(std::vector<ColorSet>::iterator it = setvec.begin(); it != setvec.end(); it++){
            mColors.push_back(it->mPrimary);
            mColors.push_back(it->mSecondary);
        }
    }
    else bs >> mColors;
}

BEGIN_COPYS(ColorPalette)
    GET_COPY_AND_ASSERT(ColorPalette, 0x4A);
    Hmx::Object::Copy(c, ty);
    COPY_MEMBER(mColors)
END_COPYS

BEGIN_HANDLERS(ColorPalette)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x53)
END_HANDLERS

BEGIN_PROPSYNCS(ColorPalette)
    SYNC_PROP(colors, mColors)
END_PROPSYNCS