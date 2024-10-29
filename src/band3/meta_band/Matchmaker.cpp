#include "meta_band/Matchmaker.h"
#include "Matchmaker.h"
#include "game/GameMode.h"
#include "net/NetSession.h"
#include "obj/Data.h"
#include "obj/Dir.h"
#include "obj/MsgSource.h"
#include "obj/ObjMacros.h"
#include "os/Debug.h"
#include "os/System.h"
#include "utl/Symbols2.h"
#include "utl/Symbols3.h"
#include "utl/Symbols4.h"

MatchmakerPoolStats::MatchmakerPoolStats(){
    DataArray* cfg = SystemConfig("net", "matchmaker", "pool_min_thresholds");
    for(int i = 0; i < 3; i++){
        mRatingThresholds[i] = cfg->Int(i + 1);
    }
    ClearStats();
}

void MatchmakerPoolStats::ClearStats(){
    for(int i = 0; i < 4; i++) mSlotRatings[i] = kRed;
    mHasCurrentStats = false;
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

Matchmaker::~Matchmaker(){
    delete mPoolStats;
    delete mQuickFindingMode;
    delete mBandFindingMode;
}

void Matchmaker::SetQuickFindingMode(MatchmakerFindType type){
    MILO_ASSERT(!IsFinding(), 0xD1);
    mQuickFindingMode->Init(type);
    mMode = mQuickFindingMode;
    UpdateMatchmakingSettings();
}

void Matchmaker::FindPlayers(MatchmakerFindType ty){
    SetQuickFindingMode(ty);
    FindPlayersImpl();
    static MatchmakerChangedMsg msg;
    Export(msg, true);
}

void Matchmaker::CancelFind(){
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
    DataArray* cfg = SystemConfig("net", "matchmaker");
    cfg->FindData("searching_interval", mSearchingInterval, true);
}

BandMatchmaker::~BandMatchmaker(){
    TheNetSession->RemoveSink(this, join_result);
    TheGameMode->RemoveSink(this, mode_changed);
}

inline int QuickFinding::GetNextQueryType(){
    MILO_ASSERT(!mQueryTypes.empty(), 0xA0);
    int next = mQueryTypes.front();
    mQueryTypes.erase(mQueryTypes.begin());
    mQueryTypes.push_back(next);
    return next;
}