#include "meta_band/AccomplishmentPanel.h"
#include "Accomplishment.h"
#include "BandProfile.h"
#include "Campaign.h"
#include "game/BandUser.h"
#include "meta_band/Accomplishment.h"
#include "meta_band/AccomplishmentCategory.h"
#include "meta_band/AccomplishmentGroup.h"
#include "meta_band/AccomplishmentManager.h"
#include "meta_band/AccomplishmentOneShot.h"
#include "meta_band/AccomplishmentProgress.h"
#include "meta_band/AccomplishmentSetlist.h"
#include "meta_band/AccomplishmentTourConditional.h"
#include "meta_band/BandProfile.h"
#include "meta_band/MetaPerformer.h"
#include "meta_band/ProfileMgr.h"
#include "meta_band/TexLoadPanel.h"
#include "obj/Data.h"
#include "os/Debug.h"
#include "stl/_algo.h"
#include "ui/UIGridProvider.h"
#include "ui/UIList.h"
#include "ui/UIPanel.h"
#include "utl/Messages.h"
#include "utl/Messages2.h"
#include "utl/Symbol.h"
#include "utl/Symbols2.h"
#include <vector>

AccomplishmentGroupCmp::AccomplishmentGroupCmp(const AccomplishmentManager* mgr) : mAccomplishmentMgr(mgr) {

}

bool AccomplishmentGroupCmp::operator()(Symbol s1, Symbol s2) const {
    AccomplishmentGroup* pLHSAccomplishmentGroup = mAccomplishmentMgr->GetAccomplishmentGroup(s1);
    MILO_ASSERT(pLHSAccomplishmentGroup, 0x37);
    AccomplishmentGroup* pRHSAccomplishmentGroup = mAccomplishmentMgr->GetAccomplishmentGroup(s2);
    MILO_ASSERT(pRHSAccomplishmentGroup, 0x3A);
    return pLHSAccomplishmentGroup->GetIndex() < pRHSAccomplishmentGroup->GetIndex();
}

AccomplishmentCategoryCmp::AccomplishmentCategoryCmp(const AccomplishmentManager* mgr) : mAccomplishmentMgr(mgr) {

}

bool AccomplishmentCategoryCmp::operator()(Symbol s1, Symbol s2) const {
    AccomplishmentCategory* pLHSAccomplishmentCategory = mAccomplishmentMgr->GetAccomplishmentCategory(s1);
    MILO_ASSERT(pLHSAccomplishmentCategory, 0x4B);
    AccomplishmentCategory* pRHSAccomplishmentCategory = mAccomplishmentMgr->GetAccomplishmentCategory(s2);
    MILO_ASSERT(pRHSAccomplishmentCategory, 0x4E);
    return pLHSAccomplishmentCategory->GetIndex() < pRHSAccomplishmentCategory->GetIndex();
}

AccomplishmentCmp::AccomplishmentCmp(const AccomplishmentManager* mgr) : mAccomplishmentMgr(mgr) {

}

bool AccomplishmentCmp::operator()(Symbol s1, Symbol s2) const {
    Accomplishment* pLHSAccomplishment = mAccomplishmentMgr->GetAccomplishment(s1);
    MILO_ASSERT(pLHSAccomplishment, 0x5F);
    Accomplishment* pRHSAccomplishment = mAccomplishmentMgr->GetAccomplishment(s2);
    MILO_ASSERT(pRHSAccomplishment, 0x62);
    return pLHSAccomplishment->mIndex < pRHSAccomplishment->mIndex;
}

bool IsAccomplishmentSecret(Accomplishment* i_pAccomplishment, const BandProfile* profile){
    MILO_ASSERT(i_pAccomplishment, 0x6A);
    if(IsAccomplished(i_pAccomplishment->GetName(), profile)) return false;
    else {
        bool b1 = true;
        const std::vector<Symbol>& prereqs = i_pAccomplishment->GetSecretPrereqs();
        for(std::vector<Symbol>::const_iterator it = prereqs.begin(); it != prereqs.end(); ++it){
            if(!IsAccomplished(*it, profile)){
                b1 = false;
                break;
            }
        }
        bool b2 = true;
        Symbol sekrit = i_pAccomplishment->GetSecretCampaignLevelPrereq();
        if(sekrit != gNullStr){
            LocalBandUser* pUser = TheCampaign->GetUser();
            MILO_ASSERT(pUser, 0x88);
            if(!TheCampaign->HasReachedCampaignLevel(pUser, sekrit)) b2 = false;
        }
        if(b1 && b2) return false;
        else return true;
    }
}

