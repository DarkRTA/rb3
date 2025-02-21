#include "MultiplayerAnalyzer.h"
#include "beatmatch/BeatMatchUtl.h"
#include "beatmatch/TrackType.h"
#include "game/BandUserMgr.h"
#include "game/Defines.h"
#include "game/Scoring.h"
#include "os/Debug.h"
#include "os/System.h"
#include "os/User.h"

MultiplayerAnalyzer::MultiplayerAnalyzer(SongData *songData)
    : mName(""), mSongData(songData), mScoreInfos(), mConfig() {}

void MultiplayerAnalyzer::PostLoad() {
    AddSolos();
    AddGems();
    AddCodas();
    for (int i = 0; i < mNumPlayers; i++) {
        Data &data = mDatas[i];
        if (data.mTrackType != kTrackNone) {
            mScoreInfos.push_back(PlayerScoreInfo(
                data.mTrackType,
                data.mDifficulty,
                data.mMaxStreakPts,
                data.mMaxPts,
                data.unk_0x20
            ));
        }
    }
    TheScoring->ComputeStarThresholds(false);
}

void MultiplayerAnalyzer::AddUser(const UserGuid &u) {
    mDatas.push_back(Data());
    Data &data = mDatas.back();
    BandUser *user = TheBandUserMgr->GetBandUser(u, false);
    data.SetUserGuid(u);
    data.mTrackType = kTrackNone;
    data.mDifficulty = user ? user->GetDifficulty() : kDifficultyEasy;
    data.mMaxStreakPts = 0;
    data.mMaxPts = 0;
    data.unk_0x20 = 0;
    data.unk_0x24 = 0;
    data.unk28 = 0;
    data.unk2c = 0;
    data.mMaxMultiplier = 1;
}

void MultiplayerAnalyzer::Configure(PlayerTrackConfigList *pList) {
    mConfig = pList;
    mNumPlayers = mConfig->NumConfigs();
    mDatas.clear();
    mScoreInfos.clear();
    for (int i = 0; i < mNumPlayers; i++) {
        AddUser(mConfig->GetUserGuidByIndex(i));
    }
}

float MultiplayerAnalyzer::GetMaxPoints(const UserGuid &userGuid) const {
    const Data *data = GetData(userGuid);
    return !data ? 0 : data->mMaxPts;
}

float MultiplayerAnalyzer::GetMaxStreakPoints(const UserGuid &userGuid) const {
    const Data *data = GetData(userGuid);
    return !data ? 0 : data->mMaxStreakPts;
}

float MultiplayerAnalyzer::GetBonusPoints(const UserGuid &userGuid) const {
    const Data *data = GetData(userGuid);
    return !data ? 0 : data->unk_0x20 + data->unk_0x24;
}

void MultiplayerAnalyzer::OverrideBasePoints(
    int i1, TrackType ty, const UserGuid &userGuid, int i4, int i5, int i6
) {
    MILO_ASSERT(!userGuid.IsNull(), 0xA1);
    Data *pData = GetData(userGuid);
    if (!pData) {
        AddUser(userGuid);
        AddTrack(i1, ty);
        pData = GetData(userGuid);
    }
    MILO_ASSERT(pData, 0xAA);
    pData->mMaxPts = i4;
    pData->mMaxStreakPts = i5;
    pData->unk_0x20 = i6;
    pData->unk_0x24 = 0;
    for (int i = 0; i < mScoreInfos.size(); i++) {
        if (ty == mScoreInfos[i].mTrackType) {
            mScoreInfos[i].unkc = i4;
            mScoreInfos[i].unk8 = i5;
            mScoreInfos[i].unk10 = i6;
            break;
        }
    }
    TheScoring->ComputeStarThresholds(false);
}

void MultiplayerAnalyzer::AddTrack(int i1, TrackType ty) {
    DataArray *cfg = SystemConfig("scoring", "points", TrackTypeToSym(ty));
    const UserGuid &u = mConfig->TrackPlayer(i1);
    if (!u.IsNull()) {
        Data *pData = GetData(u);
        MILO_ASSERT(pData, 199);
        pData->mTrackType = ty;
        pData->unk28 = cfg->FindInt("head");
        pData->unk2c = cfg->FindInt("tail");
        pData->unk30 = cfg->FindInt("chord");
        pData->mMaxMultiplier = (ty - 2U <= 7 && ((1 << (ty - 2U)) & 0xC1U)) ? 6 : 4;
        if (ty == kTrackDrum && mConfig->UseRealDrums()) {
            pData->unk28 += cfg->FindInt("pro_bonus");
        }
    }
}

void MultiplayerAnalyzer::AddGem(int i1, const GameGem &gem) {
    const UserGuid &userGuid = mConfig->TrackPlayer(i1);
    MILO_ASSERT(!userGuid.IsNull(), 0xDA);
    Data *pData = GetData(userGuid);
    MILO_ASSERT(pData, 0xDD);
    int slots = GemNumSlots(gem.GetSlots());
    int i6 = pData->unk28;
    if (slots > 1) {
        i6 = pData->unk28 * slots;
        if (pData->unk30 > 0) {
            i6 = pData->unk30;
        }
    }
    float f1;
    if (gem.IgnoreDuration()) {
        f1 = 0;
    } else {
        int i5 = pData->unk2c * gem.GetDurationTicks();
        f1 = (float)i5 / 480.0f;
    }
    int tick = gem.GetTick();
    f1 *= slots;
    pData->mGemScores.push_back(GemScore(tick, f1 + (float)i6));
}

void MultiplayerAnalyzer::AddSolo(const UserGuid &u, int i) {
    int iref = 0;
    Symbol sref;
    Data *pData = GetData(u);
    MILO_ASSERT(pData, 0xFE);
    TheScoring->GetSoloAward(100, TrackTypeToSym(pData->mTrackType), iref, sref);
    pData->unk_0x20 += i * iref;
}

const MultiplayerAnalyzer::Data *MultiplayerAnalyzer::GetData(const UserGuid &userGuid
) const {
    for (int i = 0; i < mDatas.size(); i++) {
        if (mDatas[i].mGuid == userGuid) {
            return &mDatas[i];
        }
    }

    return 0;
}

MultiplayerAnalyzer::Data *MultiplayerAnalyzer::GetData(const UserGuid &userGuid) {
    for (int i = 0; i < mDatas.size(); i++) {
        if (mDatas[i].mGuid == userGuid) {
            return &mDatas[i];
        }
    }

    return 0;
}
