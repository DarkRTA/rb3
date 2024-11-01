#include "meta_band/Leaderboard.h"
#include "Leaderboard.h"
#include "bandobj/ScoreDisplay.h"
#include "game/Defines.h"
#include "meta_band/AppLabel.h"
#include "net_band/DataResults.h"
#include "os/Debug.h"
#include "net_band/RockCentral.h"
#include "rndobj/Draw.h"
#include "ui/UIColor.h"
#include "ui/UILabel.h"
#include "ui/UIListCustom.h"
#include "ui/UIListLabel.h"
#include "ui/UIListMesh.h"
#include "utl/Symbol.h"
#include "utl/Symbols2.h"
#include "utl/Symbols4.h"

Leaderboard::Leaderboard(EntityID id, Callback* cb) : unk40(0), mHasStats(0), unk48(1), mEntityID(id), mCallback(cb), mEnumState(kEnumInactive), mSelfColor(0), mFriendColor(0), unk80(-1) {
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
    if(unk48 == 0){
        mEnumState = kEnumWaiting;
        GetStats();
    }
    else {
        mEnumState = kEnumFailure;
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
            if(row.unk18){
                if(row.unk19){
                    AppLabel* appLabel = dynamic_cast<AppLabel*>(label);
                    MILO_ASSERT(appLabel, 0x80);
                    appLabel->SetLeaderboardName(row);
                }
                else label->SetTokenFmt(percentile_fmt, 100 - row.unk10);
            }
            else {
                AppLabel* appLabel = dynamic_cast<AppLabel*>(label);
                MILO_ASSERT(appLabel, 0x8E);
                appLabel->SetLeaderboardRankAndName(row);
            }
            return;
        }
        else if(slot->Matches("difficulty") && ShowsDifficultyAndPct()){
            label->SetTextToken(DifficultyToShortSym((Difficulty)row.unk1c));
            return;
        }
        else if(slot->Matches("percentage") && ShowsDifficultyAndPct()){
            label->SetTokenFmt(eg_percent_format, row.unk20);
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
            scr->SetValues(row.unk28, row.unk24, 0, false);
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
    mEnumState = (EnumState)5;
    ShowData();
}

bool Leaderboard::EnumerateHigherRankRange(){
    if(mEnumState != 5 && mEnumState != kEnumInactive) return false;
    else if(unk48) return false;
    else {
        MILO_ASSERT(mHasStats, 0xF0);
        MILO_ASSERT(!mLeaderboardRows.empty(), 0xF1);
        const LeaderboardRow& row = mLeaderboardRows.back();
        if(row.unk14 < unk40){
            mEnumState = (EnumState)2;
            unk80 = row.unk14 + 1;
            mLeaderboardRows.clear();
            EnumerateRankRange(row.unk14 + 1, 20);
            return true;
        }
        else return false;
    }
}

bool Leaderboard::EnumerateLowerRankRange(){
    if(mEnumState != 5 && mEnumState != kEnumInactive) return false;
    else if(unk48) return false;
    else {
        MILO_ASSERT(mHasStats, 0x10A);
        MILO_ASSERT(!mLeaderboardRows.empty(), 0x10B);
        const LeaderboardRow& row = mLeaderboardRows.front();
        if(row.unk14 > 1){
            mEnumState = (EnumState)2;
            unk80 = row.unk14 - 1;
            mLeaderboardRows.clear();
            int num = row.unk14 - 20 >= 1 ? row.unk14 - 20 : 1;
            EnumerateRankRange(num, 20);
            return true;
        }
        else return false;
    }
}

int Leaderboard::GetStartingRow() const {
    for(int i = 0; i < mLeaderboardRows.size(); i++){
        if((unk80 < 0 && IsRowSelf(i)) || (unk80 == mLeaderboardRows[i].unk14)){
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
            row.unk0 = node.Str();
        }
        if(datares->GetDataResultValue("unnamed_band", node)){
            row.unkc = node.Int();
        }
        if(datares->GetDataResultValue("rank", node)){
            row.unk10 = node.Int();
        }
        if(datares->GetDataResultValue("orank", node)){
            row.unk14 = node.Int();
        }
        if(datares->GetDataResultValue("is_percentile", node)){
            row.unk18 = node.Int();
        }
        if(datares->GetDataResultValue("is_friend", node)){
            row.unk19 = node.Int();
        }
        if(datares->GetDataResultValue("pid", node)){
            row.unk1a = node.Int() == mEntityID.GetPlayerID();
        }
        if(datares->GetDataResultValue("diff_id", node)){
            row.unk1c = node.Int() - 1;
        }
        if(datares->GetDataResultValue("notes_pct", node)){
            row.unk20 = node.Int();
        }
        if(datares->GetDataResultValue("score", node)){
            row.unk24 = node.Int();
        }
        if(datares->GetDataResultValue("inst_mask", node)){
            row.unk28 = node.Int();
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
    
//   iVar15 = 0;
//   if (iVar6 > 0) {
//   }
//   DataResultList::Clear((DataResultList *)(this + 0x20));
//   LeaderboardShortcutProvider::UpdateIndices(*(LeaderboardShortcutProvider **)(this + 0x70));
//   iVar6 = (**(code **)(*(int *)this + 0x30))(this);
//   bVar1 = iVar6 == 0;
//   piVar12 = *(int **)(this + 0x6c);
//   if (piVar12 != (int *)0x0) {
//     (**(code **)(*piVar12 + 0x10))(piVar12,bVar1,bVar1,bVar1);
//   }
//   return;
}