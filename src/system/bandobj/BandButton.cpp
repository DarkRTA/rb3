#include "bandobj/BandButton.h"
#include "ui/UI.h"

INIT_REVS(BandButton);

void BandButton::Init(){
    TheUI->InitResources("BandButton");
    Register();
}

BandButton::BandButton() : mFocusAnim(0), mPulseAnim(0), mAnimTask(0), mStartTime(0) {

}

BandButton::~BandButton(){
    if(mFocusAnim) delete mFocusAnim;
    if(mPulseAnim) delete mPulseAnim;
}

BEGIN_COPYS(BandButton)
    COPY_SUPERCLASS(UIButton)
END_COPYS

SAVE_OBJ(BandButton, 0x42)

BEGIN_LOADS(BandButton)
    PreLoad(bs);
    PostLoad(bs);
END_LOADS

void BandButton::PreLoad(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(0x10, 0);
    bool bbb = false;
    if(gRev < 8){
        if(gRev <= 4){
            LOAD_SUPERCLASS(RndTransformable)
            LOAD_SUPERCLASS(RndDrawable)
        }
        else UIButton::PreLoad(bs);
        if(gRev > 2){
            int i, j, k, l;
            bs >> i >> j >> k >> l;
        }
        if(gRev <= 4){
            Symbol s;
            bs >> s;
            SetType(s);
        }
        if(gRev < 8){
            bool b8;
            bs >> b8;
            if(b8) mFitType = kFitStretch;
            else mFitType = kFitWrap;
        }
        if(gRev < 7 && mFitType == kFitStretch){
            Hmx::Matrix3 mtx;
            mtx.Identity();
            SetLocalRot(mtx);
        }
        if(gRev != 0) bs >> bbb;
        else bbb = false;
        bs >> mWidth;
        bs >> mHeight;
        if(gRev <= 4) bs >> mTextToken;
        if(gRev > 5) bs >> (int&)mAlignment;
    }
    else if(gRev == 8){
        UIButton::PreLoad(bs);
        int i; bs >> i;
        mFitType = i;
        bs >> mWidth;
        bs >> mHeight;
        bs >> mLeading;
        bs >> (int&)mAlignment;
        int w, x, y, z;
        bs >> w >> x >> y >> z;
        bs >> bbb;
        Hmx::Color col;
        bs >> col;
        bs >> mKerning;
        bs >> mTextSize;
    }
    else {
        UIButton::PreLoad(bs);
        if(gRev < 0xC){
            int i; bs >> i;
            mFitType = i;
            bs >> mWidth;
            bs >> mHeight;
            if(mFitType == kFitWrap){
                mHeight = 0;
                mWidth = 0;
            }
        }
        if(gRev < 0xB){
            bs >> mLeading;
            bs >> (int&)mAlignment;
        }
        if(gRev < 0xE){
            int i, j, k, l;
            bs >> i >> j >> k >> l;
        }
        if(gRev < 0xB){
            bs >> bbb;
            bs >> mKerning;
            bs >> mTextSize;
        }
    }
    if(gRev < 0xC){
        int i; bs >> i;
    }
    if(gRev < 0xB){
        int c = 0;
        if(bbb) c = 2;
        mCapsMode = c;
    }
    if(gRev == 0xE){
        LoadOldBandTextComp(bs);
    }
}

void BandButton::PostLoad(BinStream& bs){
    UIButton::PostLoad(bs);
    if(gRev == 13 || gRev == 14 || gRev == 15){
        ObjPtr<RndMesh, ObjectDir> meshPtr(0, 0);
        bs >> meshPtr;
    }
}

