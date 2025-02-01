#include "SongMgr.h"
#include "obj/DataFile.h"
#include "utl/MemStream.h"
#include "utl/Symbols.h"

SongMgr *TheBaseSongManger;
const char *SONG_CACHE_CONTAINER_NAME = "songcache_bb";

int GetSongID(DataArray *main_arr, DataArray *backup_arr) {
    static int sDebugSongID = 99000001;
    int theID = 0;
    main_arr->FindData(song_id, theID, false);
    if (theID == 0 && backup_arr) {
        backup_arr->FindData(song_id, theID, false);
    }
    if (theID == 0) {
        theID = TheBaseSongManger->GetSongIDFromShortName(main_arr->Sym(0), false);
    }
    if (theID == 0) {
        while (TheBaseSongManger->HasSong(sDebugSongID))
            sDebugSongID++;
        theID = sDebugSongID++;
        main_arr->Insert(main_arr->Size(), DataArrayPtr(song_id, theID));
        MILO_LOG(
            "The song %s has an invalid songID, assigning temp id %d.\n",
            main_arr->Sym(0).Str(),
            theID
        );
    }
    return theID;
}

int CountSongsInArray(DataArray *arr) {
    int i = 0;
    int size = arr->Size();
    for (; i < size && arr->Node(i).Type() != kDataArray; i++)
        ;
    return size - i;
}

SongMgr::~SongMgr() {}

void SongMgr::Init() {
    mState = kSongMgr_Nil;
    mSongCacheID = 0;
    mSongCache = 0;
    unkbc = false;
    mSongCacheNeedsWrite = false;
    mSongCacheWriteAllowed = true;
}

#pragma push
#pragma force_active on
inline bool SongMgr::HasSong(int id) const {
    return mAvailableSongs.find(id) != mAvailableSongs.end();
}
#pragma pop

bool SongMgr::HasSong(Symbol s, bool b) const {
    int songid = GetSongIDFromShortName(s, b);
    bool ret = songid != 0;
    if (ret)
        ret = HasSong(songid);
    return ret;
}

SongMetadata *SongMgr::Data(int id) const {
    if (!HasSong(id))
        return 0;
    else {
        std::map<int, SongMetadata *>::const_iterator it = mUncachedSongMetadata.find(id);
        if (it != mUncachedSongMetadata.end())
            return it->second;
        else {
            std::map<int, SongMetadata *>::const_iterator cit =
                mCachedSongMetadata.find(id);
            if (cit != mCachedSongMetadata.end())
                return cit->second;
            else {
                MILO_ASSERT(false, 0x98);
                return 0;
            }
        }
    }
}

void SongMgr::ContentStarted() {
    mAvailableSongs.clear();
    for (std::map<int, SongMetadata *>::iterator it = mCachedSongMetadata.begin();
         it != mCachedSongMetadata.end();
         ++it) {
        it->second->IncrementAge();
    }
    mContentUsedForSong.clear();
}

bool SongMgr::ContentDiscovered(Symbol s) {
    if (SongIDInContent(s)) {
        std::vector<int> vec;
        GetSongsInContent(s, vec);
        for (std::vector<int>::const_iterator vit = vec.begin(); vit != vec.end();
             ++vit) {
            int curInt = *vit;
            std::map<int, SongMetadata *>::iterator found =
                mCachedSongMetadata.find(curInt);
            if (found != mCachedSongMetadata.end()) {
                found->second->ResetAge();
                if (!HasSong(curInt)) {
                    mAvailableSongs.insert(curInt);
                    mContentUsedForSong[curInt] = s;
                    AddSongIDMapping(curInt, Data(curInt)->ShortName());
                }
            }
        }
        return true;
    } else
        return false;
}

void SongMgr::ContentLoaded(Loader *loader, ContentLocT loct, Symbol s) {
    DataLoader *d = dynamic_cast<DataLoader *>(loader);
    MILO_ASSERT(d, 0xEB);
    DataArray *data = d->Data();
    if (data) {
        if (AllowContentToBeAdded(data, loct)) {
            if (!streq(s.mStr, ".")) {
                CacheSongData(data, d, loct, s);
            } else {
                AddSongData(data, d, loct);
            }
        } else {
            std::vector<int> somevecidk;
            int datasize = data->Size();
            for (int i = datasize - CountSongsInArray(data); i < datasize; i++) {
                int songID = GetSongID(data->Array(i), 0);
                std::set<int>::iterator idIt = mAvailableSongs.find(songID);
                if (idIt != mAvailableSongs.end()) {
                    mAvailableSongs.erase(idIt);
                }
                std::map<int, Symbol>::iterator contentIt =
                    mContentUsedForSong.find(songID);
                if (contentIt != mContentUsedForSong.end()) {
                    mContentUsedForSong.erase(contentIt);
                }
            }
            ClearFromCache(s);
            TheContentMgr->UpdateShouldCreateCache();
        }
    } else
        ClearFromCache(s);
}

