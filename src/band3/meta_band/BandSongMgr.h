#ifndef META_BAND_BANDSONGMGR_H
#define META_BAND_BANDSONGMGR_H
#include "system/meta/SongMgr.h"
#include "meta_band/SongUpgradeMgr.h"
#include "meta_band/LicenseMgr.h"

enum SongID {
    kSongID_Invalid = 0,
    kSongID_Any,
    kSongID_Random
};

class BandSongMgr : public SongMgr {
public:
    class SongRanking {
    public:
        Symbol mInstrument; // 0x0
        std::vector<int> mTierRanges; // 0x4
    };

    BandSongMgr();
    virtual DataNode Handle(DataArray*, bool);
    virtual ~BandSongMgr(){}
    virtual void Init();
    virtual void Terminate();
    virtual SongMetadata* Data(int) const; // fix return type
    virtual SongInfo* SongAudioData(int) const;
    virtual void ContentDone();
    virtual void ContentMounted(const char*, const char*);
    virtual void GetContentNames(Symbol, std::vector<Symbol>&) const;
    virtual bool SongCacheNeedsWrite() const;
    virtual void ClearSongCacheNeedsWrite();
    virtual void AllowCacheWrite(bool);
    virtual void ClearCachedContent();
    virtual Symbol GetShortNameFromSongID(int, bool) const;
    virtual int GetSongIDFromShortName(Symbol, bool) const;
    virtual const char* SongName(int) const;
    virtual bool CanAddSong() const;
    virtual bool AllowContentToBeAdded(DataArray*, ContentLocT);
    virtual void AddSongData(DataArray*, DataLoader*, ContentLocT);
    virtual void AddSongData(DataArray*, std::map<int, SongMetadata*>&, const char*, ContentLocT, std::vector<int>&);
    virtual void AddSongIDMapping(int, Symbol);
    virtual void ReadCachedMetadataFromStream(BinStream&, int);
    virtual void WriteCachedMetadataFromStream(BinStream&) const;
    virtual const char* ContentPattern();
    virtual const char* ContentDir();
    virtual bool HasContentAltDirs();
    virtual const char* ContentAltDirs();

    void AddSongs(DataArray* songs);
    const char* UpgradeMidiFile(int) const;
    const char* MidiFile(Symbol) const;
    const char* SongName(Symbol) const;
    SongUpgradeData* GetUpgradeData(int) const;
    const char* SongFilePath(Symbol, const char*, bool) const;
    const char* GetAlbumArtPath(Symbol) const;
    const char* SongPath(Symbol) const;
    int NumRankTiers(Symbol) const;
    Symbol RankTierToken(int) const;

    static bool GetFakeSongsAllowed();

    mutable DataArraySongInfo* unkc0; // 0xc0
    std::map<int, Symbol> unkc4; // 0xc4
    std::map<Symbol, int> unkdc; // 0xdc
    std::map<int, Symbol> unkf4; // 0xf4
    std::list<SongRanking> mSongRankings; // 0x10c
    std::list<int> unk114; // 0x114
    std::vector<Symbol> unk11c; // 0x11c
    bool unk124; // 0x124
    SongUpgradeMgr* mUpgradeMgr; // 0x128
    LicenseMgr* mLicenseMgr; // 0x12c
    std::vector<String> unk130;
    int mMaxSongCount; // 0x138
    bool unk13c; // 0x13c
    int unk140; // 0x140
};

extern BandSongMgr* TheSongMgr;
extern BandSongMgr* TheBaseSongManger;

#endif
