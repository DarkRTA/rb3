#include "utl/Song.h"
#include "utl/FakeSongMgr.h"
#include "utl/BeatMap.h"

Song::Song() : unk1c(0), mHxSongData(0), mDebugParsers(this, kObjListNoNull), mSongEndFrame(0), mSpeed(1.0f), unk5c(0), unk60(0), unk7c(1) {
    SetName("Song", ObjectDir::Main());
    static DataNode& tool_song(DataVariable("tool_song"));
    tool_song = DataNode(this);
}

Song::~Song(){
    static DataNode& tool_song(DataVariable("tool_song"));
    tool_song = DataNode((Hmx::Object*)0);
    Unload();
}

BEGIN_COPYS(Song)
END_COPYS

SAVE_OBJ(Song, 0x38)

BEGIN_LOADS(Song)
    bs.ReadInt();
    LOAD_SUPERCLASS(RndAnimatable)
    static Symbol sSongName;
    bs >> sSongName;
    if(mSongName != sSongName){
        mSongName = sSongName;
        Load();
    }
    bool b;
    bs >> b;
    if(b) unk7c = true;
END_LOADS

float Song::GetBeat(){
    float ret;
    if(!GetTempoMap()) return 0;
    else ret = GetBeatMap()->Beat(GetTempoMap()->TimeToTick(mFrame * 1000.0f));
    return ret;
}

TempoMap* Song::GetTempoMap(){
    if(mHxSongData) return mHxSongData->GetTempoMap();
    else return 0;
}

BeatMap* Song::GetBeatMap(){
    if(mHxSongData) return mHxSongData->GetBeatMap();
    else return 0;
}

MeasureMap* Song::GetMeasureMap(){
    if(mHxSongData) return mHxSongData->GetMeasureMap();
    else return 0;
}

void Song::LoadSong(){
    CreateSong(mSongName, TheFakeSongMgr->GetSongConfig(mSongName), &mHxSongData, &unk1c);
    MILO_ASSERT_FMT(mHxSongData && unk1c, "Could not create song");
}