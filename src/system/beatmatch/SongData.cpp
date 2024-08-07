#include "beatmatch/SongData.h"
#include "beatmatch/GameGemDB.h"
#include "beatmatch/VocalNote.h"
#include "utl/BeatMap.h"

SongData::TrackInfo::TrackInfo(Symbol sym, SongInfoAudioType audioty, AudioTrackNum num, TrackType trackty, bool bb) :
    mName(sym), mLyrics(new TickedInfoCollection<String>()), mAudioType((BeatmatchAudioType)audioty), 
    mAudioTrackNum(num), mType(trackty), mIndependentSlots(bb) {

}

SongData::TrackInfo::~TrackInfo(){
    delete mLyrics;
    mLyrics = 0;
}

SongData::SongData() : unk10(0), unk14(0), unk18(0), unk1c(0), unk20(-1), unk24(-1), unk28(0), unk94(0), unk98(0), mTempoMap(0), mMeasureMap(0), mBeatMap(0), mTuningOffsetList(0),
    unkd4(0), unkd8(0), unkdc(0), unke0(0), unk118(0), unk11c(0), unk120(0) {
    mVocalNoteLists.reserve(4);
    mVocalNoteLists.push_back(new VocalNoteList(this));
}

SongData::~SongData(){
    ResetTheTempoMap();
    ResetTheBeatMap();
}

SongData::BackupTrack::~BackupTrack(){
    delete mGems;
}

SongData::FakeTrack::FakeTrack(Symbol sym) : mName(sym), mGems(new GameGemDB(1, 0x78)) {}
SongData::FakeTrack::~FakeTrack(){ delete mGems; }