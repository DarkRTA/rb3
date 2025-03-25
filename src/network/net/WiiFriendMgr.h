#pragma once
#include "obj/Msg.h"

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
};

DECLARE_MESSAGE(WiiFriendsListChangedMsg, "wii_friends_list_changed");
END_MESSAGE
;

extern WiiFriendMgr TheWiiFriendMgr;