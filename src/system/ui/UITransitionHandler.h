#ifndef UI_UITRANSITIONHANDLER_H
#define UI_UITRANSITIONHANDLER_H
#include "obj/Object.h"
#include "obj/ObjPtr_p.h"
#include "rndobj/Anim.h"

enum UITransitionAnimationState {
    kUITransitionAnimationInvalid,
    kUITransitionAnimationIdle,
    kUITransitionAnimationInAnimating,
    kUITransitionAnimationOutAnimating,
    kUITransitionAnimationReverseOutAnimating
};

class UITransitionHandler {
public:
    UITransitionHandler(Hmx::Object*);
    virtual ~UITransitionHandler();
    virtual void FinishValueChange();
    virtual void StartValueChange();
    virtual bool IsEmptyValue() const = 0;

    void SetInAnim(RndAnimatable*);
    void SetOutAnim(RndAnimatable*);
    RndAnimatable* GetInAnim() const;
    RndAnimatable* GetOutAnim() const;
    bool HasTransitions() const;
    void ClearAnimationState();
    void CopyHandlerData(const UITransitionHandler*);
    void LoadHandlerData(BinStream&);
    void UpdateHandler();
    bool IsReadyToChange() const;

    ObjPtr<RndAnimatable, ObjectDir> mInAnim;
    ObjPtr<RndAnimatable, ObjectDir> mOutAnim;
    unsigned char mAnimationState; // make this the enum above but only take up 1 byte?
    bool mChangePending, b3; // mChangePending, mOutAnimStartedThisFrame
};

#endif