void SongMgr::ContentDone() {
    if (!unkbc)
        return;
    mSongCacheNeedsWrite = true;
}

void SongMgr::ContentMounted(const char *cc1, const char *cc2) {
    unkmap5[cc1] = cc2;
    if (TheContentMgr->InDiscoveryState()) {
        if (!SongIDInContent(cc1)) {
            std::vector<int> vec;
            mSongIDsInContent[cc1] = vec;
        }
    }
}

void SongMgr::ContentUnmounted(const char *cc) {
    std::map<Symbol, String>::iterator it;
    it = unkmap5.find(cc);
    if (it != unkmap5.end()) {
        unkmap5.erase(it);
    }
}

const char *SongMgr::ContentName(int i) const {
    char buf[128];
    SongMetadata *metadata = Data(i);
    if (metadata) {
        if (metadata->IsOnDisc())
            return 0;
        else {
            const char *filename = metadata->SongBlock()->GetBaseFileName();
            strcpy(buf, filename + 4);
            char *str1 = strchr(buf, '/');
            if (str1 != 0) {
                char *str2 = strchr(str1 + 1, '/');
                if (str2 != 0)
                    *str2 = '\0';
            }
            return MakeString("%s", buf);
        }
    } else
        return 0;
}

SongInfo *SongMgr::SongAudioData(Symbol s) const {
    return SongAudioData(GetSongIDFromShortName(s, true));
}

const char *SongMgr::ContentName(Symbol s, bool b) const {
    return ContentName(GetSongIDFromShortName(s, b));
}

void SongMgr::GetContentNames(Symbol s, std::vector<Symbol> &vec) const {
    const char *cntName = ContentName(s, false);
    if (cntName) {
        Symbol sym = MakeString("%s_song", cntName);
        vec.push_back(sym);
    }
}

bool SongMgr::SongCacheNeedsWrite() const {
    return mSongCacheWriteAllowed && mSongCacheNeedsWrite;
}

bool SongMgr::IsSongCacheWriteDone() const {
    return mState == kSongMgr_Ready || mState == kSongMgr_Failure;
}

bool SongMgr::IsSongMounted(Symbol s) const {
    const char *cntName = ContentName(s, true);
    if (cntName)
        return TheContentMgr->IsMounted(cntName);
    else
        return true;
}

void SongMgr::ClearSongCacheNeedsWrite() { mSongCacheNeedsWrite = false; }

void SongMgr::StartSongCacheWrite() {
    if (SongCacheNeedsWrite()) {
        ClearSongCacheNeedsWrite();
        if (mState == kSongMgr_SaveUnmount && mSongCache) {
            SetState(kSongMgr_SaveWrite);
        } else
            SetState(kSongMgr_SaveMount);
    }
}

int gSongCacheSaveVer = 0xB;

bool SongMgr::SaveCachedSongInfo(BufStream &bs) {
    bs << gSongCacheSaveVer << mSongIDsInContent;
    WriteCachedMetadataFromStream(bs);
    return true;
}

bool SongMgr::LoadCachedSongInfo(BufStream &bs) {
    int rev;
    ClearCachedContent();
    bs >> rev >> mSongIDsInContent;
    ReadCachedMetadataFromStream(bs, rev);
    if (rev < gSongCacheSaveVer)
        ClearCachedContent();
    return true;
}

int SongMgr::GetCachedSongInfoSize() const {
    MemStream ms(false);
    int rev = 0;
    ms << rev;
    ms << mSongIDsInContent;
    WriteCachedMetadataFromStream(ms);
    return ms.Tell();
}

const char *SongMgr::GetCachedSongInfoName() const { return SONG_CACHE_CONTAINER_NAME; }

void SongMgr::ClearCachedContent() {
    mSongIDsInContent.clear();
    for (std::map<int, SongMetadata *>::iterator it = mCachedSongMetadata.begin();
         it != mCachedSongMetadata.end();
         ++it) {
        delete it->second;
    }
    mCachedSongMetadata.clear();
}

void SongMgr::ClearFromCache(Symbol s) {
    std::map<Symbol, std::vector<int> >::iterator it;
    it = mSongIDsInContent.find(s);
    MILO_ASSERT_FMT(it != mSongIDsInContent.end(), "Content %s isn't cached!", s);
    if (it != mSongIDsInContent.end()) {
        mSongIDsInContent.erase(it);
    }
}

