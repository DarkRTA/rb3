#include "beatmatch/SongParser.h"
#include "os/System.h"
#include "midi/MidiConstants.h"
#include "utl/FilePath.h"
#include "beatmatch/GameGem.h"
#include "utl/TempoMap.h"
#include "utl/TimeConversion.h"
#include "utl/UTF8.h"
#include <ctype.h>
#include "os/Timer.h"

Timer gSongLoadTimer;

#define NULL_TICK 0x10000000

// fn_80488788
SongParser::SongParser(InternalSongParserSink& sink, int diff_nums, TempoMap*& tmap, MeasureMap*& mmap, int j) : mNumSlots(32), mPlayerSlot(9),
    mLowVocalPitch(36), mHighVocalPitch(84), mTempoMap(tmap), mMeasureMap(mmap), mMidiReader(0), mFile(0), mFilename(0), mMerging(0),
    mSink(&sink), mSongInfo(0), mNumPlayers(1), mNumDifficulties(diff_nums), mTrack(-1), mRollIntervals(0), mTrillIntervals(0),
    mKeyboardDifficulty(-1), mKeyboardRangeFirstPitch(-1), mKeyboardRangeSecondPitch(-1), mKeyboardRangeStartTick(-1),
    mKeyboardRangeShiftDuration(100.0f), mIgnoreGemDurations(0), mSectionStartTick(-1), mSectionEndTick(-1), mLyricPitchSet(0),
    mLyricTextSet(0), mLyricBends(0), mNextLyricTextTick(-1), mReadingState(kReadingBeat), mNumDrumChannels(j), mDrumSubmixDifficultyMask(0),
    mCodaStartTick(-1), mCodaEndTick(-1), mSoloGemDifficultyMask(0), mVocalPhraseStartTick(-1), mLastTambourineGemTick(-1),
    mLastTambourineAutoTick(-1), mLastBeatTick(-1), mLastBeatType(-1), mHaveBeatFailure(0), mSoloPitch(0),
    mRGHandPos(-1), mRGRootNote(-1), unk1ec(-1), unk1f0(-1), unk1f4(-1), mRGSlashesStartTick(-1), mRGSlashesEndTick(-1),
    mRGChordNamingStartTick(-1), mRGChordNamingEndTick(-1), mRGEnharmonicStartTick(-1), mRGEnharmonicEndTick(-1) {

    DataArray* cfg = SystemConfig()->FindArray("beatmatcher", true);
    DataArray* watcherArr = cfg->FindArray("watcher", false);
    if(watcherArr){
        watcherArr->FindData("ignore_durations", mIgnoreGemDurations, false);
        mRollIntervals = watcherArr->FindArray("roll_interval_ms", true);
        mTrillIntervals = watcherArr->FindArray("trill_interval_ms", true)->Array(1);
    }
    DataArray* parserArr = cfg->FindArray("parser", true);
    parserArr->FindData("player_slot", mPlayerSlot, false);
    parserArr->FindData("low_vocal_pitch", mLowVocalPitch, false);
    parserArr->FindData("high_vocal_pitch", mHighVocalPitch, false);
    mTrackNameMapping = parserArr->FindArray("track_mapping", true);

    DataArray* drumInstArr = parserArr->FindArray("drum_style_instruments", false);
    if(drumInstArr){
        for(int i = 0; i < drumInstArr->Array(1)->Size(); i++){
            mDrumStyleInstruments.push_back((TrackType)drumInstArr->Array(1)->Int(i));
        }
    }

    DataArray* vocalInstArr = parserArr->FindArray("vocal_style_instruments", false);
    if(vocalInstArr){
        for(int i = 0; i < vocalInstArr->Array(1)->Size(); i++){
            mVocalStyleInstruments.push_back((TrackType)vocalInstArr->Array(1)->Int(i));
        }
    }

    mKeyboardRangeShiftDuration = parserArr->FindFloat("keyboard_range_shift_duration_ms");
    mSubMixes = cfg->FindArray("audio", true)->FindArray("submixes", false);
    for(int i = 0; i < diff_nums; i++){
        mDifficultyInfos.push_back(32);
    }
    memset(mReportedMissingDrumSubmix, 0, 4);
}

TempoMap* SongParser::GetTempoMap(){
    MILO_ASSERT(mTempoMap, 0xAD);
    return mTempoMap;
}

DECOMP_FORCEACTIVE(SongParser, "mMeasureMap")

// fn_8048987C
void SongParser::ReadMidiFile(BinStream& bs, const char* cc, SongInfo* info){
    mMerging = false;
    mSongInfo = info;
    mFilename = FilePath(FileRoot(), cc);
    MILO_ASSERT(mTrackNames.empty(), 0xC6);
    FillTrackList(mTrackNames, bs);
    AnalyzeTrackList();
    mTrack = -1;
    mNextRealTrack = 0;
    mNextFakeTrack = 0;
    mTrackPartNum = -1;
    InitReadingState();
    mMidiReader = new MidiReader(bs, *this, cc);
    mFile = &bs;
    mForceDrumStyleGems = strstr(cc, "drum_trainer");
}

void SongParser::MergeMidiFile(BinStream& bs, const char* cc){
    mMerging = true;
    mFilename = FilePath(FileRoot(), cc);
    MILO_ASSERT(!mTrackNames.empty(), 0xDD);
    FillTrackList(mTrackNames, bs);
    AnalyzeTrackList();
    for(int i = 0; i < mParts.size(); i++){
        mParts[i].overwritten = false;
    }
    mReadingState = kReadingNonParts;
    mMidiReader = new MidiReader(bs, *this, cc);
    mFile = &bs;
}

void SongParser::Poll(){
    if(mMidiReader && mMidiReader->ReadSomeEvents(20)){
        UpdateReadingState();
        bool failed = mMidiReader->mFail;
        delete mMidiReader;
        mMidiReader = 0;
        if(mReadingState == kDoneReading || failed){
            mFile = 0;
            mFilename = 0;
        }
        else {
            Reset();
            mFile->Seek(0, BinStream::kSeekBegin);
            mMidiReader = new MidiReader(*mFile, *this, mFilename.c_str());
        }
    }
}

void SongParser::SetNumPlayers(int num){ mNumPlayers = num; }

void SongParser::Reset(){
    for(int i = 0; i < mDifficultyInfos.size(); i++){
        mDifficultyInfos[i].mForceHopoOnStart = NULL_TICK;
        mDifficultyInfos[i].mForceHopoOnEnd = NULL_TICK;
        mDifficultyInfos[i].mForceHopoOffStart = NULL_TICK;
        mDifficultyInfos[i].mForceHopoOffEnd = NULL_TICK;
        mDifficultyInfos[i].mRGChordNumsStartTick = NULL_TICK;
        mDifficultyInfos[i].mRGChordNumsEndTick = NULL_TICK;
        mDifficultyInfos[i].mRGLeftHandSlideStartTick = NULL_TICK;
        mDifficultyInfos[i].mRGLeftHandSlideEndTick = NULL_TICK;
        mDifficultyInfos[i].mRGFlipSlideDirection = false;
        mDifficultyInfos[i].mRGArpeggioStartTick = -1;
        mDifficultyInfos[i].unkc8 = -1;
        mDifficultyInfos[i].unkcc = 0;
        mDifficultyInfos[i].mRGAreaStrumType = kRGNoStrum;
        mDifficultyInfos[i].mRGAreaStrumStartTick = NULL_TICK;
        mDifficultyInfos[i].mRGAreaStrumEndTick = NULL_TICK;
        mDifficultyInfos[i].mRGLooseStrumStartTick = NULL_TICK;
        mDifficultyInfos[i].mRGLooseStrumEndTick = NULL_TICK;
        mDifficultyInfos[i].unk124 = NULL_TICK;
        for(int j = 0; j < 32; j++){
            mDifficultyInfos[i].mGemsInProgress[j] = GemInProgress();
        }
        for(int j = 0; j < 6; j++){
            mDifficultyInfos[i].mRGGemsInfo[j] = RGGemInfo();
        }
    }

    mCommonPhraseInProgress = -1;
    mSoloPhraseInProgress = -1;
    mDrumFillInProgress = -1;
    mRollInProgress = -1;
    mTrillInProgress = -1;
    mSoloPhraseEndTick = -1;
    mDrumFillEndTick = -1;
    mNumSoloPhrases = 0;
    mPlayerFocusInProgress[0] = -1;
    mPlayerFocusInProgress[1] = -1;
    mVocalRangeShiftStartTick = -1;
    mRollSlotsArray.resize(mNumDifficulties);
    mTrillSlotsArray.resize(mNumDifficulties);
    mRGRollArray.resize(mNumDifficulties);
    mRGTrillArray.resize(mNumDifficulties);
    mState = kIgnore;
    mKeyboardDifficulty = -1;
    mCurrentFillLanes = 0;
    mCurrentCymbalSlots = 28;
    mDrumStyleGems = false;
    mTrackName = Symbol(0);
    mTrackType = kTrackNone;
    mTrackPart = 0;
    mCurTrackIndex = -1;
    mDrumSubmixDifficultyMask = 0;
    mSoloGemDifficultyMask = 0;
    mVocalPhraseStartTick = -1;
    mLastTambourineGemTick = -1;
    mLastTambourineAutoTick = -1;
    memset(mReportedMissingDrumSubmix, 0, 4);
    mRGHandPos = -1;
    mRGRootNote = -1;
    mRGChordNamingStartTick = -1;
    mRGChordNamingEndTick = -1;
    mRGSlashesStartTick = -1;
    mRGSlashesEndTick = -1;
    mRGEnharmonicStartTick = -1;
    mRGEnharmonicEndTick = -1;
}

