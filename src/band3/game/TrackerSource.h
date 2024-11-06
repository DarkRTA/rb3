#pragma once
#include "beatmatch/TrackType.h"
#include "game/Player.h"
#include "utl/HxGuid.h"

struct TrackerPlayerID {
    TrackerPlayerID(const UserGuid& guid) : mGuid(guid) {}

    TrackerPlayerID& operator=(const TrackerPlayerID& pid){
        if(&mGuid != &pid.mGuid){
            mGuid = pid.mGuid;
        }
        return *this;
    }

    UserGuid mGuid; // 0x0
};

class TrackerSource {
public:
    TrackerSource();
    virtual ~TrackerSource();
    virtual void HandleAddPlayer(Player*){}
    virtual void HandleRemovePlayer(Player*){}
    virtual TrackerPlayerID GetFirstPlayer() const = 0;
    virtual TrackerPlayerID GetNextPlayer(const TrackerPlayerID&) const = 0;
    virtual bool GetPlayerCount() const = 0;
    virtual Player* GetPlayer(const TrackerPlayerID&) const  = 0;
    virtual bool IsFinished() const = 0;

    bool HasPlayer(const TrackerPlayerID&) const;
    TrackerPlayerID GetIDFromInstrument(Symbol) const;
    TrackerPlayerID GetIDFromTrackType(TrackType) const;
};