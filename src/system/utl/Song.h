#pragma once
#include "obj/Data.h"
#include "obj/Dir.h"
#include "obj/Object.h"
#include "rndobj/Anim.h"
#include "rndobj/Overlay.h"
#include "midi/Midi.h"
#include "utl/MBT.h"
#include "beatmatch/HxMaster.h"
#include "beatmatch/HxSongData.h"
#include <map>

class HxSongData;
class HxMaster;

class SongCallback {
public:
    SongCallback() {}
    virtual ~SongCallback() {}
    virtual void SongSetFrame(class Song *, float) = 0;
    virtual ObjectDir *SongMainDir() = 0;
    virtual void SongPlay(bool) = 0;
    virtual void UpdateObject(const Hmx::Object *, DataArray *) = 0;
    virtual void Preload() = 0;
    virtual void ProcessBookmarks(DataNode) = 0;
};

class Song : public RndAnimatable, public MidiReceiver, public RndOverlay::Callback {
public:
    Song();
    OBJ_CLASSNAME(Song);
    OBJ_SET_TYPE(Song);
    virtual DataNode Handle(DataArray *, bool);
    virtual bool SyncProperty(DataNode &, DataArray *, int, PropOp);
    virtual void Save(BinStream &);
    virtual void Copy(const Hmx::Object *, Hmx::Object::CopyType);
    virtual void Load(BinStream &);
    virtual ~Song();
    virtual void SetFrame(float frame, float blend);
    virtual float EndFrame();

    virtual float UpdateOverlay(RndOverlay *, float);
    virtual void OnNewTrack(int) {}
    virtual void OnEndOfTrack() {}
    virtual void OnAllTracksRead() {}
    virtual void OnMidiMessage(int, unsigned char, unsigned char, unsigned char) {}
    virtual void OnText(int, const char *, unsigned char);
    virtual DataNode OnMBTFromSeconds(const DataArray *);
    virtual void CreateSong(Symbol, DataArray *, HxSongData **, HxMaster **);

    void Unload();
    void Load();
    float GetBeat();
    void LoadSong();
    TempoMap *GetTempoMap();
    BeatMap *GetBeatMap();
    MeasureMap *GetMeasureMap();
    void SyncState();
    void SetStateDirty(bool);
    MBT GetMBTFromFrame(float, int *);
    MBT GetMBTFromTick(int, int *);
    ObjectDir *MainDir() const;
    void SetLoopStart(float);
    void SetLoopEnd(float);
    void JumpTo(int);
    void JumpTo(Symbol);
    void Play();
    void Pause();
    void SetSong(Symbol);
    void AddSection(Symbol, float);
    void UpdateDebugParsers();
    void SetSpeed();

    DataNode GetBookmarks();
    DataNode GetMidiParsers();

    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    static SongCallback *sCallback;

    HxMaster *mHxMaster; // 0x1c
    HxSongData *mHxSongData; // 0x20
    std::map<int, Symbol> unk24; // 0x24
    ObjPtrList<Hmx::Object> mDebugParsers; // 0x3c
    Symbol mSongName; // 0x4c
    Symbol unk50; // 0x50
    float mSongEndFrame; // 0x54
    float mSpeed; // 0x58
    Vector2 unk5c; // 0x5c - loop start and end points
    MBT mLoopStart; // 0x64
    MBT mLoopEnd; // 0x70
    bool unk7c; // 0x7c
};
