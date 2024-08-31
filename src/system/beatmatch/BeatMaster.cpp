#include "beatmatch/BeatMaster.h"
#include "beatmatch/SongData.h"
#include "beatmatch/Output.h"
#include "beatmatch/Playback.h"
#include "beatmatch/MasterAudio.h"
#include "midi/MidiParserMgr.h"
#include "os/System.h"
#include "utl/SongInfoCopy.h"
#include "synth/Synth.h"

BeatMaster::BeatMaster(SongData* data, int i) : mSongData(data), mRecording(0), mAudio(0), mMidiParserMgr(0), mSongInfo(0), mPtCfg(0), mLoader(0), mLoaded(0), unk2d(0), mHandlers(0) {
    mSongData->AddSink(this);
    DataArray* cfg = SystemConfig("beatmatcher");
    cfg->FindData("recording", mRecording, false);
    mHandlers = cfg->FindArray("callbacks", false);
    TheBeatMatchOutput.SetActive(mRecording);
    String str;
    if(cfg->FindData("playback", str, false)){
        TheBeatMatchPlayback.LoadFile(str);
    }
    Reset();
    mAudio = new MasterAudio(cfg->FindArray("audio", true), i, this, mSongData);
}

BeatMaster::~BeatMaster(){
    delete mMidiParserMgr;
    delete mAudio;
    delete mLoader;
}

void BeatMaster::RegisterSink(BeatMasterSink& sink){
    mSinks.push_back(&sink);
}

// fn_80457BB8
void BeatMaster::Load(SongInfo* info, int i, PlayerTrackConfigList* plist, bool b, SongDataValidate validate, std::vector<MidiReceiver*>* vec){
    mSongInfo = info;
    mPtCfg = plist;
    mMidiParserMgr = new MidiParserMgr(mSongData, info->GetName());
    std::vector<MidiReceiver*> midi_receivers;
    midi_receivers.insert(midi_receivers.begin(), vec->begin(), vec->end());
    mSongData->Load(info, i, plist, midi_receivers, b, validate);
    MILO_ASSERT(!mLoader, 0x82);
    mLoader = new BeatMasterLoader(this);
    mLoaded = false;
    unk2d = false;
    if(b) TheLoadMgr.PollUntilLoaded(mLoader, 0);
}

void BeatMaster::LoaderPoll(){
    if(!mLoaded && mSongData->Poll()){
        mLoaded = true;
        mMidiParserMgr->FinishLoad();
    }
    else if(mLoaded && !unk2d){
        unk2d = true;
        mAudio->Load(mSongInfo, mPtCfg);
        mSongInfo = 0;
    }
    else if(unk2d){
        TheSynth->Poll();
        bool b1 = false;
        if(unk2d && mAudio->IsLoaded()) b1 = true;
        if(b1) RELEASE(mLoader);
    }
}

bool BeatMaster::IsLoaded(){
    bool b = false;
    if(unk2d && mAudio->IsLoaded()) b = true;
    return b;
}

void BeatMaster::AddTrack(int i, Symbol s, SongInfoAudioType atype, TrackType ttype, bool b){
    mSubmixIdxs.push_back(0);
}

void BeatMaster::Poll(float f){
    if(TheBeatMatchPlayback.mCommands) TheBeatMatchPlayback.Poll(f);
    mSongPos = mSongData->CalcSongPos(f);
    for(int i = 0; i < mSinks.size(); i++){
        mSinks[i]->UpdateSongPos(mSongPos);
    }
    mMidiParserMgr->Poll();
    float tick = mSongPos.mTotalTick;
    CheckBeat();
    CheckSubmixes(tick);
    mAudio->Poll();
}

float BeatMaster::SongDurationMs(){

}

// fn_80458830
void BeatMaster::Jump(float f){
    mSongPos = mSongData->CalcSongPos(f);
    mLastSongPos = mSongPos;
    mMidiParserMgr->Reset(mSongPos.mTotalTick);
    TheBeatMatchPlayback.Jump(f);
    float timeinloop = mSongData->GetTempoMap()->GetTimeInLoop(f);
    mAudio->Jump(timeinloop);
    mAudio->SetTimeOffset(f - timeinloop);
}

void BeatMaster::Reset(){
    mLastSongPos = SongPos();
    for(int i = 0; i < mSubmixIdxs.size(); i++){
        mSubmixIdxs[i] = 0;
    }
    ExportInitialSubmixes();
    if(mMidiParserMgr) mMidiParserMgr->Reset();
    if(mRecording) TheBeatMatchOutput.Reset();
    TheBeatMatchPlayback.Jump(0);
    HandleBeatCallback("reset");
    ResetAudio();
}

void BeatMaster::ResetAudio(){
    if(mAudio){
        if(mAudio->GetTime() != 0) mAudio->Jump(0);
    }
}

void BeatMaster::CheckBeat(){
    if((int)mLastSongPos.mTotalBeat != (int)mSongPos.mTotalBeat){
        static DataNode& beat = DataVariable("beat");
        beat = DataNode((int)mSongPos.mTotalBeat);
        HandleBeatCallback("beat");
        for(int i = 0; i < mSinks.size(); i++){
            mSinks[i]->Beat(mSongPos.mMeasure, mSongPos.mBeat);
        }
    }
    if((int)mLastSongPos.mMeasure != (int)mSongPos.mMeasure){
        static DataNode& measure = DataVariable("measure");
        measure = DataNode((int)mSongPos.mMeasure);
        HandleBeatCallback("downbeat");
    }
    if((mLastSongPos.mTick % 240) != (mSongPos.mTick % 240)){
        HandleBeatCallback("eighth_note");
    }
    if((mLastSongPos.mTick % 120) != (mSongPos.mTick % 240)){
        HandleBeatCallback("sixteenth_note");
    }
    mLastSongPos = mSongPos;
}

void BeatMaster::HandleBeatCallback(Symbol s){
    if(mHandlers){
        DataArray* arr = mHandlers->FindArray(s, false);
        if(arr) arr->ExecuteScript(1, 0, 0, 1);
    }
}