void SongParser::AddReceiver(MidiReceiver* rcvr){
    mReceivers.push_back(rcvr);
}

void SongParser::OnNewTrack(int idx){ mCurTrackIndex = idx; }

void SongParser::OnEndOfTrack(){
    if((mState == kGems || mState == kRealGuitar) && mDrumStyleGems){
        CheckDrumSubmixes();
    }
    for(int i = 0; i < mReceivers.size(); i++){
        mReceivers[i]->OnEndOfTrack();
    }
    mSink->OnEndOfTrack(mTrack, TrackAllowsOverlappingNotes(mTrackType));
}

void SongParser::OnAllTracksRead(){
    for(int i = 0; i < mReceivers.size(); i++){
        mReceivers[i]->OnAllTracksRead();
    }
}

void SongParser::OnMidiMessage(int tick, unsigned char status, unsigned char data1, unsigned char data2){
    switch(mState){
        case kGems:
            OnMidiMessageGem(tick, status, data1, data2);
            break;
        case kVocalNotes:
            OnMidiMessageVocals(tick, status, data1, data2);
            break;
        case kBeat:
            OnMidiMessageBeat(tick, status, data1, data2);
            break;
        case kRealGuitar:
            OnMidiMessageRealGuitar(tick, status, data1, data2);
            break;
        default: break;
    }
    for(int i = 0; i < mReceivers.size(); i++){
        mReceivers[i]->OnMidiMessage(tick, status, data1, data2);
    }
}

void SongParser::OnMidiMessageGem(int tick, unsigned char status, unsigned char data1, unsigned char data2){
    switch(MidiGetType(status)){
        case 0x90:
            OnMidiMessageGemOn(tick, data1, data2);
            break;
        case 0x80:
            OnMidiMessageGemOff(tick, data1);
            break;
        default: break;
    }
}

bool SongParser::OnMidiMessageCommonOn(int tick, unsigned char pitch){
    if(IsOverdrive(pitch)){
        mCommonPhraseInProgress = tick;
        return true;
    }
    else if(IsSolo(pitch)){
        mSoloPhraseInProgress = tick;
        mSoloPhraseEndTick = -1;
        mSoloGemDifficultyMask = 0;
        mNumSoloPhrases++;
        return true;
    }
    else if(CheckDrumFillMarker(pitch, true)){
        OnFillStart(tick, pitch);
        return true;
    }
    else return false;
}

bool SongParser::OnMidiMessageCommonOff(int tick, unsigned char uc){
    if(HandlePhraseEnd(tick, uc)) return true;
    else return HandleFillEnd(tick, uc);
}

void SongParser::OnMidiMessageGemOn(int tick, unsigned char pitch, unsigned char uc2){
    MILO_ASSERT(mTrack != -1, 500);
    if(!OnMidiMessageCommonOn(tick, pitch)){
        int num = -1;
        if(!CheckForceHopoMarker(tick, pitch, true)){
            if(CheckDrumMapMarker(tick, pitch, true)){
                CheckDrumCymbalMarker(tick, pitch, true);
            }
            else if(CheckRollMarker(tick, pitch, true)){
                mRollInProgress = tick;
                mRollMask = 0;
                for(int i = 0; i < 4; i++){
                    if(GetRollIntervalMs(mRollIntervals, mTrackType, i, false) > 0 && (i != 2 || uc2 <= 0x32)){
                        mRollMask |= (1 << i);
                    }
                }
            }
            else if(CheckTrillMarker(pitch, true)){
                mTrillInProgress = tick;
                mTrillMask = 0;
                for(int i = 0; i < 4; i++){
                    if(mTrillIntervals->Int(i) > 0 && (i != 2 || uc2 <= 0x32)){
                        mTrillMask |= (1 << i);
                    }
                }
            }
            else if(!CheckKeyboardRangeMarker(tick, pitch, true)){
                int slot = PitchToSlot(pitch, num, tick);
                if(slot != -1){
                    mDifficultyInfos[num].mGemsInProgress[slot] = GemInProgress(tick, mDifficultyInfos[num].mActivePlayers, mCurrentCymbalSlots);
                    if(mSoloPhraseInProgress != -1){
                        mSoloGemDifficultyMask |= (1 << num);
                    }
                    if(mDrumStyleGems){
                        if((mDrumSubmixDifficultyMask & (1 << num)) && !mReportedMissingDrumSubmix[num]){
                            MILO_WARN("%s (%s): No drum submix specified for difficulty %d before first gem at %s",
                                mFilename, mTrackName, num, PrintTick(tick));
                        }
                        int count = 0;
                        if(mNumSlots > 1){
                            for(int i = 1; i < mNumSlots; i++){
                                if(mDifficultyInfos[num].mGemsInProgress[i].mTick >= 0){
                                    count++;
                                }
                            }
                        }

                        if(count > 2){
                            MILO_WARN("%s (%s): %d simultaneous drum pad hits at %s; maximum is 2 pads plus kick",
                                mFilename, mTrackName, count, PrintTick(tick));
                        }
                    }
                }
            }
        }
    }
}

void SongParser::OnMidiMessageGemOff(int tick, unsigned char pitch){
    if(!OnMidiMessageCommonOff(tick, pitch) && !HandleRollEnd(tick, pitch) && !HandleTrillEnd(tick, pitch)){
        if(CheckDrumMapMarker(tick, pitch, false)){
            CheckDrumCymbalMarker(tick, pitch, false);
        }
        else if(!CheckForceHopoMarker(tick, pitch, false) && !CheckKeyboardRangeMarker(tick, pitch, false)){
            OnGemEnd(tick, pitch);
        }
    }
}

// fn_8048ADD0
bool SongParser::HandlePhraseEnd(int tick, unsigned char pitch){
    if(IsOverdrive(pitch)){
        if(mTrackType == kTrackRealKeys && mKeyboardDifficulty != 3){
            MILO_WARN("%s (%s): Real keys overdrive phrases should only authored in expert difficulty, but found at pitch %d at %s.",
                mFilename, mTrackName, pitch, PrintTick(tick));
            return false;
        }
        else {
            OnCommonPhraseEnd(tick);
            return true;
        }
    }
    else if(IsSolo(pitch)){
        if(mTrackType == kTrackRealKeys && mKeyboardDifficulty != 3){
            MILO_WARN("%s (%s): Real keys solo phrases should only authored in expert difficulty, but found at pitch %d at %s.",
                mFilename, mTrackName, pitch, PrintTick(tick));
            return false;
        }
        else {
            OnSoloPhraseEnd(tick);
            return true;
        }
    }
    else return false;
}

