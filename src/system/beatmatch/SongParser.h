#ifndef BEATMATCH_SONGPARSER_H
#define BEATMATCH_SONGPARSER_H
#include "midi/Midi.h"
#include "beatmatch/InternalSongParserSink.h"
#include "obj/Data.h"
#include "utl/SongInfoCopy.h"
#include "beatmatch/VocalNote.h"
#include "beatmatch/RGChords.h"

enum ReadingState {
    kReadingBeat,
    kReadingNonParts,
    kReadingParts,
    kDoneReading
};

class SongParser : public MidiReceiver {
public:

    class DifficultyInfo {
    public:
    };

    SongParser(InternalSongParserSink&, int, TempoMap*&, MeasureMap*&, int);
    virtual ~SongParser();
    virtual void OnNewTrack(int);
    virtual void OnEndOfTrack();
    virtual void OnAllTracksRead();
    virtual void OnMidiMessage(int, unsigned char, unsigned char, unsigned char);
    virtual void OnText(int, const char*, unsigned char);
    virtual bool OnAcceptMaps(TempoMap*, MeasureMap*);
    virtual void SetMidiReader(MidiReader*);

    void AddReceiver(MidiReceiver*);
    void CheckDrumSubmixes();
    bool TrackAllowsOverlappingNotes(TrackType) const;
    bool CheckDrumMapMarker(int, int, bool);
    bool CheckDrumFillMarker(int, bool);
    bool CheckDrumCymbalMarker(int, int, bool);
    bool CheckForceHopoMarker(int, int, bool);
    bool CheckKeyboardRangeMarker(int, int, bool);
    void OnFillStart(int, unsigned char);
    bool HandlePhraseEnd(int, unsigned char);
    bool HandleFillEnd(int, unsigned char);
    bool HandleRollEnd(int, unsigned char);
    bool HandleTrillEnd(int, unsigned char);
    void OnGemEnd(int, unsigned char);
    void OnCommonPhraseEnd(int);
    void OnSoloPhraseEnd(int);
    void AddPhrase(BeatmatchPhraseType, int, int&, int);
    TempoMap* GetTempoMap();
    void OnFillEnd(int, unsigned char);
    bool CheckFillMarker(int, bool);

    void OnMidiMessageGem(int, unsigned char, unsigned char, unsigned char);
    void OnMidiMessageVocals(int, unsigned char, unsigned char, unsigned char);
    void OnMidiMessageBeat(int, unsigned char, unsigned char, unsigned char);
    void OnMidiMessageRealGuitar(int, unsigned char, unsigned char, unsigned char);
    void OnMidiMessageGemOn(int, unsigned char, unsigned char);
    void OnMidiMessageGemOff(int, unsigned char);
    bool OnMidiMessageCommonOn(int, unsigned char);
    bool OnMidiMessageCommonOff(int, unsigned char);

