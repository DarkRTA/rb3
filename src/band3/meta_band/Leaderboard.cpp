#include "meta_band/Leaderboard.h"
#include "Leaderboard.h"
#include "bandobj/ScoreDisplay.h"
#include "decomp.h"
#include "game/Defines.h"
#include "game/GameMessages.h"
#include "meta_band/AppLabel.h"
#include "net_band/DataResults.h"
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "os/Debug.h"
#include "net_band/RockCentral.h"
#include "rndobj/Draw.h"
#include "ui/UIColor.h"
#include "ui/UILabel.h"
#include "ui/UIListCustom.h"
#include "ui/UIListLabel.h"
#include "ui/UIListMesh.h"
#include "utl/Symbol.h"
#include "utl/Symbols.h"
#include "utl/Symbols2.h"
#include "utl/Symbols3.h"
#include "utl/Symbols4.h"

LeaderboardRow::LeaderboardRow(){
    mRank = 0;
    mORank = 0;
    mUnnamedBand = false;
    mIsPercentile = false;
    mIsFriend = false;
    mIsEntity = false;
    mDiffID = kNumDifficulties;
    mNotesPct = 0;
    mScore = 0;
    mInstMask = 0;
}

Leaderboard::Leaderboard(EntityID id, Callback* cb) : unk40(0), mHasStats(0), mMode(kFriends), mEntityID(id), mCallback(cb), mEnumState(kEnumInactive), mSelfColor(0), mFriendColor(0), unk80(-1) {
    mShortcutProvider = new LeaderboardShortcutProvider(this);
}

Leaderboard::~Leaderboard(){
    delete mShortcutProvider;
    mDataResultList.Clear();
    mLeaderboardRows.clear();
    CancelEnumerate();
}

void Leaderboard::StartEnumerate(){
    MILO_ASSERT(mEnumState == kEnumInactive, 0x52);
    mLeaderboardRows.clear();
    if(mMode == 0){
        mEnumState = kEnumWaiting;
        GetStats();
    }
    else {
        mEnumState = kEnumState2;
        unk80 = -1;
        EnumerateFromID();
    }
    if(mCallback) mCallback->EnumerationStarted();
}

void Leaderboard::CancelEnumerate(){
    TheRockCentral.CancelOutstandingCalls(this);
    mEnumState = kEnumInactive;
}

void Leaderboard::InitData(RndDir* rdir){
    mSelfColor = rdir->Find<UIColor>("self.color", false);
    mFriendColor = rdir->Find<UIColor>("friend.color", false);
}

void Leaderboard::Text(int, int data, UIListLabel* slot, UILabel* label) const {
    if(IsEnumComplete()){
        const LeaderboardRow& row = mLeaderboardRows[data];
        if(slot->Matches("name")){
            if(row.mIsPercentile){
                if(row.mIsFriend){
                    AppLabel* appLabel = dynamic_cast<AppLabel*>(label);
                    MILO_ASSERT(appLabel, 0x80);
                    appLabel->SetLeaderboardName(row);
                }
                else label->SetTokenFmt(percentile_fmt, 100 - row.mRank);
            }
            else {
                AppLabel* appLabel = dynamic_cast<AppLabel*>(label);
                MILO_ASSERT(appLabel, 0x8E);
                appLabel->SetLeaderboardRankAndName(row);
            }
            return;
        }
        else if(slot->Matches("difficulty") && ShowsDifficultyAndPct()){
            label->SetTextToken(DifficultyToShortSym(row.mDiffID));
            return;
        }
        else if(slot->Matches("percentage") && ShowsDifficultyAndPct()){
            label->SetTokenFmt(eg_percent_format, row.mNotesPct);
            return;
        }
    }
    label->SetTextToken(gNullStr);
}

RndMat* Leaderboard::Mat(int, int, UIListMesh* slot) const {
    if(slot->Matches("difficulty_bg") && !ShowsDifficultyAndPct()){
        return nullptr;
    }
    else return slot->DefaultMat();
}

void Leaderboard::Custom(int, int data, UIListCustom* slot, Hmx::Object* obj) const {
    if(IsEnumComplete()){
        if(slot->Matches("score")){
            ScoreDisplay* scr = dynamic_cast<ScoreDisplay*>(obj);
            MILO_ASSERT(scr, 0xB5);
            const LeaderboardRow& row = mLeaderboardRows[data];
            scr->SetValues(row.mInstMask, row.mScore, 0, false);
            scr->SetShowing(true);
        }
        else {
            RndDrawable* d = dynamic_cast<RndDrawable*>(obj);
            d->SetShowing(false);
        }
    }
}

