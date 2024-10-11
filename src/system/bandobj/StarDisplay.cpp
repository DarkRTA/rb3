#include "StarDisplay.h"
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "os/Debug.h"
#include "rndobj/Text.h"
#include "ui/UI.h"
#include "ui/UIComponent.h"
#include "utl/Symbols.h"

INIT_REVS(StarDisplay)

void StarDisplay::Init() {
    Register();
    TheUI->InitResources("StarDisplay");
}

StarDisplay::StarDisplay() : mForceMixedMode(0), mShowDenominator(1), mShowEmptyStars(0), mStars(5), mTotalStars(5),
    mAlignment(RndText::kMiddleLeft), mIconOverride(gNullStr), mEmptyIconOverride(gNullStr) {
        mRsrcStarsLabel = New<BandLabel>();
        mRsrcStarsMixedLabel = New<BandLabel>();
    }
StarDisplay::~StarDisplay() {
    delete mRsrcStarsLabel;
    delete mRsrcStarsMixedLabel;
}

BEGIN_COPYS(StarDisplay)
    UIComponent::Copy(o,ty);
END_COPYS

void StarDisplay::CopyMembers(const UIComponent* ui, Hmx::Object::CopyType ct) {
    UIComponent::CopyMembers(ui, ct);
    const StarDisplay* starDisplay = dynamic_cast<const StarDisplay*>(ui);
    MILO_ASSERT(starDisplay, 62);
    mStars = starDisplay->mStars;
    mTotalStars = starDisplay->mTotalStars;
    mForceMixedMode = starDisplay->mForceMixedMode;
    mShowDenominator = starDisplay->mShowDenominator;
    mShowEmptyStars = starDisplay->mShowEmptyStars;
    mAlignment = starDisplay->mAlignment;
    mIconOverride = starDisplay->mIconOverride;
    mEmptyIconOverride = starDisplay->mEmptyIconOverride;
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
    bs >> mTotalStars;
    bs >> mForceMixedMode;
    if (gRev >= 3) {
        bs >> mShowDenominator;
        bs >> mShowEmptyStars;
        if (gRev < 5) {
            int x = 0; bs >> x;
        }
    }
    if (gRev >= 4) bs >> (int&)mAlignment;
    if (gRev == 5) {
        String s;
        bs >> s;
        bs >> s;
    }
    if (gRev >= 6) {
        bs >> mIconOverride;
        bs >> mEmptyIconOverride;
    }
    UIComponent::PreLoad(bs);
}

void StarDisplay::PostLoad(BinStream& bs) {
    UIComponent::PostLoad(bs);
    Update();
}

void StarDisplay::Enter() { UIComponent::Enter(); UpdateDisplay(); }

Symbol StarDisplay::GetSymbolForStarCount(int i) {
    switch(i){
        case 0: return stars_0;
        case 1: return stars_1;
        case 2: return stars_2;
        case 3: return stars_3;
        case 4: return stars_4;
        case 5: return stars_5;
        case 6: return stars_6;
        default:
            MILO_FAIL("Number of stars is unsupported: stars = %i", i);
            return gNullStr;
    }
}

int StarDisplay::GetStarCountForSymbol(Symbol s) {
    for(int i = 0; i <= 6; i++){
        if(GetSymbolForStarCount(i) == s) return i;
    }
    MILO_FAIL("can't set star display to token %s", s.Str());
    return 0;
}

// this gets inlined, but "*" has to be part of the stringbase - fix this
inline bool StarDisplay::HasStarIcon() const {
    return mIconOverride != gNullStr && strcmp(mIconOverride.Str(), "*") != 0;
}

char StarDisplay::GetStarIcon() const {
    char ret = '*';
    bool hasstaricon = mIconOverride != gNullStr && strcmp(mIconOverride.Str(), "*") != 0;
    if(hasstaricon){
        String str(mIconOverride);
        if(!str.empty()){
            ret = str[0];
        }
    }
    return ret;
}

