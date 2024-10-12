#include "TourProgress.h"
#include "QuestJournal.h"
#include "meta/FixedSizeSaveable.h"
#include "meta_band/MetaPerformer.h"
#include "obj/Object.h"
#include "os/DateTime.h"
#include "os/Debug.h"
#include "tour/TourPropertyCollection.h"
#include "utl/BinStream.h"
#include "utl/Symbol.h"
#include "utl/Symbols.h"
#include "utl/Symbols2.h"

TourProgress::TourProgress() : mQuests(*this), mLastTouchTime(0), mOnTour(0), m_symTourDesc(""), mNumCompletedGigs(0), mCurrentQuest(gNullStr), mMetaScore(0), mNewStars(0), mWonQuest(0), mCurrentGigNum(0) {
    mSaveSizeMethod = &SaveSize;
    ClearQuestFilters();
    unk70.clear();
    unk88.clear();
    unka0.clear();
}

TourProgress::~TourProgress(){

}

void TourProgress::SyncSave(BinStream& bs){
    bs << m_symTourDesc;
    bs << mCurrentQuest;
    bs << mOnTour;
    for(int i = 0; i < 3; i++) bs << mQuestFilters[i];
    bs << mNumCompletedGigs;
    bs << mCurrentGigNum;
    bs << mNewStars;
    bs << unk70;
    bs << mMetaScore;
    bs << unk88;
    bs << unka0;
}

void TourProgress::SyncLoad(BinStream& bs){
    bs >> m_symTourDesc;
    bs >> mCurrentQuest;
    bs >> mOnTour;
    for(int i = 0; i < 3; i++) bs >> mQuestFilters[i];
    bs >> mNumCompletedGigs;
    bs >> mCurrentGigNum;
    bs >> mNewStars;
    bs >> unk70;
    bs >> mMetaScore;
    unk88.clear();
    unka0.clear();
    bs >> unk88;
    bs >> unka0;
}

void TourProgress::HandleTourRewardApplied(){
    HandleDirty(3);
}

void TourProgress::HandleDirty(int i){
    UpdateLastTouchTime();
    SetDirty(true, i);
    MetaPerformer* p = MetaPerformer::Current();
    if(p) p->SetSyncDirty(-1, true);
}

void TourProgress::UpdateLastTouchTime(){
    DateTime dt;
    GetDateAndTime(dt);
    mLastTouchTime = dt.ToCode();
}

String TourProgress::GetLastTouchedDateString() const {
    String ret;
    DateTime dt;
    dt = DateTime(mLastTouchTime);
    dt.ToString(ret);
    return ret;
}

void TourProgress::SaveFixed(FixedSizeSaveableStream& stream) const {
    stream << mLastTouchTime;
    stream << mQuests;
    stream << mTourProperties;
    stream << mOnTour;
    FixedSizeSaveable::SaveSymbolID(stream, m_symTourDesc);
    stream << mNumCompletedGigs;
    FixedSizeSaveable::SaveSymbolID(stream, mCurrentQuest);
    for(int i = 0; i < 3; i++) FixedSizeSaveable::SaveFixedSymbol(stream, mQuestFilters[i]);
    FixedSizeSaveable::SaveStd(stream, unk70, 10, 4);
}

int TourProgress::SaveSize(int i){
    int size = QuestJournal::SaveSize(i) + 4;
    size += TourPropertyCollection::SaveSize(i);
    if(FixedSizeSaveable::sPrintoutsEnabled){
        MILO_LOG("* %s = %i\n", "TourProgress", size + 0xCF);
    }
    return size + 0xCF;
}

void TourProgress::LoadFixed(FixedSizeSaveableStream& stream, int rev){
    stream >> mLastTouchTime;
    stream >> mQuests;
    stream >> mTourProperties;
    stream >> mOnTour;
    FixedSizeSaveable::LoadSymbolFromID(stream, m_symTourDesc);
    stream >> mNumCompletedGigs;
    FixedSizeSaveable::LoadSymbolFromID(stream, mCurrentQuest);
    for(int i = 0; i < 3; i++) FixedSizeSaveable::LoadFixedSymbol(stream, mQuestFilters[i]);
    FixedSizeSaveable::LoadStd(stream, unk70, 10, 4);
}

const TourPropertyCollection& TourProgress::GetTourProperties() const { return mTourProperties; }
TourPropertyCollection& TourProgress::GetTourProperties() { return mTourProperties; }
const TourPropertyCollection& TourProgress::GetPerformanceProperties() const { return mPerformanceProperties; }
TourPropertyCollection& TourProgress::GetPerformanceProperties(){ return mPerformanceProperties; }

void TourProgress::ClearPerformanceState(){ ClearPeformanceProperties(); }
void TourProgress::ClearPeformanceProperties(){ mPerformanceProperties.Clear(); }

void TourProgress::HandleQuestFinished(){
    SetCurrentQuest(gNullStr);
    ClearQuestFilters();
}

void TourProgress::SetOnTour(bool b){
    mOnTour = b;
    HandleDirty(3);
}

bool TourProgress::IsOnTour() const { return mOnTour; }
Symbol TourProgress::GetTourDesc() const { return m_symTourDesc; }

void TourProgress::SetTourDesc(Symbol s){
    m_symTourDesc = s;
    HandleDirty(3);
}

int TourProgress::GetNumTotalGigs() const {
    MILO_ASSERT(m_symTourDesc != "", 0x1AE);
}

void TourProgress::FinalizeNewStars(){
    unk70.push_back(mNewStars);
    ClearNewStars();
    HandleDirty(2);
}

void TourProgress::ClearNewStars(){
    mNewStars = 0;
    HandleDirty(2);
}

BEGIN_HANDLERS(TourProgress)
    HANDLE_ACTION(set_on_tour, SetOnTour(_msg->Int(2)))
END_HANDLERS