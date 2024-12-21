#include "os/ContentMgr.h"
#include "os/ContentMgr_Wii.h"
#include "meta/SongMgr.h"
#include "obj/Dir.h"
#include "utl/Symbols.h"

const char* gContentStateName[11] = {
    "kUnmounted", "kNeedsMounting", "kMounting", "kUnmounting", "kMounted",
    "kAlwaysMounted", "kNeedsBackup", "kBackingUp", "kContentDeleting", "kDeleted", "kFailed"
};

void ContentMgr::Init(){
    SetName("content_mgr", ObjectDir::Main());
    mDirty = true;
    mRootLoaded = 0;
    mState = kDone;
    mReadFailureHandler = 0;
    mCreateSongCache = false;
}

void ContentMgr::ContentRecurseCallback(const char* c1, const char* c2){
    TheContentMgr->AddCallbackFile(c1, c2);
}

void ContentMgr::AddCallbackFile(const char* cc1, const char* cc2){
    const char* fp = MakeString("%s/%s", cc1, cc2);
    mCallbackFiles.push_back(CallbackFile(fp, mCallback, mLocation, mName.c_str()));
}

#pragma push
#pragma force_active on
inline bool ContentMgr::RefreshDone() const { return mState == kDiscoveryEnumerating; }

inline bool ContentMgr::RefreshInProgress(){
    return (u32)mState > 7 || !((1 << mState) & 0xC3U);
}
#pragma pop

void ContentMgr::PollRefresh(){
    if(mState == 3 || mState - 6U <= 1){
        if(PollContents()) return;
        if(mState == 3){
            for(std::list<Callback*>::iterator it = mCallbacks.begin(); it != mCallbacks.end(); ++it){
                (*it)->ContentAllMounted();
            }
            mState = kDiscoveryCheckIfDone; // 4
        }
        else mState = kDiscoveryEnumerating; // 1
    }
    if(mState == 4){
        if(mLoader){
            if(!mLoader->IsLoaded()) return;
            mCallback->ContentLoaded(mLoader, mLocation, mName.c_str());
            RELEASE(mLoader);
        }
        else {
            if(mCallbackFiles.empty()){
                for(std::list<Content*>::iterator it = mContents.begin(); it != mContents.end(); ++it){
                    Content::State curState = (*it)->GetState();
                    // this line right here officer
                    
                    if (curState == 5) {
                        if (mRootLoaded <= 0) {
                            continue;
                        }
                    } else if (curState != 4) {
                        continue;
                    }
                    
                    for(std::list<Callback*>::iterator it2 = mCallbacks.begin(); it2 != mCallbacks.end(); ++it2){
                        mCallback = *it2;
                        mLocation = (*it)->Location();
                        mName = (*it)->FileName();
                        if((*it2)->ContentDir()){
                            String pathStr(FileMakePath((*it)->Root(), (*it2)->ContentDir(), 0));
                            String makeStr(MakeString("%s/%s", pathStr, (*it2)->ContentPattern()));
                            if(mLocation == 0 || mLocation == 1){
                                WiiContent* wc = dynamic_cast<WiiContent*>(*it);
                                if(wc){
                                    gCurContentName = (*it)->Root();
                                    wc->Enumerate("/", ContentRecurseCallback, true, (*it2)->ContentPattern());
                                }
                            }
                            else {
                                FileEnumerate(pathStr.c_str(), ContentRecurseCallback, false, makeStr.c_str(), false);
                            }
                        }
                        if((*it2)->HasContentAltDirs()){
                            std::vector<String>* altDirs = (*it2)->ContentAltDirs();
                            const char* pattern = (*it2)->ContentPattern();
                            for(std::vector<String>::iterator dirIt = altDirs->begin(); dirIt != altDirs->end(); ++dirIt){
                                DataArray* cfg = SystemConfig("net", "game");
                                const char* codeStr = cfg->FindStr("code");
                                if(mName.contains(MakeString("%s/", codeStr)) && !mName.contains("_song")){
                                    AddCallbackFile("dlc/content/songs", "songs.dta");
                                }
                                else {
                                    String pathStr(FileMakePath((*it)->Root(), dirIt->c_str(), 0));
                                    String makeStr(MakeString("%s/%s", pathStr, pattern));
                                    FileEnumerate(pathStr.c_str(), ContentRecurseCallback, false, makeStr.c_str(), false);
                                }
                            }
                        }
                    }
                    if(curState == 5) mRootLoaded--;
                }
            }
        }
        if(!mCallbackFiles.empty()){
            MILO_ASSERT(mLoader == NULL, 0x127);
            mCallback = mCallbackFiles.front().unkc;
            mLocation = mCallbackFiles.front().unk10;
            mName = mCallbackFiles.front().unk14;
            mCallbackFiles.front().unk0.c_str(); // assert?
            mLoader = TheLoadMgr.AddLoader(mCallbackFiles.front().unk0, kLoadFront);
            mCallbackFiles.pop_front();
            MILO_ASSERT(mLoader, 0x130);
        }
        else mState = kMounting; // 5
    }
    else if(mState == 5){
        mState = kDiscoveryEnumerating; // 1
        {
            std::map<Symbol, Content*> contentMap;
            for(std::list<Content*>::iterator it = mContents.begin(); it != mContents.end(); ++it){
                contentMap[(*it)->FileName()] = *it;
            }
            for(std::list<Content*>::iterator it = mContents.begin(); it != mContents.end(); ++it){
                std::vector<int> songContentVec;
                Symbol filename = (*it)->FileName();
                if(!strstr(filename.mStr, "_song")){
                    TheBaseSongManger->GetSongsInContent(filename, songContentVec);
                    if(!songContentVec.empty()){
                        char buf[64];
                        sprintf(buf, "%s_song", filename.mStr);
                        if(contentMap.find(buf) == contentMap.end()){
                            MILO_LOG("CM: Error: found %s but not %s\n", filename.mStr, buf);
                            (*it)->Delete();
                        }
                    }
                }
            }
        }
        if(CanRefreshOnDone() && IsDirty()){
            for(std::list<Callback*>::iterator it = mCallbacks.begin(); it != mCallbacks.end(); ++it){
                (*it)->ContentCancelled();
            }
            StartRefresh();
        }
        if(!RefreshInProgress()){
            for(std::list<Callback*>::iterator it = mCallbacks.begin(); it != mCallbacks.end(); ++it){
                (*it)->ContentDone();
            }
        }
    }
}

