#pragma once
#include "NetSession.h"
#include "Platform/Holder.h"
#include "Platform/String.h"
#include "Services/Gathering.h"
#include "meta/Profile.h"
#include "obj/Data.h"

class RVSession : public NetSession {
public:
    RVSession();
    virtual DataNode Handle(DataArray *, bool);
    virtual ~RVSession();
    virtual void WriteStats(const std::vector<UserStat> &) {}
    virtual void SetInvitesAllowed(bool) {}
    virtual void InviteFriend(Friend *, const char *, const char *);
    virtual Job *PrepareRegisterHostSessionJob();
    virtual void StartSession();
    virtual void EndSession(bool);
    virtual void DeleteSession();
    virtual Job *PrepareConnectSessionJob();
    virtual void FinishJoin(const JoinResponseMsg &);
    virtual Job *PrepareRegisterArbitrationJob();
    virtual void UpdateSettings();

    void LeaveSession(RVSessionData *);
    bool OnMsg(const SigninChangedMsg &);

    DataNode OnUpdateFinished(DataArray *);

    Quazal::AnyObjectHolder<Quazal::Gathering, Quazal::String> mGathering; // 0x6c
    bool mJoined; // 0x74
    int mUpdateSettingsID; // 0x78
};

class RVSessionData : public SessionData {
public:
    RVSessionData();
    virtual ~RVSessionData() {}
    virtual void CopyInto(SessionData *);
    virtual void Save(BinStream &) const;
    virtual void Load(BinStream &);
    virtual bool Equals(const SessionData *) const;

    unsigned int mGatheringID; // 0x4
    unsigned int mHostID; // 0x8
};