int Leaderboard::NumData() const { return mLeaderboardRows.size(); }

UIColor* Leaderboard::SlotColorOverride(int, int data, UIListWidget*, UIColor* color) const {
    if(mSelfColor && IsRowSelf(data)){
        return mSelfColor;
    }
    else if(mFriendColor && IsRowFriend(data)){
        return mFriendColor;
    }
    else return color;
}

int Leaderboard::GetSelfRow() const {
    for(int i = 0; i < mLeaderboardRows.size(); i++){
        if(IsRowSelf(i)){
            return i;
        }
    }
    return -1;
}

void Leaderboard::OnEnumComplete(){
    mEnumState = kEnumDone;
    ShowData();
}

bool Leaderboard::EnumerateHigherRankRange(){
    if(mEnumState != kEnumDone && mEnumState != kEnumInactive) return false;
    else if(mMode) return false;
    else {
        MILO_ASSERT(mHasStats, 0xF0);
        MILO_ASSERT(!mLeaderboardRows.empty(), 0xF1);
        const LeaderboardRow& row = mLeaderboardRows.back();
        if(row.mORank < unk40){
            mEnumState = kEnumState2;
            unk80 = row.mORank + 1;
            mLeaderboardRows.clear();
            EnumerateRankRange(row.mORank + 1, 20);
            return true;
        }
        else return false;
    }
}

bool Leaderboard::EnumerateLowerRankRange(){
    if(mEnumState != kEnumDone && mEnumState != kEnumInactive) return false;
    else if(mMode) return false;
    else {
        MILO_ASSERT(mHasStats, 0x10A);
        MILO_ASSERT(!mLeaderboardRows.empty(), 0x10B);
        const LeaderboardRow& row = mLeaderboardRows.front();
        if(row.mORank > 1){
            mEnumState = kEnumState2;
            unk80 = row.mORank - 1;
            mLeaderboardRows.clear();
            int num = row.mORank - 20 >= 1 ? row.mORank - 20 : 1;
            EnumerateRankRange(num, 20);
            return true;
        }
        else return false;
    }
}

int Leaderboard::GetStartingRow() const {
    for(int i = 0; i < mLeaderboardRows.size(); i++){
        if((unk80 < 0 && IsRowSelf(i)) || (unk80 == mLeaderboardRows[i].mORank)){
            return i;
        }
    }
    MILO_WARN("Leaderboard row (rank %i) not found, selecting row 0.", unk80);
    return 0;
}

void Leaderboard::ShowData(){
    MILO_ASSERT(IsEnumComplete(), 300);
    mDataResultList.Update(0);
    mLeaderboardRows.clear();
    int numresults = mDataResultList.NumDataResults();
    for(int i = 0; i < numresults; i++){
        DataResult* datares = mDataResultList.GetDataResult(i);
        DataNode node;
        LeaderboardRow row;
        if(datares->GetDataResultValue("name", node)){
            row.mName = node.Str();
        }
        if(datares->GetDataResultValue("unnamed_band", node)){
            row.mUnnamedBand = node.Int();
        }
        if(datares->GetDataResultValue("rank", node)){
            row.mRank = node.Int();
        }
        if(datares->GetDataResultValue("orank", node)){
            row.mORank = node.Int();
        }
        if(datares->GetDataResultValue("is_percentile", node)){
            row.mIsPercentile = node.Int();
        }
        if(datares->GetDataResultValue("is_friend", node)){
            row.mIsFriend = node.Int();
        }
        if(datares->GetDataResultValue("pid", node)){
            row.mIsEntity = node.Int() == mEntityID.GetPlayerID();
        }
        if(datares->GetDataResultValue("diff_id", node)){
            row.mDiffID = (Difficulty)(node.Int() - 1);
        }
        if(datares->GetDataResultValue("notes_pct", node)){
            row.mNotesPct = node.Int();
        }
        if(datares->GetDataResultValue("score", node)){
            row.mScore = node.Int();
        }
        if(datares->GetDataResultValue("inst_mask", node)){
            row.mInstMask = node.Int();
        }
        mLeaderboardRows.push_back(row);
    }

    mDataResultList.Clear();
    mShortcutProvider->UpdateIndices();
    bool b1 = false;
    bool b2 = false;
    bool b3 = false;
    if(NumData() == 0){
        b1 = true;
        b3 = true;
        b2 = true;
    }
    if(mCallback) mCallback->ResultSuccess(b1, b2, b3);
}

