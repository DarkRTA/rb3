#include "synth/MidiInstrumentMgr.h"

MidiInstrumentMgr::MidiInstrumentMgr() : mObjectDir(), mInstrument(0, 0) {

}

MidiInstrumentMgr::~MidiInstrumentMgr(){
    UnloadInstrument();
}

void MidiInstrumentMgr::Init(){}

void MidiInstrumentMgr::SetInstrument(MidiInstrument* inst){
    mInstrument = inst;
}

void MidiInstrumentMgr::UnloadInstrument(){
    if(mInstrument) mInstrument->KillAllVoices();
    mInstrument = 0;
}

void MidiInstrumentMgr::Poll(){
    if(!mInstrument) return;
    mInstrument->Poll();
}