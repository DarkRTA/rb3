#include "synth/MidiInstrument.h"
#include "synth/Synth.h"

MidiInstrument::MidiInstrument() : mMultiSampleMap(this), mPatchNumber(0), mSend(this, 0), mReverbMixDb(-96.0f), mReverbEnable(0), 
    mActiveVoices(this, kObjListNoNull), mFaders(this), mFineTuneCents(0.0f) {
    mFaders.Add(TheSynth->unk4c);
    mFaders.Add(TheSynth->unk54);
}