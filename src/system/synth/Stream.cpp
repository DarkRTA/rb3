#include "synth/Stream.h"
#include "synth/Faders.h"
#include "synth/Synth.h"
#include "utl/Symbols.h"

Stream::Stream() : mFaders(new FaderGroup(0)) {
    mFaders->AddLocal(_default)->SetVal(0.0f);
}

Stream::~Stream(){
    delete mFaders;
}

void Stream::SetVolume(float f){
    mFaders->FindLocal(_default, true)->SetVal(f);
}