bool IsAccomplished(Symbol s, const BandProfile* profile){
    if(profile){
        AccomplishmentProgress* prog = profile->GetAccomplishmentProgress();
        return prog->IsAccomplished(s);
    }
    else return false;
}

AccomplishmentPanel::AccomplishmentPanel() : unk4c(0), mGoal(gNullStr), mGroup(gNullStr), mCategory(gNullStr), mAccomplishmentEntryProvider(0),
    mAccomplishmentProvider(0), mAccomplishmentCategoryProvider(0), mAccomplishmentGroupProvider(0), unk70(0) {

}

Symbol AccomplishmentPanel::SelectedAccomplishment() const {
    if(mState == kUp){
        UIList* pAccomplishmentList = mDir->Find<UIList>("accomplishments.lst", true);
        if(!pAccomplishmentList->ChildList()) return gNullStr;
        else {
            MILO_ASSERT(pAccomplishmentList, 0x372);
            return mAccomplishmentGridProvider->GetSymbolFromList(pAccomplishmentList);
        }
    }
    else return gNullStr;
}

Symbol AccomplishmentPanel::SelectedAccomplishmentCategory() const {
    MILO_ASSERT(GetState() == kUp, 0x37C);
    UIList* pAccomplishmentCategoriesList = mDir->Find<UIList>("categories.lst", true);
    MILO_ASSERT(pAccomplishmentCategoriesList, 0x37E);
    return pAccomplishmentCategoriesList->SelectedSym(true);
}

Symbol AccomplishmentPanel::SelectedAccomplishmentGroup() const {
    MILO_ASSERT(GetState() == kUp, 0x386);
    UIList* pAccomplishmentGroupsList = mDir->Find<UIList>("groups.lst", true);
    MILO_ASSERT(pAccomplishmentGroupsList, 0x388);
    return pAccomplishmentGroupsList->SelectedSym(true);
}

void AccomplishmentPanel::Load(){
    TexLoadPanel::Load();
    LoadCampaignIcons();
}

void AccomplishmentPanel::Exit(){ UIPanel::Exit(); }

void AccomplishmentPanel::Enter(){
    UIPanel::Enter();
    TheCampaign->SetupLaunchedAccomplishmentInfo("");
    BandProfile* pProfile = TheCampaign->GetProfile();
    MILO_ASSERT(pProfile, 0x3A5);
    MILO_ASSERT(!mAccomplishmentGroupProvider, 0x3A7);
    mAccomplishmentGroupProvider = new AccomplishmentGroupProvider();
    MILO_ASSERT(!mAccomplishmentCategoryProvider, 0x3AA);
    mAccomplishmentCategoryProvider = new AccomplishmentCategoryProvider();
    MILO_ASSERT(!mAccomplishmentProvider, 0x3AD);
    mAccomplishmentProvider = new AccomplishmentProvider();
    mAccomplishmentGridProvider = new UIGridProvider(mAccomplishmentProvider, 4);
    MILO_ASSERT(!mAccomplishmentEntryProvider, 0x3B1);
    mAccomplishmentEntryProvider = new AccomplishmentEntryProvider();
    if(unk4c == 0){
        mGoal = gNullStr;
        mCategory = gNullStr;
        mGroup = gNullStr;
        SetCareerState((CareerState)1, false);
    }
    else {
        SetCareerState((CareerState)unk4c, false);
    }
    Refresh();
}

