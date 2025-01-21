#include "char/CharTransDraw.h"
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "rndobj/Draw.h"
#include "utl/Symbols.h"

INIT_REVS(CharTransDraw);

CharTransDraw::CharTransDraw() : mChars(this) {

}

CharTransDraw::~CharTransDraw(){
    SetDrawModes(Character::kCharDrawAll);
}

SAVE_OBJ(CharTransDraw, 0x23);

void CharTransDraw::SetDrawModes(Character::DrawMode mode){
    for(ObjPtrList<Character>::iterator it = mChars.begin(); it != mChars.end(); ++it){
        (*it)->SetDrawMode(mode);
    }
}

BEGIN_LOADS(CharTransDraw)
    LOAD_REVS(bs);
    ASSERT_REVS(1, 0);
    LOAD_SUPERCLASS(Hmx::Object)
    LOAD_SUPERCLASS(RndDrawable)
    bs >> mChars;
    SetDrawModes(Character::kCharDrawOpaque);
END_LOADS

BEGIN_COPYS(CharTransDraw)
    COPY_SUPERCLASS(Hmx::Object)
    COPY_SUPERCLASS(RndDrawable)
    CREATE_COPY(CharTransDraw)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mChars)
    END_COPYING_MEMBERS
END_COPYS

void CharTransDraw::DrawShowing(){
    for(ObjPtrList<Character>::iterator it = mChars.begin(); it != mChars.end(); ++it){
        Character* theChar = *it;
        if(theChar->Showing()){
            theChar->SetDrawMode(Character::kCharDrawTranslucent);
            theChar->Draw();
            theChar->SetDrawMode(Character::kCharDrawOpaque);
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

DECOMP_FORCEFUNC(CharTransDraw, CharTransDraw, SetType)
DECOMP_FORCEFUNC_TEMPL(CharTransDraw, ObjPtrList, Replace(0, 0), Character, ObjectDir)
DECOMP_FORCEFUNC_TEMPL(CharTransDraw, ObjPtrList, RefOwner(), Character, ObjectDir)