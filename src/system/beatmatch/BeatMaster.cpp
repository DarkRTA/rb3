#include "beatmatch/BeatMaster.h"
#include "beatmatch/SongData.h"
#include "beatmatch/Output.h"
#include "beatmatch/Playback.h"
#include "beatmatch/MasterAudio.h"
#include "os/System.h"

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

}

void BeatMaster::RegisterSink(BeatMasterSink& sink){
    mSinks.push_back(&sink);
}

void BeatMaster::HandleBeatCallback(Symbol s){
    if(mHandlers){
        DataArray* arr = mHandlers->FindArray(s, false);
        if(arr) arr->ExecuteScript(1, 0, 0, 1);
    }
}