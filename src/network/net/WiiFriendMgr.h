#pragma once
#include "obj/Msg.h"

enum _WiiFriendStatus {
    kOffline = 0,
    kChannel = 1,
    kOnline = 2
};

class WiiFriend {
public:
};

class WiiFriendList {
public:
    WiiFriendList();
    ~WiiFriendList();
    std::vector<WiiFriend> mFriends; // 0x0
};

class WiiFriendMgr : public MsgSource {
public:
    WiiFriendMgr();

    void GetCachedFriends(WiiFriendList *);
    void UseConsoleFriends(bool);
    void EnumerateFriends(WiiFriendList *, Hmx::Object *);
    void SetProfileStatus(int, String);
    void SetMasterProfileStatus(String);
};

DECLARE_MESSAGE(WiiFriendsListChangedMsg, "wii_friends_list_changed")
END_MESSAGE

DECLARE_MESSAGE(WiiFriendMgrOpCompleteMsg, "wii_friend_mgr_op_complete")
END_MESSAGE

extern WiiFriendMgr TheWiiFriendMgr;