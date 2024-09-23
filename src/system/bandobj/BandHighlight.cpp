#include "bandobj/BandHighlight.h"
#include "utl/Symbols.h"

BandHighlight::BandHighlight() : unk148(0), unk154(0), unk158(0) {

}

BandHighlight::~BandHighlight(){
    
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