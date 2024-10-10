#include "Stats.h"
#include "game/Performer.h"
#include "game/GameConfig.h"
#include "game/BandUser.h"
#include "game/Band.h"
#include "game/Game.h"
#include "utl/Symbols.h"
#include "utl/Messages.h"

#pragma push
#pragma dont_inline on
Performer::Performer(BandUser* user, Band* band) : mPollMs(0), mStats(Stats()), mBand(band), unk1e0(0), unk1e1(0), unk1e2(0), mScore(0), unk1fc(0), unk1fd(1), unk1fe(1), unk1ff(1), mProgressMs(0),
    unk204(0), mMultiplierActive(1), mNumRestarts(0) {
    Difficulty diff = !user ? TheGameConfig->GetAverageDifficulty() : user->GetDifficulty();
    mCrowd = new CrowdRating(user, diff);
}
#pragma pop

Performer::~Performer(){
    RELEASE(mCrowd);
}

int Performer::GetScore() const {
    if(mStats.FailedNoScore()) return 0;
    else return mScore + 0.01;
}

int Performer::GetIndividualScore() const {
    int score = GetScore();
    if(score > 0) return score - (int)mStats.GetBandContribution();
    else return 0;
}

int Performer::GetMultiplier(bool b, int& i1, int& i2, int& i3) const {
    i1 = 1;
    i2 = 1;
    i3 = 1;
    if(mMultiplierActive){
        i2 = mBand->EnergyMultiplier();
        return i2;
    }
    else return 1;
}

float Performer::GetCrowdRating() const {
    return mCrowd->GetValue();
}

float Performer::GetCrowdWarningLevel() const {
    return mCrowd->GetValue();
}

float Performer::GetRawCrowdRating() const {
    return mCrowd->GetRawValue();
}

bool Performer::IsInCrowdWarning() const {
    return mCrowd->IsInWarning();
}

float Performer::PollMs() const { return mPollMs; }

float Performer::GetCrowdBoost() const {
    return mBand->EnergyCrowdBoost();
}

#pragma push
#pragma dont_inline on
void Performer::Restart(bool b){
    mPollMs = 0;
    mProgressMs = 0;
    mScore = 0;
    unk204 = false;
    if(!b) mStats = Stats();
    unk1e0 = 0;
    unk1e1 = 0;
    unk1e2 = 0;
    mCrowd->Reset();
    mNumRestarts++;
}
#pragma pop

ExcitementLevel Performer::GetExcitement() const {
    return mCrowd->GetExcitement();
}

void Performer::SetMultiplierActive(bool b){ mMultiplierActive = b; }
bool Performer::GetMultiplierActive() const { return mMultiplierActive; }
void Performer::SetCrowdMeterActive(bool b){ mCrowd->SetActive(b); }
bool Performer::GetCrowdMeterActive(){ return mCrowd->IsActive(); }

void Performer::UpdateScore(int i){
    if(IsNet()) mScore = i;
}

void Performer::ForceScore(int i){ mScore = i; }

void Performer::SetStats(int i, const Stats& stats){
    mStats = stats;
    mStats.SetFinalized(true);
    mScore = i;
}

void Performer::BuildHitStreak(int i, float f){
    if(IsLocal()){
        mStats.BuildHitStreak(i, f);
        SendStreak();
    }
}

void Performer::EndHitStreak(){
    if(IsLocal()){
        mStats.EndHitStreak();
        SendStreak();
    }
}

void Performer::BuildMissStreak(int i){
    if(IsLocal()){
        mStats.BuildMissStreak(i);
    }
}

void Performer::EndMissStreak(){
    if(IsLocal()){
        mStats.EndMissStreak();
    }
}

void Performer::SendStreak(){
    MILO_ASSERT(IsLocal(), 0x170);
    if(unk1fe){
        Handle(send_streak_msg, false);
    }
}

void Performer::SetRemoteStreak(int i){
    if(IsNet()){
        mStats.SetCurrentStreak(i);
    }
}

void Performer::TrulyWinGame(){
    if(unk204 || !TheGameConfig->CanEndGame()) return;
    else {
        TheGame->SetGameOver(true);
        unk204 = true;
    }
}

void Performer::WinGame(int i){
    if(i > 0){
        mBand->ForceStars(i);
        TrulyWinGame();
    }
    if(IsLocal()){
        unk1e2 = true;
        Handle(send_finished_song_msg, false);
    }
}

void Performer::ForceStars(int i){
    mScore = GetScoreForStars(i);
}

bool Performer::LoseGame(){
    if(unk204 || !TheGameConfig->CanEndGame() || !TheGame->mIsPaused) return false; // TODO: fix the variable pulled from TheGame
    else {
        mCrowd->SetActive(false);
        TheGame->SetGameOver(false);
        SetLost();
        return true;
    }
}

void Performer::SetLost(){
    unk1e0 = true;
    unk204 = true;
}

