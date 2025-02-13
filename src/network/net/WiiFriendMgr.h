#pragma once
#include "obj/Msg.h"

class WiiFriendMgr : public MsgSource {
public:
    WiiFriendMgr();
};

DECLARE_MESSAGE(WiiFriendsListChangedMsg, "wii_friends_list_changed");
END_MESSAGE
;

extern WiiFriendMgr TheWiiFriendMgr;