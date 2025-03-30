#pragma once
#include "obj/Object.h"
#include "os/Timer.h"
#include "os/User.h"

class UserStat {
public:
};

class NetGameData {
public:
    NetGameData() {}
    virtual ~NetGameData() {}
    virtual int GetNumPlayersAllowed() const = 0;
    virtual void GetEndGameStats(std::vector<UserStat> &) const = 0;
    virtual int PublicID() const = 0;
    virtual void AuthenticationData(BinStream &, const User *) const = 0;
    virtual bool AuthenticateJoin(BinStream &, int &) const = 0;
};

class BandNetGameData : public NetGameData, public Hmx::Object {
public:
    BandNetGameData();
    virtual ~BandNetGameData();
    virtual int GetNumPlayersAllowed() const;
    virtual void GetEndGameStats(std::vector<UserStat> &) const;
    virtual int PublicID() const;
    virtual void AuthenticationData(BinStream &, const User *) const;
    virtual bool AuthenticateJoin(BinStream &, int &) const;
    virtual DataNode Handle(DataArray *, bool);

    void Poll();

    Timer unk20;
};