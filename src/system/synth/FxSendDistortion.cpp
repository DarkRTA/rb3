#include "synth/FxSendDistortion.h"
#include "utl/Symbols.h"
#include "obj/PropSync_p.h"

unsigned short FxSendDistortion::gRev = 0;
unsigned short FxSendDistortion::gAltRev = 0;

FxSendDistortion::FxSendDistortion() : mDrive(0.0f) {

}

FxSendDistortion::~FxSendDistortion(){

}

SAVE_OBJ(FxSendDistortion, 0x18);

void FxSendDistortion::Load(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(1, 0);
    FxSend::Load(bs);
    bs >> mDrive;
    OnParametersChanged();
}

BEGIN_COPYS(FxSendDistortion)
    COPY_SUPERCLASS(FxSend)
    GET_COPY(FxSendDistortion)
    BEGIN_COPY_CHECKED
        COPY_MEMBER(mDrive)
    END_COPY_CHECKED
END_COPYS

BEGIN_HANDLERS(FxSendDistortion)
    HANDLE_SUPERCLASS(FxSend)
    HANDLE_CHECK(0x34)
END_HANDLERS

BEGIN_PROPSYNCS(FxSendDistortion)
    SYNC_PROP_ACTION(drive, mDrive, kPropSize|kPropGet, OnParametersChanged())
    SYNC_SUPERCLASS(FxSend)
END_PROPSYNCS
