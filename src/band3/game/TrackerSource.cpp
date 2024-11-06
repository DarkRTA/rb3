#include "game/TrackerSource.h"
#include "beatmatch/TrackType.h"
#include "meta_band/MetaPerformer.h"
#include "os/Debug.h"
#include "utl/HxGuid.h"
#include "utl/Symbol.h"

TrackerSource::TrackerSource(){

}

TrackerSource::~TrackerSource(){

}

bool TrackerSource::HasPlayer(const TrackerPlayerID& pid) const {
    for(TrackerPlayerID id = GetFirstPlayer(); !id.mGuid.Null(); id = GetNextPlayer(id)){
        if(id.mGuid == pid.mGuid) return true;
    }
    return false;
}

TrackerPlayerID TrackerSource::GetIDFromInstrument(Symbol s) const {
    return GetIDFromTrackType(SymToTrackType(s));
}

TrackerPlayerID TrackerSource::GetIDFromTrackType(TrackType ty) const {
    for(TrackerPlayerID id = GetFirstPlayer(); !id.mGuid.Null(); id = GetNextPlayer(id)){
        Player* pPlayer = GetPlayer(id);
        MILO_ASSERT(pPlayer, 0x48);
        if(ty == pPlayer->GetTrackType()){
            return TrackerPlayerID(id);
        }
    }
    return TrackerPlayerID(gNullUserGuid);
}

TrackerPlayerID TrackerSource::FindPlayerID(const Player* p) const {
    for(TrackerPlayerID id = GetFirstPlayer(); !id.mGuid.Null(); id = GetNextPlayer(id)){
        if(GetPlayer(id) == p){
            return TrackerPlayerID(id);
        }
    }
    return TrackerPlayerID(gNullUserGuid);
}

bool TrackerSource::IsPlayerLocal(const TrackerPlayerID& pid) const {
    if(!HasPlayer(pid)) return false;
    else {
        Player* pPlayer = GetPlayer(pid);
        MILO_ASSERT(pPlayer, 0x6E);
        return pPlayer->IsLocal();
    }
}

bool TrackerSource::IsPlayerEligible(const TrackerPlayerID& pid) const {
    if(!HasPlayer(pid)) return false;
    else {
        Player* pPlayer = GetPlayer(pid);
        MILO_ASSERT(pPlayer, 0x7C);
        return PlayerIsEligible(pPlayer);
    }
}

bool TrackerSource::PlayerIsEligible(const Player* iPlayer) const {
    MILO_ASSERT(iPlayer, 0x84);
    if(iPlayer->GetQuarantined()) return false;
    else {
        MetaPerformer* pPerformer = MetaPerformer::Current();
        MILO_ASSERT(pPerformer, 0x8C);
        if(pPerformer->Song() != gNullStr){
            if(!pPerformer->PartPlaysInSong(iPlayer->GetUser()->GetTrackSym())){
                return false;
            }
        }
        return true;
    }
}