void Performer::RemoteUpdateCrowd(float f){
    mCrowd->SetDisplayValue(f);
}

void Performer::RemoteFinishedSong(int i){
    UpdateScore(i);
    unk1e2 = true;
}

int Performer::GetNumRestarts() const { return mNumRestarts; }

void Performer::SetNoScorePercent(float f){
    mScore = 0;
    mStats.SetNoScorePercent(f);
}

#pragma push
#pragma dont_inline on
BEGIN_HANDLERS(Performer)
    HANDLE_EXPR(percent_complete, GetPercentComplete())
    HANDLE_EXPR(progress_ms, mProgressMs)
    HANDLE_ACTION(finalize_stats, FinalizeStats())
    HANDLE_EXPR(notes_hit, mStats.GetHitCount())
    HANDLE_EXPR(current_notes_hit_fraction, GetNotesHitFraction(0))
    HANDLE_EXPR(notes_hit_fraction, mStats.GetNotesHitFraction())
    HANDLE_EXPR(current_streak, mStats.GetCurrentStreak())
    HANDLE_EXPR(longest_streak, mStats.GetLongestStreak())
    HANDLE_EXPR(get_singer_count, mStats.GetNumberOfSingers())
    HANDLE_EXPR(get_singer_ranked_percentage, mStats.GetSingerRankedPercentage(_msg->Int(2), _msg->Int(3)))
    HANDLE_EXPR(get_singer_ranked_part, mStats.GetSingerRankedPart(_msg->Int(2), _msg->Int(3)))
    HANDLE_EXPR(get_vocal_part_percentage, mStats.GetVocalPartPercentage(_msg->Int(2)))
    HANDLE_EXPR(get_double_harmony_hit, mStats.GetDoubleHarmonyHit())
    HANDLE_EXPR(get_double_harmony_total, mStats.GetDoubleHarmonyPhraseCount())
    HANDLE_EXPR(get_triple_harmony_hit, mStats.GetTripleHarmonyHit())
    HANDLE_EXPR(get_triple_harmony_total, mStats.GetTripleHarmonyPhraseCount())
    HANDLE_EXPR(get_song_num_vocal_parts, GetSongNumVocalParts())
    HANDLE_EXPR(failed_deploy, mStats.GetFailedDeploy())
    HANDLE_EXPR(saved_count, mStats.GetPlayersSaved())
    HANDLE_EXPR(fill_hit_count, mStats.GetFillHitCount())
    HANDLE_EXPR(strummed_down, mStats.GetStrummedDown())
    HANDLE_EXPR(strummed_up, mStats.GetStrummedUp())
    HANDLE_EXPR(deploy_count, mStats.GetDeployCount())
    HANDLE_EXPR(solo_percentage, mStats.GetSoloPercentage())
    HANDLE_EXPR(perfect_solo_with_solo_buttons, mStats.GetPerfectSoloWithSoloButtons())
    HANDLE_EXPR(notes_per_streak, GetNotesPerStreak())
    HANDLE_EXPR(was_never_bad, mCrowd->GetMinValue() > mCrowd->GetThreshold(kExcitementBad))
    HANDLE_EXPR(stats_finalized, mStats.GetFinalized())
    HANDLE_ACTION(win, WinGame(_msg->Int(2)))
    HANDLE_ACTION(lose, LoseGame())
    HANDLE_EXPR(score, GetScore())
    HANDLE_EXPR(accumulated_score, GetAccumulatedScore())
    HANDLE_EXPR(total_stars, GetTotalStars())
    HANDLE_EXPR(band, GetBand())
    HANDLE_EXPR(crowd_rating_active, mCrowd->IsActive())
    HANDLE_EXPR(crowd_rating, mCrowd->GetValue())
    HANDLE_EXPR(raw_crowd_rating, GetRawValue())
    HANDLE_EXPR(display_crowd_rating, GetDisplayValue())
    HANDLE_ACTION(set_crowd_rating_active, mCrowd->SetActive(_msg->Int(2)))
    HANDLE_ACTION(set_crowd_rating, mCrowd->SetValue(_msg->Float(2)))
    HANDLE_ACTION(remote_update_score, UpdateScore(_msg->Int(2)))
    HANDLE_ACTION(remote_update_crowd, RemoteUpdateCrowd(_msg->Float(2)))
    HANDLE_ACTION(send_remote_stats, SendRemoteStats(_msg->Obj<BandUser>(2)))
    HANDLE_ACTION(remote_streak, SetRemoteStreak(_msg->Int(2)))
    HANDLE_ACTION(remote_finished_song, RemoteFinishedSong(_msg->Int(2)))
    HANDLE_ACTION(on_game_lost, SetLost())
    HANDLE_EXPR(get_multiplier_active, GetMultiplierActive())
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x24B)
END_HANDLERS
#pragma pop