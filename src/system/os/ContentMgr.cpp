#include "os/ContentMgr.h"
#include "obj/Dir.h"
#include "utl/Symbols.h"

void ContentMgr::Init(){
    SetName("content_mgr", ObjectDir::Main());
    mDirty = true;
    mRootLoaded = 0;
    mState = kDone;
    mReadFailureHandler = 0;
    mCreateSongCache = false;
}

void ContentMgr::ContentRecurseCallback(const char* c1, const char* c2){
    return TheContentMgr->AddCallbackFile(c1, c2);
}

bool ContentMgr::RefreshDone() const { return mState == kDiscoveryEnumerating; }

void ContentMgr::PollRefresh(){

}

Hmx::Object* ContentMgr::SetReadFailureHandler(Hmx::Object* o){
    Hmx::Object* oldhandler = mReadFailureHandler;
    mReadFailureHandler = o;
    return oldhandler;
}

DataNode ContentMgr::OnAddContent(DataArray* da){
    OnRemoveContent(da);
    unk34.push_back(String(da->Str(2)));
    return DataNode(0);
}

DataNode ContentMgr::OnRemoveContent(DataArray* da){
    mDirty = true;
    for(std::list<String>::iterator it = unk34.begin(); it != unk34.end(); it){
        bool res = strcmp((*it).c_str(), da->Str(2)) == 0;
        if(res){
            it = unk34.erase(it);
        }
        else it++;
    }
    return DataNode(0);
}

BEGIN_HANDLERS(ContentMgr)
    HANDLE_ACTION(start_refresh, StartRefresh())
    HANDLE_EXPR(refresh_done, mState == kDiscoveryEnumerating)
    HANDLE_EXPR(never_refreshed, mState == kDone)
    HANDLE(add_content, OnAddContent)
    HANDLE(remove_content, OnRemoveContent)
    HANDLE_EXPR(delete_content, DeleteContent(_msg->Sym(2)))
    HANDLE_EXPR(mount, MountContent(_msg->Sym(2)))
    HANDLE_EXPR(is_mounted, IsMounted(_msg->Sym(2)))
    HANDLE_CHECK(0x226)
END_HANDLERS