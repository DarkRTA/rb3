#include "utl/Song.h"
#include "utl/FakeSongMgr.h"
#include "utl/BeatMap.h"
#include "obj/Msg.h"
#include "rndobj/Poll.h"

Song::Song() : mHxMaster(0), mHxSongData(0), mDebugParsers(this, kObjListNoNull), mSongEndFrame(0), mSpeed(1.0f), unk5c(0), unk60(0), unk7c(1) {
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

MBT Song::GetMBTFromFrame(float f, int* i){
    MBT ret;
    int tick = 0;
    if(GetTempoMap()){
        tick = GetTempoMap()->TimeToTick(f * 1000.0f + 0.5f);
    }
    ret = GetMBTFromTick(tick, i);
    return ret;
}

MBT Song::GetMBTFromTick(int i, int* iptr){
    MBT ret;
    int tick = 0;
    if(GetMeasureMap()){
        GetMeasureMap()->TickToMeasureBeatTick(i, ret.measure, ret.beat, ret.tick, tick);
    }
    ret.measure++;
    ret.beat++;
    if(iptr) *iptr = tick;
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

float Song::UpdateOverlay(RndOverlay* o, float f){
    for(ObjPtrList<Hmx::Object, ObjectDir>::iterator it = mDebugParsers.begin(); it != mDebugParsers.end(); ++it){
        const DataNode& node = (*it)->Handle(Message("debug_draw", DataNode(f), DataNode(GetBeat())), true);
        f += node.Float(0);
    }
    return f;
}

float Song::EndFrame(){ return mSongEndFrame; }

void Song::Load(){
    std::vector<Symbol> vec;
    for(ObjPtrList<Hmx::Object, ObjectDir>::iterator it = mDebugParsers.begin(); it != mDebugParsers.end(); ++it){
        vec.push_back((*it)->Name());
    }
//   if (sCallback == (int *)0x0) {
//     pcVar2 = ::MakeString(kAssertStr,s_Song.cpp_80bbf8b7,0xf8,s_sCallback_80bbf8cd);
//     Debug::Fail((Debug *)TheDebug,pcVar2);
//   }
//   (**(code **)(*sCallback + 0x1c))();
    Unload();
    if(mSongName.Null()) return;
    else LoadSong();
}

void Song::LoadSong(){
    CreateSong(mSongName, TheFakeSongMgr->GetSongConfig(mSongName), &mHxSongData, &mHxMaster);
    MILO_ASSERT_FMT(mHxSongData && mHxMaster, "Could not create song");
    RndPollable* poll = dynamic_cast<RndPollable*>(MainDir());
    if(poll) poll->Enter();
    mSongEndFrame = mHxMaster->SongDurationMs() / 1000.0f;
    if(mSongName != unk50){
        SetLoopStart(0);
        SetLoopEnd(mSongEndFrame);
    }
    else {
        if(unk5c > mSongEndFrame) SetLoopStart(mSongEndFrame);
        if(unk60 > mSongEndFrame) SetLoopEnd(mSongEndFrame);
    }
    JumpTo(0);
}

void Song::CreateSong(Symbol, DataArray*, HxSongData** d, HxMaster** m){ *d = 0; *m = 0; }

void Song::Unload(){
    delete mHxMaster;
    mHxMaster = 0;
    delete mHxSongData;
    mHxSongData = 0;
    unk24.clear();
}