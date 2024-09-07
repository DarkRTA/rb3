#include "bandobj/BandButton.h"
#include "bandobj/BandLabel.h"
#include "rndobj/PropAnim.h"
#include "ui/UI.h"
#include "utl/Symbols.h"

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
        BandLabel::LoadOldBandTextComp(bs);
    }
}

void BandButton::PostLoad(BinStream& bs){
    UIButton::PostLoad(bs);
    if(gRev == 13 || gRev == 14 || gRev == 15){
        ObjPtr<RndMesh, ObjectDir> meshPtr(0, 0);
        bs >> meshPtr;
    }
}

void BandButton::DrawShowing(){
    bool focusanimating = false;
    if(mFocusAnim && mFocusAnim->IsAnimating()) focusanimating = true;
    if(mState == kFocused && (focusanimating || mPulseAnim)){
        if(!focusanimating && !mPulseAnim->IsAnimating()) StartPulseAnim();
        if(focusanimating){
            if(!mText->GetFont()) Update();
            mAnimTask->Poll(TheTaskMgr.UISeconds() - mStartTime);
            UpdateAndDrawHighlightMesh();
            mText->DrawShowing();
            if(UILabel::sDebugHighlight) Highlight();
        }
        else UILabel::DrawShowing();
    }
    else UILabel::DrawShowing();
}

void BandButton::SetState(UIComponent::State state){
    if(state != mState){
        UIComponent::State curstate = GetState();
        UIComponent::SetState(state);
        if(mState == kFocused && mFocusAnim){
            if(TheUI->IsTransitioning()) SkipToFocused();
            else {
                mAnimTask = mFocusAnim->Animate(mFocusAnim->StartFrame(), mFocusAnim->EndFrame(), kTaskUISeconds, 0.0f, 0.05f);
                mStartTime = TheTaskMgr.UISeconds();
            }
        }
        else if(curstate == kFocused){
            if(mPulseAnim && mPulseAnim->IsAnimating()) mPulseAnim->StopAnimation();
            if(mFocusAnim){
                if(TheUI->IsTransitioning()) SkipToUnfocused();
                else {
                    mAnimTask = mFocusAnim->Animate(mFocusAnim->EndFrame(), mFocusAnim->StartFrame(), kTaskUISeconds, 0.0f, 0.05f);
                    mStartTime = TheTaskMgr.UISeconds();
                }
            }
        }
    }
}

void BandButton::SkipToFocused(){
    if(mFocusAnim){
        mAnimTask = mFocusAnim->Animate(mFocusAnim->EndFrame() - 1.0f, mFocusAnim->EndFrame(), kTaskUISeconds, 0.0f, 0.0f);
        mStartTime = TheTaskMgr.UISeconds();
    }
}

void BandButton::SkipToUnfocused(){
    if(mFocusAnim){
        mAnimTask = mFocusAnim->Animate(mFocusAnim->StartFrame() + 1.0f, mFocusAnim->StartFrame(), kTaskUISeconds, 0.0f, 0.0f);
        mStartTime = TheTaskMgr.UISeconds();
    }
}

void BandButton::StartPulseAnim(){
    if(mPulseAnim){
        mAnimTask = mPulseAnim->Animate(0.05f, false, 0.0f, RndAnimatable::k30_fps_ui, mPulseAnim->StartFrame(), mPulseAnim->EndFrame(), 0.0f, 1.0f, loop);
        mStartTime = TheTaskMgr.UISeconds();
    }
}

void BandButton::Update(){
    UILabel::Update();
    if(mLabelDir->FocusAnim()){
        if(!mFocusAnim) mFocusAnim = Hmx::Object::New<RndPropAnim>();
        mFocusAnim->Copy(mLabelDir->FocusAnim(), kCopyShallow);
        mFocusAnim->Replace(mLabelDir->TextObj(mFontMatVariation), mText);
    }
    if(mLabelDir->PulseAnim()){
        if(!mPulseAnim) mPulseAnim = Hmx::Object::New<RndPropAnim>();
        mPulseAnim->Copy(mLabelDir->PulseAnim(), kCopyShallow);
        mPulseAnim->Replace(mLabelDir->TextObj(mFontMatVariation), mText);
    }
}

BEGIN_HANDLERS(BandButton)
    HANDLE_ACTION(skip_to_focused, SkipToFocused())
    HANDLE_ACTION(skip_to_unfocused, SkipToUnfocused())
    HANDLE_SUPERCLASS(UIButton)
    HANDLE_CHECK(0x171)
END_HANDLERS

BEGIN_PROPSYNCS(BandButton)
    SYNC_SUPERCLASS(UIButton)
END_PROPSYNCS