void SongParser::OnCommonPhraseEnd(int off_tick){
    AddPhrase(kCommonPhrase, -1, mCommonPhraseInProgress, off_tick);
}

void SongParser::OnSoloPhraseEnd(int tick){
    if(mDrumStyleGems && (mDrumFillInProgress != -1 || mDrumFillEndTick >= mSoloPhraseInProgress)){
        MILO_WARN("%s (%s): Drum fill overlaps solo %s-%s",
            mFilename, mTrackName, PrintTick(mSoloPhraseInProgress), PrintTick(tick));
    }
    if(mCodaStartTick != -1 && tick >= mCodaStartTick){
        MILO_WARN("%s (%s): Solo %s-%s is past [coda] event at %s",
            mFilename, mTrackName, PrintTick(mSoloPhraseInProgress), PrintTick(tick), PrintTick(mCodaStartTick));
    }
    AddPhrase(kSoloPhrase, -1, mSoloPhraseInProgress, tick);
    mSoloPhraseInProgress = -1;
    mSoloPhraseEndTick = tick;
}

void SongParser::AddPhrase(BeatmatchPhraseType type, int diff, int& on_tick, int off_tick){
    float on_time = GetTempoMap()->TickToTime(on_tick);
    float off_time = GetTempoMap()->TickToTime(off_tick);
    if(on_tick != -1){
        if(IsInSection(on_tick)){
            mSink->AddPhrase(type, diff, mTrack, on_time, on_tick, off_time - on_time, off_tick - on_tick);
        }
        on_tick = -1;
    }
}

bool SongParser::HandleFillEnd(int tick, unsigned char uc){
    bool marker = CheckFillMarker(uc, false);
    if(marker) OnFillEnd(tick, uc);
    return marker;
}

void SongParser::OnFillStart(int tick, unsigned char pitch){
    bool b = mCodaStartTick != -1 && tick >= mCodaStartTick;
    if(mDrumFillInProgress == -1){
        if(!b && !mDrumStyleGems){
            if(mCodaStartTick == -1){
                MILO_WARN("%s (%s): Big Rock Ending appears at %s, but there is no [coda] event",
                    mFilename, mTrackName, PrintTick(tick));
            }
            else {
                MILO_WARN("%s (%s): Big Rock Ending at %s appears before [coda] event at %s",
                    mFilename, mTrackName, PrintTick(tick), PrintTick(mCodaStartTick));
            }
        }
        mDrumFillInProgress = tick;
        mDrumFillEndTick = -1;
        if(b && tick != mCodaStartTick){
            MILO_WARN("%s (%s): Big Rock Ending %s-%s: lanes do not all begin at [coda]; [coda] is at %s, lane %d begins at %s",
                mFilename, mTrackName, PrintTick(mCodaStartTick), PrintTick(mCodaEndTick),
                PrintTick(mCodaStartTick), pitch - 0x77, PrintTick(tick));
            mDrumFillInProgress = mCodaStartTick;
        }
    }
    else if(tick != mDrumFillInProgress){
        if(b){
            MILO_WARN("%s (%s): Big Rock Ending %s-%s: lanes do not all begin at [coda]; [coda] is at %s, lane %d begins at %s",
                mFilename, mTrackName, PrintTick(mCodaStartTick), PrintTick(mCodaEndTick),
                PrintTick(mCodaStartTick), pitch - 0x77, PrintTick(tick));
        }
        else if(mDrumStyleGems){
            MILO_WARN("%s (%s): Drum fill beginning at %s: lanes do not all begin at the same tick; lane %d begins at %s",
                mFilename, mTrackName, PrintTick(mDrumFillInProgress), pitch - 0x77, PrintTick(tick));
        }
    }
}

void SongParser::OnFillEnd(int tick, unsigned char uc){
    bool b = mCodaStartTick != -1 && tick >= mCodaStartTick;
    int fill = mDrumFillInProgress;
    if(fill != -1){
        if(mDrumStyleGems && (mSoloPhraseInProgress != -1 || (mSoloPhraseEndTick >= fill))){
            MILO_WARN("%s (%s): Drum fill %s-%s overlaps solo",
                mFilename, mTrackName, PrintTick(mDrumFillInProgress), PrintTick(tick));
        }
        if(mCurrentFillLanes != (1 << mNumSlots) - 1){
            if(b){
                MILO_WARN("%s (%s): Big Rock Ending %s-%s is not authored for all lanes",
                    mFilename, mTrackName, PrintTick(mDrumFillInProgress), PrintTick(tick));
            }
            else if(mDrumStyleGems) {
                MILO_WARN("%s (%s): Drum fill %s-%s is not authored for all lanes",
                    mFilename, mTrackName, PrintTick(mDrumFillInProgress), PrintTick(tick));
            }
        }
        if(mDrumStyleGems && (mDrumFillInProgress < mCodaStartTick) && b){
            MILO_WARN("%s (%s): Drum fill %s-%s straddles [coda] event at %s",
                mFilename, mTrackName, PrintTick(mDrumFillInProgress), PrintTick(tick), PrintTick(mCodaStartTick));
        }
        if(IsInSection(fill)){
            if(mTrackType == kTrackRealKeys && mKeyboardDifficulty != 3){
                MILO_WARN("%s: Real keys BREs should only authored in expert difficulty, but found in track %s.", mFilename, mTrackName);
            }
            else mSink->AddDrumFill(mTrack, mCurrentFillLanes, fill, tick, b);
        }
        mDrumFillInProgress = -1;
        mDrumFillEndTick = tick;
        mCurrentFillLanes = 0;
        if(b){
            if(mCodaEndTick == -1) mCodaEndTick = tick;
            else if(tick != mCodaEndTick){
                MILO_WARN("%s (%s): Big Rock Ending %s-%s: all lanes in all tracks must end at the same tick; lane %d ends at %s",
                    mFilename, mTrackName, PrintTick(mCodaStartTick), PrintTick(mCodaEndTick), uc - 0x77, PrintTick(tick));
                mDrumFillEndTick = mCodaEndTick;
            }
        }
    }
    else {
        if(uc >= 0x78 && uc < mNumSlots + 0x78 && tick != mDrumFillEndTick){
            if(b){
                MILO_WARN("%s (%s): Big Rock Ending %s-%s: all lanes in all tracks must end at the same tick; lane %d ends at %s",
                    mFilename, mTrackName, PrintTick(mCodaStartTick), PrintTick(mCodaEndTick), uc - 0x77, PrintTick(tick));
            }
            else if(mDrumStyleGems) {
                MILO_WARN("%s (%s): Drum fill ending at %s: lanes do not all end at the same tick; lane %d ends at %s",
                    mFilename, mTrackName, PrintTick(mDrumFillEndTick), uc - 0x77, PrintTick(tick));
            }
        }
    }
}

void SongParser::CheckDrumSubmixes(){
    for(int i = 0; i < 4; i++){
        int mask = (1 << i);
        if((mDrumSubmixDifficultyMask & mask) != mask){
            MILO_WARN("%s (%s): No drum submix specified for difficulty %d", mFilename, mTrackName, i);
        }
    }
}

bool SongParser::HandleRollEnd(int tick, unsigned char pitch){
    if(!CheckRollMarker(tick, pitch, false)){
        return false;
    }
    else if(mTrackType == kTrackRealKeys && mKeyboardDifficulty != 3){
        return true;
    }
    else {
        MILO_ASSERT(mRollInProgress != -1, 0x3C6);
        if(IsInSection(mRollInProgress)){
            for(int i = 0; i < mNumDifficulties; i++){
                unsigned int u6 = mRollSlotsArray[i];
                if(mTrackType == kTrackRealKeys) u6 = 1;
                int bits = GameGem::CountBitsInSlotType(u6);
                if(mRollMask & (1 << i)){
                    mSink->AddRoll(mTrack, i, u6, mRollInProgress, tick);
                }
            }
        }
        mRollInProgress = -1;
        mRollSlotsArray.clear();
        mRollSlotsArray.resize(mNumDifficulties);
        return true;
    }
}

