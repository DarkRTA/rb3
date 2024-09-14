#include "bandobj/ReviewDisplay.h"
#include "utl/Symbols.h"

ReviewDisplay::ReviewDisplay() : unk10c(0), unk110(0), mScore(0) {

}

ReviewDisplay::~ReviewDisplay(){
    
}

BEGIN_HANDLERS(ReviewDisplay)
    HANDLE_ACTION(set_values, SetValues(_msg->Int(2), _msg->Int(3)))
    HANDLE_SUPERCLASS(UIComponent)
    HANDLE_CHECK(0xE0)
END_HANDLERS

BEGIN_PROPSYNCS(ReviewDisplay)
    SYNC_PROP_MODIFY(score, mScore, UpdateDisplay(true))
    SYNC_SUPERCLASS(UIComponent)
END_PROPSYNCS