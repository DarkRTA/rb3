#include "InlineHelp.h"
#include "obj/Data.h"
#include "os/Debug.h"
#include "os/System.h"
#include "ui/UI.h"  
#include "ui/UIComponent.h"
#include "utl/Locale.h"
#include "utl/Symbols.h"

INIT_REVS(InlineHelp)
bool InlineHelp::sHasFlippedTextThisRotation = 0;
bool InlineHelp::sNeedsTextUpdate = 0;
bool InlineHelp::sRotated = 0;

void InlineHelp::ActionElement::SetToken(Symbol s, bool secondary) {
    if (!secondary) {
        mPrimaryToken = s;
        mPrimaryStr = Localize(s, NULL);
    } else {
        mSecondaryToken = s;
        mSecondaryStr = Localize(s, NULL);
    }
}

void InlineHelp::ActionElement::SetString(const char* s, bool b) {
    if (!b) {
        mPrimaryToken = gNullStr;
        mPrimaryStr = s;
    } else {
        mSecondaryToken = gNullStr;
        mSecondaryStr = s;
    }
}

Symbol InlineHelp::ActionElement::GetToken(bool b) const {
    if (b) return mSecondaryToken; 
    return mPrimaryToken;
}

const char* InlineHelp::ActionElement::GetText(bool b) const {
    if (b && !mSecondaryStr.empty()) return mSecondaryStr.c_str();
    return mPrimaryStr.c_str();
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
    Register();
    TheUI->InitResources("InlineHelp");
}

InlineHelp::InlineHelp() : mUseConnectedControllers(0), mHorizontal(1), mSpacing(0), unk_0x12C(0), mTextColor(this, NULL) { }

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
    COPY_MEMBER_FROM(h, mHorizontal)
    COPY_MEMBER_FROM(h, mSpacing)
    COPY_MEMBER_FROM(h, mConfig)
    COPY_MEMBER_FROM(h, mTextColor)
    COPY_MEMBER_FROM(h, mUseConnectedControllers)
    UpdateIconTypes(false);
}

SAVE_OBJ(InlineHelp, 158)

BEGIN_LOADS(InlineHelp)
    PreLoad(bs);
    PostLoad(bs);
END_LOADS

void InlineHelp::PreLoad(BinStream& bs) {
    LOAD_REVS(bs)
    ASSERT_REVS(4, 0)
    bs >> mHorizontal;
    bs >> mSpacing; 
    bs >> mConfig;
    if (gRev >= 1) bs >> mTextColor; 
    if (u16(gRev + 0xFFFE) <= 1) { int x; bs >> x; }
    if (gRev >= 3) {
        bs >> mUseConnectedControllers;
    }
    UIComponent::PreLoad(bs);
}

void InlineHelp::PostLoad(BinStream& bs) {
    UIComponent::PostLoad(bs);
    Update();
}

// void InlineHelp::Enter(){

// }

BinStream& operator>>(BinStream& bs, InlineHelp::ActionElement& ae) {
    { int x; bs >> x; ae.mAction = x; }
    Symbol s; bs >> s; ae.SetToken(s, false);
    if (InlineHelp::gRev >= 2)  { bs >> s; ae.SetToken(s, true); }
    return bs;
}

BEGIN_CUSTOM_PROPSYNC(InlineHelp::ActionElement)
    SYNC_PROP(action, o.mAction)
    SYNC_PROP_SET(text_token, o.GetToken(false), o.SetToken(_val.Sym(0), false))
    SYNC_PROP_SET(secondary_token, o.GetToken(true), o.SetToken(_val.Sym(0), true))
END_CUSTOM_PROPSYNC