bool SongParser::HandleTrillEnd(int tick, unsigned char pitch){
    if(!CheckTrillMarker(pitch, false)) return false;
    if(mTrillInProgress == -1) return true;
    else if(IsInSection(mTrillInProgress)){
        for(int i = 0; i < mNumDifficulties; i++){
            if(mTrillMask & (1 << i)){
                std::pair<int,int>& curpair = mTrillSlotsArray[i];
                if(curpair.first != -1 || curpair.second != -1){
                    if(mTrackType == kTrackDrum)
                        mSink->AddRoll(mTrack, i, (1 << curpair.first) | (1 << curpair.second), mTrillInProgress, tick);
                    else mSink->AddTrill(mTrack, i, curpair.first, curpair.second, mTrillInProgress, tick);
                }
            }            
        }
    }
    mTrillInProgress = -1;
    mTrillSlotsArray.clear(); // some vector method is called here but i can't tell which one it is
    mTrillSlotsArray.resize(mNumDifficulties);
    return true;
}

void SongParser::OnGemEnd(int tick, unsigned char pitch){
    int num = -1;
    int slot = PitchToSlot(pitch, num, tick);
    if(slot != -1){
        DifficultyInfo& info = mDifficultyInfos[num];
        int infotick = info.mGemsInProgress[slot].mTick;
        if(IsInSection(infotick)){
            if(infotick >= 0){
                MultiGemInfo geminfo;
                float ticktime = GetTempoMap()->TickToTime(tick);
                geminfo.track = mTrack;
                geminfo.ms = GetTempoMap()->TickToTime(infotick);
                geminfo.duration_ticks = tick - infotick;
                geminfo.ignore_duration = false;
                geminfo.duration_ms = ticktime - geminfo.ms;
                if(mIgnoreGemDurations || geminfo.duration_ticks <= 160) geminfo.ignore_duration = true;
                geminfo.tick = infotick;
                geminfo.players = info.mGemsInProgress[slot].mPlayers;
                geminfo.slots = ComputeSlots(slot, infotick, tick, info.mGemsInProgress);
                geminfo.no_strum = GetNoStrumState(infotick, info);
                geminfo.is_cymbal = (info.mGemsInProgress[slot].unkc & geminfo.slots) == geminfo.slots;
                mSink->AddMultiGem(0, geminfo);
                if(mRollInProgress != -1 && abs(mRollInProgress - infotick) < 10 &&
                    mRollMask & (1 << num) && !mDrumStyleGems || slot != 0){
                        mRollSlotsArray.front() |= geminfo.slots;
                }
                if(mTrillInProgress != -1 && mTrillMask & (1 << num)){
                    MILO_ASSERT(!mTrillSlotsArray.empty(), 0x46A);
                    std::pair<int,int>& curpair = mTrillSlotsArray[num];
                    if(curpair.first == -1){
                        if(abs(mTrillInProgress - infotick) < 10) curpair.first = slot;
                        else {
                            MILO_WARN("%s (%s): trill start at %s doesn't have a matching gem.",
                                mFilename, mTrackName, PrintTick(mTrillInProgress));
                        }
                    }
                    else if(curpair.second == -1){
                        curpair.second = slot;
                        if(curpair.first == slot){
                            MILO_WARN("%s (%s %d): trill start at %s doesn't have a two alternating slots. Both are %d.",
                                mFilename, mTrackName, num, PrintTick(mTrillInProgress), infotick);
                            mTrillInProgress = -1;
                        }
                    }
                }
                if(mSoloPhraseInProgress != -1 && mSoloPhraseInProgress <= infotick){
                    mSoloGemDifficultyMask |= (1 << num);
                }
                float tickms = TickToMs(infotick);
                if(tickms < 2450.0f){
                    MILO_WARN("%s (%s): Gem at %s is only %.02f seconds into the song; gems cannot appear before %.02f seconds into the song",
                        mFilename, mTrackName, PrintTick(tick), tickms / 1000.0f, 2.45f);
                }
            }
            else {
                if(!TrackAllowsOverlappingNotes(mTrackType)){
                    if(abs(-(info.mGemsInProgress[slot].mTick + tick)) > 10){
                        MILO_WARN("%s (%s): chord gems don't end simultaneously at %s",
                            mFilename, mTrackName, PrintTick(tick));
                    }
                }        
            }
        }
    }
}

// fn_8048C0D4
unsigned int SongParser::ComputeSlots(int slot, int t1, int t2, std::vector<GemInProgress>& gems){
    if(mDrumStyleGems || TrackAllowsOverlappingNotes(mTrackType)){
        gems[slot].SetNegTick(t2);
        return 1 << slot;
    }
    else {
        unsigned int mask = 0;
        for(int i = 0; i < 32; i++){
            if(gems[i].mTick >= 0){
                if(abs(gems[i].mTick - t1) <= 10){
                    gems[i].SetNegTick(t2);
                    mask |= (1 << i);
                }
                else if(gems[i].mTick < t2 && !TrackAllowsOverlappingNotes(mTrackType)){
                    MILO_WARN("%s (%s): Chord gems do not start simultaneously at %s",
                        mFilename, mTrackName, PrintTick(t1));
                }
            }
        }
        return mask;
    }
}

void SongParser::OnMidiMessageVocals(int tick, unsigned char status, unsigned char data1, unsigned char data2){
    switch(MidiGetType(status)){
        case 0xB0:
            if(data1 == 8 && data2 <= 100)
                HandlePitchOffsetCC(tick, data2);
            break;
        case 0x90:
            int num = data1 - (mPlayerSlot + (mNumDifficulties - 1) * 12 + 60);
            if(0 <= num && num <= 1){
                mSink->StartVocalPlayerPhrase(tick,num);
                mVocalPhraseStartTick = tick;
            }
            else {
                if(mLowVocalPitch <= data1 && data1 <= mHighVocalPitch) StartVocalNote(tick, data1, 0);
                else {
                    if(data1 == 116) mCommonPhraseInProgress = tick;
                    else if(data1 == 96){
                        if(mLastTambourineGemTick != -1 && tick < mLastTambourineGemTick + 120){
                            MILO_WARN("%s (%s): Percussion gems at %s and %s are less than one 16th note (120 ticks) apart",
                                mFilename, mTrackName, PrintTick(mLastTambourineGemTick), PrintTick(tick));
                        }
                        if(mLastTambourineAutoTick != -1 && tick < mLastTambourineAutoTick + 60){
                            MILO_WARN("%s (%s): Percussion gem at %s is less than one 32nd note (60 ticks) after the automatic percussion hit at %s",
                                mFilename, mTrackName, PrintTick(tick), PrintTick(mLastTambourineAutoTick));
                        }
                        mSink->OnTambourineGem(tick);
                        mLastTambourineAutoTick = tick;
                    }
                    else if(data1 == 97){
                        if(mLastTambourineGemTick != -1 && tick < mLastTambourineGemTick + 60){
                            MILO_WARN("%s (%s): Automatic percussion hit at %s is less than one 32nd note (60 ticks) after the percussion gem at %s",
                                mFilename, mTrackName, PrintTick(tick), PrintTick(mLastTambourineGemTick));
                        }
                        if(mLastTambourineAutoTick != 1 && tick < mLastTambourineAutoTick + 60){
                            MILO_WARN("%s (%s): Automatic percussion hits at %s and %s are less than one 32nd note (60 ticks) apart",
                                mFilename, mTrackName, PrintTick(mLastTambourineAutoTick), PrintTick(tick));
                        }
                        mLastTambourineAutoTick = tick;
                    }
                    else if(data1 == 1) mSink->AddLyricShift(tick);
                    else if(data1 == 0){
                        if(mVocalRangeShiftStartTick != -1){
                            MILO_WARN("%s (%s): Multiple note-ons for vocal range shift!", mFilename, mTrackName);
                        }
                        mVocalRangeShiftStartTick = tick;
                    }
                }
            }
            break;
        case 0x80:
            int num80 = data1 - (mPlayerSlot + (mNumDifficulties - 1) * 12 + 60);
            if(0 <= num80 && num80 <= 1){
                MILO_WARN("%s (%s): Vocal phrase %s-%s is past [coda] event at %s",
                    mFilename, mTrackName, PrintTick(mVocalPhraseStartTick), PrintTick(tick), PrintTick(mCodaStartTick));
                mSink->EndVocalPlayerPhrase(tick, num80);
                mVocalPhraseStartTick = -1;
            }
            else {
                if(mLowVocalPitch <= data1 && data1 <= mHighVocalPitch) EndVocalNote(tick);
                else {
                    if(data1 == 116) OnCommonPhraseEnd(tick);
                    else if(data1 == 0){
                        MILO_ASSERT(mVocalRangeShiftStartTick != -1, 0x55C);
                        mSink->AddRangeShift(mVocalRangeShiftStartTick,
                            GetTempoMap()->TickToTime(tick) - GetTempoMap()->TickToTime(mVocalRangeShiftStartTick));
                        mVocalRangeShiftStartTick = -1;
                    }
                }
            }
            break;
        default: break;
    }
}

