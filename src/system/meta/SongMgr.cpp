#include "SongMgr.h"
#include "utl/MemStream.h"
#include "utl/Symbols.h"

const char* SONG_CACHE_CONTAINER_NAME = "songcache_bb";
int gSongCacheSaveVer = 0xB;

int GetSongID(DataArray*, DataArray*){
    MILO_WARN("The song %s has an invalid songID, assigning temp id %d.\n");
    return 0;
}

int CountSongsInArray(DataArray* arr){
    int i = 0;
    int size = arr->Size();
    for(; i < size && arr->Node(i).Type() != kDataArray; i++);
    return size - i;
}

SongMgr::~SongMgr(){

}

void SongMgr::Init(){
    mState = kSongMgr_Nil;
    mSongCacheID = 0;
    mSongCache = 0;
    unkbc = false;
    mSongCacheNeedsWrite = false;
    mSongCacheWriteAllowed = true;
}

bool SongMgr::HasSong(int id) const {
    return mAvailableSongs.find(id) != mAvailableSongs.end();
}

bool SongMgr::HasSong(Symbol s, bool b) const {
    int songid = GetSongIDFromShortName(s, b);
    bool ret = songid != 0;
    if(ret){
        ret = mAvailableSongs.find(songid) != mAvailableSongs.end();
    }
    return ret;
}

SongMetadata* SongMgr::Data(int) const { return 0; }

void SongMgr::ContentStarted(){
    mAvailableSongs.clear();
    for(std::map<int,SongMetadata*>::iterator it = mCachedSongMetadata.begin(); it != mCachedSongMetadata.end(); it++){
        it->second->mAge++;
    }
    mContentUsedForSong.clear();
}

bool SongMgr::ContentDiscovered(Symbol) {}

void SongMgr::ContentDone(){
    if(!unkbc) return;
    mSongCacheNeedsWrite = true;
}

void SongMgr::ContentMounted(const char*, const char*) {}
void SongMgr::ContentUnmounted(const char*) {}

const char* SongMgr::ContentName(int i) const {
    char buf[128];
    SongMetadata* metadata = Data(i);
    if(metadata){
        if(metadata->IsOnDisc()) return 0;
        else {
            const char* filename = metadata->SongBlock()->GetBaseFileName();
            strcpy(buf, filename+4);
            char* str1 = strchr(buf, '/');
            if(str1 != 0){
                char* str2 = strchr(str1 + 1, '/');
                if(str2 != 0) *str2 = '\0';
            }
            return MakeString("%s", buf);
        }
    }
    else return 0;
}

SongInfo* SongMgr::SongAudioData(Symbol s) const {
    return SongAudioData(GetSongIDFromShortName(s, true));
}

const char* SongMgr::ContentName(Symbol s, bool b) const {
    return ContentName(GetSongIDFromShortName(s, b));
}

void SongMgr::GetContentNames(Symbol s, std::vector<Symbol>& vec) const {
    const char* cntName = ContentName(s, false);
    if(cntName){
        vec.push_back(Symbol(MakeString("%s_song",cntName)));
    }
}

bool SongMgr::SongCacheNeedsWrite() const {
    return mSongCacheWriteAllowed && mSongCacheNeedsWrite;
}

bool SongMgr::IsSongCacheWriteDone() const {
    return mState == kSongMgr_Ready || mState == kSongMgr_Failure;
}

bool SongMgr::IsSongMounted(Symbol s) const {
    const char* cntName = ContentName(s, true);
    if(cntName) return TheContentMgr->IsMounted(cntName);
    else return true;
}

void SongMgr::ClearSongCacheNeedsWrite(){ mSongCacheNeedsWrite = false; }

void SongMgr::StartSongCacheWrite(){
    if(SongCacheNeedsWrite()){
        ClearSongCacheNeedsWrite();
        if(mState == kSongMgr_SaveUnmount && mSongCache){
            SetState(kSongMgr_SaveWrite);
        }
        else SetState(kSongMgr_SaveMount);
    }
}

