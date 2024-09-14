#include "bandobj/InstrumentDifficultyDisplay.h"
#include "ui/UI.h"
#include "utl/Symbols.h"

void InstrumentDifficultyDisplay::Init(){
    Register();
    TheUI->InitResources("InstrumentDifficultyDisplay");
}

InstrumentDifficultyDisplay::InstrumentDifficultyDisplay() : unk10c(0), unk114(0), unk118(0), unk11c(0), mInstrumentState(kName), mHasPart(1),
    mDifficulty(3), mNumVocalParts(0), mInstrumentType("band"), mInstrumentColorOverride(this, 0) {
    unk120 = Hmx::Object::New<BandLabel>();
    unk110 = Hmx::Object::New<RndMesh>();
}

InstrumentDifficultyDisplay::~InstrumentDifficultyDisplay(){

}

BEGIN_HANDLERS(InstrumentDifficultyDisplay)
    HANDLE_ACTION(set_values, SetValues(_msg->Sym(2), _msg->Int(3), _msg->Int(4), _msg->Int(5)))
    HANDLE_SUPERCLASS(UIComponent)
    HANDLE_CHECK(0x11B)
END_HANDLERS

BEGIN_PROPSYNCS(InstrumentDifficultyDisplay)
    SYNC_PROP_MODIFY(difficulty, mDifficulty, UpdateDisplay())
    SYNC_PROP_MODIFY(instrument_type, mInstrumentType, UpdateDisplay())
    SYNC_PROP_MODIFY(num_vocal_parts, mNumVocalParts, UpdateDisplay())
    SYNC_PROP_MODIFY(has_part, mHasPart, UpdateDisplay())
    SYNC_PROP_SET(instrument_state, mInstrumentState, SetInstrumentState((InstrumentState)_val.Int(0)))
    SYNC_PROP(instrument_color_override, mInstrumentColorOverride)
    SYNC_SUPERCLASS(UIComponent)
END_PROPSYNCS