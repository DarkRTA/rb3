#pragma once
#include "beatmatch/TrackType.h"
#include "midi/Midi.h"
#include "beatmatch/InternalSongParserSink.h"
#include "beatmatch/BeatMatchUtl.h"
#include "obj/Data.h"
#include "os/Timer.h"
#include "utl/BinStream.h"
#include "utl/SongInfoCopy.h"
#include "beatmatch/VocalNote.h"
#include "beatmatch/RGChords.h"
#include "beatmatch/GemInfo.h"
#include "utl/MBT.h"

enum ReadingState {
    kReadingBeat,
    kReadingNonParts,
    kReadingParts,
    kDoneReading
};

struct PartInfo {
    PartInfo(Symbol s1, BeatmatchAudioType i1, TrackType i2, Symbol s2)
        : part(s1), audio_type(i1), original_name(s2), audio_track_num(AudioTrackNum(-1)),
          type(i2), song_data_track(-1), overwritten(false) {}

    bool ContainsTrackName(const char *track_name) const {
        const char *orig = original_name.mStr;
        int origlen = strlen(orig);
        if (strlen(track_name) > origlen + 2)
            return false;
        else
            return strneq(orig, track_name, origlen);
    }
    bool operator==(const PartInfo &info) const {
        return original_name == info.original_name;
    }

    bool NoSongDataTrack() const { return song_data_track == -1; }
    bool FakeAudio() const { return audio_type == kAudioFake; }

    Symbol part; // 0x0
    BeatmatchAudioType audio_type; // 0x4
    Symbol original_name; // 0x8
    AudioTrackNum audio_track_num; // 0xc
    TrackType type; // 0x10
    int song_data_track; // 0x14
    bool overwritten; // 0x18
};

class SongParser : public MidiReceiver {
public:
    class GemInProgress {
    public:
        GemInProgress(int tick = -1, int players = 0, unsigned int cymbalslots = 28)
            : mTick(tick), mPlayers(players), mCymbalSlots(cymbalslots) {}

        void SetNegTick(int tick) {
            mTick = -tick;
            mPlayers = 0;
        }

        int mTick; // 0x0
        int unk4; // 0x4
        int mPlayers; // 0x8
        unsigned int mCymbalSlots; // 0xc
    };

    class RGGemInfo {
    public:
        RGGemInfo(int tick = -1, int players = 0, int fret = 0, int channel = 0)
            : mGem(tick, players, 28), mFret(fret), mChannel(channel), unk18(-1) {}

        GemInProgress mGem; // 0x0
        int mFret; // 0x10
        int mChannel; // 0x14
        int unk18; // 0x18
    };

    // size: 0x13C holy moly
    class DifficultyInfo {
    public:
        DifficultyInfo(int num_gems)
            : mActivePlayers(0), mForceHopoOnStart(-1), mForceHopoOnEnd(-1),
              mForceHopoOffStart(-1), mForceHopoOffEnd(-1), mRGArpeggioStartTick(-1),
              unkc8(-1), mRGAreaStrumType(kRGNoStrum), mRGAreaStrumStartTick(-1),
              mRGAreaStrumEndTick(-1), mRGLooseStrumStartTick(-1),
              mRGLooseStrumEndTick(-1), mRGChordTextTick(-1), mRGChordNumsStartTick(-1),
              mRGChordNumsEndTick(-1), mRGLeftHandSlideStartTick(-1),
              mRGLeftHandSlideEndTick(-1) {
            mGemsInProgress.reserve(num_gems);
            for (int i = 0; i < num_gems; i++)
                mGemsInProgress.push_back(GemInProgress());
        }

        std::vector<GemInProgress> mGemsInProgress; // 0x0
        bool mActivePlayers; // 0x8
        int mForceHopoOnStart; // 0xc
        int mForceHopoOnEnd; // 0x10
        int mForceHopoOffStart; // 0x14
        int mForceHopoOffEnd; // 0x18

        // RG string info?
        RGGemInfo mRGGemsInfo[6]; // 0x1c, 0x38, 0x54, 0x70, 0x8c, 0xa8

        int mRGArpeggioStartTick; // 0xc4
        int unkc8, unkcc;

        RGStrumType mRGAreaStrumType; // 0xd0
        int mRGAreaStrumStartTick; // 0xd4
        int mRGAreaStrumEndTick; // 0xd8
        int mRGLooseStrumStartTick; // 0xdc
        int mRGLooseStrumEndTick; // 0xe0
        char mRGChordText[64]; // 0xe4
        int mRGChordTextTick; // 0x124
        int mRGChordNumsStartTick; // 0x128
        int mRGChordNumsEndTick; // 0x12c
        int mRGLeftHandSlideStartTick; // 0x130
        int mRGLeftHandSlideEndTick; // 0x134
        bool mRGFlipSlideDirection; // 0x138
    };

