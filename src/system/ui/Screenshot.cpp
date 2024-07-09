#include "ui/Screenshot.h"
#include "math/Color.h"
#include "rndobj/Mat.h"
#include "rndobj/Rnd.h"
#include "rndobj/Tex.h"
#include "obj/PropSync_p.h"
#include "utl/Symbols.h"
#include "utl/Loader.h"

unsigned short Screenshot::gRev = 0;
unsigned short Screenshot::gAltRev = 0;

BEGIN_COPYS(Screenshot)
    COPY_SUPERCLASS(Hmx::Object)
    COPY_SUPERCLASS(RndDrawable)
    CREATE_COPY(Screenshot)
    BEGIN_COPYING_MEMBERS
        if(ty != kCopyFromMax) COPY_MEMBER(mTexPath)
    END_COPYING_MEMBERS
    Sync();
END_COPYS

SAVE_OBJ(Screenshot, 0x2D)

void Screenshot::Load(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(1, 0);
    Hmx::Object::Load(bs);
    RndDrawable::Load(bs);
    bs >> mTexPath;
    Sync();
}

void Screenshot::Sync(){
    if(TheLoadMgr.EditMode()){
        delete mTex;
        delete mMat;
        mTex = Hmx::Object::New<RndTex>();
        mTex->SetBitmap(mTexPath);
        mMat = Hmx::Object::New<RndMat>();
        mMat->SetZMode(kDisable);
        mMat->SetDiffuseTex(mTex);
    }
}

void Screenshot::DrawShowing() {
    if (!TheRnd->UnkE4() && TheLoadMgr.EditMode() && mMat) {
        TheRnd->DrawRect(Hmx::Rect(0, 0, TheRnd->Width(), TheRnd->Height()), Hmx::Color(0, 0, 0), mMat, 0, 0);
    }
}

Screenshot::~Screenshot(){
    delete mTex;
    delete mMat;
}

Screenshot::Screenshot() : mTex(0), mMat(0) {

}

BEGIN_HANDLERS(Screenshot)
    HANDLE_SUPERCLASS(RndDrawable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x85)
END_HANDLERS

BEGIN_PROPSYNCS(Screenshot)
    SYNC_PROP_MODIFY_ALT(tex_path, mTexPath, Sync())
    SYNC_SUPERCLASS(RndDrawable)
END_PROPSYNCS
