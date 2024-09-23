#include "bandobj/BandLabel.h"
#include "ui/UI.h"
#include "utl/Symbols.h"

void BandLabel::Init(){
    TheUI->InitResources("BandLabel");
    Register();
}

BandLabel::BandLabel() : UITransitionHandler(this), unk1e8(""), unk1f4(0) {

}

BandLabel::~BandLabel(){
    
}

BEGIN_HANDLERS(BandLabel)
    HANDLE_ACTION(start_count, Count(_msg->Int(2), _msg->Int(3), _msg->Float(4), _msg->Sym(5)))
    HANDLE_ACTION(finish_count, FinishCount())
    HANDLE_SUPERCLASS(UILabel)
    HANDLE_CHECK(0x162)
END_HANDLERS

BEGIN_PROPSYNCS(BandLabel)
    SYNC_PROP_SET(in_anim, GetInAnim(), SetInAnim(_val.Obj<RndAnimatable>(0)))
    SYNC_PROP_SET(out_anim, GetOutAnim(), SetOutAnim(_val.Obj<RndAnimatable>(0)))
    SYNC_SUPERCLASS(UILabel)
END_PROPSYNCS