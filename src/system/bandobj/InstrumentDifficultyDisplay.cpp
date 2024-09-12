#include "bandobj/InstrumentDifficultyDisplay.h"
#include "ui/UI.h"

void InstrumentDifficultyDisplay::Init(){
    Register();
    TheUI->InitResources("InstrumentDifficultyDisplay");
}

InstrumentDifficultyDisplay::InstrumentDifficultyDisplay() : unk10c(0), unk114(0), unk118(0), unk11c(0), unk124(1), unk128(1), unk12c(3), unk130(0), unk134("band"), unk138(this, 0) {
    unk120 = Hmx::Object::New<BandLabel>();
    unk110 = Hmx::Object::New<RndMesh>();
}

InstrumentDifficultyDisplay::~InstrumentDifficultyDisplay(){

}