bool SongMgr::SaveCachedSongInfo(BufStream& bs){
    bs << gSongCacheSaveVer << mSongIDsInContent;
    WriteCachedMetadataFromStream(bs);
    return true;
}

bool SongMgr::LoadCachedSongInfo(BufStream& bs){
    int rev;
    ClearCachedContent();
    bs >> rev >> mSongIDsInContent;
    ReadCachedMetadataFromStream(bs, rev);
    if(rev < gSongCacheSaveVer) ClearCachedContent();
    return true;
}

int SongMgr::GetCachedSongInfoSize() const {
    MemStream ms(false);
    int rev = 0;
    ms << rev << mSongIDsInContent;
    WriteCachedMetadataFromStream(ms);
    return mUncachedSongMetadata.size(); // fix
}

const char* SongMgr::GetCachedSongInfoName() const { return SONG_CACHE_CONTAINER_NAME; }

void SongMgr::ClearCachedContent(){
    mSongIDsInContent.clear();
    for(std::map<int, SongMetadata*>::iterator it = mCachedSongMetadata.begin(); it != mCachedSongMetadata.end(); ++it){
        delete it->second;
    }
    mCachedSongMetadata.clear();
}

void SongMgr::SetState(SongMgrState state){
    if(mState == state) return;
    mState = state;
    switch(mState){
        case kSongMgr_SaveMount: SaveMount(); break;
        case kSongMgr_SaveWrite: SaveWrite(); break;
        case kSongMgr_SaveUnmount: SaveUnmount(); break;
        default: break;
    }
}

void SongMgr::SaveMount(){
    if(!mSongCacheID){
        mSongCacheID = TheCacheMgr->GetCacheID(SONG_CACHE_CONTAINER_NAME);
    }
    if(mSongCacheID){
        if(!TheCacheMgr->MountAsync(mSongCacheID, &mSongCache, this)){
            CacheResult res = TheCacheMgr->GetLastResult();
            if(res == kCache_ErrorBusy) SetState(kSongMgr_Ready); // maybe take another look at the cache enums?
            else MILO_FAIL("SongMgr: Error %d while mounting.\n",res);
        }
    }
    else SetState(kSongMgr_Ready);
}

void SongMgr::SaveWrite(){
    int size = GetCachedSongInfoSize();
    void* mem = _MemAllocTemp(size, 0);
    BufStream bs(mem, size, true);
    if(SaveCachedSongInfo(bs)){
        bool ret = mSongCache->WriteAsync(SONG_CACHE_CONTAINER_NAME, mem, size, this);
        MILO_ASSERT(ret, 0x2F2);
    }
    else {
        MILO_LOG("SongMgr: Failed to save cached song info - write aborted.\n");
        SetState(kSongMgr_Ready);
    }
}

void SongMgr::SaveUnmount(){
    if(mSongCache){
        if(!TheCacheMgr->UnmountAsync(&mSongCache, this)){
            CacheResult res = TheCacheMgr->GetLastResult();
            if(res != kCache_ErrorBusy) MILO_FAIL("SongMgr: Error %d while unmounting.\n", res);
        }
    }
    else MILO_LOG("SongMgr: Failed to unmount NULL song info cache.\n");
}

void SongMgr::OnCacheMountResult(int i){
    if(mState != kSongMgr_SaveMount){
        MILO_LOG("SongMgr: Mount result received in state %d.\n", mState);
    }
    else if(i != 0){
        MILO_LOG("SongMgr: Mount result error %d - aborting cache write.\n", i);
        SetState(kSongMgr_Ready);
    }
    else SetState(kSongMgr_SaveWrite);
}

