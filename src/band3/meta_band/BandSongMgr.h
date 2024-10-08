#ifndef META_BAND_BANDSONGMGR_H
#define META_BAND_BANDSONGMGR_H
#include "system/meta/SongMgr.h"

class BandSongMgr : public SongMgr {
public:
    class SongRanking {
    public:
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
    virtual Symbol SongName(int) const;

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
    static bool GetFakeSongsAllowed();

    int unkc0;
    std::map<int, Symbol> unkc4;
    std::map<Symbol, int> unkdc;
    std::map<int, Symbol> unkf4;
    std::list<SongRanking> unk10c;
    std::list<int> unk114;
    std::vector<int> unk11c;
    bool unk124;
    int unk128; // SongUpgradeMgr*
    int unk12c; // LicenseMgr*
    std::vector<String> unk130;
    int unk138; // max song count
    bool unk13c;
    int unk140;
};

extern BandSongMgr* TheSongMgr;
extern BandSongMgr* TheBaseSongManger;

#endif
