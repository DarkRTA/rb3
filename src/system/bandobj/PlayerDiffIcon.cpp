#include "bandobj/PlayerDiffIcon.h"
#include "ui/UI.h"
#include "utl/Symbols.h"

INIT_REVS(PlayerDiffIcon)

void PlayerDiffIcon::Init(){
    Register();
    TheUI->InitResources("PlayerDiffIcon");
}

PlayerDiffIcon::PlayerDiffIcon() : mPlayerMat(0), mNoPlayerMat(0), mNumPlayers(1), mDiff(0), mAlpha(1.0f) {

}

PlayerDiffIcon::~PlayerDiffIcon(){
    
}

BEGIN_COPYS(PlayerDiffIcon)
    CREATE_COPY_AS(PlayerDiffIcon, p)
    MILO_ASSERT(p, 0x2C);
    COPY_MEMBER_FROM(p, mNumPlayers)
    COPY_MEMBER_FROM(p, mDiff)
    COPY_SUPERCLASS_FROM(UIComponent, p)
END_COPYS

SAVE_OBJ(PlayerDiffIcon, 0x36)

BEGIN_LOADS(PlayerDiffIcon)
    PreLoad(bs);
    PostLoad(bs);
END_LOADS

void PlayerDiffIcon::PreLoad(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(0, 0);
    bs >> mNumPlayers;
    bs >> mDiff;
    UIComponent::PreLoad(bs);
}

void PlayerDiffIcon::PostLoad(BinStream& bs){
    UIComponent::PostLoad(bs);
    Update();
}

void PlayerDiffIcon::DrawShowing(){
    RndDir* d = mResource->Dir();
    MILO_ASSERT(d, 0x53);
    for(int i = 0; i < mPlayerMeshes.size(); i++){
        mPlayerMeshes[i]->SetMat(i < mNumPlayers ? mPlayerMat : mNoPlayerMat);
    }
    for(int i = 0; i < mDiffLabels.size(); i++){
        mDiffLabels[i]->SetShowing(mDiff == i);
    }
    for(ObjDirItr<UILabel> it(d, true); it != 0; ++it){
        it->SetAlpha(mAlpha);
        RndFont* font = it->TextObj()->GetFont();
        if(font){
            RndMat* mat = font->GetMat();
            if(mat) mat->SetColor(mColor);
        }
    }
    for(ObjDirItr<RndMat> it(d, true); it != 0; ++it){
        it->SetAlpha(mAlpha);
    }
    d->SetWorldXfm(WorldXfm());
    d->Draw();
}

RndDrawable* PlayerDiffIcon::CollideShowing(const Segment& s, float& f, Plane& p){
    return mResource->Dir()->Collide(s, f, p);
}

int PlayerDiffIcon::CollidePlane(const Plane& p){
    return mResource->Dir()->CollidePlane(p);
}

void PlayerDiffIcon::SetAlphaColor(float a, UIColor* c){
    mAlpha = a;
    if(c) mColor = c->GetColor();
}

void PlayerDiffIcon::GrowBoundingBox(Box&) const {}

void PlayerDiffIcon::SetNumPlayersDiff(int i, int j){
    mNumPlayers = i;
    mDiff = j;
}

void PlayerDiffIcon::Update(){
    UIComponent::Update();
    const DataArray* t = TypeDef();
    MILO_ASSERT(t, 0x9A);
    RndDir* dir = mResource->Dir();
    MILO_ASSERT(dir, 0x9D);
    mPlayerMeshes.clear();
    DataArray* arr = t->FindArray(player_meshes, true);
    for(int i = 1; i < arr->Size(); i++){
        mPlayerMeshes.push_back(dir->Find<RndMesh>(arr->Str(i), true));
    }
    mPlayerMat = dir->Find<RndMat>(t->FindStr(player_mat), true);
    mNoPlayerMat = dir->Find<RndMat>(t->FindStr(no_player_mat), true);
    mDiffLabels.clear();
    DataArray* arr2 = t->FindArray(diff_labels, true);
    for(int i = 1; i < arr2->Size(); i++){
        mDiffLabels.push_back(dir->Find<BandLabel>(arr2->Str(i), true));
    }
}

BEGIN_HANDLERS(PlayerDiffIcon)
    HANDLE_ACTION(set_num_players_diff, SetNumPlayersDiff(_msg->Int(2), _msg->Int(3)))
    HANDLE_SUPERCLASS(UIComponent)
    HANDLE_CHECK(0xBD)
END_HANDLERS

BEGIN_PROPSYNCS(PlayerDiffIcon)
    SYNC_PROP(num_players, mNumPlayers)
    SYNC_PROP(diff, mDiff)
    SYNC_SUPERCLASS(UIComponent)
END_PROPSYNCS