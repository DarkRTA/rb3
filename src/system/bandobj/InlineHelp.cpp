#include "InlineHelp.h"
#include "obj/Data.h"
#include "obj/ObjMacros.h"
#include "os/Debug.h"
#include "os/System.h"
#include "ui/UI.h"  
#include "ui/UIComponent.h"
#include "utl/Locale.h"
#include "utl/MakeString.h"

INIT_REVS(InlineHelp)
bool InlineHelp::sHasFlippedTextThisRotation = 0;
bool InlineHelp::sNeedsTextUpdate = 0;
bool InlineHelp::sRotated = 0;

void InlineHelp::ActionElement::SetToken(Symbol s, bool b) {
    if (!b) {
        unk_0x4 = s;
        unk_0xC = Localize(s, NULL);
    } else {
        unk_0x8 = s;
        unk_0x18 = Localize(s, NULL);
    }
}

void InlineHelp::ActionElement::SetString(const char* s, bool b) {
    if (!b) {
        unk_0x4 = gNullStr;
        unk_0xC = s;
    } else {
        unk_0x8 = gNullStr;
        unk_0x18 = s;
    }
}

Symbol InlineHelp::ActionElement::GetToken(bool b) const {
    if (b) return unk_0x8; 
    return unk_0x4;
}

const char* InlineHelp::ActionElement::GetText(bool b) const {
    if (b && !unk_0x18.empty()) return unk_0x18.c_str();
    return unk_0xC.c_str();
}

void InlineHelp::ActionElement::SetConfig(DataNode& dn, bool b) {
    if (dn.Type() == kDataArray) {
        DataArray* da = dn.Array(NULL);
        if (da->Size() == 0) return;
        FormatString fs(Localize(da->Sym(0), NULL));
        for (int i = 1; i < da->Size(); i++) {
            DataNode& dn2 = da->Evaluate(i);
            if (dn2.Type() == kDataSymbol) {
                fs << Localize(dn2.Sym(NULL), NULL);
            } else {
                fs << dn2; 
            }
        }
        SetString(fs.Str(), b);
    } else {
        SetToken(dn.Sym(NULL), b);
    }
}

void InlineHelp::Init() {
    REGISTER_OBJ_FACTORY(InlineHelp)
    TheUI->InitResources("Symbol");
}

InlineHelp::InlineHelp() : unk_0x124(0), unk_0x125(1), unk_0x128(0), unk_0x12C(0), unk_0x130(this, NULL) { }

InlineHelp::~InlineHelp() {
    int siz = unk_0x11C.size();
    for (int i = 0; i < siz; i++) {
        delete unk_0x11C[i];
    }
}

BEGIN_COPYS(InlineHelp)
    CREATE_COPY_AS(InlineHelp, h)
    MILO_ASSERT(h, 129);
    COPY_SUPERCLASS_FROM(UIComponent, h)
    Update();
END_COPYS

void InlineHelp::CopyMembers(const UIComponent* o, Hmx::Object::CopyType ty) {
    UIComponent::CopyMembers(o, ty);
    CREATE_COPY_AS(InlineHelp, h);
    MILO_ASSERT(h, 139);
    COPY_MEMBER_FROM(h, unk_0x125)
    COPY_MEMBER_FROM(h, unk_0x128)
    COPY_MEMBER_FROM(h, unk_0x114)
    COPY_MEMBER_FROM(h, unk_0x130)
    COPY_MEMBER_FROM(h, unk_0x124)
    Update();
}

SAVE_OBJ(InlineHelp, 158)

BEGIN_LOADS(InlineHelp)
    PreLoad(bs);
    PostLoad(bs);
END_LOADS

void InlineHelp::PreLoad(BinStream& bs) {
    LOAD_REVS(bs)
    ASSERT_REVS(4, 0)
    bs >> unk_0x125;
    bs >> unk_0x128; 
    bs >> unk_0x114;
    if (gRev >= 1) bs >> unk_0x130; 
    if (u16(gRev + 0xFFFE) <= 1) { int x; bs >> x; }
    if (gRev >= 3) {
        bs >> unk_0x124;
    }
    UIComponent::PreLoad(bs);
}

void InlineHelp::PostLoad(BinStream& bs) {
    UIComponent::PostLoad(bs);
    Update();
}

BinStream& operator>>(BinStream& bs, InlineHelp::ActionElement& ae) {
    { int x; bs >> x; ae.unk_0x0 = x; }
    Symbol s; bs >> s; ae.SetToken(s, false);
    if (InlineHelp::gRev >= 2)  { bs >> s; ae.SetToken(s, true); }
    return bs;
}
