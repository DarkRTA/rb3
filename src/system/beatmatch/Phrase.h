#ifndef BEATMATCH_PHRASE_H
#define BEATMATCH_PHRASE_H
#include <vector>
#include "utl/Str.h"
#include "beatmatch/TrackType.h"
#include "beatmatch/InternalSongParserSink.h"

struct Phrase {
    Phrase(float ms, float durms, int tick, int durticks) : mMs(ms), mDurationMs(durms), mTick(tick), mDurationTicks(durticks) {}

    float GetMs() const { return mMs; }
    int GetTick() const { return mTick; }
    int GetDurationTicks() const { return mDurationTicks; }

    float mMs; // 0x0
    float mDurationMs; // 0x4
    int mTick; // 0x8
    int mDurationTicks; // 0xc
};

struct RawPhrase {
    RawPhrase(int trk, TrackType type, int start, int end, int ind, int the_id) : track(trk), track_type(type), start_tick(start), end_tick(end), independent(ind), id(the_id) {}
    
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

class PhraseAnalyzer {
public:
    class PhraseData {
    public:
        PhraseData(int, int, int);

        short unk0;
        short unk2; // mTracks?
        short unk4;
        bool mUnison; // 0x6
    };

    void AddInfo(int, TrackType, int, int, bool);
    int NumPhrases() const;
    void Analyze();
    int GetPhraseTracks(int) const;
    bool IsUnisonPhrase(int) const;
    const std::vector<RawPhrase>& GetRawPhrases() const;
    int NumPhrases(int) const;
    void SetPhraseIDs(int, int, int, int);

    bool mPerformedAnalysis; // 0x0
    int mPhraseStartWindow; // 0x4
    std::vector<PhraseData> mPhrases; // 0x8
    std::vector<RawPhrase> mRawPhrases; // 0x10
    class SongData* mSongData; // 0x18
    String mSong; // 0x1c
    bool mNotify; // 0x28
};

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

#endif