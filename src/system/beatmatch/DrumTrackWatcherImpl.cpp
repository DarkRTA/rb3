#include "beatmatch/DrumTrackWatcherImpl.h"
#include "beatmatch/SongData.h"

DrumTrackWatcherImpl::DrumTrackWatcherImpl(int track, const UserGuid& u, int slot, SongData* song_data, GameGemList* gemlist, TrackWatcherParent* parent, DataArray* cfg) : 
    TrackWatcherImpl(track, u, slot, song_data, gemlist, parent, cfg, 2), mNextKickGemToAutoplay(0), mGameCymbalLanes(0) {
    MILO_ASSERT(song_data, 0x25);
    mGameCymbalLanes = song_data->GetGameCymbalLanes();
}

DrumTrackWatcherImpl::~DrumTrackWatcherImpl(){

}

void DrumTrackWatcherImpl::Restart(){
    MILO_ASSERT(mSongData, 0x2F);
    mGameCymbalLanes = mSongData->GetGameCymbalLanes();
}