void SongMgr::SetState(SongMgrState state) {
    if (mState == state)
        return;
    mState = state;
    switch (mState) {
    case kSongMgr_SaveMount:
        SaveMount();
        break;
    case kSongMgr_SaveWrite:
        SaveWrite();
        break;
    case kSongMgr_SaveUnmount:
        SaveUnmount();
        break;
    default:
        break;
    }
}

void SongMgr::CacheSongData(
    DataArray *arr, DataLoader *loader, ContentLocT loct, Symbol s
) {
    std::vector<int> vec;
    GetSongsInContent(s, vec);
    if (!vec.empty())
        return;
    else {
        std::vector<int> otherIntVec;
        AddSongData(arr, mCachedSongMetadata, ".", loct, otherIntVec);
        std::vector<int> songIDs;
        for (int i = 0; i < arr->Size(); i++) {
            Symbol curSym = arr->Array(i)->Sym(0);
            int songID = GetSongIDFromShortName(curSym, false);
            if (songID != 0)
                songIDs.push_back(songID);
        }
        mSongIDsInContent[s] = songIDs;
        for (std::vector<int>::const_iterator it = otherIntVec.begin();
             it != otherIntVec.end();
             ++it) {
            int id = *it;
            MILO_ASSERT(mContentUsedForSong.find(id) == mContentUsedForSong.end(), 0x2BE);
            mContentUsedForSong[id] = s;
        }
        unkbc = true;
    }
}

void SongMgr::SaveMount() {
    if (!mSongCacheID) {
        mSongCacheID = TheCacheMgr->GetCacheID(SONG_CACHE_CONTAINER_NAME);
    }
    if (mSongCacheID) {
        if (!TheCacheMgr->MountAsync(mSongCacheID, &mSongCache, this)) {
            CacheResult res = TheCacheMgr->GetLastResult();
            if (res == kCache_ErrorBusy)
                SetState(kSongMgr_Ready); // maybe take another look at the cache enums?
            else
                MILO_FAIL("SongMgr: Error %d while mounting.\n", res);
        }
    } else
        SetState(kSongMgr_Ready);
}

void SongMgr::SaveWrite() {
    int size = GetCachedSongInfoSize();
    void *mem = _MemAllocTemp(size, 0);
    BufStream bs(mem, size, true);
    if (SaveCachedSongInfo(bs)) {
        bool ret = mSongCache->WriteAsync(SONG_CACHE_CONTAINER_NAME, mem, size, this);
        MILO_ASSERT(ret, 0x2F2);
    } else {
        MILO_LOG("SongMgr: Failed to save cached song info - write aborted.\n");
        SetState(kSongMgr_Ready);
    }
}

void SongMgr::SaveUnmount() {
    if (mSongCache) {
        if (!TheCacheMgr->UnmountAsync(&mSongCache, this)) {
            CacheResult res = TheCacheMgr->GetLastResult();
            if (res != kCache_ErrorBusy)
                MILO_FAIL("SongMgr: Error %d while unmounting.\n", res);
        }
    } else
        MILO_LOG("SongMgr: Failed to unmount NULL song info cache.\n");
}

void SongMgr::OnCacheMountResult(int i) {
    if (mState != kSongMgr_SaveMount) {
        MILO_LOG("SongMgr: Mount result received in state %d.\n", mState);
    } else if (i != 0) {
        MILO_LOG("SongMgr: Mount result error %d - aborting cache write.\n", i);
        SetState(kSongMgr_Ready);
    } else
        SetState(kSongMgr_SaveWrite);
}

void SongMgr::OnCacheWriteResult(int i) {
    if (mState != kSongMgr_SaveWrite) {
        MILO_LOG("SongMgr: Write result received in state %d.\n", mState);
    } else {
        if (i != 0)
            MILO_LOG("SongMgr: Write result error %d - cache write failed.\n", i);
        SetState(kSongMgr_SaveUnmount);
    }
}

void SongMgr::OnCacheUnmountResult(int i) {
    if (mState != kSongMgr_SaveUnmount) {
        MILO_LOG("SongMgr: Unmount result received in state %d.\n", mState);
    } else {
        if (i != 0)
            MILO_LOG("SongMgr: Unmount result error %d - aborting cache unmount.\n", i);
        unkbc = false;
        mSongCache = 0;
        SetState(kSongMgr_Ready);
    }
}

void SongMgr::GetSongsInContent(Symbol s, std::vector<int> &vec) const {
    std::map<Symbol, std::vector<int> >::const_iterator it = mSongIDsInContent.find(s);
    if (it != mSongIDsInContent.end())
        vec = it->second;
}

