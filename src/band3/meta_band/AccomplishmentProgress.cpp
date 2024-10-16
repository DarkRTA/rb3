#include "meta_band/AccomplishmentProgress.h"
#include "Accomplishment.h"
#include "Campaign.h"
#include "game/BandUser.h"
#include "meta/FixedSizeSaveable.h"
#include "meta_band/AccomplishmentCategory.h"
#include "meta_band/AccomplishmentGroup.h"
#include "meta_band/AccomplishmentManager.h"
#include "meta_band/MetaPerformer.h"
#include "os/Debug.h"
#include "stl/_pair.h"
#include "utl/Symbol.h"
#include "utl/Symbols.h"

GamerAwardStatus::GamerAwardStatus() : unk8(-1), unkc(0), unk10(0) {
    mSaveSizeMethod = &SaveSize;
}

GamerAwardStatus::~GamerAwardStatus(){

}

void GamerAwardStatus::SaveFixed(FixedSizeSaveableStream& stream) const {
    stream << unk8;
    stream << unkc;
}

int GamerAwardStatus::SaveSize(int){
    if(FixedSizeSaveable::sPrintoutsEnabled){
        MILO_LOG("* %s = %i\n", "GamerpicAward", 8);
    }
    return 8;
}

void GamerAwardStatus::LoadFixed(FixedSizeSaveableStream& stream, int rev){
    stream >> unk8;
    int iii = 0;
    stream >> iii;
    unkc = iii;
}

AccomplishmentProgress::AccomplishmentProgress(BandProfile* profile) : mParentProfile(profile), unk84(0), unk644(1), unk648(0) {
    Clear();
    mSaveSizeMethod = &SaveSize;
}

AccomplishmentProgress::~AccomplishmentProgress(){

}

bool AccomplishmentProgress::AddAccomplishment(Symbol s){
    if(!IsAccomplished(s)){
        Accomplishment* pAccomplishment = TheAccomplishmentMgr->GetAccomplishment(s);
        MILO_ASSERT(pAccomplishment, 0xC1);
        NotifyPlayerOfAccomplishment(s, pAccomplishment->GetIconArt());
        LocalBandUser* pUser = mParentProfile->GetAssociatedLocalBandUser();
        MILO_ASSERT(pUser, 199);
        MetaPerformer* pPerformer = MetaPerformer::Current();
        MILO_ASSERT(pPerformer, 0xCB);
        TheAccomplishmentMgr->AddGoalAcquisitionInfo(s, pUser->UserName(), pPerformer->Song());
        if(pAccomplishment->HasAward()){
            AddAward(pAccomplishment->GetAward(), s);
        }
        int lbhcstatus = TheAccomplishmentMgr->GetLeaderboardHardcoreStatus(unk4c.size());
        TheAccomplishmentMgr->GetIconHardCoreStatus(unk4c.size());
        unk4c.insert(s);
        unk64.insert(s);

        Symbol cat = pAccomplishment->GetCategory();
        AccomplishmentCategory* pCategory = TheAccomplishmentMgr->GetAccomplishmentCategory(cat);
        MILO_ASSERT(pCategory, 0xEC);
        if(TheAccomplishmentMgr->IsCategoryComplete(mParentProfile, cat)){
            NotifyPlayerOfCategoryComplete(cat);
            if(pCategory->HasAward()){
                AddAward(pCategory->GetAward(), cat);
            }
        }

        Symbol group = pCategory->GetGroup();
        AccomplishmentGroup* pGroup = TheAccomplishmentMgr->GetAccomplishmentGroup(group);
        MILO_ASSERT(pGroup, 0xFB);
        if(TheAccomplishmentMgr->IsGroupComplete(mParentProfile, group)){
            NotifyPlayerOfGroupComplete(group);
            if(pGroup->HasAward()){
                AddAward(pGroup->GetAward(), group);
            }
        }

        Symbol level4 = TheCampaign->GetCampaignLevelForMetaScore(unk84);
        int metascoreval = TheAccomplishmentMgr->GetMetaScoreValue(pAccomplishment->GetMetaScoreValue());
        SetMetaScore(unk84 + metascoreval);
        Symbol level5 = TheCampaign->GetCampaignLevelForMetaScore(unk84);
        if(level5 != level4){
            // MILO ASSERT pLevel
        }
        return true;
    }
    else return false;
}

bool AccomplishmentProgress::IsAccomplished(Symbol s) const {
    return unk4c.find(s) != unk4c.end();
}

bool AccomplishmentProgress::HasNewAwards() const {
    return !unka0.empty();
}