void SongParser::StartVocalNote(int tick, unsigned char data, const char* lyric){
    if(IsInSection(tick)){
        float tickms = TickToMs(tick);
        if(tickms < 2450.0f){
            MILO_WARN("%s (%s): Vocal note at %s is only %.02f seconds into the song; vocal notes cannot appear before %.02f seconds into the song",
                mFilename, mTrackName, PrintTick(tick), tickms / 1000.0f, 2.45f);
        }
        if(mLyricTextSet && lyric){
            if(mNextLyricTextTick != -1){
                MILO_WARN("%s (%s): Missing vocal note at %s for lyric '%s'", 
                    mFilename, mTrackName, PrintTick(tick), mNextLyric);
                mNextLyricTextTick = tick;
                mNextLyric = lyric;
            }
        }
        else {
            float ticktime = GetTempoMap()->TickToTime(tick);
            if(mLyricPitchSet || mLyricTextSet && mCurVocalNote.GetTick() != tick){
                if(data != 0){
                    MILO_WARN("%s (%s): misaligned note at %s (expected at %s)",
                        mFilename, mTrackName, PrintTick(tick), PrintTick(mCurVocalNote.GetTick()));
                }
                else {
                    MILO_WARN("%s (%s): misaligned lyric at %s (expected at %s)",
                        mFilename, mTrackName, PrintTick(tick), PrintTick(mCurVocalNote.GetTick()));
                }
            }
            mCurVocalNote.SetNoteTime(tickms, tick);
            if(data != 0){
                if(mLyricPitchSet){
                    MILO_WARN("%s (%s): missing lyric at %s", mFilename, mTrackName, PrintTick(tick));
                }
                mLyricPitchSet = true;
                mCurVocalNote.SetStartPitch(data);
                mCurVocalNote.SetEndPitch(data);
            }
            if(mNextLyricTextTick != -1){
                if(lyric || mLyricTextSet || tick != mNextLyricTextTick){
                    MILO_WARN("%s (%s): Missing vocal note at %s for lyric '%s'",
                        mFilename, mTrackName, PrintTick(mNextLyricTextTick), mNextLyric);
                }
                mLyricTextSet = true;
                mNextLyricTextTick = -1;
                mLyricBends = ParseAndStripLyricText(mNextLyric.c_str(), mCurVocalNote);
            }
            if(lyric){
                if(mLyricTextSet){
                    MILO_WARN("%s (%s): Missing vocal note at %s for lyric '%s'",
                        mFilename, mTrackName, PrintTick(tick), mNextLyric);
                }
                mLyricTextSet = true;
                mLyricBends = ParseAndStripLyricText(lyric, mCurVocalNote);
            }
            if(mLyricPitchSet && mLyricTextSet && mLyricBends){
                float ms_sum = mPrevVocalNote.GetMs() + mPrevVocalNote.GetDurationMs();
                unsigned short ticks = mPrevVocalNote.GetDurationTicks();
                int prevticks = mPrevVocalNote.GetTick();
                int curticks = mCurVocalNote.GetTick();
                if(prevticks + ticks < curticks){
                    VocalNote note(mPrevVocalNote);
                    note.SetNoteTime(ms_sum, prevticks + ticks);
                    note.SetDurationTime(mCurVocalNote.GetMs() - note.GetMs(), mCurVocalNote.GetTick() - note.GetTick());
                    note.SetStartPitch(mPrevVocalNote.EndPitch());
                    note.SetEndPitch(mCurVocalNote.StartPitch());
                    note.SetText("");
                    note.SetBends(true);
                    mSink->AddVocalNote(note);
                }
            }
        }
    }
}

void SongParser::EndVocalNote(int tick){
    float ticktime = GetTempoMap()->TickToTime(tick);
    if(!mLyricPitchSet){
        MILO_WARN("%s (%s): Missing vocal note at %s for lyric '%s'",
            mFilename, mTrackName, PrintTick(mCurVocalNote.GetTick()), mNextLyric);
    }
    if(!mLyricTextSet){
        MILO_WARN("%s (%s): missing lyric at %s",
            mFilename, mTrackName, PrintTick(mCurVocalNote.GetTick()));
    }
    mCurVocalNote.SetDurationTime(ticktime - mCurVocalNote.GetMs(), tick - mCurVocalNote.GetTick());
    mSink->AddVocalNote(mCurVocalNote);
    mPrevVocalNote = mCurVocalNote;
    mCurVocalNote = VocalNote();
    mLyricPitchSet = false;
    mLyricTextSet = false;
    mLyricBends = false;
}

void SongParser::HandlePitchOffsetCC(int tick, unsigned char uc){
    mSink->AddPitchOffset(tick, uc - 50.0f);
}

// fn_8048CEE4 - parse and strip lyric text
bool SongParser::ParseAndStripLyricText(const char* text, VocalNote& note){
    char c = *((char*)text);
    bool ret = false;
    if(c == '+'){
        ret = true;
        note.SetBends(ret);
        text++;
    }
    const char* p = text + strlen(text);
    // gross while loop
    String str;
    str.reserve((int)(p + (1 - (int)text)));
    strncpy((char*)str.c_str(), text, (int)(p + (1 - (int)text)));
    char buf[0x100];
    ASCIItoUTF8(buf, 0x100, str.c_str());
    note.SetText(buf);
    return ret;
}

void SongParser::OnMidiMessageBeat(int tick, unsigned char status, unsigned char data1, unsigned char data2){
    if(MidiGetType(status) == 0x90){
        if((data1 + 0xF4 & 0xFF) <= 1){
            mSink->AddBeat(tick, data1 == 0xC);
            if(mLastBeatTick != -1 && !mHaveBeatFailure){
                if(tick - mLastBeatTick < 0xF0){
                    MILO_WARN("%s (%s): Beat track cannot be faster than double time; less than 240 ticks between beats at %s and %s",
                        mFilename, mTrackName, PrintTick(mLastBeatTick), PrintTick(tick));
                    mHaveBeatFailure = true;
                }
                if(mLastBeatType == 0xC && data1 == 0xC){
                    MILO_WARN("%s (%s): Two downbeats occur back to back at %s and %s",
                        mFilename, mTrackName, PrintTick(mLastBeatTick), PrintTick(tick));
                    mHaveBeatFailure = true;
                }
            }
            mLastBeatTick = tick;
            mLastBeatType = data1;
        }
        else if(data1 == 0xB){
            mSink->SetDetailedGrid(true);
        }
    }
}

void SongParser::OnText(int tick, const char* text, unsigned char pitch){
    while(isspace(*text)) text++;
    if(pitch == 3){
        if(!OnTrackName(tick, text)) return;
    }
    else {
        switch(mState){
            case kGems:
            case kVocalNotes:
                if(*text == 0x5B){
                    ParseText(tick, text + 1);
                }
                else {
                    if(IsInSection(tick)){
                        mSink->AddLyricEvent(mTrack, tick, text);
                        if(mState == kVocalNotes) StartVocalNote(tick, 0, text);
                    }
                }
                break;
            case kEvents:
                if(streq(text, "[coda]")){
                    if(mCodaStartTick != -1){
                        MILO_WARN("%s (%s): duplicate [coda] event at %s; first [coda] is at %s",
                            mFilename, mTrackName, PrintTick(tick), PrintTick(mCodaStartTick));
                    }
                    if(mCodaStartTick == -1) mCodaStartTick = tick;
                }
                // break;
            case kRealGuitar:
                if(*text == 0x5B){
                    ParseRGText(tick, text + 1);
                }
                break;
            default: break;
        }
    }
    for(int i = 0; i < mReceivers.size(); i++){
        mReceivers[i]->OnText(tick, text, pitch);
    }
}

