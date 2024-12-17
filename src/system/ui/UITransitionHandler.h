#pragma once
#include "obj/Object.h"
#include "obj/ObjPtr_p.h"
#include "rndobj/Anim.h"
#include "types.h"

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

    /** "animation kicked off before extended entries are updated" */
    ObjPtr<RndAnimatable> mInAnim;
    /** "animation kicked off after extended entries are updated" */
    ObjPtr<RndAnimatable> mOutAnim;
    /** The current transition animation state. */
    unsigned char mAnimationState; // make this the enum above but only take up 1 byte?
    bool mChangePending, b3; // mChangePending, mOutAnimStartedThisFrame
};
