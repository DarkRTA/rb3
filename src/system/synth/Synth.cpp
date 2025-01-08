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
#include "obj/DataFunc.h"

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

Synth* TheSynth;

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
    mHud = RndOverlay::Find("synth_hud", true);
    mHud->SetCallback(this);
    InitSecurity();
    mMidiInstrumentMgr->Init();
}

DECOMP_FORCEACTIVE(Synth, "TheSynth != NULL", "use_null_synth")

void Synth::InitSecurity(){
    char buf[256];
    char c4 = 'A';
    buf[1] = 0;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 4; j++){
            buf[0] = j + c4;
            DataRegisterFunc(buf, returnMasterKey);
        }
        c4 += 4;
    }
    buf[0] = 'M';
    DataRegisterFunc(buf, returnMasterKey);
    mGrinder.Init();
}

void Synth::Terminate(){
    DeleteAll(mNullMics);
    RELEASE(mMidiSynth);
    RELEASE(mMasterFader);
    RELEASE(mSfxFader);
    RELEASE(mMidiInstrumentFader);
    RELEASE(mMicClientMapper);
    RELEASE(mMidiInstrumentMgr);
}

void Synth::SetMasterVolume(float vol){
    mMasterFader->SetVal(vol);
}

float Synth::GetMasterVolume(){
    return mMasterFader->GetVal();
}

void Synth::Poll(){
    for(int i = 0; i < mLevelData.size(); i++){
        LevelData& data = mLevelData[i];
        if((data.mPeak > data.mPeakHold) || ++data.mPeakAge >= 0x3C){
            data.mPeakHold = data.mPeak;
            data.mPeakAge = 0;
        }
    }
    FaderTask::PollAll();
    if(mMuted) mMasterFader->SetVal(-96.0f);
    SynthPollable::PollAll();
    mMidiInstrumentMgr->Poll();
    if(DidMicsChange()){
        MILO_ASSERT(mMicClientMapper, 0x14B);
        mMicClientMapper->HandleMicsChanged();
        ResetMicsChanged();
    }
}

void Synth::SetFX(const DataArray* data){
    MILO_ASSERT(data, 0x15F);
    int chainData = data->FindArray("chain", true)->Int(1);
    SetFXChain(chainData);
    for(int i = 0; i < 2; i++){
        DataArray* coreArr = data->FindArray(MakeString("core_%i", i), true);
        int mode = coreArr->FindArray("mode", true)->Int(1);
        float volume = coreArr->FindArray("volume", true)->Float(1);
        float delay = coreArr->FindArray("delay", true)->Float(1);
        float feedback = coreArr->FindArray("feedback", true)->Float(1);
        SetFXMode(i, (FXMode)mode);
        SetFXVolume(i, volume);
        SetFXDelay(i, delay);
        SetFXFeedback(i, feedback);
    }
}

// holy deadstrip
DECOMP_FORCEACTIVE(Synth, "transpose >= -0x2000 && transpose < 0x2000", "name", "Sequence%i", "random_group_seq", "num_seqs",
    "serial_group_seq", "parallel_group_seq", "sfx_seq", "sfx", "couldn't find sfx %s", "pan", "transpose", "wait_seq",
    "secs", "vol_mod_seq", "pan_mod_seq", "transpose_mod_seq", "loop_mod_seq", "wrapped", "can't load sequence of type %s",
    "children", "Couldn't read bank: %s", "sample")

#pragma push
#pragma dont_inline on
DECOMP_FORCEFUNC(Synth, Synth, GetNumMics())
#pragma pop

void Synth::StopPlaybackAllMics(){
    MicManagerInterface* micInterface = mMicClientMapper->mMicManager;
    if(micInterface){
        micInterface->SetPlayback(false);
    }
}

void Synth::SetMic(const DataArray* data){
    for(int i = 0; i < mNumMics; i++){
        Mic* mic = GetMic(i);
        if(mic) mic->Set(data);
    }
    SetMicFX(data->FindArray("fx", true)->Int(1));
    SetMicVolume(data->FindArray("volume", true)->Float(1));
}

DECOMP_FORCEACTIVE(Synth, "adsr", "loops", "loop not set for %s", "sequences")

void SynthPreInit(){
    MILO_ASSERT(!TheSynth, 0x2EA);
    DataArray* cfg = SystemConfig("synth");
    bool useNullSynth = cfg->FindArray("use_null_synth", true)->Int(1);
    if(useNullSynth) TheSynth = new Synth();
    else TheSynth = Synth::New();
    if(TheSynth->Fail()){
        RELEASE(TheSynth);
        TheSynth = new Synth();
    }
    TheSynth->PreInit();
}

void SynthInit(){
    if(!TheSynth) SynthPreInit();
    DataArray* cfg = SystemConfig("synth");
    TheSynth->Init();
    TheSynth->SetMic(cfg->FindArray("mic", true));
    TheSynth->SetFX(cfg->FindArray("fx", true));
    TheDebug.AddExitCallback(SynthTerminate);
}

void SynthTerminate(){
    TheSynth->Poll();
    TheDebug.RemoveExitCallback(SynthTerminate);
    TheSynth->Terminate();
    RELEASE(TheSynth);
}