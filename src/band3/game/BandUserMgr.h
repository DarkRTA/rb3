#pragma once
#include "game/Defines.h"
#include "os/UserMgr.h"
#include "utl/HxGuid.h"
#include "game/BandUser.h"
#include <vector>

class BandUserMgr : public UserMgr {
public:
    BandUserMgr(int, int);
    virtual ~BandUserMgr();
    virtual DataNode Handle(DataArray*, bool);
    virtual void GetUsers(std::vector<User*>&) const;
    virtual User* GetUser(const UserGuid&, bool) const;
    virtual LocalUser* GetLocalUser(const UserGuid&, bool) const;
    virtual RemoteUser* GetRemoteUser(const UserGuid&, bool) const;

    BandUser* GetUserWithChar(const CharData*);
    BandUser* GetBandUser(const UserGuid&, bool) const;
    LocalBandUser* GetLocalBandUser(const UserGuid&, bool) const;
    RemoteBandUser* GetRemoteBandUser(const UserGuid&, bool) const;
    NullLocalBandUser* GetNullUser() const;
    std::vector<BandUser*>& GetBandUsers();
    std::vector<LocalBandUser*>& GetLocalBandUsers();
    void ResetSlots();
    int GetSlot(const UserGuid&) const;
    void SetSlot(BandUser*, int);
    void ClearSlot(BandUser*);
    const UserGuid& GetUserGuidFromSlot(int) const;
    BandUser* GetUserFromSlot(int) const;
    int MaxSlot() const;
    int GetNumParticipants() const;
    int GetNumLocalParticipants() const;
    bool IsMultiplayerGame() const;
    int GetNumLocalPlayers() const;
    LocalBandUser* GetUserFromPad(int);
    bool AllLocalUsersInSessionAreGuests() const;
    void GetBandUsers(std::vector<BandUser*>*, int) const;
    void GetLocalBandUsers(std::vector<LocalBandUser*>*, int) const;
    void GetRemoteBandUsers(std::vector<RemoteBandUser*>*, int) const;
    bool IsCharAvailable(const CharData*) const;
    ControllerType DebugGetControllerTypeOverride(int);

    void GetLocalParticipants(std::vector<LocalBandUser*>&) const;
    void GetLocalBandUsersInSession(std::vector<LocalBandUser*>&) const;
    void GetParticipatingBandUsers(std::vector<BandUser*>&) const;
    void GetParticipatingBandUsersInSession(std::vector<BandUser*>&) const;
    void GetLocalUsersWithAnyController(std::vector<LocalBandUser*>&) const;

    static BandUser* GetBandUser(User*);
    static LocalBandUser* GetLocalBandUser(LocalUser*);
    static RemoteBandUser* GetRemoteBandUser(RemoteUser*);

    std::vector<BandUser*> mUsers; // 0x1c
    std::vector<LocalBandUser*> mLocalUsers; // 0x24
    std::vector<RemoteBandUser*> mRemoteUsers; // 0x2c
    NullLocalBandUser* mNullUser; // 0x34
    UserGuid mSlotMap[4]; // 0x38, 0x48, 0x58, 0x68
    int unk78;
};

void BandUserMgrInit();
void BandUserMgrTerminate();

extern BandUserMgr* TheBandUserMgr;