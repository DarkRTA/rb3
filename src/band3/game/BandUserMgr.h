#pragma once
#include "game/Defines.h"
#include "os/UserMgr.h"
#include "utl/HxGuid.h"
#include "game/BandUser.h"
#include <vector>

class SessionMgr;

class BandUserMgr : public UserMgr {
public:
    BandUserMgr(int, int);
    virtual ~BandUserMgr();
    virtual DataNode Handle(DataArray *, bool);
    virtual void GetUsers(std::vector<User *> &) const;
    virtual User *GetUser(const UserGuid &, bool) const;
    virtual LocalUser *GetLocalUser(const UserGuid &, bool) const;
    virtual RemoteUser *GetRemoteUser(const UserGuid &, bool) const;

    BandUser *GetUserWithChar(const CharData *);
    BandUser *GetBandUser(const UserGuid &, bool) const;
    LocalBandUser *GetLocalBandUser(const UserGuid &, bool) const;
    RemoteBandUser *GetRemoteBandUser(const UserGuid &, bool) const;
    NullLocalBandUser *GetNullUser() const;
    std::vector<BandUser *> &GetBandUsers();
    std::vector<LocalBandUser *> &GetLocalBandUsers();
    void ResetSlots();
    int GetSlot(const UserGuid &) const;
    void SetSlot(BandUser *, int);
    void ClearSlot(BandUser *);
    const UserGuid &GetUserGuidFromSlot(int) const;
    BandUser *GetUserFromSlot(int) const;
    int MaxSlot() const;
    int GetNumParticipants() const;
    int GetNumLocalParticipants() const;
    bool IsMultiplayerGame() const;
    int GetNumLocalPlayers() const;
    LocalBandUser *GetUserFromPad(int);
    bool AllLocalUsersInSessionAreGuests() const;
    int GetBandUsers(std::vector<BandUser *> *, int) const;
    int GetLocalBandUsers(std::vector<LocalBandUser *> *, int) const;
    int GetRemoteBandUsers(std::vector<RemoteBandUser *> *, int) const;
    bool IsCharAvailable(const CharData *) const;
    ControllerType DebugGetControllerTypeOverride(int);

    int GetLocalParticipants(std::vector<LocalBandUser *> &) const;
    int GetLocalBandUsersInSession(std::vector<LocalBandUser *> &) const;
    int GetParticipatingBandUsers(std::vector<BandUser *> &) const;
    int GetParticipatingBandUsersInSession(std::vector<BandUser *> &) const;
    int GetLocalUsersWithAnyController(std::vector<LocalBandUser *> &) const;
    int GetBandUsersInSession(std::vector<BandUser *> &) const;
    int GetLocalBandUsers(std::vector<LocalBandUser *> &) const;
    int GetLocalUsersNotInSessionWithAnyController(std::vector<LocalBandUser *> &) const;

    DataNode ForEachUser(const DataArray *, int);

    static BandUser *GetBandUser(User *);
    static LocalBandUser *GetLocalBandUser(LocalUser *);
    static RemoteBandUser *GetRemoteBandUser(RemoteUser *);

    std::vector<BandUser *> mUsers; // 0x1c
    std::vector<LocalBandUser *> mLocalUsers; // 0x24
    std::vector<RemoteBandUser *> mRemoteUsers; // 0x2c
    NullLocalBandUser *mNullUser; // 0x34
    UserGuid mSlotMap[4]; // 0x38, 0x48, 0x58, 0x68
    SessionMgr *mSessionMgr; // 0x78
};

void BandUserMgrInit();
void BandUserMgrTerminate();

extern BandUserMgr *TheBandUserMgr;