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
    GET_COPY(Screenshot)
    if(c && ty != kCopyFromMax) COPY_MEMBER(mTexPath)
    Sync();
END_COPYS

SAVE_OBJ(Screenshot, 0x2D)

void Screenshot::Load(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(1, 0);
    Hmx::Object::Load(bs);
    RndDrawable::Load(bs);
    char x[0x100];
    bs.ReadString(x, 256);
    mTexPath.Set(FilePath::sRoot.c_str(), x);
    Sync();
}

void Screenshot::Sync(){
    if(TheLoadMgr.EditMode()){
        delete mTex;
        delete mMat;
        mTex = Hmx::Object::New<RndTex>();
        mTex->SetBitmap(mTexPath);
        mMat = Hmx::Object::New<RndMat>();
        mMat->unkb0p1 = 0;
        mMat->unkb4p1 |= 2;
        mMat->mDiffuseTex = mTex;
        mMat->unkb4p1 |= 2;
    }
}

void Screenshot::DrawShowing() {
    if (!TheRnd->unk_0xE4 && TheLoadMgr.EditMode() && mMat) {
        TheRnd->DrawRect(Hmx::Rect(0, 0, TheRnd->mWidth, TheRnd->mHeight), Hmx::Color(0, 0, 0), mMat, 0, 0);
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
    // SYNC_PROP_ACTION(tex_path, mTexPath, kPropSize|kPropGet, Sync())
    // TODO: fix the SYNC_PROP_ACTION macro to incorporate this order of control flow, while not breaking the other SyncProps
    if(sym == tex_path){ 
        bool synced = PropSync(mTexPath, _val, _prop, _i + 1, _op);
        if(synced) { 
            if(!(_op & (kPropSize|kPropGet))){ Sync(); } 
            return true; 
        } 
        else return false; 
    }
    SYNC_SUPERCLASS(RndDrawable)
END_PROPSYNCS
