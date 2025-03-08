#include "meta_band/SongRecord.h"
#include "SavedSetlist.h"
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
#include "utl/Locale.h"
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

SetlistRecord::SetlistRecord(SavedSetlist *setlist) : mSetlist(setlist) {
    mToken = setlist->GetIdentifyingToken();
    BattleSavedSetlist *battleSetlist = dynamic_cast<BattleSavedSetlist *>(setlist);
    unk24 = battleSetlist;
    unk28 = battleSetlist ? battleSetlist->unk68 : -1;
    unk2c = battleSetlist ? battleSetlist->unk70 : -1;
    unk30 = battleSetlist ? battleSetlist->unk6c : 10;
}

bool SetlistRecord::IsLocal() const {
    return mSetlist->GetType() == SavedSetlist::kSetlistLocal;
}

bool SetlistRecord::IsNetSetlist() const {
    SavedSetlist::SetlistType ty = mSetlist->GetType();
    return ty == SavedSetlist::kSetlistFriend || ty == SavedSetlist::kSetlistHarmonix
        || ty == SavedSetlist::kBattleHarmonix || ty == SavedSetlist::kBattleFriend
        || ty == SavedSetlist::kBattleHarmonixArchived
        || ty == SavedSetlist::kBattleFriendArchived;
}

bool SetlistRecord::IsProfileOwner(const BandProfile *p) const {
    LocalSavedSetlist *setlist = dynamic_cast<LocalSavedSetlist *>(mSetlist);
    return !setlist ? false : (setlist->mOwnerProfile && setlist->mOwnerProfile == p);
}

const char *SetlistRecord::GetOwner() const {
    const char *owner = mSetlist->GetOwner();
    if (owner)
        return owner;
    else
        Localize(harmonix, nullptr);
}

BEGIN_HANDLERS(SetlistRecord)
    HANDLE_EXPR(id, unk28)
    HANDLE_EXPR(get_owner, GetOwner())
    HANDLE_EXPR(get_art_tex, mSetlist->GetArtTex())
    HANDLE_EXPR(get_setlist_type_sym, SavedSetlist::SetlistTypeToSym(mSetlist->GetType()))
    HANDLE_EXPR(is_local_setlist, mSetlist->GetType() == SavedSetlist::kSetlistLocal)
    HANDLE_EXPR(is_net_setlist, IsNetSetlist())
    HANDLE_EXPR(is_battle, mSetlist->IsBattle())
    HANDLE_EXPR(is_profile_owner, IsProfileOwner(_msg->Obj<BandProfile>(2)))
    HANDLE_EXPR(get_setlist, dynamic_cast<LocalSavedSetlist *>(mSetlist))
    HANDLE_EXPR(get_song_count, (int)mSetlist->mSongs.size())
    HANDLE_EXPR(get_length_ms, mSetlist->GetLengthMs())
    HANDLE_EXPR(get_title, mSetlist->GetTitle())
    HANDLE_EXPR(get_description, mSetlist->GetDescription())
    HANDLE_EXPR(get_battle_time_left, unk2c)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x17E)
END_HANDLERS