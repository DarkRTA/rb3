#ifndef METABAND_SONGMGR_H
#define METABAND_SONGMGR_H
#include "obj/MsgSource.h"
#include "os/ContentMgr.h"
#include "meta/SongMetadata.h"
#include "utl/CacheMgr.h"
#include "utl/Symbol.h"
#include "utl/BufStream.h"
#include <set>
#include <vector>
#include <hash_map>
#include <map>

class DataLoader;

// from RB2
enum SongMgrState {
    kSongMgr_SaveMount = 0,
    kSongMgr_SaveWrite = 1,
    kSongMgr_SaveUnmount = 2,
    kSongMgr_Ready = 3,
    kSongMgr_Failure = 4,
    kSongMgr_Max = 5,
    kSongMgr_Nil = -1,
};

class SongMgr : public MsgSource, public ContentMgr::Callback {
public:
    SongMgr(){}
    
    virtual DataNode Handle(DataArray*, bool);
    virtual ~SongMgr();
    virtual void Init();
    virtual void Terminate(){}
    virtual SongMetadata* Data(int) const;
    virtual SongInfo* SongAudioData(int) const = 0;
    virtual void ContentStarted();
    virtual bool ContentDiscovered(Symbol);
    virtual void ContentLoaded(class Loader*, ContentLocT, Symbol);
    virtual void ContentDone();
    virtual void ContentMounted(const char*, const char*);
    virtual void ContentUnmounted(const char*);
    virtual void GetContentNames(Symbol, std::vector<Symbol>&) const;
    virtual bool SongCacheNeedsWrite() const;
    virtual void ClearSongCacheNeedsWrite();
    virtual void AllowCacheWrite(bool b){ mSongCacheWriteAllowed = b; }
    virtual void ClearCachedContent();
    virtual Symbol GetShortNameFromSongID(int, bool) const = 0;
    virtual int GetSongIDFromShortName(Symbol, bool) const = 0;
    virtual Symbol SongName(int) const = 0;
    virtual bool CanAddSong() const = 0;
    virtual bool AllowContentToBeAdded(DataArray*, ContentLocT){ return true; }
    virtual void AddSongData(DataArray*, DataLoader*, ContentLocT) = 0;
    virtual void AddSongData(DataArray*, std::map<int, SongMetadata*>&, const char*, ContentLocT, std::vector<int>&) = 0;
    virtual void AddSongIDMapping(int, Symbol) = 0;
    virtual void ReadCachedMetadataFromStream(BinStream&, int) = 0;
    virtual void WriteCachedMetadataFromStream(BinStream&) const = 0;

    bool HasSong(int) const;
    bool HasSong(Symbol, bool) const;

    SongInfo* SongAudioData(Symbol) const;
    
    const char* ContentName(int) const;
    const char* ContentName(Symbol, bool) const;
    bool IsSongCacheWriteDone() const;
    bool IsSongMounted(Symbol) const;
    void ClearFromCache(Symbol);
    void OnCacheMountResult(int);
    void OnCacheWriteResult(int);
    void OnCacheUnmountResult(int);
    int NumSongsInContent(int) const;
    void DumpSongMgrContents(bool);
    void SetState(SongMgrState);
    void StartSongCacheWrite();
    bool SaveCachedSongInfo(BufStream&);
    bool LoadCachedSongInfo(BufStream&);
    int GetCachedSongInfoSize() const;
    const char* GetCachedSongInfoName() const;
    void GetSongsInContent(Symbol, std::vector<int>&) const;

    void SaveWrite();
    void SaveMount();
    void SaveUnmount();

    std::set<int> mAvailableSongs; // 0x20
    std::map<int, SongMetadata*> mUncachedSongMetadata; // 0x38
    SongMgrState mState; // 0x50
    std::map<int, SongMetadata*> mCachedSongMetadata; // 0x54
    std::map<Symbol, std::vector<int> > mSongIDsInContent; // 0x6c
    std::map<int, Symbol> mContentUsedForSong; // 0x84
    std::map<Symbol, String> unkmap5; // 0x9c
    CacheID* mSongCacheID; // 0xb4
    Cache* mSongCache; // 0xb8
    bool unkbc; // 0xbc
    bool mSongCacheNeedsWrite; // 0xbd
    bool mSongCacheWriteAllowed; // 0xbe
};

int GetSongID(DataArray*, DataArray*);
int CountSongsInArray(DataArray*);

#endif // METABAND_SONGMGR_H