void Leaderboard::Poll(){
    switch(mEnumState){
        case kEnumInactive:
        case kEnumWaiting:
        case kEnumState2:
            break;
        case kEnumFailure:
            CancelEnumerate();
            if(mCallback) mCallback->ResultFailure();
            break;
        case kEnumSuccess:
            OnEnumComplete();
            break;
        case kEnumDone:
            break;
        default:
            MILO_ASSERT(0, 0x1AB);
            break;
    }
}

DataNode Leaderboard::OnMsg(const RockCentralOpCompleteMsg& msg){
    switch(mEnumState){
        case kEnumWaiting:
            if(msg->Int(2)){
                mDataResultList.Update(0);
                if(mDataResultList.NumDataResults() != 0){
                    DataResult* res = mDataResultList.GetDataResult(0);
                    DataNode node;
                    if(res->GetDataResultValue("max_rank", node)){
                        unk40 = node.Int();
                    }
                }
                mHasStats = true;
                mDataResultList.Clear();
                mEnumState = kEnumState2;
                EnumerateFromID();
            }
            else {
                mEnumState = kEnumFailure;
            }
            break;
        case kEnumState2:
            if(msg->Int(2)){
                mEnumState = kEnumSuccess;
            }
            else {
                mEnumState = kEnumFailure;
            }
            break;
        default:
            MILO_ASSERT(0, 0x1DC);
            break;
    }
    return 1;
}

Symbol Leaderboard::GetModeSymbol(){
    switch(mMode){
        case kPercentile:
            return lb_global;
        case kFriends:
            return lb_friends;
        default:
            MILO_ASSERT(false, 0x1EF);
            return gNullStr;
    }
}

void Leaderboard::CycleMode(){
    switch(mMode){
        case kPercentile:
            SetMode(kFriends, true);
            break;
        case kFriends:
            SetMode(kPercentile, true);
            break;
        default:
            MILO_ASSERT(false, 0x201);
            break;
    }
}

void Leaderboard::SetMode(Mode mode, bool restart){
    if(mode != mMode){
        mMode = mode;
        if(restart){
            CancelEnumerate();
            StartEnumerate();
        }
    }
}

DECOMP_FORCEACTIVE(Leaderboard, "Bad Leaderboard::Mode in ModeToLeaderboardMode!")

void Leaderboard::GetPlayerIds(std::vector<int>& ids){
    ids.clear();
    if(!mEntityID.IsInvalid()){
        int id = mEntityID.GetPlayerID();
        ids.push_back(id);
    }
}

BEGIN_HANDLERS(Leaderboard)
    HANDLE_EXPR(num_data, NumData())
    HANDLE_EXPR(get_shortcut_provider, mShortcutProvider)
    HANDLE_EXPR(select_row, OnSelectRow(_msg->Int(2), _msg->Obj<BandUser>(3)))
    HANDLE_EXPR(can_rows_be_selected, CanRowsBeSelected())
    HANDLE_MESSAGE(RockCentralOpCompleteMsg)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x239)
END_HANDLERS

LeaderboardShortcutProvider::LeaderboardShortcutProvider(const Leaderboard* lb) : mLeaderboard(lb) {

}

void LeaderboardShortcutProvider::Text(int, int data, UIListLabel* slot, UILabel* label) const {
    mLeaderboard->Text(-1, mIndices[data], slot, label);
}

void LeaderboardShortcutProvider::UpdateIndices(){
    mIndices.push_back(0);
    for(int i = 1; i < mLeaderboard->NumData(); i++){
        if(mLeaderboard->IsRowFriend(i) || mLeaderboard->IsRowSelf(i)){
            mIndices.push_back(i);
        }
    }
}

int LeaderboardShortcutProvider::LeaderboardIxToIx(int idx){
    MILO_ASSERT(mIndices.size(), 0x25D);
    int i;
    for(i = 0; i < mIndices.size(); i++){
        if(mIndices[i] > idx) break;
    }
    return i;
}

BEGIN_HANDLERS(LeaderboardShortcutProvider)
    HANDLE_EXPR(num_data, NumData())
    HANDLE_EXPR(leaderboard_ix_to_ix, LeaderboardIxToIx(_msg->Int(2)))
    HANDLE_EXPR(ix_to_leaderboard_ix, IxToLeaderboardIx(_msg->Int(2)))
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x271)
END_HANDLERS

int LeaderboardShortcutProvider::NumData() const { return mIndices.size(); }