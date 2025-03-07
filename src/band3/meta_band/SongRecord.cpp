#include "meta_band/SongRecord.h"
#include "decomp.h"
#include "game/Defines.h"
#include "meta_band/BandSongMetadata.h"
#include "meta_band/BandSongMgr.h"
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "stl/_pair.h"
#include "utl/Symbols.h"
#include "utl/Symbols3.h"

SongRecord::SongRecord(const BandSongMetadata *data)
    : mShortName(), mActiveScoreType(kNumScoreTypes), mReview(0), unkf8(0),
      mData((BandSongMetadata *)data) {
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
        return mBandInstrumentMask;
    } else
        return 1 << ScoreTypeToTrackType(ty);
}

FORCE_LOCAL_INLINE
Symbol SongRecord::GetShortDifficultySym(ScoreType ty) const {
    return DifficultyToShortSym(mDiffs[ty]);
}
END_FORCE_LOCAL_INLINE

BEGIN_HANDLERS(SongRecord)
    HANDLE_EXPR(get_active_score_type, mActiveScoreType)
    HANDLE_EXPR(get_score, GetScore())
    HANDLE_EXPR(short_difficulty_sym, GetShortDifficultySym())
    HANDLE_EXPR(get_stars, mStars[mActiveScoreType])
    HANDLE_EXPR(get_notes_pct, mNotesPct[mActiveScoreType])
    HANDLE_EXPR(get_instrument_mask, GetInstrumentMask(mActiveScoreType))
    HANDLE_EXPR(get_review, mReview)
    HANDLE_EXPR(update_review, UpdateReview())
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_MEMBER_PTR(mData)
    HANDLE_CHECK(0x107)
END_HANDLERS