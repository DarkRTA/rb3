#include "beatmatch/SongData.h"
#include "beatmatch/GameGem.h"
#include "beatmatch/GameGemDB.h"
#include "beatmatch/Phrase.h"
#include "beatmatch/TrackType.h"
#include "beatmatch/VocalNote.h"
#include "beatmatch/SongParserSink.h"
#include "beatmatch/PlayerTrackConfig.h"
#include "beatmatch/TuningOffsetList.h"
#include "beatmatch/DrumMixDB.h"
#include "beatmatch/DrumMap.h"
#include "decomp.h"
#include "macros.h"
#include "utl/BeatMap.h"
#include "utl/SongInfoAudioType.h"

DECOMP_FORCEACTIVE(SongData, ".vfv")

SongData::TrackInfo::TrackInfo(Symbol sym, SongInfoAudioType audioty, AudioTrackNum num, TrackType trackty, bool bb) :
    mName(sym), mLyrics(new TickedInfoCollection<String>()), mAudioType((BeatmatchAudioType)audioty), 
    mAudioTrackNum(num), mType(trackty), mIndependentSlots(bb) {

}

SongData::TrackInfo::~TrackInfo(){
    RELEASE(mLyrics);
}

SongData::SongData() : unk10(0), unk14(0), unk18(0), unk1c(0), unk20(-1), unk24(-1), unk28(0), mPhraseAnalyzer(0), unk98(0), mTempoMap(0), mMeasureMap(0), mBeatMap(0), mTuningOffsetList(0),
    unkd4(0), unkd8(0), unkdc(0), unke0(0), unk118(0), unk11c(0), unk120(0) {
    mVocalNoteLists.reserve(4);
    mVocalNoteLists.push_back(new VocalNoteList(this));
}

SongData::~SongData(){
    ResetTheTempoMap();
    ResetTheBeatMap();
    for(int i = 0; i < mTrackInfos.size(); i++){
        RELEASE(mTrackInfos[i]);
        RELEASE(mFills[i]);
        RELEASE(mDrumMaps[i]);
        RELEASE(mRollInfos[i]);
        RELEASE(mTrillInfos[i]);
        RELEASE(mRGRollInfos[i]);
        RELEASE(mRGTrillInfos[i]);
        RELEASE(mDrumMixDBs[i]);
        RELEASE(mGemDBs[i]);
        RELEASE(mPhraseDBs[i]);
    }
    for(int i = 0; i < mBackupTracks.size(); i++){
        RELEASE(mBackupTracks[i]);
    }
    for(int i = 0; i < mFakeTracks.size(); i++){
        RELEASE(mFakeTracks[i]);
    }
    RELEASE(mPhraseAnalyzer);
    RELEASE(mTempoMap);
    RELEASE(mTuningOffsetList);
    RELEASE(mMeasureMap);
    RELEASE(mBeatMap);
    for(int i = 0; i < mVocalNoteLists.size(); i++){
        RELEASE(mVocalNoteLists[i]);
    }
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

void SongData::AddTrack(int, AudioTrackNum a, Symbol s, SongInfoAudioType songTy, TrackType trackTy, bool b){
    if(songTy == kAudioTypeFake){
        mFakeTracks.push_back(new FakeTrack(s));
    }
    else {
        unk10++;
        mTrackInfos.push_back(new TrackInfo(s, songTy, a, trackTy, b));
        mFills.push_back(new DrumFillInfo());
        mDrumMaps.push_back(new DrumMap());
        mRollInfos.push_back(new RangedDataCollection<unsigned int>());
        mTrillInfos.push_back(new RangedDataCollection<std::pair<int, int> >());
        mRGRollInfos.push_back(new RangedDataCollection<RGRollChord>());
        mRGTrillInfos.push_back(new RangedDataCollection<RGTrill>());
        mDrumMixDBs.push_back(new DrumMixDB(unk14));
        mGemDBs.push_back(new GameGemDB(unk14, unk11c));
        mPhraseDBs.push_back(new PhraseDB(unk14));
        if(trackTy == kTrackVocals){
            int harmPartNum = 0;
            if(strneq(s.mStr, "HARM", 4)){
                harmPartNum = *(s.mStr + 4) - 0x31;
                if(harmPartNum < 0) MILO_FAIL("Harmony part too low. Found part %d", harmPartNum);
                if(harmPartNum >= 3) MILO_FAIL("Harmony part too high. Found part %d", harmPartNum);
                harmPartNum++;
            }
            while(mVocalNoteLists.size() <= harmPartNum){
                mVocalNoteLists.push_back(new VocalNoteList(this));
            }
            unk98 = harmPartNum;
            mVocalNoteLists[unk98]->SetTrackName(s);
        }
    }
}

#pragma push
#pragma dont_inline on
void SongData::ClearTrack(int idx){
    mGemDBs[idx]->Clear();
    mFills[idx]->Clear();
    mDrumMaps[idx]->Clear();
    mRollInfos[idx]->Clear();
    mTrillInfos[idx]->Clear();
    mRGRollInfos[idx]->Clear();
    mRGTrillInfos[idx]->Clear();
    mDrumMixDBs[idx]->Clear();
    mPhraseDBs[idx]->Clear();
    if(mTrackInfos[idx]->mType == kTrackVocals){
        if(mVocalNoteLists.size() != 1){
            MILO_FAIL("MIDI merge can't overwrite harmony parts");
        }
        mVocalNoteLists[0]->Clear();
        unk98 = 0;
    }
}
#pragma pop

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