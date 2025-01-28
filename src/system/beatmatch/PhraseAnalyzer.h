#pragma once
#include "beatmatch/Phrase.h"
#include "os/Debug.h"

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

    PhraseAnalyzer(SongData* sd) : mPerformedAnalysis(0), mPhraseStartWindow(480), mSongData(sd), mNotify(true) {
        MILO_ASSERT(mSongData, 0x3D);
    }

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
    // String mSong; // 0x1c
    bool mNotify; // 0x1c
};