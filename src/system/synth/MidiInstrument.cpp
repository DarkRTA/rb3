#include "synth/MidiInstrument.h"
#include "synth/Synth.h"

MidiInstrument::MidiInstrument() : mMultiSampleMap(this), mPatchNumber(0), mSend(this, 0), mReverbMixDb(-96.0f), mReverbEnable(0), 
    mActiveVoices(this, kObjListNoNull), mFaders(this), mFineTuneCents(0.0f) {
    mFaders.Add(TheSynth->unk4c);
    mFaders.Add(TheSynth->unk54);
}

void MidiInstrument::Poll(){
    if(mActiveVoices.size() != 0){
        for(ObjPtrList<NoteVoiceInst, ObjectDir>::iterator it = mActiveVoices.begin(); it != mActiveVoices.end(); ++it){
            NoteVoiceInst* theinst = *it;
            theinst->Poll();
            if(theinst->Started() && !theinst->IsRunning()){
                delete theinst;
            }
        }
        if(mFaders.Dirty()){
            for(ObjPtrList<NoteVoiceInst, ObjectDir>::iterator it = mActiveVoices.begin(); it != mActiveVoices.end(); ++it){
                (*it)->UpdateVolume();
            }
        }
    }
}

SAVE_OBJ(MidiInstrument, 0x125)

BEGIN_LOADS(MidiInstrument)
    int rev;
    bs >> rev;
    if(rev > 3) MILO_WARN("Can't load new MidiInstrument");
    else {
        SampleZone::gRev = rev;
        LOAD_SUPERCLASS(Hmx::Object)
        bs >> mMultiSampleMap;
        bs >> mSend;
        bs >> mPatchNumber;
        mFaders.Load(bs);
        if(rev >= 3){
            bs >> mReverbMixDb;
            bs >> mReverbEnable;
        }
    }
END_LOADS