bool SongParser::OnTrackName(int tick, const char* name){
    mState = kIgnore;
    if(ShouldReadTrack(name)){
        if(IsPartTrackName(name, 0)){
            PartInfo* info = UsePartTrack(name);
            if(info) PrepareTrack(name, info);
            else {
                SkipCurrentTrack();
                return false;
            }
        }
        else {
            mTrackName = name;
            if(streq(name, "BEAT")) mState = kBeat;
            else if(streq(name, "EVENTS")) mState = kEvents;
        }
        for(int i = 0; i < mReceivers.size(); i++){
            mReceivers[i]->OnNewTrack(mTrack);
        }
        return true;
    }
    else {
        SkipCurrentTrack();
        return false;
    }
}

// TODO: check out retail and add inlines where appropriate
void SongParser::PrepareTrack(const char* track_name, PartInfo* info){
    Reset();
    bool b2 = false;
    for(std::vector<PartInfo>::iterator it = mParts.begin(); it != mParts.end(); ++it){
        if(it->ContainsTrackName(track_name)){
            if(it->NoSongDataTrack()){
                if(it->audio_type == kAudioFake){
                    mTrack = mNextFakeTrack++ + 100;
                }
                else {
                    mTrack = mNextRealTrack;
                    mNextRealTrack++;
                }
                b2 = true;
                mTrackPartNum++;
                it->song_data_track = mTrack;
            }
            else {
                mTrack = it->song_data_track;
                if(mMerging && !it->overwritten){
                    mSink->ClearTrack(mTrack);
                    it->overwritten = true;
                }
            }
            break;
        }
    }
    mTrackName = track_name;
    mTrackType = info->type;
    mTrackPart = info;
    if(info->type == kTrackRealKeys){
        if(info->FakeAudio()){
            mKeyboardDifficulty = 3;
        }
        else {
            switch(track_name[strlen(track_name) - 1]){
                case 'E': mKeyboardDifficulty = 0; break;
                case 'M': mKeyboardDifficulty = 1; break;
                case 'H': mKeyboardDifficulty = 2; break;
                case 'X': mKeyboardDifficulty = 3; break;
                default:
                    MILO_WARN("%s (%s): Couldn't find difficulty character in track %s!",
                        mFilename, mTrackName, track_name);
                    break;
            }
        }
        mNumSlots = 25;
        mSoloPitch = 115;
    }
    else if(info->type == kTrackRealGuitar || info->type == kTrackRealGuitar22Fret){
        mSoloPitch = 115;
        mNumSlots = 6;
    }
    else if(info->type == kTrackRealBass || info->type == kTrackRealBass22Fret){
        mSoloPitch = 115;
        mNumSlots = 4;
    }
    else {
        mSoloPitch = 103;
        mNumSlots = 5;
    }

    std::list<TrackType>::iterator it;
    for(it = mVocalStyleInstruments.begin(); it != mVocalStyleInstruments.end(); ++it){
        if(*it == info->type) break;
    }
    if(it != mVocalStyleInstruments.end()){
        mState = kVocalNotes;
    }
    else if(strstr(track_name, "REAL_GUITAR")) mState = kRealGuitar;
    else if(strstr(track_name, "REAL_BASS")) mState = kRealGuitar;
    else mState = kGems;

    bool drumstyle = mForceDrumStyleGems;
    if(!drumstyle){
        for(it = mDrumStyleInstruments.begin(); it != mDrumStyleInstruments.end(); ++it){
            if(*it == info->type) break;
        }
        drumstyle = it != mDrumStyleInstruments.end();
    }
    bool s9 = false;
    mDrumStyleGems = drumstyle;
    TrackType newty = (TrackType)(mTrackType - 1);
    mIgnoreGemDurations = mTrackType == kTrackDrum;
    if(newty <= kTrackRealBass && ((1 << (newty) & 0x1EBU) != 0)){
        s9 = true;
    }
    mTrackAllowsHopos = s9;
    if(b2){
        mSink->AddTrack(mTrack, info->audio_track_num, mTrackName, (SongInfoAudioType)info->audio_type, mTrackPart->type, mDrumStyleGems);
    }
}

// fn_8048DB10
void SongParser::OnMidiMessageRealGuitar(int tick, unsigned char status, unsigned char data1, unsigned char data2){
    unsigned char chan = MidiGetChannel(status);
    switch(MidiGetType(status)){
        case 0x90:
            OnMidiMessageRealGuitarOn(tick, data1, data2, chan);
            break;
        case 0x80:
            OnMidiMessageRealGuitarOff(tick, data1, data2, chan);
            break;
    }
}

// fn_8048DC18
void SongParser::OnMidiMessageRealGuitarOn(int tick, unsigned char pitch, unsigned char data2, unsigned char channel){
    if(!OnMidiMessageCommonOn(tick, pitch) && !HandleRGHandPos(pitch, data2) && !HandleRGRootNote(pitch) &&
        !HandleRGChordNaming(tick, pitch) && !HandleRGEnharmonic(tick, pitch) && !HandleRGSlashes(tick, pitch) &&
        !HandleRGChordMarkup(tick, pitch) && !HandleRGRollStart(tick, pitch, data2) && !HandleRGTrillStart(tick, pitch, data2)){
        int difflevel = RGGetDifficultyLevel(pitch);
        if(difflevel == -1){
            MILO_WARN("%s (%s): Real Guitar On Midi Message out of range at tick %s with pitch %d",
                mFilename, mTrackName, PrintTick(tick), pitch);
        }
        else {
            unsigned char uc1 = pitch + difflevel * -0x18;
            DifficultyInfo& info = mDifficultyInfos[difflevel];
            if(uc1 < 0 ||
                (!HandleRGHopoStart(tick, info, uc1, channel) && !HandleRGGemStart(tick, info, uc1, data2, channel, difflevel) &&
                !HandleRGArpeggioStart(tick, info, uc1) && !HandleRGAreaStrumStart(tick, info, uc1, channel) &&
                !HandleRGLooseStrumStart(tick, info, uc1) && !HandleRGChordNumsStart(tick, info, uc1) &&
                !HandleRGLeftHandSlide(tick, info, uc1, channel))){
                MILO_WARN("%s (%s): Bad Real Guitar On Midi Message at tick %s with pitch %d",
                    mFilename, mTrackName, PrintTick(tick), pitch);
            }
        }
    }
}

void SongParser::OnMidiMessageRealGuitarOff(int tick, unsigned char pitch, unsigned char data2, unsigned char channel){
    if(!OnMidiMessageCommonOff(tick, pitch) && pitch != 108 && (pitch - 4 > 11U) &&
        !HandleRGChordNamingStop(tick, pitch) && !HandleRGEnharmonicStop(tick, pitch) && !HandleRGSlashesStop(tick, pitch) &&
        !HandleRGChordMarkupStop(tick, pitch) && !HandleRGRollStop(tick, pitch) && !HandleRGTrillStop(tick, pitch)){
        int difflevel = RGGetDifficultyLevel(pitch);
        if(difflevel == -1){
            MILO_WARN("%s (%s): Real Guitar Off Midi Message out of range at tick %s with pitch %d",
                mFilename, mTrackName, PrintTick(tick), pitch);
        }
        else {
            unsigned char uc1 = pitch + difflevel * -0x18;
            DifficultyInfo& info = mDifficultyInfos[difflevel];
            if(uc1 < 0 ||
                (!HandleRGLooseStrumStop(tick, info, uc1) && !HandleRGAreaStrumStop(tick, info, uc1, channel) &&
                !HandleRGHopoStop(tick, info, uc1, channel) && !HandleRGGemStop(tick, info, uc1, difflevel) &&
                !HandleRGArpeggioStop(tick, info, uc1, difflevel) && !HandleRGChordNumsStop(tick, info, uc1) &&
                !HandleRGLeftHandSlideStop(tick, info, uc1))){
                MILO_WARN("%s (%s): Bad Real Guitar Off Midi Message at tick %s with pitch %d",
                    mFilename, mTrackName, PrintTick(tick), pitch);
            }            
        }
    }
}

