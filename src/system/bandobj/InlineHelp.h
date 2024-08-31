#pragma once

#include "obj/ObjMacros.h"
#include "os/System.h"
#include "types.h"
#include "ui/UIColor.h"
#include "ui/UIComponent.h"
#include <vector>

class InlineHelp : public UIComponent {
    public:
    class ActionElement { public:
        int unk_0x0;
        Symbol unk_0x4, unk_0x8;
        String unk_0xC;
        String unk_0x18;

        ActionElement() : unk_0x0(0), unk_0x4(gNullStr), unk_0x8(gNullStr) {}

        void SetToken(Symbol, bool);
        void SetString(const char*, bool);
        Symbol GetToken(bool) const;
        const char* GetText(bool) const;
        void SetConfig(DataNode&, bool);
    };

    InlineHelp();
    virtual ~InlineHelp();
    OBJ_CLASSNAME(InlineHelp)
    OBJ_SET_TYPE(InlineHelp)
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void CopyMembers(const UIComponent*, Hmx::Object::CopyType);
    virtual void Save(BinStream&);
    virtual void Load(BinStream&);
    virtual void PreLoad(BinStream&);
    virtual void PostLoad(BinStream&);

    std::vector<Symbol> unk_0x10C;
    std::vector<ActionElement> unk_0x114;
    std::vector<UIComponent*> unk_0x11C;
    bool unk_0x124, unk_0x125;
    float unk_0x128;
    u32 unk_0x12C;
    ObjPtr<UIColor, ObjectDir> unk_0x130;

    static void Init();
    NEW_OBJ(InlineHelp)
    DECLARE_REVS

    static bool sHasFlippedTextThisRotation;
    static bool sNeedsTextUpdate;
    static bool sRotated;
};

BinStream& operator>>(BinStream&, InlineHelp::ActionElement&);