    SongParser(InternalSongParserSink &, int, TempoMap *&, MeasureMap *&, int);
    virtual ~SongParser() {}
    virtual void OnNewTrack(int);
    virtual void OnEndOfTrack();
    virtual void OnAllTracksRead();
    virtual void OnMidiMessage(int, unsigned char, unsigned char, unsigned char);
    virtual void OnText(int, const char *, unsigned char);
    virtual bool OnAcceptMaps(TempoMap *, MeasureMap *);
    virtual void SetMidiReader(MidiReader *);

    void ReadMidiFile(BinStream &, const char *, SongInfo *);
    void MergeMidiFile(BinStream &, const char *);
    void AddReceiver(MidiReceiver *);
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
    void AddPhrase(BeatmatchPhraseType, int, int &, int);
    TempoMap *GetTempoMap();
    void OnFillEnd(int, unsigned char);
    bool CheckFillMarker(int, bool);
    void AnalyzeTrackList();
    void InitReadingState();
    void UpdateReadingState();
    void Poll();
    void Reset();
    void SetNumPlayers(int);
    bool CheckRollMarker(int, int, bool);
    bool CheckTrillMarker(int, bool);
    int PitchToSlot(int, int &, int) const;
    bool OnTrackName(int, const char *);
    bool ShouldReadTrack(Symbol);
    bool IsPartTrackName(const char *, const char **) const;
    void PrepareTrack(const char *, PartInfo *);
    PartInfo *UsePartTrack(const char *);
    int PartNumThatMatchesTrackName(const char *) const;
    void SetSectionBounds(int, int);
    NoStrumState GetNoStrumState(int, DifficultyInfo &);
    unsigned int ComputeSlots(int, int, int, std::vector<GemInProgress> &);
    bool ParseAndStripLyricText(const char *, VocalNote &);
    void ParseText(int, const char *);
    void ParseRGText(int, const char *);

    void HandlePitchOffsetCC(int, unsigned char);
    void StartVocalNote(int, unsigned char, const char *);
    void EndVocalNote(int);

    void OnMidiMessageGem(int, unsigned char, unsigned char, unsigned char);
    void OnMidiMessageVocals(int, unsigned char, unsigned char, unsigned char);
    void OnMidiMessageBeat(int, unsigned char, unsigned char, unsigned char);
    void OnMidiMessageRealGuitar(int, unsigned char, unsigned char, unsigned char);
    void OnMidiMessageRealGuitarOn(int, unsigned char, unsigned char, unsigned char);
    void OnMidiMessageRealGuitarOff(int, unsigned char, unsigned char, unsigned char);
    void OnMidiMessageGemOn(int, unsigned char, unsigned char);
    void OnMidiMessageGemOff(int, unsigned char);
    bool OnMidiMessageCommonOn(int, unsigned char);
    bool OnMidiMessageCommonOff(int, unsigned char);

    int RGGetDifficultyLevel(unsigned char);
    bool HandleRGHandPos(unsigned char, unsigned char);
    bool HandleRGRootNote(unsigned char);
    bool HandleRGChordNaming(int, unsigned char);
    bool HandleRGEnharmonic(int, unsigned char);
    bool HandleRGSlashes(int, unsigned char);
    bool HandleRGChordMarkup(int, unsigned char);
    bool HandleRGRollStart(int, unsigned char, unsigned char);
    bool HandleRGTrillStart(int, unsigned char, unsigned char);
    bool HandleRGHopoStart(int, DifficultyInfo &, unsigned char, unsigned char);
    bool HandleRGGemStart(
        int, DifficultyInfo &, unsigned char, unsigned char, unsigned char, int
    );
    bool HandleRGArpeggioStart(int, DifficultyInfo &, unsigned char);
    bool HandleRGAreaStrumStart(int, DifficultyInfo &, unsigned char, unsigned char);
    bool HandleRGLooseStrumStart(int, DifficultyInfo &, unsigned char);
    bool HandleRGChordNumsStart(int, DifficultyInfo &, unsigned char);
    bool HandleRGLeftHandSlide(int, DifficultyInfo &, unsigned char, unsigned char);
    bool HandleRGChordNamingStop(int, unsigned char);
    bool HandleRGEnharmonicStop(int, unsigned char);
    bool HandleRGSlashesStop(int, unsigned char);
    bool HandleRGChordMarkupStop(int, unsigned char);
    bool HandleRGRollStop(int, unsigned char);
    bool HandleRGTrillStop(int, unsigned char);
    bool HandleRGLooseStrumStop(int, DifficultyInfo &, unsigned char);
    bool HandleRGAreaStrumStop(int, DifficultyInfo &, unsigned char, unsigned char);
    bool HandleRGHopoStop(int, DifficultyInfo &, unsigned char, unsigned char);
    bool HandleRGGemStop(int, DifficultyInfo &, unsigned char, int);
    bool HandleRGArpeggioStop(int, DifficultyInfo &, unsigned char, int);
    bool HandleRGChordNumsStop(int, DifficultyInfo &, unsigned char);
    bool HandleRGLeftHandSlideStop(int, DifficultyInfo &, unsigned char);
    bool AudioTrackUsed(SongInfoAudioType);

