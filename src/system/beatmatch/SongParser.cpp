#include "beatmatch/SongParser.h"
#include "os/System.h"
#include "midi/MidiConstants.h"
#include "utl/FilePath.h"
#include "beatmatch/GameGem.h"
#include "utl/TempoMap.h"
#include "os/Timer.h"

Timer gSongLoadTimer;

// fn_80488788
SongParser::SongParser(InternalSongParserSink& sink, int diff_nums, TempoMap*& tmap, MeasureMap*& mmap, int j) : mNumSlots(32), mPlayerSlot(9),
    mLowVocalPitch(36), mHighVocalPitch(84), mTempoMap(tmap), mMeasureMap(mmap), mMidiReader(0), mFile(0), mFilename(0), mMerging(0),
    mSink(&sink), mSongInfo(0), mNumPlayers(1), mNumDifficulties(diff_nums), mTrack(-1), mRollIntervals(0), mTrillIntervals(0),
    mKeyboardDifficulty(-1), mKeyboardRangeFirstPitch(-1), mKeyboardRangeSecondPitch(-1), mKeyboardRangeStartTick(-1),
    mKeyboardRangeShiftDuration(100.0f), mIgnoreGemDurations(0), mSectionStartTick(-1), mSectionEndTick(-1), mLyricPitchSet(0),
    mLyricTextSet(0), mLyricBends(0), mNextLyricTextTick(-1), mReadingState(kReadingBeat), mNumDrumChannels(j), mDrumSubmixDifficultyMask(0),
    mCodaStartTick(-1), mCodaEndTick(-1), mSoloGemDifficultyMask(0), mVocalPhraseStartTick(-1), mLastTambourineGemTick(-1),
    mLastTambourineAutoTick(-1), mLastBeatTick(-1), mLastBeatType(-1), mHaveBeatFailure(0), mSoloPitch(0),
    unk1e4(-1), unk1e8(-1), unk1ec(-1), unk1f0(-1), unk1f4(-1), unk1f8(-1), unk1fc(-1), unk200(-1), unk204(-1), unk208(-1), unk20c(-1) {

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
//     fn_804890C4(auStack_15c,0x20);
//     fn_80488CE4(param_1 + 0x1f,auStack_15c);
//     fn_8047E1BC(auStack_15c,0xffffffff);
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
        // mParts[i].unk18 = 0;
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

    }
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

bool SongParser::OnMidiMessageCommonOn(int tick, unsigned char uc){
    if(uc == 0x74){
        mCommonPhraseInProgress = tick;
        return true;
    }
    else if(uc == mSoloPitch){
        mSoloPhraseInProgress = tick;
        mSoloPhraseEndTick = -1;
        mSoloGemDifficultyMask = 0;
        mNumSoloPhrases++;
        return true;
    }
    else if(CheckDrumFillMarker(uc, true)){
        OnFillStart(tick, uc);
        return true;
    }
    else return false;
}

bool SongParser::OnMidiMessageCommonOff(int tick, unsigned char uc){
    if(HandlePhraseEnd(tick, uc)) return true;
    else return HandleFillEnd(tick, uc);
}

