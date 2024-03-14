#include "ui/UITransitionHandler.h"
#include "os/Debug.h"

UITransitionHandler::UITransitionHandler(Hmx::Object* obj) : mInAnim(obj, 0), mOutAnim(obj, 0), mAnimationState(0), b2(0), b3(0) {
    
}

UITransitionHandler::~UITransitionHandler(){
    RndAnimatable* inPtr = mInAnim.operator->();
    if(inPtr) inPtr->StopAnimation();
    RndAnimatable* outPtr = mOutAnim.operator->();
    if(outPtr) outPtr->StopAnimation();
}

void UITransitionHandler::CopyHandlerData(const UITransitionHandler* ui){
    mInAnim = ui->mInAnim;
    mOutAnim = ui->mOutAnim;
}

void UITransitionHandler::UpdateHandler(){
    b3 = false;
    if(b2 && IsReadyToChange()){
        FinishValueChange();
    }
    if(mAnimationState == 3){
        MILO_ASSERT(mOutAnim, 0x43);
        if(!mOutAnim.operator->()->IsAnimating()) mAnimationState = 1;
    }
}

bool UITransitionHandler::IsReadyToChange() const {
    bool ret = false;
    switch(mAnimationState){
        case 0: case 1: ret = true; break;
        case 2:
            MILO_ASSERT(mInAnim, 0x59);
            ret = mInAnim.operator->()->IsAnimating() == 0;
        case 4:
            MILO_ASSERT(mOutAnim, 0x60);
            ret = mOutAnim.operator->()->IsAnimating() == 0;
        default:
            MILO_ASSERT(false, 0x68);
    }
    return ret;
}

void UITransitionHandler::SetInAnim(RndAnimatable* anim){
    mInAnim = anim;
}

void UITransitionHandler::SetOutAnim(RndAnimatable* anim){
    mOutAnim = anim;
}


RndAnimatable* UITransitionHandler::GetInAnim() const {
    RndAnimatable* inPtr = mInAnim.operator->();
    return (inPtr) ? inPtr : 0;
}

RndAnimatable* UITransitionHandler::GetOutAnim() const {
    RndAnimatable* outPtr = mOutAnim.operator->();
    return (outPtr) ? outPtr : 0;
}

void UITransitionHandler::ClearAnimationState(){
    mAnimationState = 0;
}

bool UITransitionHandler::HasTransitions() const {
    return (mInAnim.operator->() || mOutAnim.operator->());
}
