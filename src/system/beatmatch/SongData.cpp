#include "beatmatch/SongData.h"
#include "beatmatch/BeatMatcher.h"
#include "beatmatch/GameGem.h"
#include "beatmatch/GameGemDB.h"
#include "beatmatch/GameGemList.h"
#include "beatmatch/InternalSongParserSink.h"
#include "beatmatch/Phrase.h"
#include "beatmatch/PhraseAnalyzer.h"
#include "beatmatch/RGChords.h"
#include "beatmatch/SongParser.h"
#include "beatmatch/TimeSpanVector.h"
#include "beatmatch/TrackType.h"
#include "beatmatch/VocalNote.h"
#include "beatmatch/SongParserSink.h"
#include "beatmatch/PlayerTrackConfig.h"
#include "beatmatch/TuningOffsetList.h"
#include "beatmatch/DrumMixDB.h"
#include "beatmatch/DrumMap.h"
#include "decomp.h"
#include "macros.h"
#include "math/FileChecksum.h"
#include "math/StreamChecksum.h"
#include "obj/Data.h"
#include "os/Debug.h"
#include "os/System.h"
#include "os/Timer.h"
#include "stl/_pair.h"
#include "utl/BeatMap.h"
#include "utl/FakeSongMgr.h"
#include "utl/FilePath.h"
#include "utl/FileStream.h"
#include "utl/MBT.h"
#include "utl/MemMgr.h"
#include "utl/MemStream.h"
#include "utl/RangedData.h"
#include "utl/SongInfoAudioType.h"
#include "utl/SongInfoCopy.h"
#include "utl/TickedInfo.h"

const int kHarm3VocalNoteList = 3;

DECOMP_FORCEACTIVE(SongData, ".vfv")

SongData::TrackInfo::TrackInfo(Symbol sym, SongInfoAudioType audioty, AudioTrackNum num, TrackType trackty, bool bb) :
    mName(sym), mLyrics(new TickedInfoCollection<String>()), mAudioType((BeatmatchAudioType)audioty), 
    mAudioTrackNum(num), mType(trackty), mIndependentSlots(bb) {

}

SongData::TrackInfo::~TrackInfo(){
    RELEASE(mLyrics);
}