bool SongParser::OnAcceptMaps(TempoMap* tmap, MeasureMap* mmap){
    delete mTempoMap;
    mTempoMap = 0;
    delete mMeasureMap;
    mMeasureMap = 0;
    mTempoMap = tmap;
    mMeasureMap = mmap;
    SetTheTempoMap(mTempoMap);
    return true;
}

void SongParser::SetMidiReader(MidiReader* reader){
    mReader = reader;
    for(int i = 0; i < mReceivers.size(); i++){
        mReceivers[i]->SetMidiReader(reader);
    }
}

int SongParser::PitchToSlot(int pitch, int& diff, int tick) const {
    int i3;
    if(mTrackType == kTrackRealKeys){
        i3 = pitch - 0x30;
        if(i3 < 0){
            MILO_WARN("%s (%s): Keyboard gem pitch of %d is too low at %s.",
                mFilename, mTrackName, pitch, PrintTick(tick));
            i3 = -1;
        }
        else if(i3 >= mNumSlots){
            MILO_WARN("%s (%s): Keyboard gem pitch of %d is too high at %s.",
                mFilename, mTrackName, pitch, PrintTick(tick));
            i3 = -1;
        }
        else diff = mKeyboardDifficulty;
    }
    else {
        diff = 0;
        while(diff < mNumDifficulties){
            i3 = pitch - (diff * 0xC + 0x3C);
            if(i3 >= 0 && i3 < mNumSlots) return i3;
            diff++;
        }
        i3 = -1;
    }
    return i3;
}

bool SongParser::CheckDrumFillMarker(int pitch, bool b){
    int slots = mNumSlots;
    bool ret;
    if(mTrackType == kTrackRealKeys){
        slots = 5;
    }
    if(pitch < 120 || pitch >= slots + 120){
        ret = false;
    }
    else {
        if(b){
            if(mTrackType == kTrackRealKeys){
                if(pitch != 120){
                    MILO_WARN("%s (%s): Keyboards only use pitch 120 (C8) for BREs, but pitch %d is authored.",
                        mFilename, mTrackName, pitch);
                    mCurrentFillLanes = 0x1ffffff;
                }
            }
            else if(mTrackType == kTrackRealGuitar || mTrackType == kTrackRealGuitar22Fret){
                mCurrentFillLanes = 0x3F;
            }
            else {
                mCurrentFillLanes |= 1 << (pitch - 120 & 0x3F);
            }
        }
        return true;
    }
    return ret;
}

bool SongParser::CheckFillMarker(int pitch, bool b){ return CheckDrumFillMarker(pitch, b); }

bool SongParser::CheckDrumCymbalMarker(int, int, bool){

}

bool SongParser::CheckRollMarker(int, int pitch, bool){ return pitch == 126; }
bool SongParser::CheckTrillMarker(int pitch, bool){ return pitch == 127; }

bool SongParser::CheckDrumMapMarker(int i, int j, bool b){
    if(!mDrumStyleGems) return false;
    else if(j > 108 && j < 113){
        mSink->DrumMapLane(mTrack, i, j - 108, b);
        return true;
    }
    else return false;
}

bool SongParser::CheckKeyboardRangeMarker(int tick, int pitch, bool b){
    if(mTrackType != kTrackRealKeys) return false;
    if(pitch > 24U) return false;
    if(b){
        if(mKeyboardRangeFirstPitch == -1){
            MILO_ASSERT(mKeyboardRangeSecondPitch == -1, 0x934);
            MILO_ASSERT(mKeyboardRangeStartTick == -1, 0x935);
            mKeyboardRangeFirstPitch = pitch;
            mKeyboardRangeStartTick = tick;
        }
        else {
            MILO_ASSERT(mKeyboardRangeSecondPitch == -1, 0x93C);
            mKeyboardRangeSecondPitch = pitch;
            if(mKeyboardRangeStartTick != tick){
                MILO_WARN("%s (%s): Keyboard range markers don't begin at same time! %s vs. %s",
                    mFilename, mTrackName, PrintTick(mKeyboardRangeStartTick), PrintTick(tick));
            }
        }
    }
    else if(mKeyboardRangeStartTick != -1){
        MILO_ASSERT(mKeyboardRangeFirstPitch != -1, 0x951);
        int old_2nd = mKeyboardRangeSecondPitch;
        if(old_2nd != -1){
            int old_1st = mKeyboardRangeFirstPitch;
            if(old_2nd < old_1st){
                mKeyboardRangeFirstPitch = old_2nd;
                mKeyboardRangeSecondPitch = old_1st;
            }
            mKeyboardRangeSecondPitch++;
        }
        if(mTrack < 100){
            mSink->AddKeyboardRangeShift(mKeyboardDifficulty, mKeyboardRangeStartTick,
                mKeyboardRangeShiftDuration, mKeyboardRangeFirstPitch, mKeyboardRangeSecondPitch);
        }
        mKeyboardRangeSecondPitch = -1;
        mKeyboardRangeFirstPitch = -1;
        mKeyboardRangeStartTick = -1;
    }
    return true;
}

void SongParser::InitReadingState(){ mReadingState = kReadingBeat; }

void SongParser::UpdateReadingState(){
    switch(mReadingState){
        case kReadingBeat:
            mReadingState = kReadingNonParts;
            break;
        case kReadingNonParts:
            mReadingState = kReadingParts;
            break;
        case kReadingParts:
            mReadingState = kDoneReading;
            break;
        case kDoneReading:
            MILO_FAIL("SongParser::UpdateReadingState in wrong state");
            break;
    }
}

int SongParser::PartNumThatMatchesTrackName(const char* name) const {
    int i;
    for(i = 0; i < mParts.size(); i++){
        const char* curname = mParts[i].original_name.Str();
        int curnamelen = strlen(curname);
        bool b2;
        if(curnamelen + 2 < strlen(name)) b2 = false;
        else b2 = strncmp(curname, name, curnamelen) == 0;
        if(b2) return i;
    }
    return -1;
}

bool SongParser::ShouldReadTrack(Symbol s){
    if(mCurTrackIndex == 0) return !mMerging;
    else {
        bool isparttrackname = IsPartTrackName(s.Str(), 0);
        switch(mReadingState){
            case kReadingBeat:
                return s == "BEAT";
            case kReadingNonParts:
                bool nottrackname = !isparttrackname;
                if(nottrackname){
                    return s == "BEAT";
                }
                else return nottrackname;
            case kReadingParts:
                if(isparttrackname) return false;
                else return PartNumThatMatchesTrackName(s.Str()) != -1;
            case kDoneReading:
                MILO_FAIL("SongParser::ShouldReadTrack in wrong state");
                return false;
        }
    }
    return false;
}

void SongParser::SetSectionBounds(int start, int end){
    mSectionStartTick = start;
    mSectionEndTick = end;
}

NoStrumState SongParser::GetNoStrumState(int i, DifficultyInfo& info){
    if(!mTrackAllowsHopos) return kStrumForceOff;
    if(info.mForceHopoOnStart <= i && i < info.mForceHopoOnEnd) return kStrumForceOn;
    if(info.mForceHopoOffStart <= i && i < info.mForceHopoOffEnd) return kStrumForceOff;
    return kStrumDefault;
}

bool SongParser::TrackAllowsOverlappingNotes(TrackType ty) const {
    return ty == kTrackVocals || ty == kTrackKeys || ty == kTrackRealKeys;
}

// fn_8048F728
bool SongParser::HandleRGGemStart(int tick, DifficultyInfo& info, unsigned char uc, unsigned char data, unsigned char channel, int difflevel){
    if((uc + 0xE8 & 0xFF) <= 5){
        unsigned char newuc = uc - 24;
        info.mRGGemsInfo[newuc] = RGGemInfo(tick, info.mActivePlayers, GetFret(data), channel);
        if(mSoloPhraseInProgress != -1){
            mSoloGemDifficultyMask |= (1 << (difflevel & 0x3FU));
        }
        return true;
    }
    else return false;
}

