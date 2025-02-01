#include "ui/UITrigger.h"
#include "ui/UIComponent.h"
#include "obj/Task.h"
#include "utl/Symbols.h"
// #include "utl/ClassSymbols.h"

INIT_REVS(UITrigger)

UITrigger::UITrigger()
    : mCallbackObject(this, 0), mEndTime(0.0f), unkfc(1), mBlockTransition(0) {}

BEGIN_COPYS(UITrigger)
    COPY_SUPERCLASS(EventTrigger)
    CREATE_COPY(UITrigger)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mBlockTransition)
    END_COPYING_MEMBERS
END_COPYS

SAVE_OBJ(UITrigger, 0x2A)

// matches in retail
BEGIN_LOADS(UITrigger)
    LOAD_REVS(bs)
    ASSERT_REVS(1, 0)
    if (gRev < 1) {
        UIComponent *uiCom = Hmx::Object::New<UIComponent>();
        uiCom->Load(bs);
        delete uiCom;
        Symbol sym;
        bs >> sym;
        UnregisterEvents();
        mTriggerEvents.clear();
        mTriggerEvents.push_back(sym);
        RegisterEvents();
        ObjPtr<RndAnimatable, ObjectDir> animPtr(this, 0);
        bs >> animPtr;
        mAnims.clear();
        mAnims.push_back();
        EventTrigger::Anim &anim = mAnims.back();
        anim.mAnim = animPtr;
    } else
        LOAD_SUPERCLASS(EventTrigger);
    bs >> mBlockTransition;
END_LOADS

void UITrigger::Enter() {
    mStartTime = TheTaskMgr.UISeconds();
    mEndTime = 0.0f;
}

bool UITrigger::IsBlocking() const {
    if (mStartTime > TheTaskMgr.UISeconds()) {
        const_cast<UITrigger *>(this)->mEndTime = 0.0f;
    }
    return mBlockTransition && mEndTime && !IsDone();
}

// class Anim {
// public:
//     Anim(Hmx::Object*);

//     ObjOwnerPtr<RndAnimatable> mAnim; // 0x0
//     float mBlend; // 0xc
//     float mDelay; // 0x10
//     bool mWait; // 0x14
//     /** "Enable animation filtering" */
//     bool mEnable; // 0x15
//     /** "Rate to animate" */
//     unsigned char mRate; // 0x16 - enum?
//     /** "Start frame of animation" */
//     float mStart; // 0x18
//     /** "End frame of animation" */
//     float mEnd; // 0x1c
//     /** "Period of animation if non-zero" */
//     float mPeriod; // 0x20
//     /** "Scale of animation" */
//     float mScale; // 0x24
//     /** "Type of animation" */
//     Symbol mType; // 0x28
// };

void UITrigger::Trigger() {
    EventTrigger::Trigger();
    mStartTime = TheTaskMgr.UISeconds();
    mEndTime = 0;
    for (ObjVector<Anim>::iterator it = mAnims.begin(); it != mAnims.end(); ++it) {
        Anim &curAnim = *it;
        if (curAnim.mAnim) {
            float f4;
            if (curAnim.mEnable) {
                if (curAnim.mPeriod * 30.0f == 0.0f) {
                    f4 = curAnim.mScale;
                    if (f4 == 0)
                        f4 = 1.0f;
                    f4 = std::fabs(curAnim.mStart - curAnim.mEnd) / f4;
                }
            } else {
                f4 = std::fabs(curAnim.mAnim->StartFrame() - curAnim.mAnim->EndFrame());
            }
            MaxEq(mEndTime, (curAnim.mDelay * 30.0f + f4) / 30.0f);
        }
    }
    if (mBlockTransition && mEndTime > 5.0f) {
        MILO_WARN(
            "%s (%s) is blocking and really long! (%f seconds)",
            Name(),
            PathName(Dir()),
            mEndTime
        );
    }
    mEndTime += TheTaskMgr.UISeconds();
    unkfc = false;
}

void UITrigger::CheckAnims() {
    for (ObjVector<Anim>::iterator it = mAnims.begin(); it != mAnims.end(); ++it) {
        Anim &curAnim = *it;
        RndAnimatable *anim = curAnim.mAnim;
        if (anim && anim->GetRate() != RndAnimatable::k30_fps_ui) {
            if (LOADMGR_EDITMODE) {
                MILO_WARN("Setting animatable rate to k30_fps_ui for %s", anim->Name());
            }
            anim->SetRate(RndAnimatable::k30_fps_ui);
        }
        curAnim.mRate = RndAnimatable::k30_fps_ui;
    }
}

void UITrigger::StopAnimations() {
    for (ObjVector<EventTrigger::Anim>::iterator it = mAnims.begin(); it != mAnims.end();
         it++) {
        RndAnimatable *anim = (*it).mAnim;
        if (anim && anim->IsAnimating())
            anim->StopAnimation();
    }
}

void UITrigger::PlayStartOfAnims() {
    for (ObjVector<EventTrigger::Anim>::iterator it = mAnims.begin(); it != mAnims.end();
         it++) {
        Anim &curAnim = *it;
        RndAnimatable *anim = curAnim.mAnim;
        if (anim) {
            float f3 = anim->StartFrame();
            float f4 = 0.0099999998f;
            if (curAnim.mEnable) {
                f3 = curAnim.mStart;
                if (f3 > curAnim.mEnd) {
                    f4 *= -1;
                }
            }
            anim->Animate(f3 + f4, f3, kTaskUISeconds, 0, 0);
        }
    }
}

void UITrigger::PlayEndOfAnims() {
    for (ObjVector<EventTrigger::Anim>::iterator it = mAnims.begin(); it != mAnims.end();
         it++) {
        Anim &curAnim = *it;
        RndAnimatable *anim = curAnim.mAnim;
        if (anim) {
            float f3 = anim->EndFrame();
            float f4 = 0.0099999998f;
            if (curAnim.mEnable) {
                f3 = curAnim.mEnd;
                if (curAnim.mStart > f3) {
                    f4 *= -1;
                }
            }
            anim->Animate(f3 - f4, f3, kTaskUISeconds, 0, 0);
        }
    }
}

DataArray *UITrigger::SupportedEvents() {
    static DataArray *events =
        SystemConfig("objects", "UITrigger", "supported_events")->Array(1);
    return events;
}

void UITrigger::Poll() {
    if (!unkfc) {
        if (IsDone()) {
            unkfc = true;
            if (mCallbackObject) {
                mCallbackObject->Handle(UITriggerCompleteMsg(this), true);
            }
        }
    }
}

BEGIN_HANDLERS(UITrigger)
    HANDLE_EXPR(end_time, mEndTime)
    HANDLE_ACTION(play_start_of_anims, PlayStartOfAnims())
    HANDLE_ACTION(play_end_of_anims, PlayEndOfAnims())
    HANDLE_ACTION(stop_anims, StopAnimations())
    HANDLE_EXPR(is_done, IsDone())
    HANDLE_EXPR(is_blocking, IsBlocking())
    HANDLE_SUPERCLASS(EventTrigger)
    HANDLE_CHECK(0x10C)
END_HANDLERS

BEGIN_PROPSYNCS(UITrigger)
    SYNC_PROP(block_transition, mBlockTransition)
    SYNC_PROP(callback_object, mCallbackObject)
    SYNC_SUPERCLASS(EventTrigger)
END_PROPSYNCS