// fn_8041DE94
char StarDisplay::GetEmptyStarIcon() const {
    char ret = 'p';
    if(mEmptyIconOverride != gNullStr && strcmp(mEmptyIconOverride.mStr, "p") != 0){
        String str(mEmptyIconOverride);
        if(!str.empty()){
            ret = str[0];
        }
    }
    return ret;
}

// fn_8041DF40
void StarDisplay::UpdateDisplay(){
    bool show = !mForceMixedMode ? mTotalStars : true;
    mRsrcStarsMixedLabel->SetShowing(show);
    mRsrcStarsLabel->SetShowing(!show);
    if(show){
        char icon = GetStarIcon();
        String str("");
        str += icon;
        if(mShowDenominator){
            mRsrcStarsMixedLabel->SetTokenFmt(tour_stars_fraction_fmt, mStars, mTotalStars, str);
        }
        else {
            mRsrcStarsMixedLabel->SetTokenFmt(tour_stars_simple_fmt, mStars, str);
        }
    }
    else {
        mRsrcStarsLabel->SetTextToken(gNullStr);
        for(int i = 0; i < mTotalStars; i++){
            char icon;
            if(mStars == 6 && !HasStarIcon()) icon = '=';
            else if(i < mStars) icon = GetStarIcon();
            else if(mShowEmptyStars) icon = GetEmptyStarIcon();
            else continue;
            mRsrcStarsLabel->AppendIcon(icon);
        }
    }
    mRsrcStarsLabel->SetAlignment(mAlignment);
    mRsrcStarsMixedLabel->SetAlignment(mAlignment);
}

void StarDisplay::DrawShowing() {
    RndDir* dir = mResource->Dir();
    MILO_ASSERT(dir, 312);
    mRsrcStarsLabel->SetTransParent(this, false);
    mRsrcStarsLabel->Draw();
    mRsrcStarsMixedLabel->SetTransParent(this, false);
    mRsrcStarsMixedLabel->Draw();
    SetWorldXfm(WorldXfm());
}

void StarDisplay::SetValues(int st, int max) { mStars = st; mTotalStars = max; UpdateDisplay(); }
void StarDisplay::SetToToken(Symbol s) { mStars = GetStarCountForSymbol(s); UpdateDisplay(); }
void StarDisplay::SetAlignment(RndText::Alignment a) { mAlignment = a; UpdateDisplay(); }
void StarDisplay::SetForceMixedMode(bool b) { mForceMixedMode = b; UpdateDisplay(); }
void StarDisplay::SetShowDenominator(bool b) { mShowDenominator = b; UpdateDisplay(); }

void StarDisplay::Update() {
    UIComponent::Update();
    const DataArray* typeDef = TypeDef();
    MILO_ASSERT(typeDef, 369);
    RndDir* dir = mResource->Dir();
    MILO_ASSERT(dir, 372);
    mRsrcStarsLabel->ResourceCopy(dir->Find<BandLabel>(typeDef->FindStr(resource_stars_label), true));
    BandLabel* bl2 = dir->Find<BandLabel>(typeDef->FindStr(resource_stars_mixed_label), true);
    mRsrcStarsMixedLabel->ResourceCopy(bl2);
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
    SYNC_PROP_MODIFY(total_stars, mTotalStars, UpdateDisplay())
    SYNC_PROP_MODIFY(force_mixed_mode, mForceMixedMode, UpdateDisplay())
    SYNC_PROP_MODIFY(show_empty_stars, mShowEmptyStars, UpdateDisplay())
    SYNC_PROP_MODIFY(show_denominator, mShowDenominator, UpdateDisplay())
    SYNC_PROP_SET(alignment, mAlignment, SetAlignment((RndText::Alignment)_val.Int()))
    SYNC_PROP_MODIFY(icon_override, mIconOverride, UpdateDisplay())
    SYNC_PROP_MODIFY(empty_icon_override, mEmptyIconOverride, UpdateDisplay())
    SYNC_PROP_SET(float_stars, (float)mStars, SetValues(_val.Float(), mTotalStars))
    SYNC_PROP_SET(float_total_stars, (float)mTotalStars, SetValues(mStars, _val.Float()))
    SYNC_SUPERCLASS(UIComponent)
END_PROPSYNCS
