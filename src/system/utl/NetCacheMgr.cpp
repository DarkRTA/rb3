#include "NetCacheMgr.h"

// this is actually a NetCacheMgrWii so change this when that is implemented
NetCacheMgr *TheNetCacheMgr = 0;

NetCacheMgr::NetCacheMgr() {
    SetName("net_cache_mgr", ObjectDir::sMainDir);
}

void NetCacheMgr::Unload() {
    // impl
}

bool NetCacheMgr::IsDoneLoading() const {
    return 1;
}

bool NetCacheMgr::IsDoneUnloading() const {
    return 1;
}

void NetCacheMgr::LoadInit() {
    return;
}

void NetCacheMgr::ReadyInit() {
    return;
}

NetCacheMgrFailType NetCacheMgr::GetFailType() const {
    return mFailType;
}

#pragma push
#pragma dont_inline on
BEGIN_HANDLERS(NetCacheMgr)
    HANDLE_ACTION(init, OnInit())
    HANDLE_ACTION(debug_clear_cache, DebugClearCache())
    HANDLE_ACTION(cheat_next_server, CheatNextServer())
    HANDLE_EXPR(server_type, mServerType);
    HANDLE_CHECK(0x2f3)
END_HANDLERS
#pragma pop

void NetCacheMgrInit() {
    MILO_ASSERT(TheNetCacheMgr == NULL, 0x22);
    TheNetCacheMgr = new NetCacheMgr();
}

void NetCacheMgrTerminate() {
    delete TheNetCacheMgr;
    TheNetCacheMgr = NULL;
}