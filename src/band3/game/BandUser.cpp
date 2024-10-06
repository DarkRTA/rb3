#include "BandUser.h"
#include "game/Defines.h"
#include "beatmatch/TrackType.h"
#include "utl/Symbols.h"

BandUser::BandUser()
    : mDifficulty(DefaultDifficulty()), unk_0xC(0), mTrackType(kTrackNone),
      mControllerType(kControllerNone), mHasButtonGuitar(0), mHas22FretGuitar(0), mPreferredScoreType(kScoreBand),
      unk_0x20(5), mChar(0), mAutoplay(0), mLastHitFraction(0), mTrack(0), mPlayer(0),
      mParticipating(0), mIsWiiRemoteController(0), mJustDisconnected(0) {
    mPreviousAward = none;
}

BandUser::~BandUser() {}

LocalBandUser* BandUser::NewLocalBandUser(){
    return new LocalBandUser();
}

RemoteBandUser* BandUser::NewRemoteBandUser(){
    return new RemoteBandUser();
}

NullLocalBandUser* BandUser::NewNullLocalBandUser(){
    return new NullLocalBandUser();
}

void BandUser::Reset(){
    User::Reset();
    unk_0x20 = 5;
    mDifficulty = DefaultDifficulty();
    unk_0xC = 0;
    mTrackType = kTrackNone;
    mControllerType = kControllerNone;
    mAutoplay = false;
    mPreviousAward = none;
    mParticipating = false;
    mChar = 0;
    mLastHitFraction = 0;
    mHasButtonGuitar = 0;
    mHas22FretGuitar = 0;
}

Difficulty BandUser::GetDifficulty() const {
    return mDifficulty;
}

Symbol BandUser::GetDifficultySym() const {
    return DifficultyToSym(mDifficulty);
}

void BandUser::SetDifficulty(Difficulty d){
    MILO_ASSERT(IsLocal(), 0x74);
    MILO_ASSERT(( 0) <= (d) && (d) < ( kNumDifficulties), 0x75);
    Difficulty old = mDifficulty;
    unk_0xC = true;
    mDifficulty = d;
    if(old != d){

    }
}

bool BandUser::IsFullyInGame() const {
    bool ret = false;
    if(unk_0xC && mTrackType != kTrackPending && mTrackType != kTrackPendingVocals){
        ret = true;
    }
    return ret;
}

void BandUser::SetDifficulty(Symbol s){
    SetDifficulty(SymToDifficulty(s));
}

TrackType BandUser::GetTrackType() const {
    return mTrackType;
}

Symbol BandUser::GetTrackSym() const {
    return TrackTypeToSym(mTrackType);
}

const char* BandUser::GetOvershellFocus(){ return mOvershellFocus.c_str(); }

void BandUser::SetTrackType(TrackType ty){
    MILO_ASSERT(IsLocal(), 0xC1);
    mTrackType = ty;
    UpdateData(1);
}

void BandUser::SetTrackType(Symbol s){
    SetTrackType(SymToTrackType(s));
}

ScoreType BandUser::GetPreferredScoreType() const {
    return mPreferredScoreType;
}

void BandUser::SetPreferredScoreType(ScoreType ty){
    MILO_ASSERT(IsLocal(), 0xD2);
    mPreferredScoreType = ty;
    UpdateData(1);
}

ControllerType BandUser::GetControllerType() const {
    return mControllerType;
}

Symbol BandUser::GetControllerSym() const {
    return ControllerTypeToSym(mControllerType);
}

void BandUser::SetControllerType(ControllerType ty){
    MILO_ASSERT(IsLocal(), 0xE4);
    mControllerType = ty;
    UpdateData(1);
}

void BandUser::SetControllerType(Symbol s){
    SetControllerType(SymToControllerType(s));
}

void BandUser::SetHasButtonGuitar(bool b){
    MILO_ASSERT(IsLocal(), 0xF0);
    mHasButtonGuitar = b;
    UpdateData(1);
}

void BandUser::BandUser::SetHas22FretGuitar(bool b){
    MILO_ASSERT(IsLocal(), 0xF0);
    mHas22FretGuitar = b;
    UpdateData(1);
}

bool BandUser::HasChar() {
    return mChar != 0;
}

LocalBandUser::LocalBandUser() : unk28(5) {
    unkc = 1;
    unkd = 0;
}

LocalBandUser* LocalBandUser::GetLocalBandUser(){}
LocalBandUser* LocalBandUser::GetLocalBandUser() const {}