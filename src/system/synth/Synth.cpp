#include "synth/Synth.h"
#include "utl/Loader.h"
#include "synth/Faders.h"
#include "synth/Sfx.h"
#include "synth/MidiInstrument.h"
#include "synth/SynthSample.h"
#include "synth/Sequence.h"
#include "synth/Emitter.h"
#include "synth/FxSendReverb.h"
#include "synth/FxSendDelay.h"
#include "synth/FxSendDistortion.h"
#include "synth/FxSendCompress.h"
#include "synth/FxSendEQ.h"
#include "synth/FxSendFlanger.h"
#include "synth/FxSendChorus.h"
#include "synth/FxSendMeterEffect.h"
#include "synth/FxSendPitchShift.h"
#include "synth/FxSendSynapse.h"
#include "synth/FxSendWah.h"
#include "synth/MoggClip.h"
#include "synth/BinkClip.h"

namespace {
    struct DebugGraph {
        DebugGraph(const Hmx::Color& c){
            unk0.resize(200);
            unk8 = 0;
            unkc = c;
        }

        std::vector<float> unk0;
        int unk8;
        Hmx::Color unkc;
    };

    std::vector<DebugGraph> gDebugGraphs;
}

DataNode returnMasterKey(DataArray*){

}

Synth::Synth() : mMuted(0), mMicClientMapper(0), mMidiInstrumentMgr(0), unk60(0), unk64(0) {
    SetName("synth", ObjectDir::sMainDir);
    DataArray* cfg = SystemConfig("synth");
    cfg->FindData("mics", mNumMics, true);
    mMidiSynth = new MidiSynth();
    gDebugGraphs.push_back(DebugGraph(Hmx::Color(1,0,0)));
    gDebugGraphs.push_back(DebugGraph(Hmx::Color(0,1,0)));
    gDebugGraphs.push_back(DebugGraph(Hmx::Color(1,1,0)));
    gDebugGraphs.push_back(DebugGraph(Hmx::Color(1,1,1)));
    mMicClientMapper = new MicClientMapper();
    mMidiInstrumentMgr = new MidiInstrumentMgr();
    MILO_ASSERT(!TheSynth, 0xBB);
}

Loader* WavFactory(const FilePath& fp, LoaderPos pos){
    CacheResourceResult res;
    return new FileLoader(fp, CacheWav(fp.c_str(), res), pos, 0, false, true, nullptr);
}

void Synth::Init(){
    Fader::Init();
    Sfx::Init();
    MidiInstrument::Init();
    SynthSample::Init();
    Sequence::Init();
    SynthEmitter::Init();
    FxSendReverb::Init();
    FxSendDelay::Init();
    FxSendDistortion::Init();
    FxSendCompress::Init();
    FxSendEQ::Init();
    FxSendFlanger::Init();
    FxSendChorus::Init();
    FxSendMeterEffect::Init();
    FxSendPitchShift::Init();
    FxSendSynapse::Init();
    FxSendWah::Init();
    MoggClip::Init();
    BinkClip::Init();
    mMasterFader = Hmx::Object::New<Fader>();
    mSfxFader = Hmx::Object::New<Fader>();
    mMidiInstrumentFader = Hmx::Object::New<Fader>();
    DataArray* cfg = SystemConfig("synth");
    mMuted = cfg->FindInt("mute");
    TheLoadMgr.RegisterFactory("wav", WavFactory);
    mNullMics.resize(GetNumMics());
    for(int i = 0; i < mNullMics.size(); i++){
        mNullMics[i] = new MicNull();
    }
    unk68 = RndOverlay::Find("synth_hud", true);
    unk68->SetCallback(this);
    InitSecurity();
    mMidiInstrumentMgr->Init();
}