#include "char/CharTransDraw.h"

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