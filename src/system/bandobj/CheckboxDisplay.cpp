#include "bandobj/CheckboxDisplay.h"
#include "utl/Symbols.h"

CheckboxDisplay::CheckboxDisplay() : mChecked(1) {

}

CheckboxDisplay::~CheckboxDisplay(){
    
}

BEGIN_HANDLERS(CheckboxDisplay)
    HANDLE_SUPERCLASS(UIComponent)
    HANDLE_CHECK(0x87)
END_HANDLERS

BEGIN_PROPSYNCS(CheckboxDisplay)
    SYNC_PROP_SET(checked, mChecked, SetChecked(_val.Int(0)))
    SYNC_SUPERCLASS(UIComponent)
END_PROPSYNCS