void AccomplishmentPanel::LoadCampaignIcons(){
    std::vector<Symbol> vec;
    const std::map<Symbol, Accomplishment*>& accs = TheAccomplishmentMgr->GetAccomplishments();
    for(std::map<Symbol, Accomplishment*>::const_iterator it = accs.begin(); it != accs.end(); ++it){
        Symbol key = it->first;
        vec.push_back(key);
    }
    std::stable_sort(vec.begin(), vec.end(), GoalAlpaCmp());
    for(std::vector<Symbol>::iterator it = vec.begin(); it != vec.end(); ++it){
        Accomplishment* pAccomplishment = TheAccomplishmentMgr->GetAccomplishment(*it);
        MILO_ASSERT(pAccomplishment, 0x3E0);
        Symbol name = pAccomplishment->GetName();
        const char* art = pAccomplishment->GetIconArt();
        if(strlen(art) != 0) AddTex(art, name.Str(), true, false);
    }
    const char* sekrit = MakeString(Accomplishment::GetIconPath(), "acc_secret");
    AddTex(sekrit, "acc_secret", true, false);
}

void AccomplishmentPanel::Unload(){
    unk70 = 0;
    TexLoadPanel::Unload();
    RELEASE(mAccomplishmentProvider);
    RELEASE(mAccomplishmentGridProvider);
    RELEASE(mAccomplishmentEntryProvider);
    RELEASE(mAccomplishmentGroupProvider);
    RELEASE(mAccomplishmentCategoryProvider);
}

void AccomplishmentPanel::UpdateForGroupSelection(){
    mGroup = SelectedAccomplishmentGroup();
    RefreshCategoryList();
}

void AccomplishmentPanel::UpdateForCategorySelection(){
    mCategory = SelectedAccomplishmentCategory();
    RefreshGoalList();
}

void AccomplishmentPanel::UpdateForGoalSelection(){
    mGoal = SelectedAccomplishment();
    UpdateDetailsListState();
}

void AccomplishmentPanel::HandleSoundSelect(LocalUser* user){
    static Message cMsg("handle_sound_select", 0);
    cMsg[0] = user;
    Handle(cMsg, true);
}

void AccomplishmentPanel::HandleSoundBack(LocalUser* user){
    static Message cMsg("handle_sound_back", 0);
    cMsg[0] = user;
    Handle(cMsg, true);
}

void AccomplishmentPanel::HandleSoundToggle(LocalUser* user){
    static Message cMsg("handle_sound_toggle", 0);
    cMsg[0] = user;
    Handle(cMsg, true);
}

DataNode AccomplishmentPanel::OnMsg(const UIComponentScrollMsg& msg){
    if(GetState() == kUp){
        if(strcmp(msg.GetUIComponent()->mName, "details.lst") == 0){
            // lol
        }
        else if(strcmp(msg.GetUIComponent()->mName, "categories.lst") == 0){
            UpdateForCategorySelection();
        }
        else if(strcmp(msg.GetUIComponent()->mName, "groups.lst") == 0){
            UpdateForGroupSelection();
        }
        else UpdateForGoalSelection();
    }
    return DataNode(kDataUnhandled, 0);
}

DataNode AccomplishmentPanel::Group_HandleButtonDownMsg(const ButtonDownMsg& msg){
    switch(msg.GetAction()){
        case kAction_Confirm:
            SetCareerState((CareerState)2, true);
            HandleSoundSelect(msg.GetUser());
            return 0;
        case kAction_Cancel:
            static Message cMsg("handle_exit_career");
            Handle(cMsg, true);
            HandleSoundBack(msg.GetUser());
            break;
        case kAction_Option:
            Handle(handle_goto_leaderboard_hub_msg, true);
            HandleSoundSelect(msg.GetUser());
            break;
        default:
            break;
    }
    return DataNode(kDataUnhandled, 0);
}

DataNode AccomplishmentPanel::Category_HandleButtonDownMsg(const ButtonDownMsg& msg){
    switch(msg.GetAction()){
        case kAction_Confirm:
            SetCareerState((CareerState)3, true);
            HandleSoundSelect(msg.GetUser());
            return 0;
        case kAction_Cancel:
            SetCareerState((CareerState)1, true);
            HandleSoundBack(msg.GetUser());
            break;
        default:
            break;
    }
    return DataNode(kDataUnhandled, 0);
}

