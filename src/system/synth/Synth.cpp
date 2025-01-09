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
#include "synth/StreamNull.h"
#include "obj/DataFunc.h"
#include "os/BufFile.h"
#include "utl/Symbols.h"

MicClientID sNullClientID(-1, -1);

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

void Synth::ToggleHud(){
    mHud->SetOverlay(!mHud->Showing());
    EnableLevels(mHud->Showing());
}

DECOMP_FORCEACTIVE(Synth, "%i", "0", "stream", "chan %i", "Total active Sequences: %d")

float Synth::UpdateOverlay(RndOverlay*, float){

}

DataNode Synth::OnStartMic(const DataArray* a){
    GetMic(a->Int(2))->Start();
    return 0;
}

DataNode Synth::OnStopMic(const DataArray* a){
    GetMic(a->Int(2))->Stop();
    return 0;
}

DataNode Synth::OnNumConnectedMics(const DataArray*){
    return GetNumConnectedMics();
}

DataNode Synth::OnSetMicVolume(const DataArray* a){
    SetMicVolume(a->Float(2));
    return 0;
}

DataNode Synth::OnSetFX(const DataArray* a){
    SetFX(a->Array(2));
    return 0;
}

DataNode Synth::OnSetFXVol(const DataArray* a){
    SetFXVolume(a->Int(2), a->Float(3));
    return 0;
}

void Synth::StopAllSfx(bool b){
    const std::list<SynthPollable*>& polls = SynthPollable::sPollables;
    for(std::list<SynthPollable*>::const_iterator it = polls.begin(); it != polls.end(); ++it){
        Sequence* seq = dynamic_cast<Sequence*>(*it);
        if(seq) seq->Stop(b);
    }
}

void Synth::PauseAllSfx(bool b){
    const std::list<SynthPollable*>& polls = SynthPollable::sPollables;
    for(std::list<SynthPollable*>::const_iterator it = polls.begin(); it != polls.end(); ++it){
        Sfx* sfx = dynamic_cast<Sfx*>(*it);
        if(sfx) sfx->Pause(b);
    }
}

DataNode Synth::OnPassthrough(DataArray* a){
    if(!CheckCommonBank(false)) return 0;
    else {
        const char* str = a->Str(2);
        Hmx::Object* obj = Find<Hmx::Object>(str, false);
        if(obj) obj->Handle(a, true);
        else MILO_WARN("Synth::OnPassthrough() - %s not found in %s", str, unk40->GetPathName());
        return 0;
    }
}

void Synth::Play(const char* name, float f1, float f2, float f3){
    if(CheckCommonBank(false)){
        Sequence* seq = Find<Sequence>(name, false);
        if(seq) seq->Play(f1, f2, f3);
        else MILO_WARN("Synth::Play() - Sequence %s not found in %s", name, unk40->GetPathName());
    }
}

bool Synth::CheckCommonBank(bool notify){
    bool ret = false;
    if(unk40 && unk40.IsLoaded()) ret = true;
    if(!ret && notify){
        MILO_LOG("Synth::Find() - Common sound bank not loaded!\n");
    }
    return ret;
}

#pragma push
#pragma dont_inline on
BEGIN_HANDLERS(Synth)
    HANDLE(play, OnPassthrough)
    HANDLE(stop, OnPassthrough)
    HANDLE(start_mic, OnStartMic)
    HANDLE(stop_mic, OnStopMic)
    HANDLE_ACTION(stop_playback_all_mics, StopPlaybackAllMics())
    HANDLE(num_connected_mics, OnNumConnectedMics)
    HANDLE_EXPR(did_mics_change, DidMicsChange())
    HANDLE_ACTION(reset_mics_changed, ResetMicsChanged())
    HANDLE(set_mic_volume, OnSetMicVolume)
    HANDLE(set_fx, OnSetFX)
    HANDLE(set_fx_vol, OnSetFXVol)
    HANDLE_ACTION(stop_all_sfx, StopAllSfx(_msg->Size() == 3 ? _msg->Int(2) : false))
    HANDLE_ACTION(pause_all_sfx, PauseAllSfx(_msg->Int(2)))
    HANDLE_EXPR(master_vol, GetMasterVolume())
    HANDLE_ACTION(set_master_vol, SetMasterVolume(_msg->Float(2)))
    HANDLE_EXPR(find, Find<Hmx::Object>(_msg->Str(2), true))
    HANDLE_ACTION(toggle_hud, ToggleHud())
    HANDLE_EXPR(get_sample_mem, GetSampleMem(_msg->Obj<ObjectDir>(2), (Platform)_msg->Int(3)))
    HANDLE_EXPR(spu_overhead, GetSPUOverhead())
    HANDLE_ACTION(set_headset_target, 0)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x446)
END_HANDLERS
#pragma pop

Stream* Synth::NewStream(const char*, float f1, float, bool){
    return new StreamNull(f1);
}

Stream* Synth::NewBufStream(const void*, int, Symbol, float f1, bool){
    return new StreamNull(f1);
}

void Synth::NewStreamFile(const char* cc, File*& file, Symbol& sym){
    static char gFakeFile[16];
    file = new BufFile(gFakeFile, sizeof(gFakeFile));
    sym = "fake";
}

int Synth::GetSampleMem(ObjectDir* dir, Platform plat){
    int size = 0;
    for(ObjDirItr<SynthSample> it(dir, true); it != nullptr; ++it){
        size += it->GetPlatformSize(plat);
    }
    return size;
}

int Synth::GetFXOverhead(){
    int overheads[10] = {
        0x80, 0x26c0, 8000, 0x4c28, 0x6fe0,
        0xade0, 0xf6c0, 0x18040, 0x18040, 0x3c00
    };
    DataArray* cfg = SystemConfig("synth");
    int mode = cfg->FindArray("fx", true)->FindArray("core_0", true)->FindInt("mode");
    return overheads[mode] + 0x20000;
}

int Synth::GetSPUOverhead(){
    DataArray* cfg = SystemConfig("synth");
    int spuBufs = cfg->FindArray("iop", true)->FindInt("spu_buffers");
    return spuBufs * 0x800 + 0x5010 + GetFXOverhead();
}

FxSendPitchShift* Synth::CreatePitchShift(int stage, SendChannels chans){
    FxSendPitchShift* fx = Hmx::Object::New<FxSendPitchShift>();
    fx->SetStage(stage);
    fx->SetChannels(chans);
    return fx;
}

void Synth::DestroyPitchShift(FxSendPitchShift* fx){
    delete fx;
}