int SongMgr::NumSongsInContent(int i) const {
    Symbol key = ContentName(i);
    std::map<Symbol, std::vector<int> >::const_iterator it = mSongIDsInContent.find(key);
    if (it != mSongIDsInContent.end())
        return it->second.size();
    else
        return 0;
}

void SongMgr::DumpSongMgrContents(bool all) {
    MILO_LOG("--------------------\n");
    int idx = 0;
    int skipped = 0;
    MILO_LOG("mAvailableSongs:\n");
    for (std::set<int>::iterator it = mAvailableSongs.begin();
         it != mAvailableSongs.end();
         ++it) {
        int id = *it;
        if (all || id > 1000000) {
            MILO_LOG(" %d. ID: %d\n", idx, id);
        } else
            skipped++;
        idx++;
    }
    if (skipped > 0)
        MILO_LOG(" skipped %d non-DLC songs\n", skipped);
    MILO_LOG(" Total Count: %d\n", idx);
    idx = 0;
    skipped = 0;
    MILO_LOG("mUncachedSongMetadata:\n");
    for (std::map<int, SongMetadata *>::iterator it = mUncachedSongMetadata.begin();
         it != mUncachedSongMetadata.end();
         ++it) {
        SongMetadata *meta = it->second;
        int id = meta->ID();
        if (all || id > 1000000) {
            MILO_LOG(
                " %d. ID: %d, Short Name: %s, Age: %d\n",
                idx,
                meta->ID(),
                meta->ShortName(),
                meta->Age()
            );
        } else
            skipped++;
        idx++;
    }
    if (skipped > 0)
        MILO_LOG(" skipped %d non-DLC songs\n", skipped);
    MILO_LOG(" Total Count: %d\n", idx);
    idx = 0;
    MILO_LOG("mCachedSongMetadata:\n");
    for (std::map<int, SongMetadata *>::iterator it = mCachedSongMetadata.begin();
         it != mCachedSongMetadata.end();
         ++it) {
        SongMetadata *meta = it->second;
        MILO_LOG(
            " %d. ID: %d, Short Name: %s, Age: %d\n",
            idx,
            meta->ID(),
            meta->ShortName(),
            meta->Age()
        );
        idx++;
    }
    MILO_LOG(" Total Count: %d\n", idx);
    idx = 0;
    MILO_LOG("mSongIDsInContent:\n");
    for (std::map<Symbol, std::vector<int> >::iterator it = mSongIDsInContent.begin();
         it != mSongIDsInContent.end();
         ++it) {
        MILO_LOG(" %d. Content: %s\n", idx, it->first);
        idx++;
        for (std::vector<int>::iterator intIt = it->second.begin();
             intIt != it->second.end();
             ++intIt) {
            MILO_LOG("  SongID: %d\n", *intIt);
        }
    }
    MILO_LOG(" Total Count: %d\n", idx);
    MILO_LOG("mContentUsedForSong:\n");
    for (std::map<int, Symbol>::iterator it = mContentUsedForSong.begin();
         it != mContentUsedForSong.end();
         ++it) {
        MILO_LOG(" %d. ID: %d, Content: %s\n", 0, it->first, it->second);
    }
    MILO_LOG(" Total Count: %d\n", 0);
    MILO_LOG("--------------------\n");
}

BEGIN_HANDLERS(SongMgr)
    HANDLE_EXPR(content_name, Symbol(ContentName(_msg->Int(2))))
    HANDLE_EXPR(content_name_from_sym, Symbol(ContentName(_msg->Sym(2), true)))
    HANDLE_EXPR(is_song_mounted, IsSongMounted(_msg->Sym(2)))
    HANDLE_ACTION(clear_from_cache, ClearFromCache(_msg->Sym(2)))
    HANDLE_ACTION(cache_mgr_mount_result, OnCacheMountResult(_msg->Int(2)))
    HANDLE_ACTION(cache_write_result, OnCacheWriteResult(_msg->Int(2)))
    HANDLE_ACTION(cache_mgr_unmount_result, OnCacheUnmountResult(_msg->Int(2)))
    HANDLE_ACTION(allow_cache_write, AllowCacheWrite(_msg->Int(2)))
    HANDLE_EXPR(num_songs_in_content, NumSongsInContent(_msg->Int(2)))
    HANDLE_ACTION(dump_songs, DumpSongMgrContents(false))
    HANDLE_ACTION(dump_all_songs, DumpSongMgrContents(true))
    HANDLE_SUPERCLASS(MsgSource)
    HANDLE_CHECK(0x406)
END_HANDLERS