void SongMgr::OnCacheWriteResult(int i){
    if(mState != kSongMgr_SaveWrite){
        MILO_LOG("SongMgr: Write result received in state %d.\n", mState);
    }
    else if(i != 0){
        MILO_LOG("SongMgr: Write result error %d - cache write failed.\n", i);
        SetState(kSongMgr_SaveUnmount);
    }
}

void SongMgr::OnCacheUnmountResult(int i){
    if(mState != kSongMgr_SaveUnmount){
        MILO_LOG("SongMgr: Unmount result received in state %d.\n", mState);
    }
    else if(i != 0){
        MILO_LOG("SongMgr: Unmount result error %d - aborting cache unmount.\n", i);
        unkbc = false;
        mSongCache = 0;
        SetState(kSongMgr_Ready);
    }
}

void SongMgr::GetSongsInContent(Symbol s, std::vector<int>& vec) const {
    std::map<Symbol, std::vector<int> >::const_iterator it = mSongIDsInContent.find(s);
    if(it != mSongIDsInContent.end()) vec = it->second;
}

int SongMgr::NumSongsInContent(int i) const {
    std::map<Symbol, std::vector<int> >::const_iterator it = mSongIDsInContent.find(Symbol(ContentName(i)));
    if(it != mSongIDsInContent.end()) return it->second.size();
    else return 0;
}

void SongMgr::DumpSongMgrContents(bool all){
    MILO_LOG("--------------------\n");
    int idx = 0;
    int skipped = 0;
    MILO_LOG("mAvailableSongs:\n");
    for(std::set<int>::iterator it = mAvailableSongs.begin(); it != mAvailableSongs.end(); ++it){
        int id = *it;
        if(all || id > 1000000){
            MILO_LOG(" %d. ID: %d\n", idx, id);
        }
        else skipped++;
        idx++;
    }
    if(skipped > 0) MILO_LOG(" skipped %d non-DLC songs\n", skipped);
    MILO_LOG(" Total Count: %d\n", idx);
    idx = 0; skipped = 0;
    MILO_LOG("mUncachedSongMetadata:\n");
    for(std::map<int, SongMetadata*>::iterator it = mUncachedSongMetadata.begin(); it != mUncachedSongMetadata.end(); ++it){
        SongMetadata* meta = it->second;
        int id = meta->ID();
        if(all || id > -1){ // wrong num
            MILO_LOG(" %d. ID: %d, Short Name: %s, Age: %d\n", idx, meta->ID(), meta->ShortName(), meta->Age());
        }
        else skipped++;
        idx++;
    }
    if(skipped > 0) MILO_LOG(" skipped %d non-DLC songs\n", skipped);
    MILO_LOG(" Total Count: %d\n", idx);
    idx = 0;
    MILO_LOG("mCachedSongMetadata:\n");
    for(std::map<int, SongMetadata*>::iterator it = mCachedSongMetadata.begin(); it != mCachedSongMetadata.end(); ++it){
        SongMetadata* meta = it->second;
        MILO_LOG(" %d. ID: %d, Short Name: %s, Age: %d\n", idx, meta->ID(), meta->ShortName(), meta->Age());
        idx++;
    }
    MILO_LOG(" Total Count: %d\n", idx);
    idx = 0;
    MILO_LOG("mSongIDsInContent:\n");
    for(std::map<Symbol, std::vector<int> >::iterator it = mSongIDsInContent.begin(); it != mSongIDsInContent.end(); ++it){
        MILO_LOG(" %d. Content: %s\n", idx, it->first);
        idx++;
        for(std::vector<int>::iterator intIt = it->second.begin(); intIt != it->second.end(); ++intIt){
            MILO_LOG("  SongID: %d\n", *intIt);
        }
    }
    MILO_LOG(" Total Count: %d\n", idx);
    MILO_LOG("mContentUsedForSong:\n");
    for(std::map<int, Symbol>::iterator it = mContentUsedForSong.begin(); it != mContentUsedForSong.end(); ++it){
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