    int mNumSlots; // 0x8
    int mPlayerSlot; // 0xc
    int mLowVocalPitch; // 0x10
    int mHighVocalPitch; // 0x14
    TempoMap*& mTempoMap; // 0x18
    MeasureMap*& mMeasureMap; // 0x1c
    MidiReader* mMidiReader; // 0x20
    BinStream* mFile; // 0x24 - ref instead of ptr?
    String mFilename; // 0x28
    bool mMerging; // 0x34
    std::vector<MidiReceiver*> mReceivers; // 0x38
    InternalSongParserSink* mSink; // 0x40
    SongInfo* mSongInfo; // 0x44
    DataArray* mTrackNameMapping; // 0x48
    int mNumPlayers; // 0x4c
    int mNumDifficulties; // 0x50
    int mTrack; // 0x54
    int mCurTrackIndex; // 0x58
    int mTrackPartNum; // 0x5c
    int mNextRealTrack; // 0x60
    int mNextFakeTrack; // 0x64
    DataArray* mSubMixes; // 0x68
    DataArray* mRollIntervals; // 0x6c
    DataArray* mTrillIntervals; // 0x70
    std::vector<int> mParts; // 0x74
    std::vector<DifficultyInfo> mDifficultyInfos; // 0x7c
    int mCommonPhraseInProgress; // 0x84
    int mSoloPhraseInProgress; // 0x88
    int mDrumFillInProgress; // 0x8c
    int mRollInProgress; // 0x90
    int mTrillInProgress; // 0x94
    int mPlayerFocusInProgress[2]; // 0x98, 0x9c
    int unka0; // 0xa0
    std::vector<unsigned int> mRollSlotsArray; // 0xa4
    std::vector<std::pair<int, int> > mTrillSlotsArray; // 0xac
    std::vector<RGRollChord> mRGRollArray; // 0xb4
    std::vector<RGTrill> mRGTrillArray; // 0xbc
    int mVocalRangeShiftStartTick; // 0xc4
    int mSoloPhraseEndTick; // 0xc8
    int mDrumFillEndTick; // 0xcc
    int mNumSoloPhrases; // 0xd0
    enum {
        kIgnore = 0,
        kGems = 1,
        kVocalNotes = 2,
        kBeat = 3,
        kUnk4 = 4,
        kRealGuitar = 5
    } mState; // 0xd4
    Symbol mTrackName; // 0xd8
    TrackType mTrackType; // 0xdc
    int mTrackPart; // 0xe0 - PartInfo*
    bool mTrackAllowsHopos; // 0xe4
    int mKeyboardDifficulty; // 0xe8
    int mKeyboardRangeFirstPitch; // 0xec
    int mKeyboardRangeSecondPitch; // 0xf0
    int mKeyboardRangeStartTick; // 0xf4
    float mKeyboardRangeShiftDuration; // 0xf8
    unsigned int mCurrentFillLanes; // 0xfc
    unsigned int mCurrentCymbalSlots; // 0x100
    bool mIgnoreGemDurations; // 0x104
    bool mSeparateParts; // 0x105
    std::list<int> mDrumStyleInstruments; // 0x108
    std::list<int> mVocalStyleInstruments; // 0x110
    bool mDrumStyleGems; // 0x118
    bool mForceDrumStyleGems; // 0x119
    int mSectionStartTick; // 0x11c
    int mSectionEndTick; // 0x120
    std::vector<int> mTrackNames; // 0x124
    bool mLyricPitchSet; // 0x12c
    bool mLyricTextSet; // 0x12d
    bool mLyricBends; // 0x12e
    int mNextLyricTextTick; // 0x130
    String mNextLyric; // 0x134
    VocalNote mCurVocalNote; // 0x140
    VocalNote mPrevVocalNote; // 0x174
    ReadingState mReadingState; // 0x1a8
    int mNumDrumChannels; // 0x1ac
    int mDrumSubmixDifficultyMask; // 0x1b0
    bool mReportedMissingDrumSubmix[4]; // 0x1b4, 0x1b5, 0x1b6, 0x1b7
    int mCodaStartTick; // 0x1b8
    int mCodaEndTick; // 0x1bc
    int mSoloGemDifficultyMask; // 0x1c0
    int mVocalPhraseStartTick; // 0x1c4
    int mLastTambourineGemTick; // 0x1c8
    int mLastTambourineAutoTick; // 0x1cc
    int mLastBeatTick; // 0x1d0
    int mLastBeatType; // 0x1d4
    bool mHaveBeatFailure; // 0x1d8
    int mPartToReadIdx; // 0x1dc
    unsigned char mSoloPitch; // 0x1e0
    int unk1e4; // 0x1e4
    int unk1e8; // 0x1e8
    int unk1ec; // 0x1ec
    int unk1f0; // 0x1f0
    int unk1f4; // 0x1f4
    int unk1f8; // 0x1f8
    int unk1fc; // 0x1fc
    int unk200; // 0x200
    int unk204; // 0x204
    int unk208; // 0x208
    int unk20c; // 0x20c
};

#endif