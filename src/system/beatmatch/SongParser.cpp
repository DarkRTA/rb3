#include "beatmatch/SongParser.h"

// fn_80488788
SongParser::SongParser(InternalSongParserSink& sink, int i, TempoMap*& tmap, MeasureMap*& mmap, int j) : mNumSlots(32), mPlayerSlot(9),
    mLowVocalPitch(36), mHighVocalPitch(84), mTempoMap(&tmap), mMeasureMap(&mmap), mMidiReader(0), mFile(0), mFilename(0), mMerging(0),
    mSink(&sink), mSongInfo(0), mNumPlayers(1), mNumDifficulties(i), mTrack(-1), mRollIntervals(0), mTrillIntervals(0),
    mKeyboardDifficulty(-1), mKeyboardRangeFirstPitch(-1), mKeyboardRangeSecondPitch(-1), mKeyboardRangeStartTick(-1),
    mKeyboardRangeShiftDuration(100.0f), mSeparateParts(0), mSectionStartTick(-1), mSectionEndTick(-1), mLyricPitchSet(0),
    mLyricTextSet(0), mLyricBends(0), mNextLyricTextTick(-1), mReadingState(kReadingBeat), mNumDrumChannels(j), mDrumSubmixDifficultyMask(0),
    mCodaStartTick(-1), mCodaEndTick(-1), mSoloGemDifficultyMask(0), mVocalPhraseStartTick(-1), mLastTambourineGemTick(-1),
    mLastTambourineAutoTick(-1), mLastBeatTick(-1), mLastBeatType(-1), mHaveBeatFailure(0), mSoloPitch(0),
    unk1e4(-1), unk1e8(-1), unk1ec(-1), unk1f0(-1), unk1f4(-1), unk1f8(-1), unk1fc(-1), unk200(-1), unk204(-1), unk208(-1), unk20c(-1) {

}