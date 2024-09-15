#include "bandobj/ReviewDisplay.h"
#include "ui/UI.h"
#include "utl/Symbols.h"

INIT_REVS(ReviewDisplay);

void ReviewDisplay::Init(){
    Register();
    TheUI->InitResources("ReviewDisplay");
}

ReviewDisplay::ReviewDisplay() : mReviewAnim(0), mFocusAnim(0), mScore(0) {

}

ReviewDisplay::~ReviewDisplay(){
    
}

BEGIN_COPYS(ReviewDisplay)
    COPY_SUPERCLASS(UIComponent)
END_COPYS

void ReviewDisplay::CopyMembers(const UIComponent* o, Hmx::Object::CopyType ty){
    UIComponent::CopyMembers(o, ty);
    CREATE_COPY_AS(ReviewDisplay, p);
    MILO_ASSERT(p, 0x35);
    COPY_MEMBER_FROM(p, mScore);
}

SAVE_OBJ(ReviewDisplay, 0x40);

BEGIN_LOADS(ReviewDisplay)
    PreLoad(bs);
    PostLoad(bs);
END_LOADS

void ReviewDisplay::PreLoad(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(0, 0);
    bs >> mScore;
    UIComponent::PreLoad(bs);
}

void ReviewDisplay::PostLoad(BinStream& bs){
    UIComponent::PostLoad(bs);
    Update();
}

void ReviewDisplay::Enter(){
    UIComponent::Enter();
    UpdateDisplay(false);
}

void ReviewDisplay::Poll(){
    UIComponent::Poll();
    MILO_ASSERT(mResource, 99);
    if(mResource->Dir()){
        mResource->Dir()->Poll();
    }
}

void ReviewDisplay::UpdateDisplay(bool){}

void ReviewDisplay::DrawShowing(){
    RndDir* dir = mResource->Dir();
    MILO_ASSERT(dir, 0x79);
    mReviewAnim->SetFrame(mScore * 10.0f, 1.0f);
    RndAnimatable* focus = mFocusAnim;
    focus->SetFrame(GetState() == kFocused ? 1.0f : 0.0f, 1.0f);
    dir->SetWorldXfm(WorldXfm());
    dir->DrawShowing();
}

void ReviewDisplay::SetValues(int score, bool b){
    mScore = score;
    UpdateDisplay(b);
}

void ReviewDisplay::SetToToken(Symbol s){
    mScore = GetReviewScoreForSymbol(s);
    UpdateDisplay(false);
}

void ReviewDisplay::Update(){
    UIComponent::Update();
    const DataArray* typeDef = TypeDef();
    MILO_ASSERT(typeDef, 0x9E);
    RndDir* dir = mResource->Dir();
    MILO_ASSERT(dir, 0xA1);
    mReviewAnim = dir->Find<RndAnimatable>(typeDef->FindStr(review_anim), true);
    mFocusAnim = dir->Find<RndAnimatable>(typeDef->FindStr(focus_anim), true);
}

Symbol ReviewDisplay::GetSymbolForReviewScore(int score){
    switch(score){
        case 0: return unreviewed;
        case 1: return review_1;
        case 2: return review_2;
        case 3: return review_3;
        case 4: return review_4;
        case 5: return review_5;
        default:
            MILO_FAIL("Review is unsupported: review = %i", score);
            return gNullStr;
    }
}

int ReviewDisplay::GetReviewScoreForSymbol(Symbol s){
    for(int i = 0; i <= 5; i++){
        if(GetSymbolForReviewScore(i) == s) return i;
    }
    MILO_FAIL("can't set review display to token %s", s.Str());
    return 0;
}

BEGIN_HANDLERS(ReviewDisplay)
    HANDLE_ACTION(set_values, SetValues(_msg->Int(2), _msg->Int(3)))
    HANDLE_SUPERCLASS(UIComponent)
    HANDLE_CHECK(0xE0)
END_HANDLERS

BEGIN_PROPSYNCS(ReviewDisplay)
    SYNC_PROP_MODIFY(score, mScore, UpdateDisplay(true))
    SYNC_SUPERCLASS(UIComponent)
END_PROPSYNCS