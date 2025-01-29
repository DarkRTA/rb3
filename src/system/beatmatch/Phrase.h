#pragma once
#include <vector>
#include "utl/Str.h"
#include "beatmatch/TrackType.h"
#include "beatmatch/InternalSongParserSink.h"

struct PhraseInfo {

};

struct Phrase {
    Phrase(float ms, float durms, int tick, int durticks) : mMs(ms), mDurationMs(durms), mTick(tick), mDurationTicks(durticks) {}

    float GetMs() const { return mMs; }
    float GetDurationMs() const { return mDurationMs; }
    int GetTick() const { return mTick; }
    int GetDurationTicks() const { return mDurationTicks; }

    float mMs; // 0x0
    float mDurationMs; // 0x4
    int mTick; // 0x8
    int mDurationTicks; // 0xc
};

struct RawPhrase {
    RawPhrase(int trk, TrackType type, int start, int end, int ind) : track(trk), track_type(type), start_tick(start), end_tick(end), independent(ind), id(-1) {}
    
    int track; // 0x0
    TrackType track_type; // 0x4
    int start_tick; // 0x8
    int end_tick; // 0xc
    int independent; // 0x10
    int id; // 0x14
};

inline bool RawPhraseCmp(const RawPhrase& p1, const RawPhrase& p2){
    return p1.start_tick < p2.start_tick;
}

class PhraseList {
public:
    PhraseList(){}
    void Clear();
    void AddPhrase(float, int, float, int);
    bool IsTickInPhrase(int) const;

    std::vector<Phrase> mPhrases; // 0x0
};

class PhraseListCollection {
public:
    PhraseListCollection();
    ~PhraseListCollection();
    void Clear();
    void AddPhrase(BeatmatchPhraseType, float, int, float, int);

    std::vector<PhraseList*> mPhraseLists; // 0x0
};

class PhraseDB {
public:
    PhraseDB(int);
    ~PhraseDB();
    void Clear();
    void AddPhrase(BeatmatchPhraseType, int, float, int, float, int);
    const PhraseList& GetPhraseList(int, BeatmatchPhraseType) const;

    std::vector<PhraseListCollection*> mPhraseListCollections; // 0x0
};