Symbol AccomplishmentProgress::GetFirstNewAward() const {
    MILO_ASSERT(HasNewAwards(), 0x158);
    return unka0.front().first;
}

Symbol AccomplishmentProgress::GetFirstNewAwardReason() const {
    MILO_ASSERT(HasNewAwards(), 0x161);
    return unka0.front().second;
}

void AccomplishmentProgress::ClearFirstNewAward(){
    MILO_ASSERT(HasNewAwards(), 0x16A);
    unka0.pop_front();
    mParentProfile->MakeDirty();
}

void AccomplishmentProgress::AddNewRewardVignette(Symbol s){
    std::list<Symbol>::iterator it;
    for(it = unka8.begin(); it != unka8.end() && *it != s; ++it);
    if(it == unka8.end()){
        unka8.push_back(s);
    }
    unkb0.insert(s);
    mParentProfile->MakeDirty();
}

bool AccomplishmentProgress::IsUploadDirty() const {
    return unk644 || !unk64.empty();
}

bool AccomplishmentProgress::HasNewRewardVignettes() const {
    return !unka8.empty();
}

Symbol AccomplishmentProgress::GetFirstNewRewardVignette() const {
    MILO_ASSERT(HasNewRewardVignettes(), 0x18C);
    return unka8.front();
}

void AccomplishmentProgress::ClearFirstNewRewardVignette(){
    MILO_ASSERT(HasNewRewardVignettes(), 0x194);
    unka8.pop_front();
    mParentProfile->MakeDirty();
}

bool AccomplishmentProgress::HasNewRewardVignetteFestival() const {
    return !unk645;
}

void AccomplishmentProgress::ClearNewRewardVignetteFestival(){
    unk645 = true;
    unkb0.insert(campaign_rewardvignette_festival_replay_screen);
}

bool AccomplishmentProgress::AddAward(Symbol s1, Symbol s2){
    if(!HasAward(s1)){
        unk88.insert(s1);
        unka0.push_back(std::make_pair(s1, s2));
        Award* pAward = TheAccomplishmentMgr->GetAward(s1);
        MILO_ASSERT(pAward, 0x1BD);
        pAward->GrantAwards(mParentProfile);
        mParentProfile->MakeDirty();
        return true;
    }
    else return false;
}

bool AccomplishmentProgress::HasAward(Symbol s) const {
    return unk88.find(s) != unk88.end();
}

void AccomplishmentProgress::Poll(){}

void AccomplishmentProgress::SaveFixed(FixedSizeSaveableStream& stream) const {
    stream << unk644;
    FixedSizeSaveable::SaveStd(stream, unk4c, 1000);
    FixedSizeSaveable::SaveStd(stream, unk64, 1000);
    FixedSizeSaveable::SaveStd(stream, unk88, 500);
    FixedSizeSaveable::SaveStd(stream, unka8, 20);
    FixedSizeSaveable::SaveStd(stream, unkb0, 20);
    stream << unk40;
    stream << unk84;
    stream << unkc8;
    stream << unkd0;
    stream << unkcc;
    stream << unkd4;
    stream << unkd8;
    stream << unkdc;
    stream << unke0;
    stream << unke4;
    stream << unke8;
    stream << unkec;
    stream << unk3dc;
    for(int i = 0; i < 11; i++){
        stream << unk3e0[i];
        stream << unk3b0[i];
        stream << unk40c[i];
        stream << unk438[i];
        stream << unk464[i];
        stream << unk490[i];
        stream << unk4bc[i];
        stream << unk4e8[i];
        stream << unk514[i];
        stream << unk540[i];
        for(int j = 0; j < 4; j++){
            stream << unkf0[i][j];
            stream << unk1a0[i][j];
            stream << unk250[i][j];
            stream << unk300[i][j];
        }
    }
    for(int i = 0; i < 4; i++){
        stream << unk56c[i];
        stream << unk57c[i];
        stream << unk58c[i];
        stream << unk59c[i];
        stream << unk5ac[i];
        stream << unk5bc[i];
        stream << unk5cc[i];
    }
    stream << unk5dc;
    stream << unk5e0;
    stream << unk645;
    FixedSizeSaveable::SaveStd(stream, unk5e4, 10, 8);
    FixedSizeSaveable::SaveStd(stream, unk5fc, 10, 8);
    FixedSizeSaveable::SaveStd(stream, unk614, 10, 8);
    FixedSizeSaveable::SaveStd(stream, unk62c, 0x32, 8);
    FixedSizeSaveable::SaveStdPtr(stream, unk44, 0x32, GamerAwardStatus::SaveSize(0x97));
}