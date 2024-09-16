#pragma once
#include "ui/UIComponent.h"
#include "rndobj/EventTrigger.h"
#include "rndobj/Anim.h"

class MicManagerInterface;

class MicInputArrow : public UIComponent {
public:
    MicInputArrow();
    OBJ_CLASSNAME(MicInputArrow);
    OBJ_SET_TYPE(MicInputArrow);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void DrawShowing();
    virtual ~MicInputArrow(){}
    virtual void PreLoad(BinStream&);
    virtual void PostLoad(BinStream&);
    virtual void Update();

    void SetMicMgr(MicManagerInterface*);
    void SetMicConnected(bool, int);
    void SetMicExtended(int);
    void SetMicPreview(int);
    void SetMicHidden(int);

    static void Init();
    static void Register(){
        REGISTER_OBJ_FACTORY(MicInputArrow);
    }
    NEW_OBJ(MicInputArrow);

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;

    int mArrowNum; // 0x10c
    MicManagerInterface* mMicManagerInterface; // 0x110
    std::vector<char> mConnectedFlags; // 0x114
    std::vector<bool> mHiddenFlags; // 0x11c
    std::vector<EventTrigger*> mConnectedTrigs; // 0x124
    std::vector<EventTrigger*> mDisconnectedTrigs; // 0x12c
    std::vector<EventTrigger*> mHiddenTrigs; // 0x134
    std::vector<EventTrigger*> mPreviewTrigs; // 0x13c
    std::vector<EventTrigger*> mExtendedTrigs; // 0x144
    std::vector<RndAnimatable*> mLevelAnims; // 0x14c
    std::vector<int> unk154; // 0x154
    float mMicEnergyNormalizer; // 0x15c
    bool unk160; // 0x160
    float unk164[3]; // 0x164
};