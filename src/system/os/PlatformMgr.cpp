#include "os/PlatformMgr.h"
#include "os/Debug.h"
#include "os/User.h"
#include "os/UserMgr.h"
#include "utl/Option.h"
#include "obj/DataUtl.h"
#include "os/ProfileSwappedMsg.h"
#include "utl/UTF8.h"
#include "utl/Symbols.h"

PlatformMgr ThePlatformMgr;

LocalUser* ProfileSwappedMsg::GetUser1() const {
    return mData->Obj<LocalUser>(2);
}

LocalUser* ProfileSwappedMsg::GetUser2() const {
    return mData->Obj<LocalUser>(3);
}

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

void UTF8FilterKeyboardString(char* c, int i, const char* cc){
    static const char* allowed = SystemConfig(platform_mgr)->FindArray(keyboard_allowed_chars, true)->Str(1);
    UTF8FilterString(c, i, cc, allowed, '?');
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

void PlatformMgr::SetRegion(PlatformRegion region){
    const char* regionStr = OptionStr("region", 0);
    if(regionStr) mRegion = SymbolToPlatformRegion(regionStr);
    else mRegion = region;
    MILO_ASSERT(mRegion != kRegionNone, 200);
    class String platRegion(PlatformRegionToSymbol(mRegion));
    platRegion.ToUpper();
    platRegion = MakeString("REGION_%s", (class String)(platRegion));
    DataArray* arr;
    {
        DataNode node(1);
        arr = new DataArray(1);
        arr->Node(0) = node;
    }
    DataSetMacro(platRegion.c_str(), arr);
    arr->Release();
}

#pragma push
#pragma dont_inline on
BEGIN_HANDLERS(PlatformMgr)
    HANDLE_EXPR(is_connected, IsConnected())
    HANDLE_EXPR(is_ethernet_cable_connected, IsEthernetCableConnected())
    HANDLE(signin, OnSignInUsers)
    HANDLE_EXPR(get_signin_mask, SigninMask())
    HANDLE_EXPR(get_signin_changed_mask, SigninChangedMask())
    HANDLE_EXPR(is_user_signed_in, IsUserSignedIn(_msg->Obj<LocalUser>(2)))
    HANDLE_EXPR(has_user_signin_changed, HasUserSigninChanged(_msg->Obj<LocalUser>(2)))
    HANDLE_EXPR(get_name, GetName(_msg->Int(2)))
    HANDLE_EXPR(is_user_signed_into_live, IsUserSignedIntoLive(_msg->Obj<LocalUser>(2)))
    HANDLE_EXPR(has_online_privilege, HasOnlinePrivilege(_msg->Int(2)))
    HANDLE_EXPR(user_has_online_privilege, UserHasOnlinePrivilege(_msg->Obj<LocalUser>(2)))
    HANDLE_EXPR(guide_showing, mGuideShowing)
    HANDLE_EXPR(is_user_a_guest, IsUserAGuest(_msg->Obj<LocalUser>(2)))
    HANDLE_EXPR(get_owner_user_of_guest_user, GetOwnerUserOfGuestUser(_msg->Obj<LocalUser>(2)))
    HANDLE_ACTION(set_screen_saver, SetScreenSaver(_msg->Int(2)))
    HANDLE_ACTION(run_net_start_utility, RunNetStartUtility())
    HANDLE_ACTION(set_notify_ui_location, SetNotifyUILocation((NotifyLocation)_msg->Int(2)))
    HANDLE_EXPR(get_region, mRegion)
    HANDLE_EXPR(is_user_a_wiiguest, IsUserAWiiGuest(_msg->Obj<LocalUser>(2)))
    HANDLE_EXPR(init_nintendo_connection, InitNintendoConnection())
    HANDLE_ACTION(close_nintendo_connection, CloseNintendoConnection(_msg->Int(2), false))
    HANDLE_EXPR(last_dwc_error, GetLastDWCError())
    HANDLE_EXPR(has_net_error, HasNetError())
    HANDLE_EXPR(get_net_error_string, GetNetErrorString(false))
    HANDLE_EXPR(get_net_error_string_store, GetNetErrorStringAsDataArray(true))
    HANDLE_ACTION(clear_net_error, ClearNetError())
    HANDLE_ACTION(clear_dwc_error, ClearDWCError())
    HANDLE_EXPR(is_checking_profanity, mCheckingProfanity)
    HANDLE_ACTION(enable_profanity_check, EnableProfanity(_msg->Int(2)))
    HANDLE_EXPR(is_online_restricted, IsOnlineRestricted())
    HANDLE_ACTION(relax_online_restriction, RelaxOnlineRestriction())
    HANDLE_EXPR(last_nhttp_error, GetLastNHTTPError())
    HANDLE_ACTION(set_connected, SetConnected(_msg->Int(2)))
    HANDLE_ACTION(set_party_mic_options_showing, SetPartyMicOptionsShowing(_msg->Int(2)))
    HANDLE_EXPR(last_dns_error, GetLastDNSError())
    HANDLE_EXPR(did_storage_change, mStorageChanged)
    HANDLE_ACTION(set_is_restarting, SetIsRestarting(_msg->Int(2)))
    HANDLE_ACTION(set_home_menu_enabled, SetHomeMenuEnabled(_msg->Int(2)))
    HANDLE_EXPR(home_menu_active, HomeMenuActive())
    HANDLE_ACTION(enable_sfx, EnableSFX(_msg->Int(2)))
    HANDLE_EXPR(are_sfx_enabled, AreSFXEnabled())
    HANDLE_ACTION(ignore_wii_speak_friends, IgnoreWiiSpeakFriends())
    HANDLE_ACTION(print_parental_pin, PrintParentalPin())
    HANDLE_MESSAGE(ButtonDownMsg)
    HANDLE_MESSAGE(ButtonUpMsg)
    HANDLE_ACTION(trigger_disk_error, SetDiskError(kFailedChecksum))
    HANDLE_ACTION(debug_spam_profanity_check, unkce69 = true; StartProfanity("This is a string", 0))
    HANDLE_SUPERCLASS(MsgSource)
    HANDLE_CHECK(0x1BA)
END_HANDLERS
#pragma pop