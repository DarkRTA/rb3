#include "rndobj/MatAnim.h"

INIT_REVS(RndMatAnim)

Hmx::Object* RndMatAnim::sOwner;

DECOMP_FORCEACTIVE(MatAnim, __FILE__, "o")

RndMatAnim::TexPtr::TexPtr() : ObjPtr<RndTex, ObjectDir>(sOwner, 0) {}
RndMatAnim::TexPtr::TexPtr(RndTex* tex) : ObjPtr<RndTex, ObjectDir>(sOwner, tex) {}
RndMatAnim::TexKeys::TexKeys(Hmx::Object* o) : mOwner(o) {}

RndMatAnim::TexKeys& RndMatAnim::TexKeys::operator=(const RndMatAnim::TexKeys& keys){
    if(this != &keys){
        sOwner = mOwner;
    }
}

RndMatAnim::RndMatAnim() : mMat(this, 0), mKeysOwner(this, this), mTexKeys(this) {

}

void RndMatAnim::SetMat(RndMat* mat){
    mMat = mat;
}

void RndMatAnim::Replace(Hmx::Object* from, Hmx::Object* to){
    Hmx::Object::Replace(from, to);
    if(mKeysOwner == from){
        if(!to) mKeysOwner = this;
        else mKeysOwner = dynamic_cast<RndMatAnim*>(to)->mKeysOwner;
    }
}

SAVE_OBJ(RndMatAnim, 0x6C)

void RndMatAnim::LoadStage(BinStream& bs){
    if(gRev < 2) MILO_WARN("Can't convert old MatAnim stages");
    if(gRev != 0){
        bs >> mTransKeys >> mScaleKeys >> mRotKeys;
    }
    if(gRev > 1) bs >> mTexKeys;
}

void RndMatAnim::LoadStages(BinStream& bs){
    int rev;
    bs >> rev;
    bool oldeditmode = TheLoadMgr.EditMode();
    if(rev != 0){
        TheLoadMgr.SetEditMode(true);
        float f = 0.0f;
        for(int i = 1; LoadStage(bs), i != rev; i++){
            if(EndFrame() != f){
                const char* mnm = MakeString("%s_%d.mnm", FileGetBase(Name(), 0), i);
                MILO_WARN("Splitting out %s from %s", mnm, PathName(this));
                RndMatAnim* mAnim = Hmx::Object::New<RndMatAnim>();
                if(mnm) mAnim->SetName(mnm, Dir());
                mAnim->SetMat(LookupOrCreateMat(MakeString("%s_%d", FileGetBase(mMat->Name(), 0), i), Dir()));
            }
        }
        TheLoadMgr.SetEditMode(oldeditmode);
    }
}

BEGIN_LOADS(RndMatAnim)
    LOAD_REVS(bs)
    ASSERT_REVS(7, 0)
    if(gRev > 5) LOAD_SUPERCLASS(Hmx::Object)
    LOAD_SUPERCLASS(RndAnimatable)
    sOwner = this;
    bs >> mMat;
    if(gRev < 7) LoadStages(bs);
    bs >> mKeysOwner;
    if(!mKeysOwner) mKeysOwner = this;
    if(gRev > 1){
        Keys<Hmx::Color, Hmx::Color> k1;
        Keys<Hmx::Color, Hmx::Color> k2;
        if(gRev < 5) bs >> k1;
        if(gRev < 3) bs >> k2;
        bs >> mColorKeys;
        if(gRev < 4){
            Keys<Hmx::Color, Hmx::Color> k3;
            bs >> k3;
        }
        bs >> mAlphaKeys;
        if(gRev < 5 && mColorKeys.empty()){
            if(!k1.empty()) mColorKeys = k1;
            else if(!k2.empty()) mColorKeys = k2;
        }
    }
    if(gRev > 6) bs >> mTransKeys >> mScaleKeys >> mRotKeys >> mTexKeys;
END_LOADS

