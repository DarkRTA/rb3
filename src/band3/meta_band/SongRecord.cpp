#include "meta_band/SongRecord.h"
#include "decomp.h"
#include "game/Defines.h"
#include "meta_band/BandProfile.h"
#include "meta_band/BandSongMetadata.h"
#include "meta_band/BandSongMgr.h"
#include "meta_band/MusicLibrary.h"
#include "meta_band/ProfileMgr.h"
#include "meta_band/SessionMgr.h"
#include "meta_band/SongStatusMgr.h"
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "stl/_pair.h"
#include "utl/Symbols.h"
#include "utl/Symbols3.h"

SongRecord::SongRecord(const BandSongMetadata *data)
    : mShortName(), mActiveScoreType(kNumScoreTypes), mReview(0), mPlays(0), mData(data) {
    mShortName = TheSongMgr.GetShortNameFromSongID(data->ID(), true);
    mDemo = TheSongMgr.IsDemo(data->ID());
    mRestricted = TheSongMgr.IsRestricted(data->ID());
    FOREACH (it, data->Ranks()) {
        Symbol key = it->first;
        float val = it->second;
        int tier = TheSongMgr.RankTier(val, key);
        mTier.insert(std::make_pair(key, tier));
    }
    for (int i = 0; i < kNumScoreTypes; i++) {
        mScores[i] = 0;
        mDiffs[i] = kDifficultyEasy;
        mStars[i] = 0;
        mNotesPct[i] = 0;
    }
    mBandInstrumentMask = 0;
    UpdateScoreType();
    UpdateSharedStatus();
    UpdatePerformanceData();
    UpdateReview();
}

int SongRecord::GetTier(Symbol s) const {
    if (mTier.find(s) == mTier.end()) {
        MILO_WARN(
            "Couldn't find %s rank for song %s. Please update songs.dta!",
            s.mStr,
            mShortName.mStr
        );
        return 0;
    } else
        return mTier.find(s)->second;
}

short SongRecord::GetInstrumentMask(ScoreType ty) const {
    if (ty == kScoreBand) {
        return GetBandInstrumentMask();
    } else
        return 1 << ScoreTypeToTrackType(ty);
}

FORCE_LOCAL_INLINE
Symbol SongRecord::GetShortDifficultySym(ScoreType ty) const {
    return DifficultyToShortSym(GetDifficulty(ty));
}
END_FORCE_LOCAL_INLINE

bool SongRecord::UpdatePerformanceData() {
    bool updated = false;
    BandProfile *profile = TheProfileMgr.GetPrimaryProfile();
    int plays = 0;
    if (profile) {
        plays = profile->GetSongStatusMgr()->GetSongPlayCount(mData->ID());
    }
    if (plays != mPlays) {
        mPlays = plays;
        updated = true;
    }
    for (int i = 0; i < kNumScoreTypes; i++) {
        int curScore = 0;
        Difficulty curDiff = kDifficultyEasy;
        int curStars = 0;
        int curAccuracy = 0;
        short curMask = 0;
        if (profile && !mDemo) {
            curScore = profile->GetSongHighScore(mData->ID(), (ScoreType)i);
            curDiff = profile->GetSongStatusMgr()->GetHighScoreDifficulty(
                mData->ID(), (ScoreType)i
            );
            curStars =
                profile->GetSongStatusMgr()->GetStars(mData->ID(), (ScoreType)i, curDiff);
            curAccuracy = profile->GetSongStatusMgr()->GetAccuracy(
                mData->ID(), (ScoreType)i, curDiff
            );
            if (i == 10) {
                curMask = profile->GetSongStatusMgr()->GetBandInstrumentMask(mData->ID());
            }
        }
        if (curScore != mScores[i]) {
            mScores[i] = curScore;
            updated = true;
        }
        if (curDiff != mDiffs[i]) {
            mDiffs[i] = curDiff;
            updated = true;
        }
        if (curStars != mStars[i]) {
            mStars[i] = curStars;
            updated = true;
        }
        if (curAccuracy != mNotesPct[i]) {
            mNotesPct[i] = curAccuracy;
            updated = true;
        }
        if (i == 10 && curMask != mBandInstrumentMask) {
            mBandInstrumentMask = curMask;
            updated = true;
        }
    }
    return updated;
}

bool SongRecord::UpdateReview() {
    int review = 0;
    BandProfile *profile = TheProfileMgr.GetPrimaryProfile();
    if (profile) {
        review = profile->GetSongStatusMgr()->GetSongReview(mData->ID());
    }
    if (review != mReview) {
        mReview = review;
        return true;
    } else
        return false;
}

bool SongRecord::UpdateScoreType() {
    ScoreType ty = TheMusicLibrary->ActiveScoreType();
    if (ty != mActiveScoreType) {
        mActiveScoreType = ty;
        return true;
    } else
        return false;
}

bool SongRecord::UpdateSharedStatus() {
    bool shared = TheSessionMgr->GetMachineMgr()->IsSongShared(mData->ID());
    if (shared != mIsShared) {
        mIsShared = shared;
        return true;
    } else
        return false;
}

bool SongRecord::UpdateRestricted() {
    bool restricted = TheSongMgr.IsRestricted(mData->ID());
    if (restricted != mRestricted) {
        mRestricted = restricted;
        return true;
    } else
        return false;
}

BEGIN_HANDLERS(SongRecord)
    HANDLE_EXPR(get_active_score_type, mActiveScoreType)
    HANDLE_EXPR(get_score, GetScore())
    HANDLE_EXPR(short_difficulty_sym, GetShortDifficultySym())
    HANDLE_EXPR(get_stars, GetStars())
    HANDLE_EXPR(get_notes_pct, GetNotesPct())
    HANDLE_EXPR(get_instrument_mask, GetInstrumentMask())
    HANDLE_EXPR(get_review, GetReview())
    HANDLE_EXPR(update_review, UpdateReview())
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_MEMBER_PTR(((BandSongMetadata *)mData))
    HANDLE_CHECK(0x107)
END_HANDLERS