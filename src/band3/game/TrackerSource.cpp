#include "game/TrackerSource.h"
#include "beatmatch/TrackType.h"
#include "game/Player.h"
#include "meta_band/MetaPerformer.h"
#include "os/Debug.h"
#include "utl/HxGuid.h"
#include "utl/Symbol.h"

TrackerSource::TrackerSource() {}

TrackerSource::~TrackerSource() {}

bool TrackerSource::HasPlayer(const TrackerPlayerID &pid) const {
    for (TrackerPlayerID id = GetFirstPlayer(); !id.mGuid.Null();
         id = GetNextPlayer(id)) {
        if (id.mGuid == pid.mGuid)
            return true;
    }
    return false;
}

TrackerPlayerID TrackerSource::GetIDFromInstrument(Symbol s) const {
    return GetIDFromTrackType(SymToTrackType(s));
}

TrackerPlayerID TrackerSource::GetIDFromTrackType(TrackType ty) const {
    for (TrackerPlayerID id = GetFirstPlayer(); !id.mGuid.Null();
         id = GetNextPlayer(id)) {
        Player *pPlayer = GetPlayer(id);
        MILO_ASSERT(pPlayer, 0x48);
        if (ty == pPlayer->GetTrackType()) {
            return TrackerPlayerID(id);
        }
    }
    return TrackerPlayerID(gNullUserGuid);
}

TrackerPlayerID TrackerSource::FindPlayerID(const Player *p) const {
    for (TrackerPlayerID id = GetFirstPlayer(); !id.mGuid.Null();
         id = GetNextPlayer(id)) {
        if (GetPlayer(id) == p) {
            return TrackerPlayerID(id);
        }
    }
    return TrackerPlayerID(gNullUserGuid);
}

bool TrackerSource::IsPlayerLocal(const TrackerPlayerID &pid) const {
    if (!HasPlayer(pid))
        return false;
    else {
        Player *pPlayer = GetPlayer(pid);
        MILO_ASSERT(pPlayer, 0x6E);
        return pPlayer->IsLocal();
    }
}

bool TrackerSource::IsPlayerEligible(const TrackerPlayerID &pid) const {
    if (!HasPlayer(pid))
        return false;
    else {
        Player *pPlayer = GetPlayer(pid);
        MILO_ASSERT(pPlayer, 0x7C);
        return PlayerIsEligible(pPlayer);
    }
}

bool TrackerSource::PlayerIsEligible(const Player *iPlayer) const {
    MILO_ASSERT(iPlayer, 0x84);
    if (iPlayer->GetQuarantined())
        return false;
    else {
        MetaPerformer *pPerformer = MetaPerformer::Current();
        MILO_ASSERT(pPerformer, 0x8C);
        if (pPerformer->Song() != gNullStr) {
            if (!pPerformer->PartPlaysInSong(iPlayer->GetUser()->GetTrackSym())) {
                return false;
            }
        }
        return true;
    }
}

PlayerTrackerSource::PlayerTrackerSource(Player *p) : mPlayer(p) {
    if (!PlayerIsEligible(p))
        mPlayer = nullptr;
}

PlayerTrackerSource::~PlayerTrackerSource() {}

void PlayerTrackerSource::HandleRemovePlayer(Player *p) {
    if (p == mPlayer)
        mPlayer = nullptr;
}

TrackerPlayerID PlayerTrackerSource::GetFirstPlayer() const {
    if (!mPlayer) {
        return TrackerPlayerID(gNullUserGuid);
    } else {
        return TrackerPlayerID(mPlayer->GetUserGuid());
    }
}

TrackerPlayerID PlayerTrackerSource::GetNextPlayer(const TrackerPlayerID &) const {
    return TrackerPlayerID(gNullUserGuid);
}

int PlayerTrackerSource::GetPlayerCount() const {
    return !mPlayer ? 0 : PlayerIsEligible(mPlayer);
}

Player *PlayerTrackerSource::GetPlayer(const TrackerPlayerID &iID) const {
    if (!mPlayer)
        return nullptr;
    else {
        MILO_ASSERT(mPlayer->GetUserGuid() == iID.GetGuid(), 0xE2);
        return mPlayer;
    }
}

bool PlayerTrackerSource::IsFinished() const {
    return !mPlayer ? true : mPlayer->mGameOver;
}

BandTrackerSource::BandTrackerSource(Band *band) : mBand(band) {
    MILO_ASSERT(mBand, 0xFA);
}

BandTrackerSource::~BandTrackerSource() {}