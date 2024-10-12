#include "bandobj/InstrumentDifficultyDisplay.h"
#include "ui/UI.h"
#include "utl/Symbols.h"

INIT_REVS(InstrumentDifficultyDisplay);

void InstrumentDifficultyDisplay::Init(){
    Register();
    TheUI->InitResources("InstrumentDifficultyDisplay");
}

InstrumentDifficultyDisplay::InstrumentDifficultyDisplay() : mDifficultyAnim(0), mVocalPart1Mat(0), mVocalPart2Mat(0), mVocalPart3Mat(0), mInstrumentState(kName), mHasPart(1),
    mDifficulty(3), mNumVocalParts(0), mInstrumentType("band"), mInstrumentColorOverride(this, 0) {
    mInstrumentLabel = Hmx::Object::New<BandLabel>();
    mVocalPartMesh = Hmx::Object::New<RndMesh>();
}

InstrumentDifficultyDisplay::~InstrumentDifficultyDisplay(){
    delete mInstrumentLabel;
    delete mVocalPartMesh;
}

BEGIN_COPYS(InstrumentDifficultyDisplay)
    CREATE_COPY_AS(InstrumentDifficultyDisplay, p)
    MILO_ASSERT(p, 0x39);
    COPY_MEMBER_FROM(p, mDifficulty)
    COPY_MEMBER_FROM(p, mNumVocalParts)
    COPY_MEMBER_FROM(p, mInstrumentType)
    COPY_MEMBER_FROM(p, mHasPart)
    COPY_MEMBER_FROM(p, mInstrumentState)
    COPY_MEMBER_FROM(p, mInstrumentColorOverride)
    UIComponent::Copy(p, ty);
END_COPYS

SAVE_OBJ(InstrumentDifficultyDisplay, 0x4E)

BEGIN_LOADS(InstrumentDifficultyDisplay)
    PreLoad(bs);
    PostLoad(bs);
END_LOADS

void InstrumentDifficultyDisplay::PreLoad(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(4, 0);
    bs >> mInstrumentType >> mDifficulty >> mHasPart;
    if(gRev >= 1) bs >> mInstrumentColorOverride;
    if(gRev >= 2) bs >> mNumVocalParts;
    if(gRev == 3){
        bool b; bs >> b;
        mInstrumentState = (InstrumentState)b;
    }
    if(gRev >= 4){
        int i; bs >> i;
        mInstrumentState = (InstrumentState)i;
    }
    UIComponent::PreLoad(bs);
}

DECOMP_FORCEACTIVE(InstrumentDifficultyDisplay, "false")

void InstrumentDifficultyDisplay::PostLoad(BinStream& bs){
    UIComponent::PostLoad(bs);
    Update();
}

void InstrumentDifficultyDisplay::UpdateDisplay(){
    mVocalPartMesh->SetShowing(false);
    if(mInstrumentState == kName){
        mInstrumentLabel->SetColorOverride(mInstrumentColorOverride);
        if(mInstrumentLabel->TextToken() != mInstrumentType){
            mInstrumentLabel->SetTextToken(mInstrumentType);
        }
    }
    else if(mInstrumentState == kIcon){
        Message msg(get_inst_icon);
        DataNode handled = HandleType(msg);
        if(handled.Type() == kDataString){
            mInstrumentLabel->SetIcon(*handled.Str());
        }
        else MILO_WARN("InstrumentDifficultyDisplay::UpdateDisplay missing icon inst");
    }
    mInstrumentLabel->SetShowing(true);
}

void InstrumentDifficultyDisplay::DrawShowing(){
    RndDir* dir = mResource->Dir();
    MILO_ASSERT(dir, 0xBB);
    RndPropAnim* anim = mDifficultyAnim;
    anim->SetFrame(mHasPart ? mDifficulty : 7.0f, 1.0f);
    if(mInstrumentState != kHidden){
        mInstrumentLabel->SetTransParent(this, false);
        mInstrumentLabel->Draw();
    }
    SetWorldXfm(WorldXfm());
    dir->SetWorldXfm(WorldXfm());
    dir->Draw();
    mVocalPartMesh->SetTransParent(this, false);
    mVocalPartMesh->Draw();
}

DECOMP_FORCEACTIVE(InstrumentDifficultyDisplay, "set_song")

void InstrumentDifficultyDisplay::SetValues(Symbol s, int i1, int i2, bool b){
    mInstrumentType = s;
    mDifficulty = i1;
    mNumVocalParts = i2;
    mHasPart = b;
    UpdateDisplay();
}

void InstrumentDifficultyDisplay::SetInstrumentState(InstrumentState state){
    mInstrumentState = state;
    UpdateDisplay();
}

void InstrumentDifficultyDisplay::Update(){
    UIComponent::Update();
    const DataArray* typeDef = TypeDef();
    MILO_ASSERT(typeDef, 0xEF);
    RndDir* dir = mResource->Dir();
    MILO_ASSERT(dir, 0xF2);
    mDifficultyAnim = dir->Find<RndPropAnim>(typeDef->FindStr(difficulty_anim), true);
    mVocalPart1Mat = dir->Find<RndMat>(typeDef->FindStr(vocal_part1_mat), true);
    mVocalPart2Mat = dir->Find<RndMat>(typeDef->FindStr(vocal_part2_mat), true);
    mVocalPart3Mat = dir->Find<RndMat>(typeDef->FindStr(vocal_part3_mat), true);
    RndMesh* vocalpartmesh = dir->Find<RndMesh>(typeDef->FindStr(vocal_part_mesh), true);
    mVocalPartMesh->Copy(vocalpartmesh, kCopyShallow);
    vocalpartmesh->SetShowing(false);
    BandLabel* instrLabel = dir->Find<BandLabel>(typeDef->FindStr(instrument_label), true);
    BandLabel* instrIcon = dir->Find<BandLabel>(typeDef->FindStr(instrument_icon), true);
    if(mInstrumentState == kName){
        mInstrumentLabel->ResourceCopy(instrLabel);
    }
    else if(mInstrumentState == kIcon){
        mInstrumentLabel->ResourceCopy(instrIcon);
    }
    instrLabel->SetShowing(false);
    instrIcon->SetShowing(false);
    UpdateDisplay();
}

BEGIN_HANDLERS(InstrumentDifficultyDisplay)
    HANDLE_ACTION(set_values, SetValues(_msg->Sym(2), _msg->Int(3), _msg->Int(4), _msg->Int(5)))
    HANDLE_SUPERCLASS(UIComponent)
    HANDLE_CHECK(0x11B)
END_HANDLERS

BEGIN_PROPSYNCS(InstrumentDifficultyDisplay)
    SYNC_PROP_MODIFY(difficulty, mDifficulty, UpdateDisplay())
    SYNC_PROP_MODIFY(instrument_type, mInstrumentType, UpdateDisplay())
    SYNC_PROP_MODIFY(num_vocal_parts, mNumVocalParts, UpdateDisplay())
    SYNC_PROP_MODIFY(has_part, mHasPart, UpdateDisplay())
    SYNC_PROP_SET(instrument_state, mInstrumentState, SetInstrumentState((InstrumentState)_val.Int()))
    SYNC_PROP(instrument_color_override, mInstrumentColorOverride)
    SYNC_SUPERCLASS(UIComponent)
END_PROPSYNCS
