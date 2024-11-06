#include "game/TrackerSource.h"
#include "beatmatch/TrackType.h"
#include "os/Debug.h"
#include "utl/HxGuid.h"

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