#include "beatmatch/TrackWatcher.h"
#include "beatmatch/TrackWatcherImpl.h"
#include "os/System.h"
#include "utl/Symbols.h"

Symbol ControllerTypeToTrackWatcherType(Symbol cntType){
    DataArray* cfg = SystemConfig("beatmatcher", "controllers", "beatmatch_controller_mapping");
    Symbol watchType = cfg->FindArray(cntType, true)->Sym(1);
    if(watchType == joypad_guitar) return guitar;
    else return watchType;
}

TrackWatcher::TrackWatcher(int track, const UserGuid& u, int slot, Symbol cntType, SongData* data, TrackWatcherParent* parent, DataArray* cfg) : 
    mImpl(0), mSinks(), mControllerType(), mUserGuid() {
        mTrack = track;
        mUserGuid = u;
        mPlayerSlot = slot;
        mControllerType = cntType;
        mSongData = data;
        mParent = parent;
        mCfg = cfg;
        SetImpl();
}

TrackWatcher::~TrackWatcher(){
    delete mImpl;
    mImpl = 0;
}

void TrackWatcher::ReplaceImpl(Symbol sym){
    mControllerType = sym;
    SetImpl();
}

void TrackWatcher::SetImpl(){
    // std::vector<int> vec;
    TrackWatcherState state;
    if(mImpl) mImpl->SaveState(state);
    delete mImpl;
    mImpl = 0;
    mImpl = NewTrackWatcherImpl(mTrack, mUserGuid, mPlayerSlot, mControllerType, mSongData, mParent, mCfg);
    mImpl->Init();
    for(int i = 0; i < mSinks.size(); i++){
        mImpl->AddSink(mSinks[i]);
    }
    if(mImpl) mImpl->LoadState(state);
}

void TrackWatcher::RecalcGemList(){
    mImpl->RecalcGemList();
}

void TrackWatcher::SetIsCurrentTrack(bool b){
    mImpl->SetIsCurrentTrack(b);
}

void TrackWatcher::AddSink(BeatMatchSink* sink){
    mSinks.push_back(sink);
    mImpl->AddSink(sink);
}

void TrackWatcher::Poll(float f){
    mImpl->Poll(f);
}

void TrackWatcher::Jump(float f){
    mImpl->Jump(f);
}

void TrackWatcher::Restart(){
    mImpl->Restart();
}

bool TrackWatcher::Swing(int i, bool b1, bool b2, GemHitFlags flags){
    return mImpl->Swing(i, b1, b2, flags);
}

void TrackWatcher::NonStrumSwing(int i, bool b1, bool b2){
    mImpl->NonStrumSwing(i, b1, b2);
}

void TrackWatcher::FretButtonDown(int i){
    mImpl->FretButtonDown(i);
}

void TrackWatcher::RGFretButtonDown(int i){
    mImpl->RGFretButtonDown(i);
}

void TrackWatcher::FretButtonUp(int i){
    mImpl->FretButtonUp(i);
}

void TrackWatcher::Enable(bool b){
    mImpl->Enable(b);
}

void TrackWatcher::SetCheating(bool b){
    mImpl->SetCheating(b);
}

void TrackWatcher::SetAutoplayError(int i){
    mImpl->SetAutoplayError(i);
}

void TrackWatcher::SetAutoplayCoda(bool b){
    mImpl->SetAutoplayCoda(b);
}

float TrackWatcher::CycleAutoplayAccuracy(){
    return mImpl->CycleAutoplayAccuracy();
}

void TrackWatcher::SetAutoplayAccuracy(float f){
    mImpl->SetAutoplayAccuracy(f);
}

void TrackWatcher::SetSyncOffset(float f){
    mImpl->SetSyncOffset(f);
}

void TrackWatcher::E3CheatIncSlop(){
    mImpl->E3CheatIncSlop();
}

void TrackWatcher::E3CheatDecSlop(){
    mImpl->E3CheatDecSlop();
}