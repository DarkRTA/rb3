#include "beatmatch/SongParser.h"
#include "os/System.h"

// fn_80488788
SongParser::SongParser(InternalSongParserSink& sink, int diff_nums, TempoMap*& tmap, MeasureMap*& mmap, int j) : mNumSlots(32), mPlayerSlot(9),
    mLowVocalPitch(36), mHighVocalPitch(84), mTempoMap(&tmap), mMeasureMap(&mmap), mMidiReader(0), mFile(0), mFilename(0), mMerging(0),
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