DataNode AccomplishmentPanel::Goal_HandleButtonDownMsg(const ButtonDownMsg& msg){
    switch(msg.GetAction()){
        case kAction_Confirm:
            if(CanLaunchGoal()){
                static Message cMsg("handle_launch_goal", 0);
                cMsg[0] = msg.GetUser();
                Handle(cMsg, true);
                HandleSoundSelect(msg.GetUser());
            }
            return 0;
        case kAction_Cancel:
            SetCareerState((CareerState)2, true);
            HandleSoundSelect(msg.GetUser());
            break;
        case kAction_WiiHomeMenu:
            if(CanNavigateList()){
                SetCareerState((CareerState)4, true);
                HandleSoundSelect(msg.GetUser());
            }
            break;
        case kAction_Option:
            if(HasLeaderboard()){
                Handle(handle_goto_leaderboard_msg, true);
                HandleSoundSelect(msg.GetUser());
            }
            break;
        default:
            break;
    }
    return DataNode(kDataUnhandled, 0);
}

DataNode AccomplishmentPanel::Details_HandleButtonDownMsg(const ButtonDownMsg& msg){
    switch(msg.GetAction()){
        case kAction_Confirm:
            if(CanLaunchSelectedEntry()){
                static Message cMsg("handle_launch_selected_entry", 0);
                cMsg[0] = msg.GetUser();
                Handle(cMsg, true);
                HandleSoundSelect(msg.GetUser());
            }
            return 0;
        case kAction_Cancel:
            SetCareerState((CareerState)3, true);
            HandleSoundBack(msg.GetUser());
            break;
        case kAction_WiiHomeMenu:
            SetCareerState((CareerState)3, true);
            HandleSoundBack(msg.GetUser());
            break;
        case kAction_Option:
            if(HasLeaderboard()){
                Handle(handle_goto_leaderboard_msg, true);
                HandleSoundSelect(msg.GetUser());
            }
            break;
        default:
            break;
    }
    return DataNode(kDataUnhandled, 0);
}

DataNode AccomplishmentPanel::OnMsg(const ButtonDownMsg& msg){
    if(msg.GetAction() == kAction_ViewModify){
        TheProfileMgr.SetPrimaryProfileByUser(msg.GetUser());
        HandleSoundToggle(msg.GetUser());
        return DataNode(kDataUnhandled, 0);
    }
    else switch(unk4c){
        case 1:
            return Group_HandleButtonDownMsg(msg);
        case 2:
            return Category_HandleButtonDownMsg(msg);
        case 3:
            return Goal_HandleButtonDownMsg(msg);
        case 4:
            return Details_HandleButtonDownMsg(msg);
        default:
            MILO_ASSERT(false, 0x502);
            return DataNode(kDataUnhandled, 0);
    }
}

bool AccomplishmentPanel::CanNavigateList() const {
    if(GetState() != kUp) return false;
    if(unk4c - 1 <= 1U) return false;
    Symbol selacc = SelectedAccomplishment();
    Accomplishment* acc = TheAccomplishmentMgr->GetAccomplishment(selacc);
    if(!acc) return false;
    BandProfile* pProfile = TheCampaign->GetProfile();
    MILO_ASSERT(pProfile, 0x520);
    if(IsAccomplishmentSecret(acc, pProfile)) return false;
    if(!TheAccomplishmentMgr->IsAvailableToEarn(selacc)) return false;
    std::vector<Symbol> vec;
    if(!acc->InqIncrementalSymbols(pProfile, vec)) return false;
    return true;
}

bool AccomplishmentPanel::CanLaunchGoal() const {
    if(unk4c - 1 <= 1U) return false;
    Symbol selacc = SelectedAccomplishment();
    Accomplishment* acc = TheAccomplishmentMgr->GetAccomplishment(selacc);
    if(!acc) return false;
    BandProfile* pProfile = TheCampaign->GetProfile();
    MILO_ASSERT(pProfile, 0x547);
    if(IsAccomplishmentSecret(acc, pProfile)) return false;
    if(!TheAccomplishmentMgr->IsAvailableToEarn(selacc)) return false;
    return acc->CanBeLaunched();
}

