#pragma once
#include "obj/Data.h"
#include "obj/Msg.h"

enum _WiiFriendStatus {
    kOffline = 0,
    kChannel = 1,
    kOnline = 2
};

class WiiFriend;

class WiiFriendProfile {
public:
    WiiFriendProfile();
    ~WiiFriendProfile();
    WiiFriendProfile &operator=(const WiiFriendProfile &);

    const char *Name() const { return mName.c_str(); }
    void SetStatus(const char *stat) { mStatus = stat; }

    int mPrincipalID; // 0x0
    String mName; // 0x4
    String mStatus; // 0x10
    WiiFriend *unk1c; // 0x1c
};

typedef bool WiiFriendSortFunc(WiiFriend *, WiiFriend *);
typedef bool WiiFriendProfileSortFunc(WiiFriendProfile *, WiiFriendProfile *);

class WiiFriend {
public:
    WiiFriend();
    ~WiiFriend();
    WiiFriendProfile *GetProfileByIdx(int) const;
    WiiFriendProfile *GetProfileByPrincipalID(int) const;
    WiiFriendProfile *GetProfile(const char *) const;
    WiiFriend &operator=(const WiiFriend &);
    void SortProfiles(WiiFriendProfileSortFunc);
    WiiFriendProfile *AddProfile(int, String);
    void SetMasterProfileStatus(const char *);
    bool PromoteMasterProfile();
    int NumProfiles() const { return unk18.size(); }
    unsigned long long ConsoleCode() const { return mConsoleCode; }
    WiiFriendProfile *MasterProfile() const { return mMasterProfile; }

    String unk0; // 0x0
    int unkc;
    unsigned long long mConsoleCode; // 0x10
    std::vector<WiiFriendProfile *> unk18; // 0x18
    WiiFriendProfile *mMasterProfile; // 0x20
    int unk24;
};

class WiiFriendList {
public:
    WiiFriendList();
    ~WiiFriendList();
    WiiFriendList &operator=(const WiiFriendList &);
    WiiFriend *GetFriendByIdx(int) const;
    WiiFriend *GetFriendByMasterPrincipalID(int) const;
    WiiFriend *GetFriendByConsoleCode(unsigned long long) const;
    WiiFriendProfile *GetProfile(int) const;
    WiiFriend *AddFriend(unsigned long long, String);
    bool RemoveFriend(unsigned long long);
    void Sort(WiiFriendSortFunc);

    std::vector<WiiFriend *> mFriends; // 0x0
};

class WiiFriendMgr : public MsgSource {
public:
    WiiFriendMgr();
    virtual DataNode Handle(DataArray *, bool);
    virtual ~WiiFriendMgr();

    void GetCachedFriends(WiiFriendList *);
    void UseConsoleFriends(bool);
    void EnumerateFriends(WiiFriendList *, Hmx::Object *);
    void SetProfileStatus(int, String);
    void SetMasterProfileStatus(String);
    void SetStatusDelimiter(char);
    static String GetMasterProfileName(unsigned long long);

    int unk1c;
    int unk20;
    WiiFriendList unk24;
    bool unk2c;
    bool unk2d;
    Timer unk30;
    int unk60;
    int unk64;
    bool unk68;
    int unk6c;
    int unk70;
    bool unk74;
    String unk78[4];
    String unka8;
    int unkb4;
    int unkb8;
    Timer unkc0;
    String unkf0;
};

DECLARE_MESSAGE(WiiFriendsListChangedMsg, "wii_friends_list_changed")
END_MESSAGE

DECLARE_MESSAGE(WiiFriendMgrOpCompleteMsg, "wii_friend_mgr_op_complete")
END_MESSAGE

extern WiiFriendMgr TheWiiFriendMgr;