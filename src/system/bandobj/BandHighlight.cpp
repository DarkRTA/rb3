#include "bandobj/BandHighlight.h"
#include "ui/UI.h"
#include "utl/Symbols.h"

INIT_REVS(BandHighlight);

void BandHighlight::Init(){
    TheUI->InitResources("BandHighlight");
    Register();
}

BandHighlight::BandHighlight() : unk148(0), unk154(0), unk158(0) {

}

BandHighlight::~BandHighlight(){
    
}

BEGIN_COPYS(BandHighlight)
    CREATE_COPY_AS(BandHighlight, s)
    MILO_ASSERT(s, 0x29);
    COPY_SUPERCLASS_FROM(UIComponent, s)
END_COPYS

SAVE_OBJ(BandHighlight, 0x32)

BEGIN_LOADS(BandHighlight)
    PreLoad(bs);
    PostLoad(bs);
END_LOADS

void BandHighlight::PreLoad(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(0, 0);
    UIComponent::PreLoad(bs);
}

void BandHighlight::PostLoad(BinStream& bs){
    UIComponent::PostLoad(bs);
    Update();
}

void BandHighlight::Enter(){
    OnRegisterFocus();
    UIComponent::Enter();
}

void BandHighlight::Exit(){
    OnUnregisterFocus();
    UIComponent::Exit();
}

void BandHighlight::Poll(){
    UIComponent::Poll();
    SetState(kDisabled);
    UIScreen* curscreen = TheUI->CurrentScreen();
    if(curscreen){
        UIPanel* focuspanel = curscreen->FocusPanel();
        if(focuspanel){
            if(focuspanel->GetPanelDir() == Dir()){
                SetState(kNormal);
            }
        }
    }
    float loc28;
    if(mAnimDuration != 0) loc28 = (TheTaskMgr.UISeconds() - unk124) / mAnimDuration;
    else loc28 = 1.0f;
    ClampEq(loc28, 0.0f, 1.0f);
    Vector3 v24;
    Interp(unk10c, unk118, loc28, v24);
    SetLocalPos(v24);
    if(unk148){
        if(unk13c.x == 0){
            UpdateTargetEdge(TransParent());
        }
        if(unk13c.x != 0){
            Interp(unk130, unk13c, loc28, v24);
            unk148->SetLocalPos(v24);
        }
    }
}

void BandHighlight::DrawShowing(){
    SyncDir();
    mHelpTextLabel->SetShowing(GetState() != kDisabled);
    UpdateMeshes(GetState());
    mResource->Dir()->DrawShowing();
}

RndDrawable* BandHighlight::CollideShowing(const Segment& s, float& f, Plane& pl){
    SyncDir();
    RndDrawable* showing = mResource->Dir()->CollideShowing(s, f, pl);
    return showing ? showing : 0;
}

int BandHighlight::CollidePlane(const Plane& pl){
    SyncDir();
    return mResource->Dir()->CollidePlane(pl);
}

void BandHighlight::Update(){
    UIComponent::Update();
    TypeDef()->FindData("anim_duration", mAnimDuration, true);
    mHelpTextLabel = mResource->Dir()->Find<BandLabel>("helptext.lbl", true);
    DataArray* textarr = TypeDef()->FindArray("text_edge", false);
    if(textarr){
        unk148 = mResource->Dir()->Find<RndTransformable>(textarr->Str(1), true);
        unk13c = unk130 = unk148->mLocalXfm.v;
    }
    DataArray* matarr = TypeDef()->FindArray("mirror_mats", false);
    if(matarr){
        for(int i = 1; i < matarr->Size(); i++){
            mMirrorMats.push_back(mResource->Dir()->Find<RndMat>(matarr->Str(i), true));
        }
    }
}

void BandHighlight::SetTarget(UIComponent* c, bool b){
    if(unk154){
        bool good = false;
        for(UIComponent* it = unk154; it != 0; it = it->NavDown()){
            if(it == c) good = true;
        }
        if(!good) return;
    }
    if(c == this) c = 0;
    SetTransParent(c, true);
    unk124 = TheTaskMgr.UISeconds();
    unk10c = mLocalXfm.v;
    Vector3 v28(0,0,0);
    unk118 = c ? v28 : unk10c;
    if(b) unk10c = unk118;
    if(unk148) UpdateTargetEdge(c);
}

void BandHighlight::UpdateTargetEdge(RndTransformable* t){
    if(unk148){
        UILabel* lbl = dynamic_cast<UILabel*>(t);
        if(lbl){
            RndText* txt = lbl->TextObj();
            float f4;
            if(txt){
                f4 = txt->GetStringWidthUTF8(txt->unk_cc.c_str(), 0, false, 0);
            }
            else f4 = 0;
            unk13c = unk130 = unk148->mLocalXfm.v;
            unk13c.x = f4;
        }
    }
}

void BandHighlight::SyncDir(){
    mResource->Dir()->SetWorldXfm(WorldXfm());
}

DataNode BandHighlight::OnMsg(const UIComponentFocusChangeMsg& msg){
    // TODO: the getting of UIComponent at 2 needs to be inlined
    // I just currently don't know what that UIComponent is supposed to represent
    SetTarget(msg->Obj<UIComponent>(2), false);
    return DataNode(kDataUnhandled, 0);
}

void BandHighlight::OnRegisterFocus(){
    unk158++;
    if(unk158 == 1){
        UIComponent* target = 0;
        PanelDir* pdir = dynamic_cast<PanelDir*>(Dir());
        if(pdir){
            pdir->AddSink(this, "component_focus");
            target = pdir->FocusComponent();
        }
        SetTarget(target, true);
    }
}

void BandHighlight::OnUnregisterFocus(){
    if(unk158){
        unk158--;
        if(unk158 == 0){
            MsgSource* pdir = dynamic_cast<PanelDir*>(Dir());
            if(pdir) pdir->RemoveSink(this);
        }
    }
}

BEGIN_HANDLERS(BandHighlight)
    HANDLE_MESSAGE(UIComponentFocusChangeMsg)
    HANDLE_ACTION(register_focus, OnRegisterFocus())
    HANDLE_ACTION(unregister_focus, OnUnregisterFocus())
    HANDLE_SUPERCLASS(UIComponent)
    HANDLE_CHECK(0x12B)
END_HANDLERS

BEGIN_PROPSYNCS(BandHighlight)
    SYNC_SUPERCLASS(UIComponent)
END_PROPSYNCS