// in retail this also appears to take a bool
Content* ContentMgr::FindFirstContent(Content::State state){
    for(std::list<Content*>::iterator it = mContents.begin(); it != mContents.end(); ++it){
        if(state == (*it)->GetState()) return *it;
    }
    return nullptr;
}

bool ContentMgr::PollContents(){
    Content* theContent = FindFirstContent(Content::kMounting);
    if(!theContent){
        theContent = FindFirstContent(Content::kNeedsMounting);
        if(theContent && InDiscoveryState() && mCreateSongCache){
            theContent->Unmount();
            NotifyFailed(theContent);
            return true;
        }
    }
    if(theContent){
        Content::State prevState = theContent->GetState();
        theContent->Poll();
        Content::State newState = theContent->GetState();
        if(newState == 10){
            MILO_LOG("CM: content operation failed!\n");
            NotifyFailed(theContent);
            if(mState == 7){
                theContent->Unmount();
            }
            else if(mState == 3){
                mContents.remove(theContent);
            }
        }
        else if(newState == 4 && prevState == 2){
            NotifyMounted(theContent);
        }
        else if(newState == 0 && prevState == 4){
            NotifyUnmounted(theContent);
        }
        else if(newState == 9 && prevState == 8){
            NotifyDeleted(theContent);
        }
        return true;
    }
    else return false;
}

void ContentMgr::RegisterCallback(Callback* cb, bool midRefreshAllowed){
    MILO_ASSERT(midRefreshAllowed || !RefreshInProgress(), 0x1DC);
    mCallbacks.push_back(cb);
}

void ContentMgr::UnregisterCallback(Callback* cb, bool midRefreshAllowed){
    MILO_ASSERT(midRefreshAllowed || !RefreshInProgress(), 0x1E2);
    mCallbacks.remove(cb);
}

Hmx::Object* ContentMgr::SetReadFailureHandler(Hmx::Object* o){
    Hmx::Object* oldhandler = mReadFailureHandler;
    mReadFailureHandler = o;
    return oldhandler;
}

DataNode ContentMgr::OnAddContent(DataArray* da){
    OnRemoveContent(da);
    unk34.push_back(String(da->Str(2)));
    return 0;
}

DataNode ContentMgr::OnRemoveContent(DataArray* da){
    mDirty = true;
    for(std::list<String>::iterator it = unk34.begin(); it != unk34.end(); it){
        if(streq((*it).c_str(), da->Str(2))){
            it = unk34.erase(it);
        }
        else ++it;
    }
    return 0;
}

BEGIN_HANDLERS(ContentMgr)
    HANDLE_ACTION(start_refresh, StartRefresh())
    HANDLE_EXPR(refresh_done, RefreshDone())
    HANDLE_EXPR(never_refreshed, NeverRefreshed())
    HANDLE(add_content, OnAddContent)
    HANDLE(remove_content, OnRemoveContent)
    HANDLE_EXPR(delete_content, DeleteContent(_msg->Sym(2)))
    HANDLE_EXPR(mount, MountContent(_msg->Sym(2)))
    HANDLE_EXPR(is_mounted, IsMounted(_msg->Sym(2)))
    HANDLE_CHECK(0x226)
END_HANDLERS