#include "char/CharTransDraw.h"
#include "utl/Symbols.h"

INIT_REVS(CharTransDraw);

CharTransDraw::CharTransDraw() : mChars(this, kObjListNoNull) {

}

CharTransDraw::~CharTransDraw(){
    SetDrawModes(Character::kCharDrawAll);
}

SAVE_OBJ(CharTransDraw, 0x23);

void CharTransDraw::Load(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(1, 0);
    Hmx::Object::Load(bs);
    RndDrawable::Load(bs);
    bs >> mChars;
    SetDrawModes(Character::kCharDrawOpaque);
}

BEGIN_HANDLERS(CharTransDraw)
    HANDLE_SUPERCLASS(RndDrawable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x5E)
END_HANDLERS

BEGIN_PROPSYNCS(CharTransDraw)
    SYNC_PROP(chars, mChars)
    SYNC_SUPERCLASS(RndDrawable)
END_PROPSYNCS