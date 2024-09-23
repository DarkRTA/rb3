#include "bandobj/CharKeyHandMidi.h"
#include "utl/Symbols.h"

CharKeyHandMidi::CharKeyHandMidi() : mIKObject(this, 0), mFirstSpot(this, 0), mSecondSpot(this, 0), unk7c(this, 0) {

}

CharKeyHandMidi::~CharKeyHandMidi(){
    
}

BEGIN_HANDLERS(CharKeyHandMidi)
    HANDLE(fingers_up, OnFingersUp)
    HANDLE(fingers_down, OnFingersDown)
    HANDLE_ACTION(run_test, RunTest())
    HANDLE_ACTION(end_test, EndTest())
    HANDLE_SUPERCLASS(CharWeightable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x319)
END_HANDLERS

BEGIN_PROPSYNCS(CharKeyHandMidi)
    SYNC_PROP(ik_object, mIKObject)
    SYNC_PROP(first_spot, mFirstSpot)
    SYNC_PROP(second_spot, mSecondSpot)
    SYNC_PROP(is_right_hand, mIsRightHand)
    SYNC_SUPERCLASS(CharWeightable)
END_PROPSYNCS