#include "beatmatch/SongData.h"
#include "beatmatch/GameGemDB.h"
#include "beatmatch/VocalNote.h"
#include "beatmatch/SongParserSink.h"
#include "beatmatch/PlayerTrackConfig.h"
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

void SongData::AddSink(SongParserSink* sink){
    mSongParserSinks.push_back(sink);
}

void SongData::FixUpTrackConfig(PlayerTrackConfigList* plist){
    std::vector<TrackType> types;
    types.reserve(unk10);
    for(int i = 0; i < unk10; i++){
        types.push_back(mTrackInfos[i]->mType);
    }
    plist->Process(types);
}

void SongData::SetUpTrackDifficulties(PlayerTrackConfigList* plist){
    mTrackDifficulties.clear();
    mTrackDifficulties.reserve(plist->mTrackDiffs.size());
    for(int i = 0; i < plist->mTrackDiffs.size(); i++){
        int topush = plist->mTrackDiffs[i];
        if(topush == -1) topush = 0;
        mTrackDifficulties.push_back(topush);
    }
}

void SongData::UpdatePlayerTrackConfigList(PlayerTrackConfigList* plist){
    SetUpTrackDifficulties(plist);
    ComputeVocalRangeData();
}

// fn_804855E4
SongPos SongData::CalcSongPos(float f){
    MILO_ASSERT(mTempoMap, 0x6BA);
    MILO_ASSERT(mMeasureMap, 0x6BB);
    MILO_ASSERT(mBeatMap, 0x6BC);
    float tick = mTempoMap->TimeToTick(f);
    int itick = tick;
    int m, b, t;
    mMeasureMap->TickToMeasureBeatTick(itick, m, b, t);
    return SongPos(tick, mBeatMap->Beat(itick), m, b, t);
}

SongData::BackupTrack::~BackupTrack(){
    delete mGems;
}

SongData::FakeTrack::FakeTrack(Symbol sym) : mName(sym), mGems(new GameGemDB(1, 0x78)) {}
SongData::FakeTrack::~FakeTrack(){ delete mGems; }