SongData::SongData() : mNumTracks(0), mNumDifficulties(0), mLoaded(0), mSongInfo(0), mSectionStartTick(-1), mSectionEndTick(-1), mFakeHitGemsInFill(0), mPhraseAnalyzer(0), mLoadingVocalNoteListIndex(0), mTempoMap(0), mMeasureMap(0), mBeatMap(0), mTuningOffsetList(0),
    unkd4(0), mMemStream(0), mSongParser(0), mPlayerTrackConfigList(0), mGems(0), mHopoThreshold(0), mDetailedGrid(0) {
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

void Validate(MemStream* ms, const char* file, bool b){
    if(UsingCD() && HasFileChecksumData()){
        StreamChecksumValidator v;
        StreamChecksumValidator& vref = v;
        if(vref.Begin(file, b)){
            vref.Update((const unsigned char*)ms->Buffer(), ms->BufferSize());
            vref.End();
            vref.Validate();
        }
    }
}

void SongData::Load(SongInfo* info, int i, PlayerTrackConfigList* pList, std::vector<MidiReceiver*>& midircvrs, bool bb, SongDataValidate v){
    const char* midi = FakeSongMgr::MidiFile(info);
    FileStream fs(midi, FileStream::kRead, false);
    mMemStream = new MemStream();
    {
        MemDoTempAllocations m(true, false);
        mMemStream->Resize(fs.Size());
        fs.Read((void*)mMemStream->Buffer(), fs.Size());
        if(v == kSongData_ValidateUsingNameOnly || v == kSongData_Validate){
            Validate(mMemStream, midi, v == kSongData_ValidateUsingNameOnly);
        }
    }
    Load(midi, info, i, pList, midircvrs, bb);
    FileStream fs88(FakeSongMgr::GetPath(info, ".vfv"), FileStream::kRead, true);
    if(!fs88.Fail()){
        int count = 0;
        fs88 >> count;
        vecc4.clear();
        veccc.clear();
        for(int i = 0; i < count; i++){
            float f94 = 0;
            float f98 = 0;
            fs88 >> f94; fs88 >> f98;
            vecc4.push_back(f94);
            veccc.push_back(f98);
        }
    }
}

void SongData::Load(const char* midifile, SongInfo* info, int i, PlayerTrackConfigList* pList, std::vector<MidiReceiver*>& midircvrs, bool bb){
#ifdef MILO_DEBUG
    if(DataVariable("log_midi_file_load").Int()){
        MILO_LOG("Loading MIDI file %s\n", midifile);
    }
#endif
    mSongInfo = info;
    mNumDifficulties = i;
    mDetailedGrid = false;
    mHopoThreshold = mSongInfo->GetHopoThreshold();
    mKeyboardRangeSections.resize(mNumDifficulties);
    MILO_ASSERT(mTempoMap == NULL, 0xF5);
    MILO_ASSERT(mTuningOffsetList == NULL, 0xF6);
    MILO_ASSERT(mMeasureMap == NULL, 0xF7);
    MILO_ASSERT(mBeatMap == NULL, 0xF8);
    MILO_ASSERT(mPhraseAnalyzer == NULL, 0xF9);
    mBeatMap = new BeatMap();
    SetTheBeatMap(mBeatMap);
    mPhraseAnalyzer = new PhraseAnalyzer(this);
    int numchannels = mSongInfo->NumChannelsOfTrack(kAudioTypeDrum);
    mSongParser = new SongParser(*this, i, mTempoMap, mMeasureMap, numchannels);
    mTuningOffsetList = new TuningOffsetList();
    for(int i = 0; i < midircvrs.size(); i++){
        mSongParser->AddReceiver(midircvrs[i]);
    }
    unkc = 0;
    mPlayerTrackConfigList = pList;
    mSongParser->SetNumPlayers(mPlayerTrackConfigList->NumConfigs());
    mSongParser->SetSectionBounds(mSectionStartTick, mSectionEndTick);
    mSongParser->ReadMidiFile(*mMemStream, midifile, mSongInfo);
    if(bb) while(!Poll());
}

bool SongData::Poll(){
    if(mSongParser){
        Timer timer;
        timer.Restart();
        mSongParser->Poll();
        if(mSongParser->NoMidiReader()){
            unkc++;
            RELEASE(mMemStream);
            int i6 = unkc;
            if(i6 <= mSongInfo->NumExtraMidiFiles()){
                const char* midi = mSongInfo->GetExtraMidiFile(i6 - 1);
                MILO_LOG("MIDI: merged filename: %s\n", midi);
                unke4 = FilePath(FileRoot(), midi);
                MILO_LOG("MIDI: merged filename2: %s\n", unke4);
                FileStream fs(midi, FileStream::kRead, false);
                mMemStream = new MemStream();
                {
                    MemDoTempAllocations m(true, false);
                    mMemStream->Resize(fs.Size());
                    fs.Read((void*)mMemStream->Buffer(), fs.Size());
                }
                mSongParser->MergeMidiFile(*mMemStream, midi);
                return false;
            }
            else {
                PostLoad(mPlayerTrackConfigList);
                RELEASE(mSongParser);
                return true;
            }
        }
        else return false;
    }
    else return true;
}

void SongData::AddSink(SongParserSink* sink){
    mSongParserSinks.push_back(sink);
}

void SongData::FixUpTrackConfig(PlayerTrackConfigList* plist){
    std::vector<TrackType> types;
    types.reserve(mNumTracks);
    for(int i = 0; i < mNumTracks; i++){
        types.push_back(mTrackInfos[i]->mType);
    }
    plist->Process(types);
}

void SongData::SetUpTrackDifficulties(PlayerTrackConfigList* plist){
    mTrackDifficulties.clear();
    mTrackDifficulties.reserve(plist->mTrackDiffs.size());
    for(int i = 0; i < (int)plist->mTrackDiffs.size(); i++){
        int topush = plist->mTrackDiffs[i];
        if(topush == -1) topush = 0;
        mTrackDifficulties.push_back(topush);
    }
}

void SongData::UpdatePlayerTrackConfigList(PlayerTrackConfigList* plist){
    SetUpTrackDifficulties(plist);
    ComputeVocalRangeData();
}

void SongData::PostLoad(PlayerTrackConfigList* pList){
    FixUpTrackConfig(pList);
    SetUpTrackDifficulties(pList);
    for(std::vector<SongParserSink*>::iterator it = mSongParserSinks.begin(); it != mSongParserSinks.end(); ++it){
        (*it)->SetNumTracks(mNumTracks);
    }
    for(int i = 0; i < mGemDBs.size(); i++){
        mGemDBs[i]->Finalize();
    }
    if(mTempoMap) mTempoMap->Finalize();
    else MILO_WARN("%s: MIDI file does not have a valid tempo map", SongFullPath());
    MakeBackupTracks();
    RestoreAllTracksFromBackup();
    for(int i = 0; i < mNumTracks; i++){
        PostLoadTrack(i);
    }
    mPhraseAnalyzer->Analyze();
    for(std::vector<BeatMatcher*>::iterator it = mBeatMatchers.begin(); it != mBeatMatchers.end(); ++it){
        (*it)->PostLoad();
    }
    PostLoadVocals();
    mLoaded = true;
}

void SongData::PostLoadTrack(int idx){
    TrackInfo* trackInfo = mTrackInfos[idx];
    if(!trackInfo->FakeAudio()){
        const PhraseList& phrases = mPhraseDBs[idx]->GetPhraseList(0, kCommonPhrase);
        for(std::vector<Phrase>::const_iterator it = phrases.mPhrases.begin(); it != phrases.mPhrases.end(); ++it){
            mPhraseAnalyzer->AddInfo(idx, trackInfo->mType, it->GetTick(), it->GetTick() + it->GetDurationTicks(), trackInfo->mAudioType == kAudioVocals);
        }
        for(std::vector<BeatMatcher*>::iterator it = mBeatMatchers.begin(); it != mBeatMatchers.end(); ++it){
            (*it)->AddTrack(idx, trackInfo->mName, (SongInfoAudioType)trackInfo->mAudioType, trackInfo->mType, trackInfo->mIndependentSlots);
        }
        for(std::vector<SongParserSink*>::iterator it = mSongParserSinks.begin(); it != mSongParserSinks.end(); ++it){
            (*it)->AddTrack(idx, trackInfo->mName, (SongInfoAudioType)trackInfo->mAudioType, trackInfo->mType, trackInfo->mIndependentSlots);
        }
        if(HasTrackDiffs()){
            SendPhrases(idx);
            SendGems(idx);
        }
    }
}

void SongData::SendPhrases(int idx){
    int curTrackDiff = mTrackDifficulties[idx];
    PhraseDB* curPhraseDB = mPhraseDBs[idx];
    for(int i = 0; i < kNumPhraseTypes; i++){
        const PhraseList& phrases = curPhraseDB->GetPhraseList(curTrackDiff, (BeatmatchPhraseType)i);
        for(std::vector<Phrase>::const_iterator it = phrases.mPhrases.begin(); it != phrases.mPhrases.end(); ++it){
            for(std::vector<SongParserSink*>::iterator sit = mSongParserSinks.begin(); sit != mSongParserSinks.end(); ++sit){
                (*sit)->AddPhrase((BeatmatchPhraseType)i, idx, *it);
            }
        }
    }
}

void SongData::SendGems(int idx){
    int curTrackDiff = mTrackDifficulties[idx];
    const GameGemDB* curDB = mGemDBs[curTrackDiff];
    const std::vector<GameGem>& gems = curDB->GetDiffGemList(idx)->mGems;
    for(std::vector<GameGem>::const_iterator it = gems.begin(); it != gems.end(); ++it){
        for(std::vector<SongParserSink*>::iterator sit = mSongParserSinks.begin(); sit != mSongParserSinks.end(); ++sit){
            (*sit)->AddMultiGem(idx, *it);
        }
    }
}

void SongData::PostLoadVocals(){
    for(int i = 0; i < mVocalNoteLists.size(); i++){
        VocalNoteList* curList = mVocalNoteLists[i];
        bool b = i == 0 || i == 1;
        if(i == 2){
            curList->CopyLyricPhrases();
        }
        if(i > 1){
            curList->CopyPhrasesFrom(mVocalNoteLists[1]);
        }
        curList->NotesDone(*mTempoMap, b);
        if(i == 2 && curList->mLyricPhrases.empty()){
            MILO_WARN("%s: no lyric phrases authored for HARM2, defaulting to HARM1 phrases", SongFullPath());
            curList->CopyLyricPhrases();
        }
    }

    std::vector<std::pair<float, float> > floatPairVec;
    for(int i = 1; i < mVocalNoteLists.size(); i++){
        VocalNoteList* curList = mVocalNoteLists[i];
        std::vector<std::pair<float, float> > morePairs;
        curList->GenerateLegalFreestyleSections(morePairs);
        if(i == 1) floatPairVec = morePairs;
        else {
            std::vector<std::pair<float, float> > pairs3;
            IntersectTimeSpans(floatPairVec, morePairs, pairs3);
            floatPairVec = pairs3;
        }
    }

    for(int i = 1; i < mVocalNoteLists.size(); i++){
        VocalNoteList* curList = mVocalNoteLists[i];
        std::vector<std::pair<float, float> > morePairs;
        IntersectTimeSpans(curList->mFreestyleSections, floatPairVec, morePairs);
        curList->SetFreestyleSections(morePairs);
    }

    if(mVocalNoteLists.size() == 4){
        VocalNoteList* list2 = mVocalNoteLists[2];
        VocalNoteList* list3 = mVocalNoteLists[3];
        std::vector<std::pair<float, float> > morePairs;
        IntersectTimeSpans(list2->mFreestyleSections, list3->mFreestyleSections, morePairs);
        list2->SetFreestyleSections(morePairs);
        list3->SetFreestyleSections(morePairs);
    }

    for(int i = 0; i < mVocalNoteLists.size(); i++){
        mVocalNoteLists[i]->RemoveInvalidFreestyleSections();
    }
    ComputeVocalRangeData();
    ValidateVocalSPPhrases();
}

void SongData::ComputeVocalRangeData(){
    mRangeSections.clear();
    mRangeSections.push_back(RangeSection(0, 0));
    for(std::map<int, float>::iterator it = mRangeShifts.begin(); it != mRangeShifts.end(); ++it){
        RangeSection s;
        s.unk0 = it->first;
        s.unk4 = it->second;
        mRangeSections.push_back(s);
    }
    int i9 = 0;
    int u10 = 0;
    if(mPlayerTrackConfigList->UseVocalHarmony()){
        i9 = mVocalNoteLists.size() - 1;
        u10 = 1;
    }

    for(int i = 0; i < mRangeSections.size(); i++){
        RangeSection& curSect = mRangeSections[i];
        int i2 = -1;
        if(i + 1 < mRangeSections.size()){
            i2 = mRangeSections[i].unk0;
        }
        for(; u10 <= i9; u10++){
            mVocalNoteLists[u10]->UpdatePitchRangeTickDelimited(curSect.unk0, i2, curSect.unk8, curSect.unkc);
        }
        if(curSect.unk8 > 200.0f){
            curSect.unk8 = i > 0 ? mRangeSections[i - 1].unk8 : 60.0f;
        }
        if(curSect.unkc < 0){
            curSect.unkc = i > 0 ? mRangeSections[i - 1].unkc : 72.0f;
        }
        static bool dumpRangeSections;
        if(dumpRangeSections){
            MILO_LOG("New Range Section: tick %d, (%.1f, %.1f) size: %.0f\n", curSect.unk0, curSect.unk8, curSect.unkc, curSect.unkc - curSect.unk8);
        }
    }
}

void SongData::UnflipGems(int i1, int i2, int i3){
    std::vector<GameGem>& backup_gems = mBackupTracks[i2]->mGems->GetDiffGemList(i3)->mGems;
    TickedInfoCollection<String>& backup_mixes = mBackupTracks[i2]->mMixes->GetMixList(i3);
    std::vector<GameGem>& gems = mGemDBs[i1]->GetDiffGemList(i3)->mGems;
    TickedInfoCollection<String>& mixes = mDrumMixDBs[i1]->GetMixList(i3);
    MILO_ASSERT(backup_gems.size() == gems.size(), 0x2CE);
    MILO_ASSERT(backup_mixes.Size() == mixes.Size(), 0x2CF);
    DataArray* cfg = SystemConfig("beatmatcher", "audio");
    DataArray* submixArr = cfg->FindArray("flipped_submixes", false);
    if(submixArr && !backup_mixes.mInfos.empty()){
        Symbol tag = backup_mixes.mInfos[0].mInfo.c_str();
        Symbol s;
        bool found = submixArr->FindData(tag, s, false);
        if(found){
            mixes.SetInfo(0, s);
        }
        int i11 = 1;
        int i7 = backup_mixes.Size() == 1 ? 0x7fffffff : backup_mixes.mInfos[1].mTick;
        for(int g = 0; g < gems.size(); g++){
            MILO_ASSERT(backup_gems[g].GetTick() == gems[g].GetTick(), 0x2F4);
            if(backup_gems[g].GetTick() >= i7){
                Symbol tag = backup_mixes.mInfos[i11].mInfo.c_str();
                bool found = submixArr->FindData(tag, s, false);
                if(found){
                    mixes.SetInfo(i11, s);
                }
                i11++;
                if(i11 == backup_mixes.Size()){
                    if(!found) return;
                    i7 = 0x7fffffff;
                }
                else i7 = backup_mixes.mInfos[i11].mTick;
            }
            else if(found) gems[g].Flip(backup_gems[g]);
        }
    }
}

void SongData::RestoreGems(int i1, int i2, int i3){
    GameGemList* backup_gems = mBackupTracks[i2]->mGems->GetDiffGemList(i3);
    GameGemList* gems = mGemDBs[i2]->GetDiffGemList(i3);
    // gems->mGems = backup_gems->mGems;
    if(mBackupTracks[i2]->mMixes){
        TickedInfoCollection<String>& backup_mixes = mBackupTracks[i2]->mMixes->GetMixList(i3);
        TickedInfoCollection<String>& mixes = mDrumMixDBs[i2]->GetMixList(i3);
        mixes = backup_mixes;
    }
}

void SongData::TrimOverlappingGems(int, int, int){
    MILO_WARN("Empty track found for SongData::TrimOverlappingGems!");
    MILO_WARN("shortestDurationTick >= 0");
    MILO_WARN("shortestDurationMs >= 0.0f");
}

void SongData::ValidateVocalSPPhrases(){
    Symbol voxSym;
    int i14;
    bool harm = true;
    if(mPlayerTrackConfigList->UseVocalHarmony()){
        i14 = std::min<int>(kHarm3VocalNoteList, mVocalNoteLists.size() - 1);
        voxSym = "HARM1";
    }
    else {
        harm = false;
        i14 = 0;
        voxSym = "PART VOCALS";
    }

    int u15 = harm;
    int trackIdx;
    for(trackIdx = 0; trackIdx < mTrackInfos.size(); trackIdx++){
        if(mTrackInfos[trackIdx]->mName == voxSym) break;
    }

    if(trackIdx == mTrackInfos.size() || mNumDifficulties <= 0) return;
    else {
        PhraseDB* curDB = mPhraseDBs[trackIdx];
        const PhraseList& phrases = curDB->GetPhraseList(mTrackDifficulties[trackIdx], kCommonPhrase);
        VocalNoteList* curVoxList = mVocalNoteLists[u15];
        for(int i = 0; i < phrases.mPhrases.size(); i++){
            float f20 = phrases.mPhrases[i].mMs;
            float f1 = phrases.mPhrases[i].mMs;
            float f18 = phrases.mPhrases[i].GetDurationMs();
            int i13 = 0; // change type
            bool b2 = false;
            for(int j = u15; j <= i14; j++){
                if(mVocalNoteLists[j]->NextNote(f20)){
                    b2 = true;
                    break;
                }
            }
            if(!b2){
                curVoxList->GetTrackName();
                SongFullPath();
            }
            else {
                VocalNote* next = curVoxList->NextNote(f20);
                if(next){
                    float f19 = next->GetMs();
                    if(f20 > f19){
                        curVoxList->GetTrackName();
                        SongFullPath();
                    }
                }
            }
        }
    }

    MILO_WARN("NOTIFY %s %s : vocal overdrive phrase at %i ms is after all notes.\n");
    MILO_WARN("NOTIFY %s %s : vocal overdrive phrase at %i ms begins during a note.\n");
    MILO_WARN("NOTIFY %s %s : vocal overdrive phrase at %i ms starts mid-phrase.\n");
    MILO_WARN("NOTIFY %s %s : vocal overdrive phrase at %i ms ends prematurely.\n");
    MILO_WARN("NOTIFY %s %s : vocal overdrive phrase at %i ms cuts into next phrase.\n");
}

void SongData::AddBeatMatcher(BeatMatcher* bm){
    mBeatMatchers.push_back(bm);
}

void SongData::PostDynamicAdd(BeatMatcher* bm, int trk){
    if(HasBackupTrack(trk)){
        RestoreTrackFromBackup(trk);
    }
    for(int i = 0; i < mNumTracks; i++){
        TrackInfo* curTrackInfo = mTrackInfos[i];
        bm->AddTrack(i, curTrackInfo->mName, (SongInfoAudioType)curTrackInfo->mAudioType, curTrackInfo->mType, curTrackInfo->mIndependentSlots);
    }
}

void SongData::RemoveBeatMatcher(BeatMatcher* bm){
    std::vector<BeatMatcher*>::iterator it = std::find(mBeatMatchers.begin(), mBeatMatchers.end(), bm);
    mBeatMatchers.erase(it, mBeatMatchers.end());
}

const PhraseList& SongData::GetPhraseList(int i, BeatmatchPhraseType ty) const {
    return mPhraseDBs[i]->GetPhraseList(mTrackDifficulties[i], ty);
}

void SongData::AddTrack(int, AudioTrackNum a, Symbol s, SongInfoAudioType songTy, TrackType trackTy, bool b){
    if(songTy == kAudioTypeFake){
        mFakeTracks.push_back(new FakeTrack(s));
    }
    else {
        mNumTracks++;
        mTrackInfos.push_back(new TrackInfo(s, songTy, a, trackTy, b));
        mFills.push_back(new DrumFillInfo());
        mDrumMaps.push_back(new DrumMap());
        mRollInfos.push_back(new RangedDataCollection<unsigned int>());
        mTrillInfos.push_back(new RangedDataCollection<std::pair<int, int> >());
        mRGRollInfos.push_back(new RangedDataCollection<RGRollChord>());
        mRGTrillInfos.push_back(new RangedDataCollection<RGTrill>());
        mDrumMixDBs.push_back(new DrumMixDB(mNumDifficulties));
        mGemDBs.push_back(new GameGemDB(mNumDifficulties, mHopoThreshold));
        mPhraseDBs.push_back(new PhraseDB(mNumDifficulties));
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
            mLoadingVocalNoteListIndex = harmPartNum;
            mVocalNoteLists[mLoadingVocalNoteListIndex]->SetTrackName(s);
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
        mLoadingVocalNoteListIndex = 0;
    }
}
#pragma pop

void SongData::OnEndOfTrack(int i, bool b){
    if(b && i < mGemDBs.size()){
        mGemDBs[i]->MergeChordGems();
    }
}

void SongData::AddMultiGem(int iii, const MultiGemInfo& info){
    unkd4 = Max(info.ms, info.duration_ms);
    int curTrack = info.track;
    if(curTrack >= 100){
        mFakeTracks[curTrack - 100]->mGems->AddMultiGem(0, info);
    }
    else {
        if(!mGemDBs[curTrack]->AddMultiGem(iii, info)){
            MILO_WARN("%s (%s): Overlapping or too-close gems at %s for difficulty %d", SongFullPath(), mTrackInfos[info.track]->mName, TickFormat(info.tick, *mMeasureMap), iii);
        }
    }
}

void SongData::AddVocalNote(const VocalNote& note){
    mVocalNoteLists[mLoadingVocalNoteListIndex]->AddNote(note);
}

void SongData::AddPitchOffset(int tick, float offset){
    mTuningOffsetList->AddInfo(tick, offset);
}

void SongData::AddLyricShift(int i){
    mVocalNoteLists[mLoadingVocalNoteListIndex]->AddLyricShift(mTempoMap->TickToTime(i));
}

void SongData::OnTambourineGem(int i){
    mVocalNoteLists[mLoadingVocalNoteListIndex]->AddTambourineGem(i);
}

void SongData::StartVocalPlayerPhrase(int i, int j){
    mVocalNoteLists[mLoadingVocalNoteListIndex]->StartPlayerPhrase(i, j);
}

void SongData::EndVocalPlayerPhrase(int i, int j){
    mVocalNoteLists[mLoadingVocalNoteListIndex]->EndPlayerPhrase(i, j);
}

void SongData::AddPhrase(BeatmatchPhraseType ty, int i2, int i3, float f4, int i5, float f6, int i7){
    int i1 = i2;
    if(i2 == -1){
        i2 = 0;
        i1 = 3;
    }
    for(; i2 <= i1; i2++){
        mPhraseDBs[i3]->AddPhrase(ty, i2, f4, i5, f6, i7);
    }
}

void SongData::AddDrumFill(int i1, int i2, int i3, int i4, bool b5){
    bool fillBool = mFills[i1]->AddFill(i3, i4 - i3, b5);
    bool laneBool = mFills[i1]->AddLanes(i3, i2);
    if(!(fillBool & 1 & laneBool)){
        MILO_WARN("%s (%s): Error adding %s at %s", SongFullPath(), mTrackInfos[i1]->mName,
            b5 ? "Big Rock Ending lanes" : "drum fill", TickFormat(i3, *mMeasureMap));
    }
}

void SongData::AddRoll(int i1, int i2, unsigned int ui, int i4, int i5){
    if(i1 < 100) mRollInfos[i1]->AddData(i2, i4, i5, ui);
}

void SongData::AddTrill(int i1, int i2, int t1, int t2, int i4, int i5){
    if(i1 < 100) mTrillInfos[i1]->AddData(i2, i4, i5, std::make_pair(t1, t2));
}

void SongData::AddRGRoll(int i1, int i2, const RGRollChord& chord, int i4, int i5){
    mRGRollInfos[i1]->AddData(i2, i4, i5, chord);
}

void SongData::AddRGTrill(int i1, int i2, const RGTrill& trill, int i4, int i5){
    mRGTrillInfos[i1]->AddData(i2, i4, i5, trill);
}

void SongData::AddMix(int i1, int i2, int diff, const char* cc){
    if(diff < 0 || diff >= mNumDifficulties){
        MILO_WARN("%s (%s): Error adding mix '%s' at %s; difficulty %d is out of range", SongFullPath(), mTrackInfos[i1]->mName, cc, TickFormat(i2, *mMeasureMap), diff);
    }
    else {
        if(!mDrumMixDBs[i1]->AddMix(diff, i2, cc)){
            MILO_WARN("%s (%s): Error adding mix '%s' at %s", SongFullPath(), mTrackInfos[i1]->mName, cc, TickFormat(i2, *mMeasureMap));
        }
    }
}

void SongData::AddLyricEvent(int i1, int i2, const char* cc){
    if(mTrackInfos[i1]->mLyrics->AddInfo(i2, cc)) return;
    else MILO_WARN("%s (%s): Error adding lyric event '%s' at %s", SongFullPath(), mTrackInfos[i1]->mName, cc, TickFormat(i2, *mMeasureMap));
}

void SongData::DrumMapLane(int i1, int i2, int i3, bool laneOn){
    if(laneOn){
        if(!mDrumMaps[i1]->LaneOn(i2, i3)){
            MILO_WARN("%s (%s): Error adding drum lane %d at %s", SongFullPath(), mTrackInfos[i1]->mName, i3, TickFormat(i2, *mMeasureMap));
        }
    }
    else {
        if(!mDrumMaps[i1]->LaneOff(i2, i3)){
            MILO_WARN("%s (%s): Error ending drum lane %d at %s", SongFullPath(), mTrackInfos[i1]->mName, i3, TickFormat(i2, *mMeasureMap));
        }
    }
}

void SongData::AddBeat(int i, int j){
    if(!mBeatMap->AddBeat(i, j)){
        MILO_WARN("%s (BEAT): Error adding beat at %s, probably double note", SongFullPath(), TickFormat(i, *mMeasureMap));
    }
}

void SongData::SetDetailedGrid(bool b){ mDetailedGrid = b; }
void SongData::AddRangeShift(int i, float f){ mRangeShifts[i] = f; }

void SongData::AddKeyboardRangeShift(int i1, int i2, float f3, int i4, int i5){
    RangeSection sect(i1, f3);
    sect.unk8 = i4;
    sect.unkc = i5;
    std::vector<RangeSection>& curRanges = mKeyboardRangeSections[i1];
    if(sect.unkc == -1.0f){
        float fSpan = 16.0f;
        if(curRanges.size() != 0){
            fSpan = curRanges.back().unkc - curRanges.back().unk8;
            MILO_ASSERT(fSpan > 0.0f, 0x589);
        }
        sect.unkc += fSpan;
    }
    curRanges.push_back(sect);
}

void SongData::AddRGGem(int i, const RGGemInfo& info){
    unkd4 = Max(unkd4, info.ms + info.duration_ms);
    if(!mGemDBs[info.track]->AddRGGem(i, info)){
        MILO_WARN("%s, %s: Overlapping or too-close real guitar gems at tick %d (%s)", SongFullPath(), mTrackInfos[info.track]->mName, info.tick, TickFormat(info.tick, *mMeasureMap));
    }
}

void SongData::SetFakeHitGemsInFill(bool b){ mFakeHitGemsInFill = b; }
bool SongData::GetFakeHitGemsInFill() const { return mFakeHitGemsInFill; }

unsigned int SongData::GetRollingSlotsAtTick(int i1, int i2) const {
    RangedDataCollection<unsigned int>* pRollInfo = mRollInfos[i1];
    MILO_ASSERT(pRollInfo, 0x5B4);
    return pRollInfo->GetData(mTrackDifficulties[i1], i2);
}

bool SongData::RollStartsAt(int idx, int startTick, int& endTick) const {
    RangedDataCollection<unsigned int>* pRollInfo = mRollInfos[idx];
    MILO_ASSERT(pRollInfo, 0x5C2);
    return pRollInfo->StartsAt(mTrackDifficulties[idx], startTick, endTick);
}

bool SongData::GetNextRoll(int idx, int i2, unsigned int& roll, int& iref) const {
    RangedDataCollection<unsigned int>* pRollInfo = mRollInfos[idx];
    MILO_ASSERT(pRollInfo, 0x5D0);
    int iref_loc;
    return pRollInfo->GetNext(mTrackDifficulties[idx], i2, roll, iref_loc, iref);
}

bool SongData::TrillStartsAt(int idx, int startTick, int& endTick){
    RangedDataCollection<std::pair<int, int> >* pTrillInfo = mTrillInfos[idx];
    MILO_ASSERT(pTrillInfo, 0x5F7);
    return pTrillInfo->StartsAt(mTrackDifficulties[idx], startTick, endTick);
}

RangedDataCollection<unsigned int>* SongData::GetRollInfo(int idx) const {
    RangedDataCollection<unsigned int>* pRollInfo = mRollInfos[idx];
    MILO_ASSERT(pRollInfo, 0x5DE);
    return pRollInfo;
}

bool SongData::GetTrillSlotsAtTick(int idx, int i2, std::pair<int, int>& p) const {
    RangedDataCollection<std::pair<int, int> >* pTrillInfo = mTrillInfos[idx];
    MILO_ASSERT(pTrillInfo, 0x5E8);
    return pTrillInfo->AtTick(mTrackDifficulties[idx], i2, p);
}

RangedDataCollection<std::pair<int, int> >* SongData::GetTrillInfo(int idx) const {
    RangedDataCollection<std::pair<int, int> >* pTrillInfo = mTrillInfos[idx];
    MILO_ASSERT(pTrillInfo, 0x605);
    return pTrillInfo;
}

bool SongData::RGRollStartsAt(int idx, int startTick, int& endTick) const {
    RangedDataCollection<RGRollChord>* pRollInfo = mRGRollInfos[idx];
    MILO_ASSERT(pRollInfo, 0x60F);
    return pRollInfo->StartsAt(mTrackDifficulties[idx], startTick, endTick);
}

bool SongData::GetNextRGRoll(int idx, int i2, RGRollChord& cref, int& iref) const {
    RangedDataCollection<RGRollChord>* pRollInfo = mRGRollInfos[idx];
    MILO_ASSERT(pRollInfo, 0x61C);
    int iref_loc;
    return pRollInfo->GetNext(mTrackDifficulties[idx], i2, cref, iref_loc, iref);
}

RGRollChord SongData::GetRGRollingSlotsAtTick(int i, int j) const {
    RangedDataCollection<RGRollChord>* pRollInfo = mRGRollInfos[i];
    MILO_ASSERT(pRollInfo, 0x62A);
    return pRollInfo->GetData(mTrackDifficulties[i], j);
}

RangedDataCollection<RGRollChord>* SongData::GetRGRollInfo(int idx) const {
    RangedDataCollection<RGRollChord>* pRollInfo = mRGRollInfos[idx];
    MILO_ASSERT(pRollInfo, 0x636);
    return pRollInfo;
}

bool SongData::GetRGTrillAtTick(int idx, int i2, RGTrill& trill) const {
    RangedDataCollection<RGTrill>* pTrillInfo = mRGTrillInfos[idx];
    MILO_ASSERT(pTrillInfo, 0x640);
    return pTrillInfo->AtTick(mTrackDifficulties[idx], i2, trill);
}

RangedDataCollection<RGTrill>* SongData::GetRGTrillInfo(int idx) const {
    RangedDataCollection<RGTrill>* trillInfo = mRGTrillInfos[idx];
    MILO_ASSERT(trillInfo, 0x64D);
    return trillInfo;
}

bool SongData::RGTrillStartsAt(int idx, int i2, int& iref){
    RangedDataCollection<RGTrill>* pTrillInfo = mRGTrillInfos[idx];
    MILO_ASSERT(pTrillInfo, 0x656);
    return pTrillInfo->StartsAt(mTrackDifficulties[idx], i2, iref);
}

void SongData::RecalculateGemTimes(int i){
    GameGemList* gemList = mGemDBs[i]->GetDiffGemList(mTrackDifficulties[i]);
    gemList->RecalculateGemTimes(GetTempoMap());
}

void SongData::EnableGems(int, float, float){

}

GameGemList* SongData::GetGemListByDiff(int i, int diff){
    return mGemDBs[i]->GetDiffGemList(diff);
}

GameGemList* SongData::GetGemList(int i){
    return mGemDBs[i]->GetDiffGemList(mTrackDifficulties[i]);
}

TickedInfoCollection<String>& SongData::GetSubmixes(int i) const {
    return mDrumMixDBs[i]->GetMixList(mTrackDifficulties[i]);
}

// fn_804855E4
SongPos SongData::CalcSongPos(float f){
    MILO_ASSERT(mTempoMap, 0x6BA);
    MILO_ASSERT(mMeasureMap, 0x6BB);
    MILO_ASSERT(mBeatMap, 0x6BC);
    float tick = mTempoMap->TimeToTick(f);
    int itick = tick;
    int m, b, t, x;
    mMeasureMap->TickToMeasureBeatTick(itick, m, b, t, x);
    return SongPos(tick, mBeatMap->Beat(itick), m, b, t);
}

Symbol SongData::TrackName(int idx) const {
    return mTrackInfos[idx]->mName;
}

int SongData::TrackNamed(Symbol name) const {
    for(int i = 0; i < mTrackInfos.size(); i++){
        if(mTrackInfos[i]->mName == name) return i;
    }
    return -1;
}

DrumFillInfo* SongData::GetDrumFillInfo(int idx){
    return mFills[idx];
}

FillInfo* SongData::GetFillInfo(int idx){
    return mFills[idx];
}

bool SongData::GetUsingRealDrums() const {
    return mPlayerTrackConfigList->UseRealDrums();
}

SongData::BackupTrack::~BackupTrack(){
    delete mGems;
    delete mMixes;
}

void SongData::MakeBackupTracks(){
    for(int i = 0; i < mTrackInfos.size(); i++){
        if(mTrackInfos[i]->mType == kTrackDrum){
            mBackupTracks.push_back(new BackupTrack(i, mGemDBs[i]->Duplicate(), mDrumMixDBs[i]->Duplicate()));
        }
        else if(mTrackInfos[i]->mType == kTrackKeys){
            mBackupTracks.push_back(new BackupTrack(i, mGemDBs[i]->Duplicate(), nullptr));
        }
    }
}

bool SongData::HasBackupTrack(int track) const {
    for(int i = 0; i < mBackupTracks.size(); i++){
        if(track == mBackupTracks[i]->mOriginalTrack) return true;
    }
    return false;
}

void SongData::RestoreAllTracksFromBackup(){
    for(int i = 0; i < mNumTracks; i++){
        if(HasBackupTrack(i)){
            RestoreTrackFromBackup(i);
        }
    }
}

void SongData::RestoreTrackFromBackup(int track){
    int backupIdx = 0;
    for(int i = 0; i < mBackupTracks.size(); i++){
        if(mBackupTracks[i]->mOriginalTrack == track) break;
        backupIdx++;
    }
    if(backupIdx == mBackupTracks.size()) MILO_FAIL("Trying to backup track %d with no backup\n", track);
    else {
        TrackType ty = mTrackInfos[track]->mType;
        if(ty == kTrackDrum){
            if(mPlayerTrackConfigList->mDiscoUnflip){
                for(int i = 0; i < mNumDifficulties; i++){
                    UnflipGems(track, backupIdx, i);
                }
            }
            else {
                for(int i = 0; i < mNumDifficulties; i++){
                    RestoreGems(track, backupIdx, i);
                }
            }
        }
        else if(ty == kTrackKeys){
            if(mPlayerTrackConfigList->unk2c){
                for(int i = 0; i < mNumDifficulties; i++){
                    RestoreGems(track, backupIdx, i);
                }
            }
            else {
                for(int i = 0; i < mNumDifficulties; i++){
                    TrimOverlappingGems(track, backupIdx, i);
                }
            }
        }
    }
}

SongData::FakeTrack::FakeTrack(Symbol sym) : mName(sym), mGems(new GameGemDB(1, 0x78)) {}
SongData::FakeTrack::~FakeTrack(){ delete mGems; }