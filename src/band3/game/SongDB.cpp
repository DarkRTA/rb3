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

// void __thiscall SongDB::RebuildData(SongDB *this)

// {
//   SetupPhrases(this);
//   RunMultiplayerAnalyzer(this);
//   return;
// }