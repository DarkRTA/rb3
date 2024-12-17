#pragma once
#include "ui/UIComponent.h"
#include "obj/ObjPtr_p.h"
#include "rndobj/EventTrigger.h"
#include "os/Timer.h"

class UILabel;

/** "a ticker to control counting up or down for a given number based label" */
class LabelNumberTicker : public UIComponent {
public:
    LabelNumberTicker();
    OBJ_CLASSNAME(LabelNumberTicker)
    OBJ_SET_TYPE(LabelNumberTicker)
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual ~LabelNumberTicker();
    virtual void PreLoad(BinStream&);
    virtual void PostLoad(BinStream&);
    virtual void Enter();
    virtual void Poll();

    void UpdateDisplay();
    void SetLabel(UILabel*);
    void SnapToValue(int);
    void CountUp();
    void SetDesiredValue(int);

    UILabel* Label() const {
        if(!mLabel) return 0;
        else return mLabel;
    }

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(LabelNumberTicker)
    static void Init();

    static void Register(){ REGISTER_OBJ_FACTORY(LabelNumberTicker); }

    /** "label to be shrink wrapped" */
    ObjPtr<UILabel> mLabel; // 0x10c
    /** "desired value" */
    int mDesiredValue; // 0x118
    /** "Time taken for number ticking animation" */
    float mAnimTime; // 0x11c
    /** "delay before number ticking animation" */
    float mAnimDelay; // 0x120
    /** "Localization token to use for wrapper (must include %s)" */
    Symbol mWrapperText; // 0x124
    /** "Higher number accelerates faster, 3 is a good number." */
    float mAcceleration; // 0x128
    int unk12c; // 0x12c
    int unk130; // 0x130
    int unk134; // 0x134
    Timer mTimer; // 0x138
    /** "Event to trigger while counting up" */
    ObjPtr<EventTrigger> mTickTrigger; // 0x168
    /** "Trigger tick_trigger every time the count goes up by this much" */
    int mTickEvery; // 0x174
};
