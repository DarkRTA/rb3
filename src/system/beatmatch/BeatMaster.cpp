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

void BeatMaster::Load(SongInfo* info, int i, PlayerTrackConfigList* plist, bool b, SongDataValidate validate, std::vector<MidiReceiver*>* vec){
    mSongInfo = info;
    mPtCfg = plist;
    mMidiParserMgr = new MidiParserMgr(mSongData, info->GetName());
    std::vector<MidiReceiver*> midi_receivers;
    midi_receivers = *vec;
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

void BeatMaster::HandleBeatCallback(Symbol s){
    if(mHandlers){
        DataArray* arr = mHandlers->FindArray(s, false);
        if(arr) arr->ExecuteScript(1, 0, 0, 1);
    }
}