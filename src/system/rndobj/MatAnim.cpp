#include "rndobj/MatAnim.h"

INIT_REVS(RndMatAnim)

Hmx::Object* RndMatAnim::sOwner;

DECOMP_FORCEACTIVE(MatAnim, __FILE__, "o")

RndMatAnim::TexPtr::TexPtr() : ObjPtr<RndTex, ObjectDir>(sOwner, 0) {}
RndMatAnim::TexPtr::TexPtr(RndTex* tex) : ObjPtr<RndTex, ObjectDir>(sOwner, tex) {}
RndMatAnim::TexKeys::TexKeys(Hmx::Object* o) : mOwner(o) {}

// fn_805FA384
int RndMatAnim::TexKeys::Add(RndTex* tex, float frame, bool b){
    sOwner = mOwner;
    return Keys<TexPtr, RndTex*>::Add(TexPtr(tex), frame, b);
}

// matches in retail with the right inlining settings
RndMatAnim::TexKeys& RndMatAnim::TexKeys::operator=(const RndMatAnim::TexKeys& keys){
    if(this != &keys){
        sOwner = mOwner;
        resize(keys.size());
        TexKeys::iterator it = begin();
        TexKeys::const_iterator otherIt = keys.begin();
        for(; it != end(); ++it, ++otherIt){
            *it = *otherIt;
        }
    }
}

RndMatAnim::RndMatAnim() : mMat(this), mKeysOwner(this, this), mTexKeys(this) {

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
    uint rev;
    bs >> rev;
    if(rev != 0){
        bool oldeditmode = LOADMGR_EDITMODE;
        TheLoadMgr.SetEditMode(true);
        RndMatAnim* it = this;
        int i = 1;
        while(true){
            it->LoadStage(bs);
            if(i == rev) break;
            else if(EndFrame()){
                const char* mnm = MakeString("%s_%d.mnm", FileGetBase(Name(), 0), i);
                MILO_WARN("Splitting out %s from %s", mnm, PathName(this));
                it = Dir()->New<RndMatAnim>(mnm);
                it->SetMat(LookupOrCreateMat(MakeString("%s_%d", FileGetBase(mMat->Name(), 0), i), Dir()));
            }
            i++;
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

// fn_805FB82C - matches in retail
float RndMatAnim::EndFrame(){
    float end = Max(TransKeys().LastFrame(), ScaleKeys().LastFrame());
    end = Max(end, GetTexKeys().LastFrame(), RotKeys().LastFrame());
    end = Max(end, AlphaKeys().LastFrame(), ColorKeys().LastFrame());
    return end;
}

// fn_805FBA6C
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
            GetTexKeys().AtFrame(f1, tex); // fn_805FBDAC - AtFrame for TexPtr, RndTex*
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
            float alpha = mMat->Alpha();
            AlphaKeys().AtFrame(f1, alpha); // fn_803B1308 - Keys<float, float>::AtFrame, which calls another AtFrame method fn_803B1374
            if(f2 != 1.0f){
                Interp(mMat->Alpha(), alpha, f2, alpha);
            }
            mMat->SetAlpha(alpha);
        }
    }
}
#pragma pop

void RndMatAnim::SetKey(float frame){
    if(mMat){
        Vector3 v28, v34;
        MakeEulerScale(mMat->mTexXfm.m, v28, v34);
        TransKeys().Add(mMat->mTexXfm.v, frame, true);
        RotKeys().Add(v28, frame, true);
        ScaleKeys().Add(v34, frame, true);
        GetTexKeys().Add(mMat->GetDiffuseTex(), frame, true);
        ColorKeys().Add(mMat->mColor, frame, true);
        AlphaKeys().Add(mMat->Alpha(), frame, true);
    }
}

void Interp(const RndMatAnim::TexPtr& texPtr, const RndMatAnim::TexPtr&, float, RndTex*& tex){
    tex = texPtr;
}

BEGIN_HANDLERS(RndMatAnim)
    HANDLE_SUPERCLASS(RndAnimatable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x19D)
END_HANDLERS

BEGIN_PROPSYNCS(RndMatAnim)
    SYNC_SUPERCLASS(RndAnimatable)
END_PROPSYNCS