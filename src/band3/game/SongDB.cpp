#include "game/SongDB.h"

SongDB::SongDB() : mSongData(new SongData()), mSongDurationMs(0), mCodaStartTick(-1), mMultiplayerAnalyzer(new MultiplayerAnalyzer(mSongData)), unk24(-1), unk28(-1) {
    mSongData->AddSink(this);
}

SongDB::~SongDB(){
    RELEASE(mSongData);
}

void SongDB::PostLoad(DataEventList* list){
    ParseEvents(list);
    SpewAllVocalNotes();
    SpewTrackSizes();
    SetupPhrases();
    DisableCodaGems();
    RunMultiplayerAnalyzer();
    SetupPracticeSections();
}

void SongDB::RunMultiplayerAnalyzer(){

}

void SongDB::RebuildPhrases(int i){
    ClearTrackPhrases(i);
    mSongData->SendPhrases(i);
}

void SongDB::RebuildData(){
    SetupPhrases();
    RunMultiplayerAnalyzer();
}

void SongDB::OverrideBasePoints(int i, TrackType ty, const UserGuid& guid, int i1, int i2, int i3){
    mMultiplayerAnalyzer->OverrideBasePoints(i, ty, guid, i1, i2, i3);
}

int SongDB::TotalBasePoints(){ return mMultiplayerAnalyzer->TotalBasePoints(); }
float SongDB::GetSongDurationMs() const { return mSongDurationMs; }
int SongDB::GetCodaStartTick() const { return mCodaStartTick; }

bool SongDB::IsInCoda(int i) const {
    return mCodaStartTick != -1 && i >= mCodaStartTick;
}

int SongDB::GetNumTracks() const { return mSongData->unk10; }
int SongDB::GetNumTrackData() const { return mTrackData.size(); }

int SongDB::GetBaseMaxPoints(const UserGuid& u) const {
    return mMultiplayerAnalyzer->GetMaxPoints(u);
}

int SongDB::GetBaseMaxStreakPoints(const UserGuid& u) const {
    return mMultiplayerAnalyzer->GetMaxStreakPoints(u);
}

int SongDB::GetBaseBonusPoints(const UserGuid& u) const {
    return mMultiplayerAnalyzer->GetBonusPoints(u);
}

GameGemList* SongDB::GetGemList(int i) const {
    return mSongData->GetGemList(i);
}

GameGemList* SongDB::GetGemListByDiff(int i, int j) const {
    return mSongData->GetGemListByDiff(i, j);
}

const std::vector<GameGem>& SongDB::GetGems(int i) const {
    return mSongData->GetGemList(i)->mGems;
}

#pragma push
#pragma dont_inline on
void SongDB::AddTrack(int, Symbol, SongInfoAudioType, TrackType ty, bool){
    mTrackData.push_back(ty);
}
#pragma pop

std::vector<RangeSection>& SongDB::GetRangeSections(){ return mSongData->mRangeSections; }

void SongDB::ChangeDifficulty(int i, Difficulty diff){
    mSongData->ChangeTrackDiff(i, diff);
}

void SongDB::SetTrainerGems(int i, int j){
    unk24 = i;
    unk28 = j;
}