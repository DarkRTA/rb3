#include "char/CharTransDraw.h"
#include "utl/Symbols.h"

INIT_REVS(CharTransDraw);

CharTransDraw::CharTransDraw() : mChars(this, kObjListNoNull) {

}

CharTransDraw::~CharTransDraw(){
    SetDrawModes(Character::kCharDrawAll);
}

SAVE_OBJ(CharTransDraw, 0x23);

void CharTransDraw::SetDrawModes(Character::DrawMode mode){
    for(ObjPtrList<Character, ObjectDir>::iterator it = mChars.begin(); it != mChars.end(); ++it){
        (*it)->mDrawMode = mode;
    }
}

void CharTransDraw::Load(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(1, 0);
    Hmx::Object::Load(bs);
    RndDrawable::Load(bs);
    bs >> mChars;
    SetDrawModes(Character::kCharDrawOpaque);
}

BEGIN_COPYS(CharTransDraw)
    COPY_SUPERCLASS(Hmx::Object)
    COPY_SUPERCLASS(RndDrawable)
    CREATE_COPY(CharTransDraw)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mChars)
    END_COPYING_MEMBERS
END_COPYS

void CharTransDraw::DrawShowing(){
    for(ObjPtrList<Character, ObjectDir>::iterator it = mChars.begin(); it != mChars.end(); ++it){
        Character* theChar = *it;
        if(theChar->Showing()){
            theChar->mDrawMode = Character::kCharDrawTranslucent;
            theChar->Draw();
            theChar->mDrawMode = Character::kCharDrawOpaque;
        }
    }
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