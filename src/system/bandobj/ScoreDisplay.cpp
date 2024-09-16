#include "bandobj/ScoreDisplay.h"
#include "ui/UI.h"
#include "utl/Locale.h"
#include "utl/LocaleOrdinal.h"
#include "utl/Symbols.h"

INIT_REVS(ScoreDisplay)

void ScoreDisplay::Init(){
    Register();
    TheUI->InitResources("ScoreDisplay");
}

ScoreDisplay::ScoreDisplay() : unk114(0), mScore(1000000), mRank(0), mGlobally(0), mTextColor(this, 0) {
    mCombinedLabel = Hmx::Object::New<BandLabel>();
}

ScoreDisplay::~ScoreDisplay(){
    delete mCombinedLabel;
}

BEGIN_COPYS(ScoreDisplay)
    COPY_SUPERCLASS(UIComponent)
    CREATE_COPY_AS(ScoreDisplay, p);
    MILO_ASSERT(p, 0x32);
END_COPYS

void ScoreDisplay::CopyMembers(const UIComponent* o, Hmx::Object::CopyType ty){
    UIComponent::CopyMembers(o, ty);
    CREATE_COPY_AS(ScoreDisplay, p);
    MILO_ASSERT(p, 0x3A);
    COPY_MEMBER_FROM(p, unk114)
    COPY_MEMBER_FROM(p, mScore)
    COPY_MEMBER_FROM(p, mRank)
    COPY_MEMBER_FROM(p, mGlobally)
    COPY_MEMBER_FROM(p, mTextColor)
}

SAVE_OBJ(ScoreDisplay, 0x4B)

BEGIN_LOADS(ScoreDisplay)
    PreLoad(bs);
    PostLoad(bs);
END_LOADS

void ScoreDisplay::PreLoad(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(2, 0);
    bs >> unk114;
    bs >> mScore;
    if(gRev != 0) bs >> mTextColor;
    if(gRev > 1){
        bs >> mRank;
        bs >> mGlobally;
    }
    UIComponent::PreLoad(bs);
}

void ScoreDisplay::PostLoad(BinStream& bs){
    UIComponent::PostLoad(bs);
    Update();
}

void ScoreDisplay::Enter(){
    UIComponent::Enter();
    UpdateDisplay();
}

void ScoreDisplay::SetAlphaColor(float f, UIColor* col){
    mCombinedLabel->mAlpha = f;
    SetColorOverride(col);
}

void ScoreDisplay::GrowBoundingBox(Box&) const {}

void ScoreDisplay::UpdateDisplay(){
    if(TheLoadMgr.EditMode()){
        if(mRank == 0){
            mCombinedLabel->SetEditText(MakeString("<alt>GBDV</alt> %s", LocalizeSeparatedInt(mScore)));
        }
        else {
            mCombinedLabel->SetEditText(MakeString("<alt>GBDV</alt> %s (%s %s)", LocalizeSeparatedInt(mScore),
                LocalizeOrdinal(mRank, LocaleGenderMasculine, LocaleSingular, true), Localize(mGlobally ? ir_among_all : ir_among_friends, 0)));
        }
    }
}

void ScoreDisplay::DrawShowing(){
    RndDir* dir = mResource->Dir();
    MILO_ASSERT(dir, 0x9B);
    mCombinedLabel->SetTransParent(this, false);
    mCombinedLabel->Draw();
    SetWorldXfm(WorldXfm());
}

DataNode ScoreDisplay::OnSetValues(const DataArray* da){
    if(da->Size() <= 4) SetValues(da->Int(2), da->Int(3), 0, false);
    else SetValues(da->Int(2), da->Int(3), da->Int(4), da->Int(5));
    return DataNode(1);
}

void ScoreDisplay::SetValues(short s, int i1, int i2, bool b){
    unk114 = s;
    mScore = i1;
    mRank = i2;
    mGlobally = b;
    UpdateDisplay();
}

void ScoreDisplay::SetColorOverride(UIColor* col){
    mTextColor = col;
    mCombinedLabel->SetColorOverride(mTextColor);
}

void ScoreDisplay::Update(){
    UIComponent::Update();
    const DataArray* typeDef = TypeDef();
    MILO_ASSERT(typeDef, 0xCA);
    RndDir* dir = mResource->Dir();
    MILO_ASSERT(dir, 0xCD);
    mCombinedLabel->ResourceCopy(dir->Find<BandLabel>(typeDef->FindStr(combined_label), true));
    mCombinedLabel->SetColorOverride(mTextColor);
}

BEGIN_HANDLERS(ScoreDisplay)
    HANDLE(set_values, OnSetValues)
    HANDLE_SUPERCLASS(UIComponent)
    HANDLE_CHECK(0xDA)
END_HANDLERS

BEGIN_PROPSYNCS(ScoreDisplay)
    SYNC_PROP_MODIFY(score, mScore, UpdateDisplay())
    SYNC_PROP_MODIFY(rank, mRank, UpdateDisplay())
    SYNC_PROP_MODIFY(globally, mGlobally, UpdateDisplay())
    SYNC_PROP_MODIFY_ALT(text_color, mTextColor, mCombinedLabel->SetColorOverride(mTextColor))
    SYNC_SUPERCLASS(UIComponent)
END_PROPSYNCS