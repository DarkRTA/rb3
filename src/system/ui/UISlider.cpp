#include "ui/UISlider.h"
#include "ui/UI.h"
#include "ui/UIPanel.h"
#include "ui/Utl.h"
#include "os/Joypad.h"
#include "ui/UIMessages.h"
#include "utl/Symbols.h"
#include "decomp.h"

INIT_REVS(UISlider)

UISlider::UISlider() : mCurrent(0), mNumSteps(10), mVertical(0) {

}

void UISlider::Init(){
    TheUI->InitResources("UISlider");
    REGISTER_OBJ_FACTORY(UISlider);
}

BEGIN_COPYS(UISlider)
    CREATE_COPY_AS(UISlider, s)
    MILO_ASSERT(s, 0x2B);
    UIComponent::Copy(s, ty);
    COPY_MEMBER_FROM(s, unk_0x4)
END_COPYS

SAVE_OBJ(UISlider, 0x36)

BEGIN_LOADS(UISlider)
    PreLoad(bs);
    PostLoad(bs);
END_LOADS

void UISlider::PreLoad(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(1, 0);
    UIComponent::PreLoad(bs);
}

void UISlider::PostLoad(BinStream& bs){
    UIComponent::PostLoad(bs);
    if(gRev != 0){
        bs >> unk_0x4;
    }
    Update();
}

void UISlider::Enter(){
    UIComponent::Enter();
    Reset();
}

void UISlider::DrawShowing(){
    SyncSlider();
    UpdateMeshes(DrawState(this));
    RndDir* dir = mResource->Dir();
    dir->DrawShowing();
}

// fn_80578C5C
RndDrawable* UISlider::CollideShowing(const Segment& seg, float& f, Plane& pl){
    SyncSlider();
    RndDir* dir = mResource->Dir();
    return dir->CollideShowing(seg, f, pl) ? this : nullptr;
}

int UISlider::CollidePlane(const Plane& pl){
    SyncSlider();
    RndDir* dir = mResource->Dir();
    return dir->CollidePlane(pl);
}

int UISlider::Current() const { return mCurrent; }

float UISlider::Frame() const {
    if(mNumSteps == 1) return 0.0f;
    else return (float)(mCurrent) / (float)(mNumSteps - 1);
}

void UISlider::SetCurrent(int i){
    if(i < 0 || i >= mNumSteps){
        MILO_FAIL("Can't set slider to %i (%i steps)", i, mNumSteps);
    }
    else mCurrent = i;
}

void UISlider::SetNumSteps(int i){
    if(i < 1) MILO_FAIL("Can't set num steps to %i (must be >= 1)", i);
    else mNumSteps = i;
}

void UISlider::Update(){
    UIComponent::Update();
    TypeDef()->FindData("vertical", mVertical, false);
}

void UISlider::SyncSlider(){
    mResource->Dir()->SetFrame(Frame(), 1.0f);
    mResource->Dir()->SetWorldXfm(WorldXfm());
}

void UISlider::SetFrame(float frame){
    MILO_ASSERT(frame >= 0 && frame <= 1.0f, 0xAE);
    mCurrent = frame * (mNumSteps - 1) + 0.5f;
}

int UISlider::SelectedAux() const { return mCurrent; }
void UISlider::SetSelectedAux(int i){
    SetCurrent(i);
}

BEGIN_HANDLERS(UISlider)
    HANDLE_MESSAGE(ButtonDownMsg)
    HANDLE_EXPR(current, mCurrent)
    HANDLE_EXPR(num_steps, mNumSteps)
    HANDLE_EXPR(frame, Frame())
    HANDLE_ACTION(set_num_steps, SetNumSteps(_msg->Int(2)))
    HANDLE_ACTION(set_current, SetCurrent(_msg->Int(2)))
    HANDLE_ACTION(set_frame, SetFrame(_msg->Float(2)))
    HANDLE_ACTION(store, Store())
    HANDLE_ACTION(undo, RevertScrollSelect(this, _msg->Obj<LocalUser>(2), 0))
    HANDLE_ACTION(undo_handled_by, RevertScrollSelect(this, _msg->Obj<LocalUser>(2), _msg->Obj<UIPanel>(3)))
    HANDLE_ACTION(confirm, Reset())
    HANDLE_SUPERCLASS(ScrollSelect)
    HANDLE_SUPERCLASS(UIComponent)
    HANDLE_CHECK(0xDA)
END_HANDLERS

DataNode UISlider::OnMsg(const ButtonDownMsg& msg){
    Symbol cnttype = JoypadControllerTypePadNum(UNCONST_ARRAY(msg)->Int(5));
    if(CanScroll()){
        JoypadAction act = ScrollDirection(msg, cnttype, mVertical, 1);
        if(act != kAction_None){
            if(mVertical) act = (JoypadAction)-act;
            int step = mCurrent + act;
            if(step >= 0 && step < mNumSteps){
                SetCurrent(step);
                UIComponentScrollMsg scroll_msg(this, msg.GetUser());
                TheUI->Handle(scroll_msg, 0);
            }
            return DataNode(1);
        }
        if(CatchNavAction(msg.GetAction())){
            return DataNode(1);
        }
    }
    JoypadAction thisAct = msg.GetAction();
    LocalUser* user = msg.GetUser();
    if(thisAct == kAction_Confirm && SelectScrollSelect(this, user)){
        return DataNode(1);
    }
    else if(thisAct == kAction_Cancel && RevertScrollSelect(this, user, 0)){
        return DataNode(1);
    }
    return DataNode(kDataUnhandled, 0);
}

BEGIN_PROPSYNCS(UISlider)
    SYNC_SUPERCLASS(ScrollSelect)
    SYNC_SUPERCLASS(UIComponent)
END_PROPSYNCS

DECOMP_FORCEFUNC(UISlider, UISlider, SetType)