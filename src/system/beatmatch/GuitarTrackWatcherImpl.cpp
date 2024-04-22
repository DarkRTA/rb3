#include "beatmatch/GuitarTrackWatcherImpl.h"
#include "os/Debug.h"
#include "beatmatch/GameGemList.h"

GuitarTrackWatcherImpl::GuitarTrackWatcherImpl(int track, const UserGuid& u, int slot, SongData* data, GameGemList* gemlist, TrackWatcherParent* parent, DataArray* cfg) :
    BaseGuitarTrackWatcherImpl(track, u, slot, data, gemlist, parent, cfg), mFretButtonsDown(0) {

}

GuitarTrackWatcherImpl::~GuitarTrackWatcherImpl(){

}

bool GuitarTrackWatcherImpl::Swing(int i, bool b1, bool b2, GemHitFlags flags){
    return BaseGuitarTrackWatcherImpl::Swing(i, b1, b2, flags);
}

bool GuitarTrackWatcherImpl::HandleHitsAndMisses(int i1, int i2, float ff, bool b1, bool b2, bool b3, GemHitFlags flags){
    GameGem& gem = mGemList->GetGem(i1);
}

void GuitarTrackWatcherImpl::RecordFretButtonDown(int i){
    mFretButtonsDown |= 1 << i;
}

void GuitarTrackWatcherImpl::RecordFretButtonUp(int i){
    mFretButtonsDown &= ~(1 << i);
}

unsigned int GuitarTrackWatcherImpl::GetFretButtonsDown() const { return mFretButtonsDown; }

bool GuitarTrackWatcherImpl::HarmlessFretDown(int i1, int i2) const {
    int slot_bit = 1 << i1;
    MILO_ASSERT(mFretButtonsDown & slot_bit, 0xB7);
    if(slot_bit < int(mFretButtonsDown - slot_bit)){
        return true;
    }
    else if(i2 == -1) return false;
    else {
        GameGem& gem = mGemList->GetGem(i2);
        if(gem.mSlots & slot_bit) return true;
        else return false;
    }
}

bool GuitarTrackWatcherImpl::IsCoreGuitar() const { return true; }

bool GuitarTrackWatcherImpl::FretMatch(int i, bool b1, bool b2) const {
    GameGem& gem = mGemList->GetGem(i);
    if(gem.NumSlots() == 1){
        int slot = gem.GetSlot();
        int highest = GameGem::GetHighestSlot(mFretButtonsDown);
        return slot == highest;
    }
    else {
        return gem.mSlots == mFretButtonsDown;
    }
}

bool GuitarTrackWatcherImpl::IsChordSubset(int i) const {
    GameGem& gem = mGemList->GetGem(i);
    return (mFretButtonsDown & gem.mSlots) == mFretButtonsDown;
}

bool GuitarTrackWatcherImpl::IsHighestFret(int i) const {
    int slot = 1 << i + 1;
    return (slot ^ mFretButtonsDown);
}

bool GuitarTrackWatcherImpl::InGem(int i, const GameGem& gem) const {
    return 1 << i & gem.mSlots;
}