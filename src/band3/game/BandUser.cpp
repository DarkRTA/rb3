#include "BandUser.h"
#include "game/Defines.h"
#include "beatmatch/TrackType.h"
#include "game/Player.h"
#include "utl/Symbols.h"

BandUser::BandUser()
    : mDifficulty(DefaultDifficulty()), unk_0xC(0), mTrackType(kTrackNone),
      mControllerType(kControllerNone), mHasButtonGuitar(0), mHas22FretGuitar(0), mPreferredScoreType(kScoreBand),
      mOvershellState(kState_JoinedDefault), mChar(0), mAutoplay(0), mLastHitFraction(0), mTrack(0), mPlayer(0),
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
    mOvershellState = kState_JoinedDefault;
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
    MILO_ASSERT_RANGE(d, 0, kNumDifficulties, 0x75);
    Difficulty old = mDifficulty;
    unk_0xC = true;
    mDifficulty = d;
    if(old != d && mPlayer){

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

void BandUser::SetOvershellSlotState(OvershellSlotStateID id){
    mOvershellState = id;
    UpdateData(1);
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

bool BandUser::HasChar(){ return mChar; }
CharData* BandUser::GetChar(){ return mChar; }

DataNode BandUser::OnSetDifficulty(DataArray* da){
    DataNode& eval = da->Node(2).Evaluate();
    if(eval.Type() == kDataInt){
        SetDifficulty((Difficulty)eval.Int());
    }
    else if(eval.Type() == kDataSymbol){
        SetDifficulty(eval.Sym());
    }
    else if(eval.Type() == kDataString){
        SetDifficulty(eval.ForceSym());
    }
    else MILO_FAIL("bad difficulty arg");
    return 1;
}

DataNode BandUser::OnSetTrackType(DataArray* da){
    DataNode& eval = da->Node(2).Evaluate();
    if(eval.Type() == kDataInt){
        SetTrackType((TrackType)eval.Int());
    }
    else if(eval.Type() == kDataSymbol || eval.Type() == kDataString){
        SetTrackType(eval.ForceSym());
    }
    else MILO_FAIL("bad TrackType arg");
    return 1;
}

DataNode BandUser::OnSetHas22FretGuitar(DataArray* da){
    DataNode& eval = da->Node(2).Evaluate();
    if(eval.Type() == kDataInt){
        SetHas22FretGuitar(eval.Int());
    }
    else MILO_FAIL("bad bool arg");
    return 1;
}

DataNode BandUser::OnSetPreferredScoreType(DataArray* da){
    DataNode& eval = da->Node(2).Evaluate();
    if(eval.Type() == kDataInt){
        SetPreferredScoreType((ScoreType)eval.Int());
    }
    else MILO_FAIL("bad ScoreType arg");
    return 1;
}

DataNode BandUser::OnSetControllerType(DataArray* da){
    DataNode& eval = da->Node(2).Evaluate();
    if(eval.Type() == kDataInt){
        SetControllerType((ControllerType)eval.Int());
    }
    else if(eval.Type() == kDataSymbol || eval.Type() == kDataString){
        SetControllerType(eval.ForceSym());
    }
    else MILO_FAIL("bad ControllerType arg");
    return 1;
}

#pragma push
#pragma dont_inline on
BEGIN_HANDLERS(BandUser)
    HANDLE_EXPR(get_difficulty, GetDifficulty())
    HANDLE_EXPR(get_difficulty_sym, GetDifficultySym())
    HANDLE(set_difficulty, OnSetDifficulty)
    HANDLE_EXPR(intro_name, IntroName())
    HANDLE_EXPR(get_user_name, UserName())
    HANDLE_EXPR(get_slot_num, GetSlot())
    HANDLE_EXPR(get_track_type, GetTrackType())
    HANDLE_EXPR(get_track_sym, GetTrackSym())
    HANDLE_EXPR(get_track_icon, GetTrackIcon())
    HANDLE(set_track_type, OnSetTrackType)
    HANDLE_EXPR(get_preferred_score_type, GetPreferredScoreType())
    HANDLE(set_preferred_score_type, OnSetPreferredScoreType)
    HANDLE_EXPR(get_controller_type, GetControllerType())
    HANDLE_EXPR(get_controller_sym, GetControllerSym())
    HANDLE(set_controller_type, OnSetControllerType)
    HANDLE(set_has_22_fret_guitar, OnSetHas22FretGuitar)
    HANDLE_EXPR(get_gameplay_options, GetGameplayOptions())
    HANDLE_EXPR(is_participating, IsParticipating())
    HANDLE_EXPR(player, mPlayer)
    HANDLE_EXPR(get_player, mPlayer)
    HANDLE_EXPR(get_hardcore_icon_level, GetCurrentHardcoreIconLevel())
    HANDLE(set_prefab_char, OnSetPrefabChar)
    HANDLE_EXPR(has_char, mChar != 0)
    HANDLE_EXPR(is_char_customizable, mChar->IsCustomizable())
    HANDLE_EXPR(get_last_hit_fraction, GetLastHitFraction())
    HANDLE_ACTION(set_last_hit_fraction, SetLastHitFraction(_msg->Float(2)))
    HANDLE_SUPERCLASS(User)
    HANDLE_CHECK(0x2D5)
END_HANDLERS
#pragma pop

BEGIN_PROPSYNCS(BandUser)
    SYNC_PROP(autoplay, mAutoplay)
    SYNC_PROP(previous_award, mPreviousAward)
    SYNC_SUPERCLASS(User)
END_PROPSYNCS

LocalBandUser::LocalBandUser() : mControllerTypeOverride(kControllerNone) {
    unkc = 1;
    mHasSeenRealGuitarPrompt = 0;
}

LocalBandUser* LocalBandUser::GetLocalBandUser(){}
LocalBandUser* LocalBandUser::GetLocalBandUser() const {}

RemoteBandUser* LocalBandUser::GetRemoteBandUser(){
    MILO_FAIL("Bad Conversion");
    return 0;
}

RemoteBandUser* LocalBandUser::GetRemoteBandUser() const {
    MILO_FAIL("Bad Conversion");
    return 0;
}

void LocalBandUser::Reset(){
    BandUser::Reset();
    LocalUser::Reset();
    mShownIntrosSet.clear();
    mHasSeenRealGuitarPrompt = 0;
    unkc = 1;
}

bool LocalBandUser::HasSeenRealGuitarPrompt() const { return mHasSeenRealGuitarPrompt; }
void LocalBandUser::SetHasSeenRealGuitarPrompt(){ mHasSeenRealGuitarPrompt = true; }

void LocalBandUser::SetOvershellFocus(const char* cc){
    mOvershellFocus = cc;
    UpdateData(1);
}

ControllerType LocalBandUser::DebugGetControllerTypeOverride() const { return mControllerTypeOverride; }

void LocalBandUser::DebugSetControllerTypeOverride(ControllerType ct){
    MILO_ASSERT_RANGE_EQ(ct, 0, kNumControllerTypes, 0x3B2);
    mControllerTypeOverride = ct;
}

BEGIN_HANDLERS(LocalBandUser)
    HANDLE_EXPR(can_save_data, CanSaveData())
    HANDLE_EXPR(can_get_achievements, CanSaveData())
    HANDLE_EXPR(connected_controller_type, ConnectedControllerType())
    HANDLE_EXPR(connected_controller_sym, ControllerTypeToSym(ConnectedControllerType()))
    HANDLE_ACTION(set_contributes_song_progress, unkc = _msg->Int(2))
    HANDLE_EXPR(has_as_friend, (_msg->Obj<BandUser>(2), 1))
    HANDLE_SUPERCLASS(LocalUser)
    HANDLE_SUPERCLASS(BandUser)
    HANDLE_CHECK(0x3CC)
END_HANDLERS

RemoteBandUser::RemoteBandUser(){

}

RemoteBandUser::~RemoteBandUser(){

}

LocalBandUser* RemoteBandUser::GetLocalBandUser(){
    MILO_FAIL("Bad Conversion");
    return 0;
}

LocalBandUser* RemoteBandUser::GetLocalBandUser() const {
    MILO_FAIL("Bad Conversion");
    return 0;
}

RemoteBandUser* RemoteBandUser::GetRemoteBandUser(){}
RemoteBandUser* RemoteBandUser::GetRemoteBandUser() const {}
