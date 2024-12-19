#include "meta/PreloadPanel.h"
#include "meta/SongMgr.h"
#include "os/ContentMgr_Wii.h"
#include "utl/Messages.h"
#include "utl/Symbols.h"

FileCache* PreloadPanel::sCache;

PreloadPanel::PreloadPanel() : mPreloadResult(kPreloadInProgress), mMounted(0), mAppReadFailureHandler(0), unk58(0), unk68(0) {
    if(!sCache) sCache = new FileCache(0x500000, kLoadBack, true);
}

PreloadPanel::~PreloadPanel(){

}

void PreloadPanel::SetTypeDef(DataArray* da){
    if(TypeDef() != da){
        UIPanel::SetTypeDef(da);
#ifdef MILO_DEBUG
        CheckTypeDef("song_mgr");
        CheckTypeDef("current_song");
        CheckTypeDef("on_preload_ok");
        CheckTypeDef("preload_files");
#endif
    }
}

void PreloadPanel::CheckTypeDef(Symbol s){
    if(!TypeDef()->FindArray(s, false)){
        MILO_WARN("PreloadPanel %s missing %s handler (%s)", Name(), s, TypeDef()->File());
    }
}

void PreloadPanel::Load(){
    UIPanel::Load();
    mPreloadResult = kPreloadInProgress;
    TheContentMgr->RegisterCallback(this, false);
    mAppReadFailureHandler = TheContentMgr->SetReadFailureHandler(this);
    MILO_ASSERT(mAppReadFailureHandler, 0x57);
    unk58 = false;
    unk5c = gNullStr;
    Symbol songSym = TypeDef()->FindSym(current_song);
    if(songSym.Null()) MILO_WARN("Trying to preload null song");
    class SongMgr* song_mgr = SongMgr();
    MILO_ASSERT(song_mgr, 0x67);
    mContentNames.clear();
    unk68 = false;
}

inline SongMgr* PreloadPanel::SongMgr() const {
    return TypeDef()->FindArray(song_mgr, true)->Obj<class SongMgr>(1);
}

void PreloadPanel::PollForLoading(){
    UIPanel::PollForLoading();
    if(UIPanel::IsLoaded()){
        if(!mMounted && mContentNames.empty()){
            StartCache();
        }
        if(mPreloadResult == 0 && mMounted && sCache->DoneCaching()){
            if(unk68) mPreloadResult = kPreloadFailure;
            else {
                for(std::vector<String>::iterator it = mPreloadedFiles.begin(); it != mPreloadedFiles.end(); ++it){
                    if(!CheckFileCached(it->c_str())){
                        mPreloadResult = kPreloadFailure;
                    }
                }
            }
            if(mPreloadResult != 2) mPreloadResult = kPreloadSuccess;
        }
    }
}

bool PreloadPanel::IsLoaded() const {
    if(UIPanel::IsLoaded()) return mPreloadResult != kPreloadInProgress;
    else return false;
}

void PreloadPanel::FinishLoad(){
    UIPanel::FinishLoad();
    TheContentMgr->UnregisterCallback(this, true);
    ClearAndShrink(mPreloadedFiles);
    TheContentMgr->SetReadFailureHandler(mAppReadFailureHandler);
}

void PreloadPanel::Unload(){
    mContentNames.clear();
    UIPanel::Unload();
}

void PreloadPanel::ContentMounted(const char* cc, const char*){
    OnContentMountedOrFailed(cc, true);
}

void PreloadPanel::ContentFailed(const char* cc){
    OnContentMountedOrFailed(cc, false);
    MILO_LOG("PreloadPanel: setting fail state because of %s\n", cc);
    mPreloadResult = kPreloadFailure;
}

Symbol PreloadPanel::CurrentSong() const {
    return TypeDef()->FindSym(current_song);
}

void PreloadPanel::StartCache(){
    MILO_ASSERT(mContentNames.empty(), 0x10E);
    mMounted = true;
    MILO_ASSERT(sCache, 0x111);
    sCache->Clear();
    sCache->StartSet(0);
    if(!unk68 && mPreloadResult != 2){
        DataArray* preloadFilesArr = TypeDef()->FindArray(preload_files, true);
        for(int i = 1; i < preloadFilesArr->Size(); i++){
            DataArray* innerArr = preloadFilesArr->Array(i);
            const char* path = innerArr->Str(0);
            MILO_ASSERT(path, 0x11E);
            if(innerArr->Int(1) == 0 || FileExists(DirLoader::CachedPath(path, false), 0)){
                sCache->Add(FilePath(path), 1, FilePath(path));
                mPreloadedFiles.push_back(path);
            }
        }
    }
    sCache->EndSet();
}

void PreloadPanel::OnContentMountedOrFailed(const char* contentName, bool b){
    if(!mContentNames.empty()){
        MILO_ASSERT(contentName, 0x13F);
        bool b1 = false;
        for(std::vector<Symbol>::iterator it = mContentNames.begin(); it != mContentNames.end(); ++it){
            Symbol cur = *it;
            if(cur == contentName){
                mContentNames.erase(it);
                b1 = true;
                break;
            }
        }
        if(b1 && !b){
            TheWiiContentMgr.UnmountContents(contentName);
        }
    }
}

bool PreloadPanel::CheckFileCached(const char* cc){
    if(*cc != '\0' && !sCache->FileCached(cc)){
        MILO_WARN("Could not cache %s", cc);
        return false;
    }
    else return true;
}

DataNode PreloadPanel::OnMsg(const ContentReadFailureMsg& msg){

}

DataNode PreloadPanel::OnMsg(const UITransitionCompleteMsg& msg){
    MILO_ASSERT(mPreloadResult != kPreloadInProgress, 0x174);
    if(mPreloadResult == kPreloadSuccess){
        HandleType(on_preload_ok_msg);
    }
    else {
        if(HandleType(on_preload_failed_msg) == DataNode(kDataUnhandled, 0)){
            MILO_ASSERT(mAppReadFailureHandler, 0x180);
            static ContentReadFailureMsg msg(0, gNullStr);
            msg[0] = unk58;
            msg[1] = unk5c;
            mAppReadFailureHandler->Handle(msg, true);
        }
    }
    mAppReadFailureHandler = nullptr;
    return DataNode(kDataUnhandled, 0);
}

BEGIN_HANDLERS(PreloadPanel)
    HANDLE_MESSAGE(ContentReadFailureMsg)
    HANDLE_MESSAGE(UITransitionCompleteMsg)
    HANDLE_SUPERCLASS(UIPanel)
    HANDLE_CHECK(0x192)
END_HANDLERS