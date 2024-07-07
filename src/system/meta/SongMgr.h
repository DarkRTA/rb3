#ifndef METABAND_SONGMGR_H
#define METABAND_SONGMGR_H
#include "obj/MsgSource.h"
#include "os/ContentMgr.h"
#include "meta/SongMetadata.h"
#include "utl/Symbol.h"
#include <set>
#include <vector>
#include <hash_map>
#include <map>

class DataLoader;

class SongMgr : public MsgSource, public ContentMgr::Callback {
public:
    SongMgr(){}
    
    virtual DataNode Handle(DataArray*, bool);
    virtual ~SongMgr();
    virtual void Init();
    virtual void Terminate();
    virtual SongMetadata* Data(int) const;
    virtual int SongAudioData(int) const = 0;
    virtual void ContentStarted();
    virtual bool ContentDiscovered(Symbol);
    virtual void ContentLoaded(class Loader*, ContentLocT, Symbol);
    virtual void ContentDone();
    virtual void ContentMounted(const char*, const char*);
    virtual void ContentUnmounted(const char*);
    virtual void GetContentNames(Symbol, std::vector<Symbol>&) const;
    virtual bool SongCacheNeedsWrite() const;
    virtual void ClearSongCacheNeedsWrite();
    virtual void AllowCacheWrite(bool);
    virtual void ClearCachedContent();
    virtual Symbol GetShortNameFromSongID(int, bool) const = 0;
    virtual int GetSongIDFromShortName(Symbol, bool) const = 0;
    virtual Symbol SongName(int) const = 0;
    virtual bool CanAddSong() const = 0;
    virtual bool AllowContentToBeAdded(DataArray*, ContentLocT);
    virtual void AddSongData(DataArray*, DataLoader*, ContentLocT) = 0;
    virtual void AddSongData(DataArray*, std::map<int, SongMetadata*>&, const char*, ContentLocT, std::vector<int>&) = 0;
    virtual void AddSongIDMapping(int, Symbol) = 0;
    virtual void ReadCachedMetadataFromStream(BinStream&, int) = 0;
    virtual void WriteCachedMetadataFromStream(BinStream&) const = 0;

    bool HasSong(int) const;
    bool HasSong(Symbol, bool) const;

    void SongAudioData(Symbol) const;
    
    const char* ContentName(int) const;
    const char* ContentName(Symbol, bool) const;
    void IsSongCacheWriteDone() const;
    void IsSongMounted(Symbol) const;

    std::set<int> mAvailableSongs; //
    std::hash_map<const int, Symbol> mUncachedSongMetadata; 
};

int GetSongID(DataArray*, DataArray*);
int CountSongsInArray(DataArray*);

#endif // METABAND_SONGMGR_H