#include "bandobj/MicInputArrow.h"
#include "synth/MicManagerInterface.h"
#include "utl/Symbols.h"

MicClientID sNullMicClientID(-1, -1);

MicInputArrow::MicInputArrow() : mArrowNum(0), mMicManagerInterface(0), unk15c(1.0f), unk160(0) {
    for(int i = 0; i < 3; i++){
        unk114.push_back(-1);
        unk11c.push_back(true);
        unk164[i] = 0;
    }
}

BEGIN_HANDLERS(MicInputArrow)
    HANDLE_ACTION(set_mic_mgr, SetMicMgr(_msg->Obj<MicManagerInterface>(0)))
    HANDLE_ACTION(set_mic_connected, SetMicConnected(_msg->Int(2), _msg->Int(3)))
    HANDLE_ACTION(set_mic_extended, SetMicExtended(_msg->Int(2)))
    HANDLE_ACTION(set_mic_preview, SetMicPreview(_msg->Int(2)))
    HANDLE_ACTION(set_mic_hidden, SetMicHidden(_msg->Int(2)))
    HANDLE_SUPERCLASS(UIComponent)
    HANDLE_CHECK(0x10B)
END_HANDLERS

BEGIN_PROPSYNCS(MicInputArrow)
    SYNC_PROP(arrow_num, mArrowNum)
    SYNC_SUPERCLASS(UIComponent)
END_PROPSYNCS