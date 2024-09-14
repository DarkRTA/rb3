#include "bandobj/DialogDisplay.h"
#include "utl/Symbols.h"

DialogDisplay::DialogDisplay() : mDialogLabel(this, 0), mTopBone(this, 0), mBottomBone(this, 0) {

}

DialogDisplay::~DialogDisplay(){
    
}

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