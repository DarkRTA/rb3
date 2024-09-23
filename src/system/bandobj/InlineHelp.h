#pragma once

#include "obj/ObjMacros.h"
#include "os/System.h"
#include "types.h"
#include "ui/UIColor.h"
#include "ui/UIComponent.h"
#include "bandobj/BandLabel.h"
#include <vector>

class InlineHelp : public UIComponent {
public:
    class ActionElement {
    public:
        JoypadAction mAction; // 0x0
        Symbol mPrimaryToken; // 0x4
        Symbol mSecondaryToken; // 0x8
        String mPrimaryStr; // 0xc
        String mSecondaryStr; // 0x18

        ActionElement() : mAction(kAction_None), mPrimaryToken(gNullStr), mSecondaryToken(gNullStr) {}
        ActionElement(JoypadAction a) : mAction(a), mPrimaryToken(gNullStr), mSecondaryToken(gNullStr) {}

        bool HasSecondaryStr() const { return !mSecondaryStr.empty(); }
        void SetToken(Symbol, bool);
        void SetString(const char*, bool);
        Symbol GetToken(bool) const;
        const char* GetText(bool) const;
        void SetConfig(DataNode&, bool);
    };

    InlineHelp();
    OBJ_CLASSNAME(InlineHelp)
    OBJ_SET_TYPE(InlineHelp)
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void DrawShowing();
    virtual ~InlineHelp();
    virtual void PreLoad(BinStream&);
    virtual void PostLoad(BinStream&);
    virtual void Enter();
    virtual void Poll();
    virtual void CopyMembers(const UIComponent*, Hmx::Object::CopyType);
    virtual void Update();
    virtual void SyncLabelsToConfig();
    virtual void UpdateIconTypes(bool);
    virtual String GetIconStringFromAction(int);

    void SetActionToken(JoypadAction, DataNode&);
    void ClearActionToken(JoypadAction);
    void UpdateTextColors();
    void UpdateLabelText();

    DataNode OnSetConfig(const DataArray*);

    std::vector<Symbol> mIconTypes; // 0x10c
    std::vector<ActionElement> mConfig; // 0x114
    std::vector<UILabel*> mTextLabels; // 0x11c
    bool mUseConnectedControllers; // 0x124
    bool mHorizontal; // 0x125
    float mSpacing; // 0x128
    BandLabel* unk_0x12C; // 0x12c
    ObjPtr<UIColor, ObjectDir> mTextColor; // 0x130

    static void Init();
    static void Register(){
        REGISTER_OBJ_FACTORY(InlineHelp)
    }
    NEW_OBJ(InlineHelp)
    DECLARE_REVS
    NEW_OVERLOAD
    DELETE_OVERLOAD

    static void SetLabelRotationPcts(float);
    static void ResetRotation();

    static bool sHasFlippedTextThisRotation;
    static bool sNeedsTextUpdate;
    static bool sRotated;
    static float sLastUpdatedTime;
    static float sRotationTime;
    static float sLabelRot;
};

BinStream& operator>>(BinStream&, InlineHelp::ActionElement&);