    const char *PrintTick(int tick) const { return TickFormat(tick, *mMeasureMap); }

    unsigned char GetFret(unsigned char pitch) const { return pitch - 100; }

    bool IsOverdrive(int pitch) const { return pitch == 116; }
    bool IsSolo(int pitch) const { return pitch == mSoloPitch; }
    bool IsInSection(int tick) const {
        bool b2 = true;
        if (mSectionStartTick != -1) {
            bool b1 = false;
            if (tick >= mSectionStartTick && tick < mSectionEndTick) {
                b1 = true;
            }
            if (!b1)
                b2 = false;
        }
        return b2;
    }
    bool NoMidiReader() const { return !mMidiReader; }

    int mNumSlots; // 0x8
    int mPlayerSlot; // 0xc
    int mLowVocalPitch; // 0x10
    int mHighVocalPitch; // 0x14
    TempoMap *&mTempoMap; // 0x18
    MeasureMap *&mMeasureMap; // 0x1c
    MidiReader *mMidiReader; // 0x20
    BinStream *mFile; // 0x24
    String mFilename; // 0x28
    bool mMerging; // 0x34
    std::vector<MidiReceiver *> mReceivers; // 0x38
    InternalSongParserSink *mSink; // 0x40
    SongInfo *mSongInfo; // 0x44
    DataArray *mTrackNameMapping; // 0x48
    int mNumPlayers; // 0x4c
    int mNumDifficulties; // 0x50
    int mTrack; // 0x54
    int mCurTrackIndex; // 0x58
    int mTrackPartNum; // 0x5c
    int mNextRealTrack; // 0x60
    int mNextFakeTrack; // 0x64
    DataArray *mSubMixes; // 0x68
    DataArray *mRollIntervals; // 0x6c
    DataArray *mTrillIntervals; // 0x70
    std::vector<PartInfo> mParts; // 0x74
    std::vector<DifficultyInfo> mDifficultyInfos; // 0x7c
    int mCommonPhraseInProgress; // 0x84
    int mSoloPhraseInProgress; // 0x88
    int mDrumFillInProgress; // 0x8c
    int mRollInProgress; // 0x90
    int mTrillInProgress; // 0x94
    int mPlayerFocusInProgress[2]; // 0x98, 0x9c
    unsigned char mTrillMask; // 0xa0
    unsigned char mRollMask; // 0xa1
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
        kEvents = 4,
        kRealGuitar = 5
    } mState; // 0xd4
    Symbol mTrackName; // 0xd8
    TrackType mTrackType; // 0xdc
    PartInfo *mTrackPart; // 0xe0
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
    std::list<TrackType> mDrumStyleInstruments; // 0x108
    std::list<TrackType> mVocalStyleInstruments; // 0x110
    bool mDrumStyleGems; // 0x118
    bool mForceDrumStyleGems; // 0x119
    int mSectionStartTick; // 0x11c
    int mSectionEndTick; // 0x120
    std::vector<Symbol> mTrackNames; // 0x124
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
    int mRGHandPos; // 0x1e4
    int mRGRootNote; // 0x1e8
    int unk1ec; // 0x1ec
    int unk1f0; // 0x1f0
    int unk1f4; // 0x1f4
    int mRGSlashesStartTick; // 0x1f8
    int mRGSlashesEndTick; // 0x1fc
    int mRGChordNamingStartTick; // 0x200
    int mRGChordNamingEndTick; // 0x204
    int mRGEnharmonicStartTick; // 0x208
    int mRGEnharmonicEndTick; // 0x20c
};

class MidiTrackLister : public MidiReceiver {
public:
    MidiTrackLister(std::vector<Symbol> &, BinStream &);
    virtual ~MidiTrackLister();
    virtual void OnNewTrack(int) {}
    virtual void OnEndOfTrack() {}
    virtual void OnAllTracksRead() {}
    virtual void OnMidiMessage(int, unsigned char, unsigned char, unsigned char) {}
    virtual void OnText(int, const char *, unsigned char);

    void FillTrackList(std::vector<Symbol> &, BinStream &);

    std::vector<Symbol> *unk8; // 0x8
};

extern Timer gSongLoadTimer;