void AccomplishmentPanel::BuildSetList(){
    Symbol selacc = SelectedAccomplishment();
    Accomplishment* pAccomplishment = TheAccomplishmentMgr->GetAccomplishment(selacc);
    MILO_ASSERT(pAccomplishment, 0x561);
    if(pAccomplishment->GetType() == kAccomplishmentTypeSetlist){
        MetaPerformer* pPerformer = MetaPerformer::Current();
        MILO_ASSERT(pPerformer, 0x567);
        AccomplishmentSetlist* pSetListAccomplishment = dynamic_cast<AccomplishmentSetlist*>(pAccomplishment);
        MILO_ASSERT(pSetListAccomplishment, 0x56A);
        pPerformer->SetSetlist(pSetListAccomplishment->mSetlist);
    }
    else if(pAccomplishment->GetType() == kAccomplishmentTypeOneShot){
        MetaPerformer* pPerformer = MetaPerformer::Current();
        MILO_ASSERT(pPerformer, 0x572);
        AccomplishmentOneShot* pOneShotAccomplishment = dynamic_cast<AccomplishmentOneShot*>(pAccomplishment);
        MILO_ASSERT(pOneShotAccomplishment, 0x575);
        Symbol symSong = pOneShotAccomplishment->mOneShotSong;
        MILO_ASSERT(symSong != gNullStr, 0x578);
        pPerformer->SetSong(symSong);
    }
    else FillSetlistWithAccomplishmentSongs(selacc, 0);
}

void AccomplishmentPanel::FillSetlistWithAccomplishmentSongs(Symbol s, int i){
    MetaPerformer* pPerformer = MetaPerformer::Current();
    MILO_ASSERT(pPerformer, 0x586);
    Accomplishment* pAccomplishment = TheAccomplishmentMgr->GetAccomplishment(s);
    MILO_ASSERT(pAccomplishment, 0x589);
    BandProfile* pProfile = TheCampaign->GetProfile();
    MILO_ASSERT(pProfile, 0x58C);
    AccomplishmentProgress* prog = pProfile->GetAccomplishmentProgress();
    bool accomplished = prog->IsAccomplished(s);
    std::vector<Symbol> vSongs;
    std::vector<Symbol> v40;
    bool bGotSymbols = pAccomplishment->InqIncrementalSymbols(pProfile, v40);
    MILO_ASSERT(bGotSymbols, 0x593);
    int count = 0;
    for(std::vector<Symbol>::iterator it = v40.begin(); it != v40.end(); ++it){
        Symbol cur = *it;
        if(accomplished || !pAccomplishment->IsSymbolEntryFulfilled(pProfile, cur)){
            vSongs.push_back(cur);
            count++;
            if(i > 0 && i <= count) break;
        }
    }
    MILO_ASSERT(!vSongs.empty(), 0x5AA);
    MILO_ASSERT(std::find( vSongs.begin(), vSongs.end(), gNullStr ) == vSongs.end(), 0x5AB);
    pPerformer->SetSongs(vSongs);
}

void AccomplishmentPanel::CreateAndSubmitMusicLibraryTask(){
    Accomplishment* pAccomplishment = TheAccomplishmentMgr->GetAccomplishment(SelectedAccomplishment());
    MILO_ASSERT(pAccomplishment, 0x5B6);
    // requires MusicLibraryTask
}

