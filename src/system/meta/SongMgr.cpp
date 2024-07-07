#include "SongMgr.h"
#include "utl/Symbols.h"

const char* SONG_CACHE_CONTAINER_NAME = "songcache_bb";

int GetSongID(DataArray*, DataArray*){

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

bool SongMgr::HasSong(int) const { return false; }
bool SongMgr::HasSong(Symbol, bool) const { return false; }
SongMetadata* SongMgr::Data(int) const { return 0; }
void SongMgr::ContentStarted() {}
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

void SongMgr::OnCacheMountResult(int i){
    if(mState != kSongMgr_SaveMount){
        TheDebug << MakeString("SongMgr: Mount result received in state %d.\n", mState);
    }
    else if(i != 0){
        TheDebug << MakeString("SongMgr: Mount result error %d - aborting cache write.\n", i);
        SetState(kSongMgr_Ready);
    }
    else SetState(kSongMgr_SaveWrite);
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