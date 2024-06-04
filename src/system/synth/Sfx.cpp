#include "synth/SfxInst.h"
#include "synth/MoggClipMap.h"
#include "synth/SfxMap.h"
#include "synth/FxSend.h"
#include "synth/Synth.h"
#include "synth/Sfx.h"
#include "utl/Symbols.h"

SfxInst::SfxInst(Sfx* sfx) : SeqInst(sfx), mMoggClips(this, kObjListNoNull), mStartProgress(0.0f) {
    
}

Sfx::Sfx() : mMaps(this), mMoggClipMaps(this), mSend(this), mReverbMixDb(-96.0f), mReverbEnable(0), mSfxInsts(this, kObjListNoNull) {
    mFaders.Add(TheSynth->unk4c);
    mFaders.Add(TheSynth->unk50);
}

void Sfx::SynthPoll(){ Sequence::SynthPoll(); }

void Sfx::Pause(bool b){
    for(ObjPtrList<SfxInst, ObjectDir>::iterator it = mSfxInsts.begin(); it != mSfxInsts.end(); ++it){
        (*it)->Pause(b);
    }
}

SeqInst* Sfx::MakeInstImpl(){
    SfxInst* inst = new SfxInst(this);
    mSfxInsts.push_back(inst);
    return inst;
}

BEGIN_HANDLERS(Sfx)
    HANDLE_ACTION(add_map, mMaps.push_back(SfxMap(this)))
    HANDLE_SUPERCLASS(Sequence)
    HANDLE_CHECK(0x147)
END_HANDLERS