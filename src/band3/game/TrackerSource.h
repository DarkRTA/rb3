#pragma once
#include "beatmatch/TrackType.h"
#include "game/Player.h"
#include "utl/HxGuid.h"
#include "game/Band.h"

struct TrackerPlayerID {
    TrackerPlayerID() : mGuid(gNullUserGuid) {}
    TrackerPlayerID(const UserGuid &guid) : mGuid(guid) {}

    TrackerPlayerID &operator=(const TrackerPlayerID &pid) {
        if (&mGuid != &pid.mGuid) {
            mGuid = pid.mGuid;
        }
        return *this;
    }

    bool operator<(const TrackerPlayerID &pid) const { return mGuid < pid.mGuid; }

    bool NotNull() const { return !mGuid.Null(); }

    const UserGuid &GetGuid() const { return mGuid; }

    UserGuid mGuid; // 0x0
};

class TrackerSource {
public:
    TrackerSource();
    virtual ~TrackerSource();
    virtual void HandleAddPlayer(Player *) {}
    virtual void HandleRemovePlayer(Player *) {}
    virtual TrackerPlayerID GetFirstPlayer() const = 0;
    virtual TrackerPlayerID GetNextPlayer(const TrackerPlayerID &) const = 0;
    virtual int GetPlayerCount() const = 0;
    virtual Player *GetPlayer(const TrackerPlayerID &) const = 0;
    virtual bool IsFinished() const = 0;

    bool HasPlayer(const TrackerPlayerID &) const;
    TrackerPlayerID GetIDFromInstrument(Symbol) const;
    TrackerPlayerID GetIDFromTrackType(TrackType) const;
    TrackerPlayerID FindPlayerID(const Player *) const;
    bool IsPlayerLocal(const TrackerPlayerID &) const;
    bool IsPlayerEligible(const TrackerPlayerID &) const;
    bool PlayerIsEligible(const Player *) const;
};

class PlayerTrackerSource : public TrackerSource {
public:
    PlayerTrackerSource(Player *);
    virtual ~PlayerTrackerSource();
    virtual void HandleRemovePlayer(Player *);
    virtual TrackerPlayerID GetFirstPlayer() const;
    virtual TrackerPlayerID GetNextPlayer(const TrackerPlayerID &) const;
    virtual int GetPlayerCount() const;
    virtual Player *GetPlayer(const TrackerPlayerID &) const;
    virtual bool IsFinished() const;

    Player *mPlayer; // 0x4
};

class BandTrackerSource : public TrackerSource {
public:
    BandTrackerSource(Band *);
    virtual ~BandTrackerSource();
    virtual TrackerPlayerID GetFirstPlayer() const;
    virtual TrackerPlayerID GetNextPlayer(const TrackerPlayerID &) const;
    virtual int GetPlayerCount() const;
    virtual Player *GetPlayer(const TrackerPlayerID &) const;
    virtual bool IsFinished() const;

    Band *mBand; // 0x4
};