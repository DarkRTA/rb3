#pragma once
#include "meta/SongMetadata.h"
#include "meta_band/BandSongMgr.h"
#include "os/DateTime.h"

class BandSongMetadata : public SongMetadata {
public:
    BandSongMetadata(BandSongMgr*);
    BandSongMetadata(DataArray*, DataArray*, bool, BandSongMgr*);
    virtual ~BandSongMetadata();
    virtual DataNode Handle(DataArray*, bool);
    virtual void Save(BinStream&);
    virtual void Load(BinStream&);
    virtual bool IsVersionOK() const;

    void InitBandSongMetadata();
    const char* Title() const;
    const char* Artist() const;
    const char* Album() const;
    int AlbumTrackNum() const;
    Symbol Genre() const;
    int LengthMs() const;
    bool HasAlternatePath() const;
    bool MuteWinCues() const;
    const std::map<Symbol, float>& Ranks() const;
    int Rating() const;
    float GuidePitchVolume() const;
    int VocalTonicNote() const;
    int SongKey() const;
    int SongTonality() const;
    float ScrollSpeed() const;
    float TuningOffset() const;
    Symbol VocalPercussionBank() const;
    Symbol DrumKitBank() const;
    bool HasAlbumArt() const;
    bool IsMasterRecording() const;
    Symbol BandFailCue() const;
    int RealGuitarTuning(int) const;
    int RealBassTuning(int) const;
    Symbol Decade() const;
    bool HasPart(Symbol, bool) const;
    float Rank(Symbol) const;
    bool HasVocalHarmony() const;
    bool IsPrivate() const;
    bool IsRanked() const;
    Symbol LengthSym() const;
    Symbol RatingSym() const;
    Symbol SourceSym() const;
    Symbol VocalPartsSym() const;
    Symbol HasProGuitarSym() const;
    bool HasKeys() const;
    bool HasGuitar() const;
    bool HasBass() const;
    Symbol HasKeysSym() const;
    bool HasSolo(Symbol) const;
    Symbol HasSoloSym(Symbol) const;

    static int sBandSaveVer;

    String mTitle; // 0x40
    String mArtist; // 0x4c
    String mAlbum; // 0x58
    short mAlbumTrackNum; // 0x64
    short mRating; // 0x66
    DateTime mDateRecorded; // 0x68
    DateTime mDateReleased; // 0x6e
    Symbol mGenre; // 0x74
    int mAnimTempo; // 0x78
    Symbol mVocalGender; // 0x7c
    int mLengthMs; // 0x80
    int mBasePoints; // 0x84
    std::map<Symbol, float> mRanks; // 0x88
    float mGuidePitchVolume; // 0xa0
    int mVocalTonicNote; // 0xa4
    int mSongKey; // 0xa8
    int mSongTonality; // 0xac
    float mSongScrollSpeed; // 0xb0
    float mTuningOffsetCents; // 0xb4
    Symbol mVocalPercussionBank; // 0xb8
    Symbol mDrumKitBank; // 0xbc
    Symbol mBandFailCue; // 0xc0
    int mRealGuitarTuning[6]; // 0xc4
    int mRealBassTuning[4]; // 0xdc
    std::vector<Symbol> mSolos; // 0xec
    bool mHasAlternatePath; // 0xf4
    bool mIsBonus; // 0xf5
    bool mIsFake; // 0xf6
    bool mIsTutorial; // 0xf7
    bool mMuteWinCues; // 0xf8
    bool mHasAlbumArt; // 0xf9
    bool mIsMasterRecording; // 0xfa
    bool mIsTriFrame; // 0xfb
    bool mHasDiscUpdate; // 0xfc
    BandSongMgr* mSongMgr; // 0x100
};