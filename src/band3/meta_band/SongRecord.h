#pragma once
#include "game/Defines.h"
#include "meta_band/BandSongMetadata.h"
#include "obj/Object.h"

class SongRecord : public Hmx::Object {
public:
    SongRecord(const BandSongMetadata *);
    virtual ~SongRecord() {}
    virtual DataNode Handle(DataArray *, bool);

    void UpdateScoreType();
    void UpdateSharedStatus();
    void UpdatePerformanceData();
    bool UpdateReview();
    int GetTier(Symbol) const;
    short GetInstrumentMask(ScoreType) const;
    Symbol GetShortDifficultySym(ScoreType) const;
    int GetScore() const { return mScores[mActiveScoreType]; }
    Symbol GetShortDifficultySym() const {
        return GetShortDifficultySym(mActiveScoreType);
    }

    Symbol mShortName; // 0x1c
    bool unk20;
    bool mDemo; // 0x21
    bool mRestricted; // 0x22
    std::map<Symbol, int> mTier; // 0x24
    ScoreType mActiveScoreType; // 0x3c
    int mScores[11]; // 0x40
    Difficulty mDiffs[11]; // 0x6c
    int mStars[11]; // 0x98
    int mNotesPct[11]; // 0xc4
    short mBandInstrumentMask; // 0xf0
    int mReview; // 0xf4
    int unkf8;
    BandSongMetadata *mData; // 0xfc
};