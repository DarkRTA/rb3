#include "StarDisplay.h"
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "os/Debug.h"
#include "rndobj/Text.h"
#include "ui/UI.h"
#include "ui/UIComponent.h"
#include "utl/Symbol.h"
#include "utl/Symbols.h"
#include "utl/Symbols2.h"
#include "utl/Symbols3.h"

INIT_REVS(StarDisplay)

void StarDisplay::Init() {
    Hmx::Object::RegisterFactory(StaticClassName(), NewObject);
    TheUI->InitResources("StarDisplay");
}

StarDisplay::StarDisplay() : unk_0x114(0), unk_0x115(1), unk_0x116(0), mStars(5), unk_0x11C(5),
    unk_0x120(RndText::kMiddleLeft), unk_0x124(gNullStr), unk_0x128(gNullStr) {
        unk_0x10C = New<BandLabel>();
        unk_0x110 = New<BandLabel>();
    }
StarDisplay::~StarDisplay() {
    delete unk_0x10C;
    delete unk_0x110;
}

BEGIN_COPYS(StarDisplay)
    UIComponent::Copy(o,ty);
END_COPYS

void StarDisplay::CopyMembers(const UIComponent* ui, Hmx::Object::CopyType ct) {
    UIComponent::CopyMembers(ui, ct);
    const StarDisplay* starDisplay = dynamic_cast<const StarDisplay*>(ui);
    MILO_ASSERT(starDisplay, 62);
    mStars = starDisplay->mStars;
    unk_0x11C = starDisplay->unk_0x11C;
    unk_0x114 = starDisplay->unk_0x114;
    unk_0x115 = starDisplay->unk_0x115;
    unk_0x116 = starDisplay->unk_0x116;
    unk_0x120 = starDisplay->unk_0x120;
    unk_0x124 = starDisplay->unk_0x124;
    unk_0x128 = starDisplay->unk_0x128;
}

SAVE_OBJ(StarDisplay, 86)

BEGIN_LOADS(StarDisplay)
    PreLoad(bs);
    PostLoad(bs);
END_LOADS

void StarDisplay::PreLoad(BinStream& bs) {
    LOAD_REVS(bs)
    ASSERT_REVS(6, 0)
    if (gRev != 1) bs >> mStars;
    bs >> unk_0x11C;
    bs >> unk_0x114;
    if (gRev >= 3) {
        bs >> unk_0x115;
        bs >> unk_0x116;
        if (gRev < 5) { 
            int x = 0; bs >> x; 
        }
    }
    if (gRev >= 4) bs >> (int&)unk_0x120;
    if (gRev == 5) {
        String s;
        bs >> s;
        bs >> s;
    }
    if (gRev >= 6) {
        bs >> unk_0x124;
        bs >> unk_0x128;
    } 
    UIComponent::PreLoad(bs);
}

void StarDisplay::PostLoad(BinStream& bs) {
    UIComponent::PostLoad(bs);
    Update();
}

void StarDisplay::Enter() { UIComponent::Enter(); UpdateDisplay(); }

Symbol StarDisplay::GetSymbolForStarCount(int i) {
    switch (i) {
        case 0:
            return stars_0; 
        case 1:
            return stars_1; 
        case 2:
            return stars_2; 
        case 3:
            return stars_3; 
        case 4:
            return stars_4;
        case 5:
            return stars_5;  
        case 6:
            return stars_6;
        default:
            MILO_FAIL("Number of stars is unsupported: stars = %i", i);
            return gNullStr; 
    }
}

int StarDisplay::GetStarCountForSymbol(Symbol s) {
    int i = 0;
    Symbol* s2;
    do {
        s2 = &GetSymbolForStarCount(i);
        if (*s2 == s) return i;
    } while (++i <= 6);
    MILO_FAIL("can't set star display to token %s", s.Str());
    return 0;
}

void StarDisplay::DrawShowing() {
    ObjectDir* dir = mMesh->mDir.mDir;
    MILO_ASSERT(dir, 312);
    unk_0x10C->SetTransParent(this, false);
    unk_0x10C->Draw();
    unk_0x110->SetTransParent(this, false);
    unk_0x110->Draw();
    Transform* t;
    if (mCache->mFlags & 1) t = &WorldXfm_Force();
    else t = &mWorldXfm;
    SetWorldXfm(*t);
}

void StarDisplay::SetValues(int st, int max) { mStars = st; unk_0x11C = max; UpdateDisplay(); }

void StarDisplay::SetToToken(Symbol s) { mStars = GetStarCountForSymbol(s); UpdateDisplay(); }

void StarDisplay::SetAlignment(RndText::Alignment a) { unk_0x120 = a; UpdateDisplay(); }

void StarDisplay::SetForceMixedMode(bool b) { unk_0x114 = b; UpdateDisplay(); }

void StarDisplay::SetShowDenominator(bool b) { unk_0x115 = b; UpdateDisplay(); }

void StarDisplay::Update() {
    UIComponent::Update();
    DataArray* typeDef = mTypeDef;
    MILO_ASSERT(typeDef, 369);
    ObjectDir* dir = mMesh->mDir.mDir;
    MILO_ASSERT(dir, 372);
    unk_0x10C->ResourceCopy(dir->Find<BandLabel>(typeDef->FindArray(resource_stars_label, true)->Str(1), true));
    BandLabel* bl2 = dir->Find<BandLabel>(typeDef->FindArray(resource_stars_mixed_label, true)->Str(1), true);
    unk_0x110->ResourceCopy(bl2);
    UpdateDisplay();
}

BEGIN_HANDLERS(StarDisplay)
    HANDLE_ACTION(set_values, SetValues(_msg->Int(2), _msg->Int(3)))
    HANDLE_ACTION(set_to_token, SetToToken(_msg->Sym(2)))
    HANDLE_SUPERCLASS(UIComponent)
    HANDLE_CHECK(391)
END_HANDLERS

BEGIN_PROPSYNCS(StarDisplay)
    SYNC_PROP_MODIFY(stars, mStars, UpdateDisplay())
    SYNC_PROP_MODIFY(total_stars, unk_0x11C, UpdateDisplay())
    SYNC_PROP_MODIFY(force_mixed_mode, unk_0x114, UpdateDisplay())
    SYNC_PROP_MODIFY(show_empty_stars, unk_0x116, UpdateDisplay())
    SYNC_PROP_MODIFY(show_denominator, unk_0x115, UpdateDisplay())
    SYNC_PROP_SET(alignment, unk_0x120, SetAlignment((RndText::Alignment)_val.Int(NULL)))
    SYNC_PROP_MODIFY(icon_override, unk_0x124, UpdateDisplay())
    SYNC_PROP_MODIFY(empty_icon_override, unk_0x128, UpdateDisplay())
    SYNC_PROP_SET(float_stars, (float)mStars, SetValues(_val.Float(NULL), unk_0x11C))
    SYNC_PROP_SET(float_total_stars, (float)unk_0x11C, SetValues(mStars, _val.Float(NULL)))
    SYNC_SUPERCLASS(UIComponent)
END_PROPSYNCS
