#ifndef BEATMATCH_PHRASE_H
#define BEATMATCH_PHRASE_H
#include <vector>
#include "utl/Str.h"
#include "beatmatch/TrackType.h"

struct Phrase {
    float mMs;
    float mDurationMs;
    int mTick;
    int mDurationTicks;
};

struct RawPhrase {
    RawPhrase(int trk, TrackType type, int start, int end, int ind, int the_id) : track(trk), track_type(type), start_tick(start), end_tick(end), independent(ind), id(the_id) {

    }
    
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

#endif