#include "beatmatch/SongParser.h"
#include "os/System.h"
#include "midi/MidiConstants.h"

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
            mDrumStyleInstruments.push_back(drumInstArr->Array(1)->Int(i));
        }
    }

    DataArray* vocalInstArr = parserArr->FindArray("vocal_style_instruments", false);
    if(vocalInstArr){
        for(int i = 0; i < vocalInstArr->Array(1)->Size(); i++){
            mVocalStyleInstruments.push_back(vocalInstArr->Array(1)->Int(i));
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