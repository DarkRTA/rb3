#include "meta_band/Matchmaker.h"
#include "Matchmaker.h"
#include "game/BandUserMgr.h"
#include "game/GameMode.h"
#include "math/Rand.h"
#include "meta_band/SessionMgr.h"
#include "net/MatchmakingSettings.h"
#include "net/Net.h"
#include "net/NetSearchResult.h"
#include "net/NetSession.h"
#include "obj/Data.h"
#include "obj/Dir.h"
#include "obj/Msg.h"
#include "obj/ObjMacros.h"
#include "os/Debug.h"
#include "os/System.h"
#include "utl/Symbols2.h"
#include "utl/Symbols3.h"
#include "utl/Symbols4.h"

MatchmakerPoolStats::MatchmakerPoolStats() {
    DataArray *cfg = SystemConfig("net", "matchmaker", "pool_min_thresholds");
    for (int i = 0; i < 3; i++) {
        mRatingThresholds[i] = cfg->Int(i + 1);
    }
    ClearStats();
}

void MatchmakerPoolStats::ClearStats() {
    for (int i = 0; i < 4; i++)
        mSlotRatings[i] = kRed;
    mHasCurrentStats = false;
}

void MatchmakerPoolStats::ReadStats(const std::vector<NetSearchResult *> &results) {
    int i10 = 0;
    int i9 = 0;
    int i8 = 0;
    for (int i = 0; i < results.size(); i++) {
        MatchmakingSettings *settings = results[i]->mSettings;
        i10 += (2 - settings->GetCustomValueByID(0x1000000c));
        i9 += (1 - settings->GetCustomValueByID(0x1000000a));
        i8 += (1 - settings->GetCustomValueByID(0x1000000b));
    }
    for (int i = 0; i < 3; i++) {
        int curThresh = mRatingThresholds[i];
        if (i10 >= curThresh) {
            mSlotRatings[3] = (SlotRating)i;
            mSlotRatings[0] = (SlotRating)i;
        }
        if (i9 >= curThresh) {
            mSlotRatings[1] = (SlotRating)i;
        }
        if (i8 >= curThresh) {
            mSlotRatings[2] = (SlotRating)i;
        }
    }
    mHasCurrentStats = true;
}

#define kGameNumSlots 4

SlotRating MatchmakerPoolStats::GetSlotRating(int slot) const {
    MILO_ASSERT(( 0) <= (slot) && (slot) < ( kGameNumSlots), 0x52);
    MILO_ASSERT(HasCurrentStats(), 0x53);
    return mSlotRatings[slot];
}

Matchmaker::Matchmaker() : mMode(0), unk20(0) {
    SetName("matchmaker", ObjectDir::Main());
    mQuickFindingMode = new QuickFinding();
    mBandFindingMode = new BandFinding();
    mPoolStats = new MatchmakerPoolStats();
}

Matchmaker::~Matchmaker() {
    delete mPoolStats;
    delete mQuickFindingMode;
    delete mBandFindingMode;
}

void Matchmaker::SetQuickFindingMode(MatchmakerFindType type) {
    MILO_ASSERT(!IsFinding(), 0xD1);
    mQuickFindingMode->Init(type);
    mMode = mQuickFindingMode;
    UpdateMatchmakingSettings();
}

void Matchmaker::FindPlayers(MatchmakerFindType ty) {
    SetQuickFindingMode(ty);
    FindPlayersImpl();
    static MatchmakerChangedMsg msg;
    Export(msg, true);
}

void Matchmaker::CancelFind() {
    mPoolStats->ClearStats();
    CancelFindImpl();
    static MatchmakerChangedMsg msg;
    Export(msg, true);
}

bool Matchmaker::IsHostingQp() const {
    return mMode == mQuickFindingMode && mQuickFindingMode->mFindType == kMatchmaker_Qp;
}

bool Matchmaker::IsHostingTour() const {
    return mMode == mQuickFindingMode && mQuickFindingMode->mFindType == kMatchmaker_Tour;
}

BEGIN_HANDLERS(Matchmaker)
    HANDLE_ACTION(find_players, FindPlayers((MatchmakerFindType)_msg->Int(2)))
    HANDLE_SUPERCLASS(MsgSource)
    HANDLE_CHECK(0xFD)
END_HANDLERS

BandMatchmaker::BandMatchmaker() : mSearching(0), unk32(0), unk6c(0), mDevChannel(0) {
    MILO_ASSERT(TheNetSession, 0x108);
    TheNetSession->AddSink(this, join_result);
    MILO_ASSERT(TheGameMode, 0x10C);
    TheGameMode->AddSink(this, mode_changed);
    MILO_ASSERT(TheNet.GetSearcher(), 0x110);
    TheNet.GetSearcher()->AddSink(this, search_finished);
    DataArray *cfg = SystemConfig("net", "matchmaker");
    cfg->FindData("searching_interval", mSearchingInterval, true);
}

BandMatchmaker::~BandMatchmaker() {
    TheNetSession->RemoveSink(this, join_result);
    TheGameMode->RemoveSink(this, mode_changed);
    TheNet.GetSearcher()->RemoveSink(this, search_finished);
    SetName(nullptr, ObjectDir::Main());
}

void BandMatchmaker::Poll() {
    mTime.Split();
    if (mSearching && !unk6c && TheNetSession->IsLocal() && !TheNetSession->IsBusy()) {
        if (!TheNet.GetSearcher()->Searching()) {
            unk6c = mTime.Ms();
        }
    }
    if (unk6c && mTime.Ms() > unk6c) {
        MILO_ASSERT(mSearching, 0x136);
        unk6c = 0;
        StartSearch(false);
    }
}

