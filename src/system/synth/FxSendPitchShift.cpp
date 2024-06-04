#include "synth/FxSendPitchShift.h"
#include "utl/Symbols.h"
#include "obj/PropSync_p.h"
#include "os/Debug.h"

unsigned short FxSendPitchShift::gRev = 0;
unsigned short FxSendPitchShift::gAltRev = 0;

FxSendPitchShift::FxSendPitchShift() : mRatio(1.0f) {

}

BEGIN_HANDLERS(FxSendPitchShift)
    HANDLE_SUPERCLASS(FxSend)
    HANDLE_CHECK(0x1C)
END_HANDLERS

BEGIN_PROPSYNCS(FxSendPitchShift)
    SYNC_PROP_MODIFY(pitch_ratio, mRatio, OnParametersChanged())
    SYNC_SUPERCLASS(FxSend)
END_PROPSYNCS

SAVE_OBJ(FxSendPitchShift, 0x2A);

void FxSendPitchShift::Load(BinStream& bs){
    MILO_FAIL("FxSendPitchShift objects should not be created in Milo!\n");
    int rev;
    bs >> rev;
    if(rev > 1) MILO_WARN("Can't load new FxSendPitchShift");
    else {
        FxSend::Load(bs);
        bs >> mRatio;
        OnParametersChanged();
    }
}

BEGIN_COPYS(FxSendPitchShift)
    COPY_SUPERCLASS(FxSend)
    CREATE_COPY(FxSendPitchShift, c)
    if(c){
        COPY_MEM(c, mRatio)
    }
END_COPYS