void SongParser::OnMidiMessageGemOn(int tick, unsigned char uc1, unsigned char uc2){
    MILO_ASSERT(mTrack != -1, 500);
    if(!OnMidiMessageCommonOn(tick, uc1)){
        int num = -1;
        if(!CheckForceHopoMarker(tick, uc1, true)){
            if(CheckDrumMapMarker(tick, uc1, true)){
                CheckDrumCymbalMarker(tick, uc1, true);
            }
            else if(CheckRollMarker(tick, uc1, true)){
                mRollInProgress = tick;
                unka1 = 0;
                for(int i = 0; i < 4; i++){
                    if(GetRollIntervalMs(mRollIntervals, mTrackType, i, false) > 0 && (i != 2 || uc2 <= 0x32)){
                        unka1 |= (1 << (i & 0x3F));
                    }
                }
            }
            else if(CheckTrillMarker(uc1, true)){
                mTrillInProgress = tick;
                unka0 = 0;
                for(int i = 0; i < 4; i++){
                    if(mTrillIntervals->Int(i) > 0 && (i != 2 || uc2 <= 0x32)){
                        unka0 |= (1 << (i & 0x3F));
                    }
                }
            }
            else if(!CheckKeyboardRangeMarker(tick, uc1, true) && PitchToSlot(uc1, num, tick) != -1){
                //   iVar7 = *(int *)(this + 0x100);
                //   bVar1 = *(byte *)(*(int *)(this + 0x7c) + local_50 * 0x13c + 8);
                //   piVar2 = (int *)(*(int *)(*(int *)(this + 0x7c) + local_50 * 0x13c) + iVar5 * 0x10);
                //   *piVar2 = param_1;
                //   piVar2[1] = unaff_r28;
                //   piVar2[2] = (uint)bVar1;
                //   piVar2[3] = iVar7;
                if(mSoloPhraseInProgress != -1){
                    mSoloGemDifficultyMask |= (1 << (num & 0x3F));
                }
                if(mDrumStyleGems){
                    if((mDrumSubmixDifficultyMask & 1 << (num & 0x3F) == 0) && !mReportedMissingDrumSubmix[num]){
                        MILO_WARN("%s (%s): No drum submix specified for difficulty %d before first gem at %s",
                            mFilename, mTrackName, num, PrintTick(tick));
                    }
                    int count = 0;
                    if(mNumSlots > 1){
                        for(int i = 0; i < mNumSlots - 1; i++){
                            // fix this
                            count++;
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
    if(pitch == 0x74){
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
    else if(pitch == mSoloPitch){
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
        bool b2 = true;
        if(mSectionStartTick != -1){
            bool b1 = false;
            if(on_tick >= mSectionStartTick && on_tick < mSectionEndTick){
                b1 = true;
            }
            if(!b1) b2 = false;
        }
        if(b2){
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

void SongParser::OnFillStart(int tick, unsigned char uc){
    bool b = false;
    if(mCodaStartTick != -1 && tick >= mCodaStartTick) b = true;
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
                PrintTick(mCodaStartTick), uc - 0x77, PrintTick(tick));
            mDrumFillInProgress = mCodaStartTick;
        }
    }
    else if(tick != mDrumFillInProgress){
        if(b){
            MILO_WARN("%s (%s): Big Rock Ending %s-%s: lanes do not all begin at [coda]; [coda] is at %s, lane %d begins at %s",
                mFilename, mTrackName, PrintTick(mCodaStartTick), PrintTick(mCodaEndTick),
                PrintTick(mCodaStartTick), uc - 0x77, PrintTick(tick));
        }
        else if(mDrumStyleGems){
            MILO_WARN("%s (%s): Drum fill beginning at %s: lanes do not all begin at the same tick; lane %d begins at %s",
                mFilename, mTrackName, PrintTick(mDrumFillInProgress), uc - 0x77, PrintTick(tick));
        }
    }
}

void SongParser::OnFillEnd(int tick, unsigned char uc){
    bool b = false;
    if(mCodaStartTick != -1 && tick >= mCodaStartTick) b = true;
    if(mDrumFillInProgress != -1){
        if(mDrumStyleGems && (mSoloPhraseInProgress != -1 || (mDrumFillInProgress <= mSoloPhraseEndTick))){
            MILO_WARN("%s (%s): Drum fill %s-%s overlaps solo",
                mFilename, mTrackName, PrintTick(mDrumFillInProgress), PrintTick(tick));
        }
        if(mCurrentFillLanes != (1 << (mNumSlots & 0x3F)) - 1){
            if(b){
                MILO_WARN("%s (%s): Big Rock Ending %s-%s is not authored for all lanes",
                    mFilename, mTrackName, PrintTick(mDrumFillInProgress), PrintTick(tick));
            }
            else {
                MILO_WARN("%s (%s): Drum fill %s-%s is not authored for all lanes",
                    mFilename, mTrackName, PrintTick(mDrumFillInProgress), PrintTick(tick));
            }
        }
        if(mDrumStyleGems && (mDrumFillInProgress < mCodaStartTick) && b){
            MILO_WARN("%s (%s): Drum fill %s-%s straddles [coda] event at %s",
                mFilename, mTrackName, PrintTick(mDrumFillInProgress), PrintTick(tick), PrintTick(mCodaStartTick));
        }

        bool b2 = false;
        if(mSectionStartTick != -1){
            bool b1 = false;
            if(mSectionStartTick <= mDrumFillInProgress && mDrumFillInProgress < mSectionEndTick) b1 = true;
            if(!b1) b2 = false;
        }
        if(b2){
            if(mTrackType == kTrackRealKeys && mKeyboardDifficulty != 3){
                MILO_WARN("%s: Real keys BREs should only authored in expert difficulty, but found in track %s.", mFilename, mTrackName);
            }
        }
        mDrumFillInProgress = -1;
        mDrumFillEndTick = tick;
        mCurrentFillLanes = 0;
        if(b){
            if(mCodaEndTick == -1) mCodaEndTick = tick;
            else if(tick != mCodaEndTick){
                MILO_WARN("%s (%s): Big Rock Ending %s-%s: all lanes in all tracks must end at the same tick; lane %d ends at %s",
                    mFilename, mTrackName, PrintTick(mCodaStartTick), PrintTick(mCodaEndTick), uc - 0x77, PrintTick(tick));
            }
        }
    }
    else {
        if(uc > 0x77 && uc < mNumSlots + 0x78 && tick != mDrumFillEndTick){
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
        int curmask = 1 << (i & 0x3F);
        if(curmask & mDrumSubmixDifficultyMask){
            MILO_WARN("%s (%s): No drum submix specified for difficulty %d", mFilename, mTrackName, i);
        }
    }
}

bool SongParser::HandleRollEnd(int tick, unsigned char uc){
    if(!CheckRollMarker(tick, uc, false)){
        return false;
    }
    else if(mTrackType == kTrackRealKeys && mKeyboardDifficulty != 3){
        return true;
    }
    else {
        MILO_ASSERT(mRollInProgress != -1, 0x3C6);
        bool b2 = true;
        if(mSectionStartTick != -1){
            bool b1 = false;
            if(mSectionStartTick <= mRollInProgress && mRollInProgress < mSectionEndTick){
                b1 = true;
            }
            if(!b1) b2 = false;
        }
        if(b2){
            for(int i = 0; i < mNumDifficulties; i++){
                unsigned int u6 = mRollSlotsArray[i];
                if(mTrackType == kTrackRealKeys) u6 = 1;
                int bits = GameGem::CountBitsInSlotType(u6);
                if(unka1 & (1 << (i & 0x3F))){
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
            if(strcmp(name, "BEAT") == 0) mState = kBeat;
            else if(strcmp(name, "EVENTS") == 0) mState = kEvents;
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

void SongParser::PrepareTrack(const char* track_name, PartInfo* info){
    Reset();
    bool b2 = false;
    for(std::vector<PartInfo>::iterator it = mParts.begin(); it != mParts.end(); ++it){
        int original_name_len = strlen(it->original_name.Str());
        bool b3;
        if(original_name_len + 2 < strlen(track_name)) b3 = false;
        else b3 = strncmp(it->original_name.Str(), track_name, original_name_len) == 0;
        if(b3){
            if(it->song_data_track == -1){
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
        if(info->audio_type == kAudioFake){
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
    if(newty < kTrackRealBass22Fret && ((1 << (newty & 0x3F) & 0x1EBU) != 0)){
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