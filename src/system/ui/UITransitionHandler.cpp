#include "ui/UITransitionHandler.h"
#include "os/Debug.h"
#include "ui/UI.h"

#include "decomp.h"

DECOMP_FORCEACTIVE(UITransitionHandler,
    __FILE__,
    "0"
)

UITransitionHandler::UITransitionHandler(Hmx::Object* obj) : mInAnim(obj, 0), mOutAnim(obj, 0), 
    mAnimationState(0), mChangePending(0), b3(0) {

}

UITransitionHandler::~UITransitionHandler(){
    if(mInAnim) mInAnim->StopAnimation();
    if(mOutAnim) mOutAnim->StopAnimation();
}

void UITransitionHandler::CopyHandlerData(const UITransitionHandler* ui){
    mInAnim = ui->mInAnim;
    mOutAnim = ui->mOutAnim;
}

void UITransitionHandler::LoadHandlerData(BinStream& bs){
    bs >> mInAnim >> mOutAnim;
}

void UITransitionHandler::UpdateHandler(){
    b3 = false;
    if(mChangePending && IsReadyToChange()){
        FinishValueChange();
    }
    if(mAnimationState == 3){
        MILO_ASSERT(mOutAnim, 0x43);
        if(!mOutAnim.operator->()->IsAnimating()) mAnimationState = 1;
    }
}

bool UITransitionHandler::IsReadyToChange() const {
    bool ret = false;
    unsigned int theState = mAnimationState;
    switch(theState){
        case 0: case 1: ret = true; break;
        case 2:
            MILO_ASSERT(mInAnim, 0x59);
            ret = mInAnim->IsAnimating() == 0;
            break;
        case 4:
            MILO_ASSERT(mOutAnim, 0x60);
            ret = mOutAnim->IsAnimating() == 0;
            break;
        default:
            MILO_ASSERT(false, 0x68);
            break;
    }
    return ret;
}

void UITransitionHandler::StartValueChange(){
    unsigned char theState = mAnimationState;
    mChangePending = true;
    if(theState == 0){
        FinishValueChange();
    }
    else if(theState == 1){
        if(mInAnim && !TheUI->IsTransitioning()){
            mInAnim->Animate(0.0f, false, 0.0f);
            mAnimationState = 2;
        }
        else {
            FinishValueChange();
        }
    }
    else if(theState == 3){
        MILO_ASSERT(mOutAnim, 0x8B);
        if(b3) FinishValueChange();
        else {
            mOutAnim->Animate(mOutAnim->GetFrame(), mOutAnim->StartFrame(), mOutAnim->Units(), 0.0f, 0.0f);
            mAnimationState = 4;
        }
    }
}

void UITransitionHandler::FinishValueChange(){
    if(IsEmptyValue()) ClearAnimationState();
    else {
        if(mOutAnim && !TheUI->IsTransitioning()){
            b3 = true;
            mOutAnim->Animate(0.0f, false, 0.0f);
            mAnimationState = 3;
        }
        else mAnimationState = 1;
    }
    mChangePending = false;
}

void UITransitionHandler::SetInAnim(RndAnimatable* anim){
    mInAnim = anim;
}

void UITransitionHandler::SetOutAnim(RndAnimatable* anim){
    mOutAnim = anim;
}


RndAnimatable* UITransitionHandler::GetInAnim() const {
    if(mInAnim) return mInAnim;
    else return 0;
}

RndAnimatable* UITransitionHandler::GetOutAnim() const {
    if(mOutAnim) return mOutAnim;
    else return 0;
}

void UITransitionHandler::ClearAnimationState(){
    mAnimationState = 0;
}

bool UITransitionHandler::HasTransitions() const {
    return (mInAnim.operator->() || mOutAnim.operator->());
}
