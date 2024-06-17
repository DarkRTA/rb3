#ifndef UI_LABELNUMBERTICKER_H
#define UI_LABELNUMBERTICKER_H
#include "ui/UIComponent.h"
#include "obj/ObjPtr_p.h"
#include "rndobj/EventTrigger.h"
#include "os/Timer.h"

class UILabel;

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

    ObjPtr<UILabel, ObjectDir> mLabel; // 0x10c
    int mDesiredValue; // 0x118
    float mAnimTime; // 0x11c
    float mAnimDelay; // 0x120
    Symbol mWrapperText; // 0x124
    float mAcceleration; // 0x128
    int unk12c; // 0x12c
    int unk130; // 0x130
    int unk134; // 0x134
    Timer mTimer; // 0x138
    ObjPtr<EventTrigger, ObjectDir> mTickTrigger; // 0x168
    int mTickEvery; // 0x174
};

#endif
