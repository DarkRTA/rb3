#include "bandobj/DialogDisplay.h"
#include "ui/UI.h"
#include "utl/Symbols.h"

INIT_REVS(DialogDisplay);

void DialogDisplay::Init(){
    Register();
    TheUI->InitResources("DialogDisplay");
}

DialogDisplay::DialogDisplay() : mDialogLabel(this, 0), mTopBone(this, 0), mBottomBone(this, 0) {

}

DialogDisplay::~DialogDisplay(){
    
}

BEGIN_COPYS(DialogDisplay)
    COPY_SUPERCLASS(Hmx::Object)
    CREATE_COPY_AS(DialogDisplay, pDisplay)
    MILO_ASSERT(pDisplay, 0x2D);
    COPY_MEMBER_FROM(pDisplay, mDialogLabel)
    COPY_MEMBER_FROM(pDisplay, mTopBone)
    COPY_MEMBER_FROM(pDisplay, mBottomBone)
END_COPYS

SAVE_OBJ(DialogDisplay, 0x3B)

BEGIN_LOADS(DialogDisplay)
    LOAD_REVS(bs)
    ASSERT_REVS(0, 0)
    bs >> mDialogLabel;
    bs >> mTopBone;
    bs >> mBottomBone;
    LOAD_SUPERCLASS(Hmx::Object)
END_LOADS

float DialogDisplay::GetLabelHeight(){
    float height = 0;
    if(mDialogLabel) height = mDialogLabel->GetDrawHeight();
    return height;
}

void DialogDisplay::Poll(){
    if(mTopBone && mBottomBone && mDialogLabel){
        Vector3 pos = mTopBone->LocalXfm().v;
        pos.z -= GetLabelHeight();
        mBottomBone->SetLocalPos(pos);
    }
}

void DialogDisplay::SetLabel(UILabel* lbl){ mDialogLabel = lbl; }
void DialogDisplay::SetTopBone(RndMesh* mesh){ mTopBone = mesh; }
void DialogDisplay::SetBottomBone(RndMesh* mesh){ mBottomBone = mesh; }

BEGIN_HANDLERS(DialogDisplay)
    HANDLE_SUPERCLASS(RndPollable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x8C)
END_HANDLERS

BEGIN_PROPSYNCS(DialogDisplay)
    SYNC_PROP_SET(dialog_label, GetLabel(), SetLabel(_val.Obj<UILabel>(0)))
    SYNC_PROP_SET(top_bone, GetTopBone(), SetTopBone(_val.Obj<RndMesh>(0)))
    SYNC_PROP_SET(bottom_bone, GetBottomBone(), SetBottomBone(_val.Obj<RndMesh>(0)))
    SYNC_SUPERCLASS(RndPollable)
    SYNC_SUPERCLASS(Hmx::Object)
END_PROPSYNCS