BEGIN_COPYS(RndMatAnim)
    CREATE_COPY_AS(RndMatAnim, m)
    MILO_ASSERT(m, 0xF1);
    COPY_SUPERCLASS(Hmx::Object)
    COPY_SUPERCLASS(RndAnimatable)
    COPY_MEMBER_FROM(m, mMat)
    if(ty == kCopyShallow || (ty == kCopyFromMax && m->mKeysOwner != m)) COPY_MEMBER_FROM(m, mKeysOwner)
    else {
        sOwner = this;
        mKeysOwner = this;
        mColorKeys = m->mKeysOwner->mColorKeys;
        mAlphaKeys = m->mKeysOwner->mAlphaKeys;
        mTransKeys = m->mKeysOwner->mTransKeys;
        mScaleKeys = m->mKeysOwner->mScaleKeys;
        mRotKeys = m->mKeysOwner->mRotKeys;
        mTexKeys = m->mKeysOwner->mTexKeys;
    }
END_COPYS

void RndMatAnim::Print(){
    TextStream& ts = TheDebug;
    ts << "   mat: " << mMat << "\n";
    ts << "   transKeys: " << mTransKeys << "\n";
    ts << "   scaleKeys: " << mScaleKeys << "\n";
    ts << "   rotKeys:" << mRotKeys << "\n";
    ts << "   texKeys: " << mTexKeys << "\n";
    ts << "   keysOwner: " << mKeysOwner << "\n";
    ts << "   baseKeys: " << mColorKeys << "\n";
    ts << "   alphaKeys: " << mAlphaKeys << "\n";
}

Keys<Vector3, Vector3>& RndMatAnim::TransKeys(){ return mKeysOwner->mTransKeys; }
Keys<Vector3, Vector3>& RndMatAnim::ScaleKeys(){ return mKeysOwner->mScaleKeys; }
RndMatAnim::TexKeys& RndMatAnim::GetTexKeys(){ return mKeysOwner->mTexKeys; }
Keys<Vector3, Vector3>& RndMatAnim::RotKeys(){ return mKeysOwner->mRotKeys; }
Keys<float, float>& RndMatAnim::AlphaKeys(){ return mKeysOwner->mAlphaKeys; }
Keys<Hmx::Color, Hmx::Color>& RndMatAnim::ColorKeys(){ return mKeysOwner->mColorKeys; }

#pragma push
#pragma dont_inline on
void RndMatAnim::SetFrame(float f1, float f2){
    RndAnimatable::SetFrame(f1, f2);
    if(mMat){
        Vector3 v68;
        Vector3 v74;
        Transform t58(mMat->TexXfm());
        if(!TransKeys().empty()){
            if(f2 != 1.0f){
                TransKeys().AtFrame(f1, v68);
                Interp(t58.v, v68, f2, t58.v);
            }
            else TransKeys().AtFrame(f1, t58.v);
        }
        if(!RotKeys().empty()){
            RotKeys().AtFrame(f1, v68);
            if(f2 != 1.0f){
                Vector3 v80;
                if(ScaleKeys().empty()) MakeEuler(t58.m, v80);
                else MakeEulerScale(t58.m, v80, v74);
                Interp(v80, v68, f2, v68);
            }
            MakeRotMatrix(v68, t58.m, true);
        }
        if(!ScaleKeys().empty()){
            ScaleKeys().AtFrame(f1, v68);
            if(f2 != 1.0f){
                Interp(v74, v68, f2, v68);
            }
            Scale(v68, t58.m, t58.m);
        }
        if(!TransKeys().empty() || !RotKeys().empty() || !ScaleKeys().empty()){
            mMat->SetTexXfm(t58);
        }
        if(!GetTexKeys().empty()){
            RndTex* tex;
            GetTexKeys().AtFrame(f1, tex);
            mMat->SetDiffuseTex(tex);
        }
        Hmx::Color col(mMat->GetColor());
        if(!ColorKeys().empty()){
            ColorKeys().AtFrame(f1, col);
            if(f2 != 1.0f){
                Interp(mMat->GetColor(), col, f2, col);
            }
            mMat->SetColor(col);
        }
        if(!AlphaKeys().empty()){
            
        }
    }
}
#pragma pop

BEGIN_HANDLERS(RndMatAnim)
    HANDLE_SUPERCLASS(RndAnimatable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x19D)
END_HANDLERS

BEGIN_PROPSYNCS(RndMatAnim)
    SYNC_SUPERCLASS(RndAnimatable)
END_PROPSYNCS