bool SongParser::HandleRGHandPos(unsigned char pitch, unsigned char velocity){
    if(pitch == 108){
        mRGHandPos = GetFret(velocity) & 0xFF;
        return true;
    }
    else return false;
}

bool SongParser::HandleRGArpeggioStart(int tick, DifficultyInfo& info, unsigned char uc1){
    if(uc1 == 32){
        info.mRGArpeggioStartTick = tick;
        return true;
    }
    else return false;
}

bool SongParser::HandleRGAreaStrumStart(int tick, DifficultyInfo& info, unsigned char uc1, unsigned char channel){
    if(uc1 == 33){
        RGStrumType state = kRGNoStrum;
        if(channel == 15) state = kRGStrumLow;
        else if(channel == 14) state = kRGStrum;
        else if(channel == 13) state = kRGStrumHigh;
        info.mRGAreaStrumType = state;
        info.mRGAreaStrumStartTick = tick;
        info.mRGAreaStrumEndTick = NULL_TICK;
        return true;
    }
    else return false;
}

bool SongParser::HandleRGChordNumsStart(int tick, DifficultyInfo& info, unsigned char uc1){
    if(uc1 == 35){
        info.mRGChordNumsStartTick = tick;
        info.mRGChordNumsEndTick = NULL_TICK;
        return true;
    }
    else return false;
}

bool SongParser::HandleRGLooseStrumStart(int tick, DifficultyInfo& info, unsigned char uc1){
    if(uc1 == 34){
        info.mRGLooseStrumStartTick = tick;
        info.mRGLooseStrumEndTick = NULL_TICK;
        return true;
    }
    return false;
}

bool SongParser::HandleRGRootNote(unsigned char uc){
    if((uc + 0xFC & 0xFF) <= 0xB){
        mRGRootNote = uc % 12;
        return true;
    }
    return false;
}

bool SongParser::HandleRGGemStop(int tick, DifficultyInfo& info, unsigned char uc1, int difflevel){
    bool b1 = (uc1 + 0xE8 & 0xFF) > 5;
    if(b1) return false;
    else {
        bool b2 = true;
        if(!b1){
            unsigned char stringnum = uc1 - 24;
            if(info.mRGGemsInfo[0].mGem.mTick == -1){
                MILO_WARN("%s (%s): RG Gem on string %d ended but never started at tick %s",
                    mFilename, mTrackName, stringnum, PrintTick(tick));
                return true;
            }
        }
    }
}

bool SongParser::HandleRGChordNaming(int tick, unsigned char pitch){
    if(pitch == 17){
        mRGChordNamingStartTick = tick;
        mRGChordNamingEndTick = NULL_TICK;
        return true;
    }
    else return false;
}

bool SongParser::HandleRGEnharmonic(int tick, unsigned char pitch){
    if(pitch == 18){
        mRGEnharmonicStartTick = tick;
        mRGEnharmonicEndTick = NULL_TICK;
        return true;
    }
    else return false;
}

bool SongParser::HandleRGSlashes(int tick, unsigned char pitch){
    if(pitch == 16){
        mRGSlashesStartTick = tick;
        mRGSlashesEndTick = NULL_TICK;
        return true;
    }
    else return false;
}

bool SongParser::HandleRGChordMarkup(int tick, unsigned char pitch){
    if(pitch == 45){
        unk1ec = tick;
        return true;
    }
    if(pitch == 69){
        unk1f0 = tick;
        return true;
    }
    if(pitch == 93){
        unk1f4 = tick;
        return true;
    }
    return false;
}

bool SongParser::HandleRGChordMarkupStop(int tick, unsigned char pitch){
    if(pitch == 45){
        if(unk1ec != -1){
            AddPhrase(kChordMarkupPhrase, 1, unk1ec, tick);
            unk1ec = -1;
            return true;
        }
        MILO_WARN("double note-off in the real guitar part: pitch %d, tick %d", pitch, tick);
    }
    if(pitch == 69){
        if(unk1f0 != -1){
            AddPhrase(kChordMarkupPhrase, 2, unk1f0, tick);
            unk1f0 = -1;
            return true;
        }
        MILO_WARN("double note-off in the real guitar part: pitch %d, tick %d", pitch, tick);
    }
    if(pitch == 93){
        if(unk1f4 != -1){
            AddPhrase(kChordMarkupPhrase, 3, unk1f4, tick);
            unk1f4 = -1;
            return true;
        }
        MILO_WARN("double note-off in the real guitar part: pitch %d, tick %d", pitch, tick);
    }
    return false;
}

bool SongParser::HandleRGLeftHandSlide(int tick, DifficultyInfo& info, unsigned char uc1, unsigned char channel){
    if(uc1 == 31){
        info.mRGLeftHandSlideStartTick = tick;
        info.mRGLeftHandSlideEndTick = NULL_TICK;
        info.mRGFlipSlideDirection = (channel == 11);
        return true;
    }
    else return false;
}

bool SongParser::HandleRGLeftHandSlideStop(int tick, DifficultyInfo& info, unsigned char uc1){
    if(uc1 == 31){
        info.mRGLeftHandSlideEndTick = tick;
        return true;
    }
    else return false;
}

bool SongParser::HandleRGArpeggioStop(int tick, DifficultyInfo& info, unsigned char uc1, int difflevel){
    if(uc1 == 32){
        AddPhrase(kArpeggioPhrase, difflevel, info.mRGArpeggioStartTick, tick);
        info.mRGArpeggioStartTick = -1;
        return true;
    }
    else return false;
}

bool SongParser::HandleRGHopoStart(int tick, DifficultyInfo& info, unsigned char uc1, unsigned char channel){
    if(uc1 == 30){
        if(channel != 12){
            info.mForceHopoOnStart = tick;
            info.mForceHopoOnEnd = NULL_TICK;
        }
        else {
            info.mForceHopoOffStart = tick;
            info.mForceHopoOffEnd = NULL_TICK;
        }
        return true;
    }
    else return false;
}

bool SongParser::HandleRGHopoStop(int tick, DifficultyInfo& info, unsigned char uc1, unsigned char channel){
    if(uc1 == 30){
        if(channel != 12){
            info.mForceHopoOnEnd = tick;
        }
        else {
            info.mForceHopoOffEnd = tick;
        }
        return true;
    }
    else return false;
}

bool SongParser::HandleRGChordNamingStop(int tick, unsigned char pitch){
    if(pitch == 17){
        mRGChordNamingEndTick = tick;
        return true;
    }
    else return false;
}

bool SongParser::HandleRGEnharmonicStop(int tick, unsigned char pitch){
    if(pitch == 18){
        mRGEnharmonicEndTick = tick;
        return true;
    }
    else return false;
}

bool SongParser::HandleRGSlashesStop(int tick, unsigned char pitch){
    if(pitch == 16){
        mRGSlashesEndTick = tick;
        return true;
    }
    else return false;
}

bool SongParser::HandleRGLooseStrumStop(int tick, DifficultyInfo& info, unsigned char pitch){
    if(pitch == 34){
        info.mRGLooseStrumEndTick = tick;
        return true;
    }
    else return false;
}

bool SongParser::HandleRGAreaStrumStop(int tick, DifficultyInfo& info, unsigned char pitch, unsigned char channel){
    if(pitch == 33){
        info.mRGAreaStrumEndTick = tick;
        return true;
    }
    else return false;
}

bool SongParser::HandleRGChordNumsStop(int tick, DifficultyInfo& info, unsigned char pitch){
    if(pitch == 35){
        info.mRGChordNumsEndTick = tick;
        return true;
    }
    else return false;
}

bool SongParser::HandleRGRollStart(int tick, unsigned char pitch, unsigned char data){
    if(pitch == 126){
        mRollInProgress = tick;
        mRollMask = 0;
        for(int i = 0; i < mNumDifficulties; i++){
            if(GetRollIntervalMs(mRollIntervals, mTrackType, i, false) > 0.0f && (i != 2 || data <= 0x32)){
                mRollMask |= (1 << (i & 0x3F));
            }
        }
        return true;
    }
    else return false;
}

int SongParser::RGGetDifficultyLevel(unsigned char pitch){
    if(pitch < 24) return -1;
    int diff = (pitch - 24) / 24;
    if(diff > 3) return -1;
    else return diff;
}