#pragma push
#pragma pool_data off
void AccomplishmentPanel::LaunchGoal(LocalBandUser* user){
    MILO_ASSERT(CanLaunchGoal(), 0x5C8);
    Symbol selectedacc = SelectedAccomplishment();
    Accomplishment* pAccomplishment = TheAccomplishmentMgr->GetAccomplishment(selectedacc);
    MILO_ASSERT(pAccomplishment, 0x5CC);
    TheCampaign->SetupLaunchedAccomplishmentInfo(selectedacc);
    BandProfile* pProfile = TheCampaign->GetProfile();
    MILO_ASSERT(pProfile, 0x5E0);

    if(selectedacc == acc_calibrate){
        Handle(handle_launch_calibration_msg, true);
    }
    else if(selectedacc == acc_charactercreate){
        if(pProfile->NumChars() >= 10){
            Handle(handle_cant_launch_charactercreator_msg, true);
        }
        else {
            static Message cMsg("handle_launch_charactercreator", 0);
            cMsg[0] = user;
            Handle(cMsg, true);
        }
    }
    else if(selectedacc == acc_bandcreate || selectedacc == acc_bandlogo || selectedacc == acc_standins ||
        selectedacc == acc_joinalabel || selectedacc == acc_startalabel){
        static Message cMsg("handle_launch_customize", 0);
        cMsg[0] = user;
        Handle(cMsg, true);
    }
    else if(selectedacc == acc_multiplayersession){
        CreateAndSubmitMusicLibraryTask();
        TheCampaign->SetWasLaunchedIntoMusicLibrary(true);
        Handle(handle_goto_musiclibrary_msg, true);
    }
    else if(selectedacc == acc_createsetlist || selectedacc == acc_HMXrecommends){
        Handle(handle_launch_oneway_setlistbrowser_msg, true);
    }
    else if(selectedacc == acc_guitartutorial01){
        Handle(handle_acc_guitartutorial01_msg, true);
    }
    else if(selectedacc == acc_guitartutorial02){
        Handle(handle_acc_guitartutorial02_msg, true);
    }
    else if(selectedacc == acc_guitartutorial03){
        Handle(handle_acc_guitartutorial03_msg, true);
    }
    else if(pAccomplishment->GetType() == kAccomplishmentTypeTourConditional){
        AccomplishmentTourConditional* pTourAccomplishment = dynamic_cast<AccomplishmentTourConditional*>(pAccomplishment);
        MILO_ASSERT(pTourAccomplishment, 0x627);
        static Message cMsg("handle_launch_tour", 0);
        cMsg[0] = pTourAccomplishment->GetAssociatedTour();
        Handle(cMsg, true);
    }
    else if(pAccomplishment->GetType() == kAccomplishmentTypeLessonSongListConditional ||
        pAccomplishment->GetType() == kAccomplishmentTypeLessonDiscSongConditional){
        Symbol entry = TheAccomplishmentMgr->GetFirstUnfinishedAccomplishmentEntry(pProfile, selectedacc);
        static Message cMsg("handle_goto_trainer_songlesson", 0, 0, 0, 0);
        cMsg[0] = entry;
        cMsg[1] = TheCampaign->GetRequiredTrackTypeForGoal(selectedacc);
        cMsg[2] = pAccomplishment->GetRequiredDifficulty();
        cMsg[3] = user;
        Handle(cMsg, true);
    }
    else if(pAccomplishment->GetType() == kAccomplishmentTypeTrainerListConditional ||
        pAccomplishment->GetType() == kAccomplishmentTypeTrainerCategoryConditional){
        Symbol entry = TheAccomplishmentMgr->GetFirstUnfinishedAccomplishmentEntry(pProfile, selectedacc);
        static Message cMsg("handle_goto_trainer_lesson", 0, 0);
        cMsg[0] = entry;
        cMsg[1] = user;
        Handle(cMsg, true);
    }
    else if(pAccomplishment->HasSpecificSongsToLaunch()){
        BuildSetList();
        Handle(handle_goto_difficultyselect_msg, true);
    }
    else {
        CreateAndSubmitMusicLibraryTask();
        TheCampaign->SetWasLaunchedIntoMusicLibrary(true);
        Handle(handle_goto_musiclibrary_msg, true);
    }
}
#pragma pop

Symbol AccomplishmentPanel::GetMusicLibraryBackScreen(){
    MILO_ASSERT(GetState() == kUp, 0x662);
    return Handle(get_musiclibrary_backscreen_msg, true).Sym();
}

Symbol AccomplishmentPanel::GetMusicLibraryNextScreen(){
    MILO_ASSERT(GetState() == kUp, 0x66E);
    return Handle(get_musiclibrary_nextscreen_msg, true).Sym();
}

void AccomplishmentPanel::SelectGoal(Symbol s){
    int i9 = 0;
    if(s != ""){
        i9 = 0;
        std::vector<Symbol>& syms = mAccomplishmentProvider->unk20;
        for(std::vector<Symbol>::iterator it = syms.begin(); it != syms.end(); ++it, i9++){
            if(s == *it){
                i9 = 0;
                break;
            }
        }
        mGoal = mAccomplishmentProvider->DataSymbol(i9);
    }

    UIList* pGoalsList = mDir->Find<UIList>("accomplishments.lst", true);
    MILO_ASSERT(pGoalsList, 0x683);
    mAccomplishmentGridProvider->SetListToData(pGoalsList, i9);
    UpdateForGoalSelection();
}

inline Symbol AccomplishmentProvider::DataSymbol(int i_iData) const {
    MILO_ASSERT(i_iData < NumData(), 0x341);
    return unk20[i_iData];
}