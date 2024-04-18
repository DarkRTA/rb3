#include "os/PlatformMgr.h"
#include "os/Debug.h"
#include "os/User.h"
#include "os/UserMgr.h"

PlatformMgr ThePlatformMgr;

Symbol PlatformRegionToSymbol(PlatformRegion r){
    MILO_ASSERT(r < kNumRegions, 0x29);
    static Symbol sym[4] = { "", "na", "europe", "japan" };
    return sym[r];
}

PlatformRegion SymbolToPlatformRegion(Symbol s){
    for(int i = 0; i < 4; i++){
        PlatformRegion r = (PlatformRegion)i;
        if(PlatformRegionToSymbol(r) == s) return r;
    }
    MILO_FAIL("Invalid region %s", s);
    return kNumRegions;
}

bool PlatformMgr::IsSignedIn(int padnum) const {
    if(padnum < 0){
        MILO_FAIL("PadNum = %d", padnum);
    }
    return 1 << padnum & mSigninMask;
}

bool PlatformMgr::IsUserSignedIn(const LocalUser* pUser) const {
    MILO_ASSERT(pUser, 0x51);
    return IsSignedIn(pUser->GetPadNum());
}

bool PlatformMgr::HasUserSigninChanged(const LocalUser* pUser) const {
    MILO_ASSERT(pUser, 0x58);
    int padnum = pUser->GetPadNum();
    if(padnum < 0) MILO_FAIL("PadNum = %d", padnum);
    return 1 << padnum & mSigninChangeMask;
}

bool PlatformMgr::IsUserSignedIntoLive(const LocalUser* pUser) const {
    MILO_ASSERT(pUser, 0x60);
    return IsSignedIntoLive(pUser->GetPadNum());
}

bool PlatformMgr::IsAnyUserSignedIntoLive() const {
    for(int i = 0; i < 4; i++){
        if(IsSignedIntoLive(i)) return true;
    }
    return false;
}

bool PlatformMgr::UserHasOnlinePrivilege(const LocalUser* pUser) const {
    MILO_ASSERT(pUser, 0x70);
    return HasOnlinePrivilege(pUser->GetPadNum());
}

bool PlatformMgr::IsUserAGuest(const LocalUser*) const { return false; }
PlatformRegion PlatformMgr::GetRegion() const { return mRegion; }

LocalUser* PlatformMgr::GetOwnerUserOfGuestUser(LocalUser* pUser){
    MILO_ASSERT(pUser, 0xBA);
    return TheUserMgr->GetLocalUserFromPadNum(GetOwnerOfGuest(pUser->GetPadNum()));
}
