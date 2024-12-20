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

}

bool ContentMgr::PollContents(){
    
}

// undefined4 PollContents__10ContentMgrFv(int *param_1)

// {
//   int iVar1;
//   int iVar2;
//   undefined4 uVar3;
//   int *local_18 [4];
  
//   local_18[0] = (int *)FindFirstContent__10ContentMgrFQ27Content5State(param_1,2,0);
//   if ((local_18[0] == (int *)0x0) &&
//      (local_18[0] = (int *)FindFirstContent__10ContentMgrFQ27Content5State(param_1,1,0),
//      local_18[0] != (int *)0x0) && (iVar1 = (**(code **)(*param_1 + 0x98))(param_1), iVar1 != 0) &&
//      (*(char *)(param_1 + 7) != '\0')) {
//     (**(code **)(*local_18[0] + 0x2c))();
//     (**(code **)(*param_1 + 0xa8))(param_1,local_18[0]);
//     return 1;
//   }
//   if (local_18[0] == (int *)0x0) {
//     uVar3 = 0;
//   }
//   else {
//     iVar1 = (**(code **)(*local_18[0] + 0x20))();
//     (**(code **)(*local_18[0] + 0x24))();
//     iVar2 = (**(code **)(*local_18[0] + 0x20))();
//     if (iVar2 == 10) {
//       (**(code **)(*param_1 + 0xa8))(param_1,local_18[0]);
//       if (param_1[8] == 7) {
//         (**(code **)(*local_18[0] + 0x2c))();
//       }
//       else if (param_1[8] == 3) {
//         fn_802F1D68(param_1 + 0xb,local_18);
//       }
//     }
//     else if ((iVar2 == 4) && (iVar1 == 2)) {
//       (**(code **)(*param_1 + 0x9c))(param_1,local_18[0]);
//     }
//     else if ((iVar2 == 0) && (iVar1 == 4)) {
//       (**(code **)(*param_1 + 0xa0))(param_1,local_18[0]);
//     }
//     else if ((iVar2 == 9) && (iVar1 == 8)) {
//       (**(code **)(*param_1 + 0xa4))(param_1,local_18[0]);
//     }
//     uVar3 = 1;
//   }
//   return uVar3;
// }

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