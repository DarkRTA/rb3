#include "utl/Song.h"
#include "utl/FakeSongMgr.h"
#include "utl/BeatMap.h"
#include "obj/Msg.h"
#include "rndobj/Poll.h"
#include "beatmatch/HxAudio.h"
#include "synth/Synth.h"
#include "midi/MidiParser.h"
#include "midi/MidiParserMgr.h"
#include "utl/Symbols.h"

Hmx::Object* Song::sCallback; // almost definitely some derivative of an Object, rather than an Object itself

// (**(code **)(*sCallback + 0xc))((double)fVar1,sCallback,this);
// (**(code **)(*sCallback + 0x10))(); - returns an ObjectDir*
// (**(code **)(*sCallback + 0x14))(sCallback,1); - presumably the dtor
// (**(code **)(*sCallback + 0x18))(sCallback,this,this_00);
// (**(code **)(*sCallback + 0x1c))(); - returns void

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
        f += node.Float();
    }
    return f;
}

float Song::EndFrame(){ return mSongEndFrame; }

void Song::Load(){
    std::vector<Symbol> vec;
    for(ObjPtrList<Hmx::Object, ObjectDir>::iterator it = mDebugParsers.begin(); it != mDebugParsers.end(); ++it){
        vec.push_back((*it)->Name());
    }
    MILO_ASSERT(sCallback, 0xF8);
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

void Song::Play(){
    if(mHxMaster){
        mHxMaster->Jump(mFrame * 1000.0f);
        while(!mHxMaster->GetHxAudio()->IsReady()){
            TheSynth->Poll();
            mHxMaster->GetHxAudio()->Poll();
        }
        mHxMaster->GetHxAudio()->SetPaused(false);
    }
}

void Song::Pause(){
    if(mHxMaster){
        if(mHxMaster){
            mHxMaster->GetHxAudio()->SetPaused(true);
        }
    }
}

void Song::SetSong(Symbol s){
    mSongName = s;
    Load();
}

void Song::OnText(int i, const char* cc, unsigned char uc){
    static bool sListening;
    if(uc == 3){
        sListening = strcmp(cc, "EVENTS") == 0;
    }
    if(sListening){
        bool insection = strncmp(cc, "[section ", 9) == 0;
        if(insection){
            String str(cc);
            str = str.substr(9, strlen(str.c_str()) - 10);
            Symbol s(str.c_str());
            AddSection(s, GetBeatMap()->Beat(i));
        }
    }
}

DataNode Song::OnMBTFromSeconds(const DataArray* da){
    MBT mbt = GetMBTFromFrame(da->Float(2), 0);
    *da->Var(3) = DataNode(mbt.measure);
    *da->Var(4) = DataNode(mbt.beat);
    *da->Var(5) = DataNode(mbt.tick);
    return DataNode(0);
}

void Song::JumpTo(Symbol s){
    int jump = 0;
    for(std::map<int, Symbol>::iterator it = unk24.begin(); it != unk24.end(); ++it){
        if(s == it->second){
            jump = it->first;
            break;
        }
    }
    JumpTo(jump);
}

void Song::JumpTo(int i){
    float f = 0;
    if(mHxSongData){
        f = mHxSongData->GetTempoMap()->TickToTime(i) / 1000.0f;
    }
    MILO_ASSERT(sCallback, 0x19A);
    // (**(code **)(*sCallback + 0xc))((double)fVar1,sCallback,this);
    SyncState();
}

BEGIN_HANDLERS(Song)
    if(sym == get_bookmarkers) return GetBookmarks();
    if(sym == get_midi_parsers) return GetMidiParsers();
    HANDLE_ACTION(jump_to, _msg->Type(2) == kDataSymbol ? JumpTo(_msg->Sym(2)) : JumpTo(_msg->Int(2)))
    HANDLE_ACTION(sync_state, SyncState())
    HANDLE_ACTION(set_loop_start, SetLoopStart(_msg->Float(2)))
    HANDLE_ACTION(set_loop_end, SetLoopEnd(_msg->Float(2)))
    HANDLE_ACTION(play, Play())
    HANDLE_ACTION(pause, Pause())
    HANDLE_EXPR(song_name, mSongName)
    HANDLE(mbt_from_seconds, OnMBTFromSeconds)
    HANDLE_ACTION(add_section, AddSection(_msg->Sym(2), _msg->Float(3)))
    HANDLE_SUPERCLASS(RndAnimatable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x239)
END_HANDLERS

DataNode Song::GetBookmarks(){
    DataArrayPtr ptr(new DataArray(unk24.size() + 1));
    ptr->Node(0) = DataNode("song_begin");
    int idx = 1;
    for(std::map<int, Symbol>::iterator it = unk24.begin(); it != unk24.end(); ++it){
        ptr->Node(idx) = DataNode(it->second);
        idx++;
    }
    return DataNode(ptr);
}

DataNode Song::GetMidiParsers(){
    DataArrayPtr ptr(new DataArray(0));
    if(TheMidiParserMgr){
        for(std::list<MidiParser*>::iterator it = MidiParser::sParsers.begin(); it != MidiParser::sParsers.end(); ++it){
            String str((*it)->Name());
            if(str != "events_parser"){
                ptr->Insert(ptr->Size(), DataNode(*it));
            }
        }
    }
    return DataNode(ptr);
}

void Song::UpdateDebugParsers(){
    RndOverlay* o = RndOverlay::Find("song", true);
    if(o) o->mCallback = this;
    o->mShowing = mDebugParsers.size() > 0;
    o->mTimer.Restart();
}

void Song::SetLoopStart(float f){
    unk5c = f;
    mLoopStart = GetMBTFromFrame(f, 0);
    if(unk60 < f) SetLoopEnd(f);
}

void Song::SetLoopEnd(float f){
    unk60 = f;
    mLoopEnd = GetMBTFromFrame(f, 0);
    if(unk5c > f) SetLoopStart(f);
}

// fn_8035FC14
void Song::SetStateDirty(bool dirty){
    unk7c = dirty;
    DataArrayPtr ptr(DataNode(Symbol(Name())));
//   (**(code **)(*sCallback + 0x18))(sCallback,this,this_00); sCallback->SomeMethod(this, (DataArray*)ptr);
}

void Song::SetSpeed(){
    if(mHxMaster){
        mHxMaster->GetHxAudio()->GetSongStream();
    }
}

void Song::AddSection(Symbol s, float f){
    int idx = GetBeatMap()->BeatToTick(f);
    unk24[idx] = s;
}

BEGIN_CUSTOM_PROPSYNC(MBT)
    SYNC_PROP(m, o.measure)
    SYNC_PROP(b, o.beat)
    SYNC_PROP(t, o.tick)
END_CUSTOM_PROPSYNC

BEGIN_PROPSYNCS(Song)
    SYNC_PROP_SET(song, mSongName, SetSong(_val.Sym()))
    SYNC_PROP_MODIFY(speed, mSpeed, SetSpeed())
    SYNC_PROP_MODIFY_ALT(debug_parsers, mDebugParsers, UpdateDebugParsers())
    SYNC_PROP(loop_start, mLoopStart)
    SYNC_PROP(loop_end, mLoopEnd)
    SYNC_PROP(song_end_frame, mSongEndFrame)
    SYNC_SUPERCLASS(RndAnimatable)
END_PROPSYNCS