void BandMatchmaker::FindPlayersImpl() {
    MILO_ASSERT(TheSessionMgr->IsOnlineEnabled(), 0x140);
    MILO_ASSERT(mMode, 0x142);
    bool host = mMode->ShouldHost();
    bool search = mMode->ShouldSearch() && TheNetSession->IsLocal();
    MILO_ASSERT(host || search, 0x145);
    if (host && !search) {
        TheNetSession->mSettings->SetPublic(true);
        StartSearch(true);
    } else {
        MILO_ASSERT(!mSearching, 0x150);
        mSearching = true;
        unk32 = host;
        mTime.Restart();
        StartSearch(true);
    }
}

bool BandMatchmaker::IsFinding() const {
    return mSearching || TheNetSession->mSettings->mPublic;
}

void BandMatchmaker::CancelFindImpl() {
    mSearching = false;
    unk31 = false;
    unk32 = false;
    unk6c = 0;
    mTime.Stop();
    if (TheNetSession->GetSessionSettings()->HasSyncPermission()) {
        TheNetSession->GetSessionSettings()->SetPublic(false);
    }
    TheNet.GetSearcher()->StopSearching();
    TheNet.GetSearcher()->ClearSearchResults();
}

void BandMatchmaker::SetChannel(int i) {
    mDevChannel = i;
    UpdateMatchmakingSettings();
}

#pragma push
#pragma pool_data off
DataNode BandMatchmaker::OnSearchFinished() {
    if (unk31) {
        std::vector<NetSearchResult *> results;
        TheNet.GetSearcher()->GetSearchResults(results);
        mPoolStats->ReadStats(results);
        unk31 = false;
        static MatchmakerChangedMsg msg;
        Export(msg, true);
    }
    if (!mSearching)
        return 0;
    else if (!TheNetSession->IsLocal()) {
        unk6c = 0;
        return 0;
    } else {
        NetSearchResult *res;
        do {
            res = TheNet.GetSearcher()->GetNextResult();
            if (!res)
                break;
        } while (!HasCompatibleInstruments(res));
        if (res) {
            TheNetSession->Join(res);
            static MatchmakerChangedMsg msg;
            Export(msg, true);
        } else {
            float randF = RandomFloat(0, mSearchingInterval);
            unk6c = mSearchingInterval + randF + mTime.Ms();
            if (unk32)
                TheNetSession->mSettings->SetPublic(true);
        }
        return 1;
    }
}
#pragma pop

DataNode BandMatchmaker::OnMsg(const JoinResultMsg &msg) {
    static MatchmakerChangedMsg updateMsg;
    Export(updateMsg, true);
    if (msg->Int(2) == 0) {
        mSearching = false;
        TheNet.GetSearcher()->ClearSearchResults();
    } else if (mSearching) {
        OnSearchFinished();
    }
    return 1;
}

DataNode BandMatchmaker::OnMsg(const ModeChangedMsg &msg) {
    SessionSettings *settings = TheNetSession->GetSessionSettings();
    if (settings->HasSyncPermission()) {
        settings->SetMode(TheGameMode->mMode, 0);
        settings->SetRanked(TheGameMode->Property(ranked, true)->Int());
    }
    return 1;
}

void BandMatchmaker::UpdateMatchmakingSettings() {
    SessionSettings *settings = TheNetSession->GetSessionSettings();
    if (settings->HasSyncPermission()) {
        settings->SetMode(TheGameMode->mMode, 0);
        settings->SetRanked(TheGameMode->Property(ranked, true)->Int());
        AddCustomSettings(settings, (CustomSettingsType)0);
    }
}

void BandMatchmaker::StartSearch(bool b) {
    MILO_ASSERT(mMode, 0x1E5);
    unk31 = b;
    int ty = mMode->GetNextQueryType();
    bool prop = TheGameMode->Property(ranked, true)->Int();
    SearchSettings settings(0, prop, ty);
    AddCustomSettings(&settings, (CustomSettingsType)(unk31 ? 2 : 1));
    TheNet.GetSearcher()->StartSearching(TheNetSession->GetLocalHost(), settings);
}

void BandMatchmaker::AddCustomSettings(
    MatchmakingSettings *settings, CustomSettingsType settingsType
) {
    settings->ClearCustomSettings();
    settings->AddCustomSetting(0x10000009, mDevChannel);
    std::vector<BandUser *> users;
    TheBandUserMgr->GetBandUsersInSession(users);
    if (settingsType == 1) {
    } else if (settingsType == 0) {
    } else {
        MILO_ASSERT(settingsType == kGeneralSearch, 0x214);
    }
    MILO_FAIL("Session Participant has no controller\n");
}

bool BandMatchmaker::HasCompatibleInstruments(NetSearchResult *res) {
    MILO_FAIL("Participating user has not controller set.");
}

BEGIN_HANDLERS(BandMatchmaker)
    HANDLE_EXPR(is_finding, IsFinding())
    HANDLE_ACTION(cancel_find, CancelFind())
    HANDLE_ACTION(set_channel, SetChannel(_msg->Int(2)))
    HANDLE_EXPR(get_channel, mDevChannel)
    HANDLE_ACTION(search_finished, OnSearchFinished())
    HANDLE_MESSAGE(JoinResultMsg)
    HANDLE_MESSAGE(ModeChangedMsg)
    HANDLE_SUPERCLASS(Matchmaker)
    HANDLE_CHECK(0x2A4)
END_HANDLERS

BEGIN_PROPSYNCS(BandMatchmaker)
    SYNC_PROP(searching_interval, mSearchingInterval)
END_PROPSYNCS

inline int QuickFinding::GetNextQueryType() {
    MILO_ASSERT(!mQueryTypes.empty(), 0xA0);
    int next = mQueryTypes.front();
    mQueryTypes.erase(mQueryTypes.begin());
    mQueryTypes.push_back(next);
    return next;
}