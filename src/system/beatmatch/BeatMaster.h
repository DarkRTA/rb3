#ifndef BEATMATCH_BEATMASTER_H
#define BEATMATCH_BEATMASTER_H
#include "beatmatch/BeatMasterSink.h"
#include "beatmatch/SongParserSink.h"
#include "beatmatch/HxMaster.h"
#include "beatmatch/SongPos.h"

class MasterAudio;
class MidiParserMgr;
class SongInfo;
class PlayerTrackConfigList;
class BeatMasterLoader;

class BeatMaster : public SongParserSink, public HxMaster {
public:
    BeatMaster(SongData*, int);
    virtual ~BeatMaster();
    virtual void AddTrack(int, Symbol, SongInfoAudioType, TrackType, bool);
    virtual void AddMultiGem(int, const GameGem&){}
    virtual void AddPhrase(BeatmatchPhraseType, int, const Phrase&){}
    virtual void Poll(float);
    virtual void Jump(float);
    virtual void Reset();
    virtual class HxAudio* GetHxAudio();
    virtual float SongDurationMs();

    void RegisterSink(BeatMasterSink&);
    void HandleBeatCallback(Symbol);

    bool mRecording; // 0x8
    SongData* mSongData; // 0xc
    std::vector<BeatMasterSink*> mSinks; // 0x10
    MasterAudio* mAudio; // 0x18
    MidiParserMgr* mMidiParserMgr; // 0x1c
    SongInfo* mSongInfo; // 0x20
    PlayerTrackConfigList* mPtCfg; // 0x24
    BeatMasterLoader* mLoader; // 0x28
    bool mLoaded; // 0x2c
    bool unk2d; // 0x2d
    SongPos mSongPos; // 0x30
    SongPos mLastSongPos; // 0x44
    std::vector<int> mSubmixIdxs; // 0x58
    DataArray* mHandlers; // 0x60
};

#endif