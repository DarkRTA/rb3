#include "beatmatch/SongData.h"
#include "beatmatch/GameGemDB.h"

SongData::TrackInfo::TrackInfo(Symbol sym, SongInfoAudioType audioty, AudioTrackNum num, TrackType trackty, bool bb) :
    mName(sym), mLyrics(new TickedInfoCollection<String>()), mAudioType((BeatmatchAudioType)audioty), 
    mAudioTrackNum(num), mType(trackty), mIndependentSlots(bb) {

}

SongData::TrackInfo::~TrackInfo(){
    delete mLyrics;
    mLyrics = 0;
}

SongData::SongData() : unk10(0), unk14(0), unk18(0), unk1c(0), unk20(-1), unk24(-1), unk28(0) {
    
}

SongData::~SongData(){
    
}

SongData::BackupTrack::~BackupTrack(){
    delete mGems;
}

SongData::FakeTrack::FakeTrack(Symbol sym) : mName(sym), mGems(new GameGemDB(1, 0x78)) {}
SongData::FakeTrack::~FakeTrack(){ delete mGems; }