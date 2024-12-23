#include "beatmatch/RealGuitarTrackWatcherImpl.h"
#include "beatmatch/SongData.h"

RealGuitarTrackWatcherImpl::RealGuitarTrackWatcherImpl(int track, const UserGuid& u, int slot, SongData* data, GameGemList* gemlist, TrackWatcherParent* parent, DataArray* cfg) :
    BaseGuitarTrackWatcherImpl(track, u, slot, data, gemlist, parent, cfg), unk1f0(0), mMissWindowMs(0), mIs22Fret(0) {
    mSlop = 125.0f;
    mFretSlop = 100.0f;
    if(cfg) cfg->FindData("real_guitar_miss_window_ms", mMissWindowMs, false);
    mIs22Fret = data->TrackTypeAt(track) == kTrackRealGuitar22Fret || data->TrackTypeAt(track) == kTrackRealBass22Fret;
}

RealGuitarTrackWatcherImpl::~RealGuitarTrackWatcherImpl(){

}