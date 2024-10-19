#include "meta_band/AccomplishmentPanel.h"
#include "Accomplishment.h"
#include "AccomplishmentPanel.h"
#include "BandProfile.h"
#include "Campaign.h"
#include "game/BandUser.h"
#include "game/BandUserMgr.h"
#include "game/Defines.h"
#include "meta_band/Accomplishment.h"
#include "meta_band/AccomplishmentCategory.h"
#include "meta_band/AccomplishmentGroup.h"
#include "meta_band/AccomplishmentManager.h"
#include "meta_band/AccomplishmentOneShot.h"
#include "meta_band/AccomplishmentProgress.h"
#include "meta_band/AccomplishmentSetlist.h"
#include "meta_band/AccomplishmentSongFilterConditional.h"
#include "meta_band/AccomplishmentTourConditional.h"
#include "meta_band/BandProfile.h"
#include "meta_band/MetaPerformer.h"
#include "meta_band/ProfileMgr.h"
#include "meta_band/TexLoadPanel.h"
#include "obj/Data.h"
#include "obj/ObjMacros.h"
#include "os/Debug.h"
#include "os/JoypadMsgs.h"
#include "stl/_algo.h"
#include "ui/UIGridProvider.h"
#include "ui/UIList.h"
#include "ui/UIMessages.h"
#include "ui/UIPanel.h"
#include "utl/Locale.h"
#include "utl/Messages.h"
#include "utl/Messages2.h"
#include "utl/Messages3.h"
#include "utl/Messages4.h"
#include "utl/Symbol.h"
#include "utl/Symbols.h"
#include "utl/Symbols2.h"
#include "utl/Symbols3.h"
#include "utl/Symbols4.h"
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

AccomplishmentPanel::AccomplishmentPanel() : mCareerState(kCareerStateNone), mGoal(gNullStr), mGroup(gNullStr), mCategory(gNullStr), mAccomplishmentEntryProvider(0),
    mAccomplishmentProvider(0), mAccomplishmentCategoryProvider(0), mAccomplishmentGroupProvider(0), mOtherUserToView(0) {

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
    if(mCareerState == kCareerStateNone){
        mGoal = gNullStr;
        mCategory = gNullStr;
        mGroup = gNullStr;
        SetCareerState(kCareerStateGroup, false);
    }
    else {
        SetCareerState(mCareerState, false);
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
    mOtherUserToView = 0;
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
            SetCareerState(kCareerStateCategory, true);
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
            SetCareerState(kCareerStateGoal, true);
            HandleSoundSelect(msg.GetUser());
            return 0;
        case kAction_Cancel:
            SetCareerState(kCareerStateGroup, true);
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
            SetCareerState(kCareerStateCategory, true);
            HandleSoundSelect(msg.GetUser());
            break;
        case kAction_WiiHomeMenu:
            if(CanNavigateList()){
                SetCareerState(kCareerStateDetails, true);
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
            SetCareerState(kCareerStateGoal, true);
            HandleSoundBack(msg.GetUser());
            break;
        case kAction_WiiHomeMenu:
            SetCareerState(kCareerStateGoal, true);
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
    else switch(mCareerState){
        case kCareerStateGroup:
            return Group_HandleButtonDownMsg(msg);
        case kCareerStateCategory:
            return Category_HandleButtonDownMsg(msg);
        case kCareerStateGoal:
            return Goal_HandleButtonDownMsg(msg);
        case kCareerStateDetails:
            return Details_HandleButtonDownMsg(msg);
        default:
            MILO_ASSERT(false, 0x502);
            return DataNode(kDataUnhandled, 0);
    }
}

bool AccomplishmentPanel::CanNavigateList() const {
    if(GetState() != kUp) return false;
    if(mCareerState == kCareerStateGroup || mCareerState == kCareerStateCategory) return false;
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
    if(mCareerState == kCareerStateGroup || mCareerState == kCareerStateCategory) return false;
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
    int idx = 0;
    if(s != ""){
        idx = mAccomplishmentProvider->GoalIndex(s);
        mGoal = mAccomplishmentProvider->DataSymbol(idx);
    }
    UIList* pGoalsList = mDir->Find<UIList>("accomplishments.lst", true);
    MILO_ASSERT(pGoalsList, 0x683);
    mAccomplishmentGridProvider->SetListToData(pGoalsList, idx);
    UpdateForGoalSelection();
}

inline Symbol AccomplishmentProvider::DataSymbol(int i_iData) const {
    MILO_ASSERT(i_iData < NumData(), 0x341);
    return mGoals[i_iData];
}

void AccomplishmentPanel::SelectCategory(Symbol s){
    int idx = 0;
    if(s != ""){
        idx = mAccomplishmentCategoryProvider->CategoryIndex(s);
        mCategory = mAccomplishmentCategoryProvider->DataSymbol(idx);
    }
    UIList* pCategoryList = mDir->Find<UIList>("categories.lst", true);
    MILO_ASSERT(pCategoryList, 0x695);
    pCategoryList->SetSelected(idx, -1);
    UpdateForCategorySelection();
}

inline Symbol AccomplishmentCategoryProvider::DataSymbol(int i_iData) const {
    MILO_ASSERT(i_iData < NumData(), 0x1C1);
    return mCategories[i_iData];
}

void AccomplishmentPanel::SelectGroup(Symbol s){
    int idx = 0;
    if(s != ""){
        idx = mAccomplishmentGroupProvider->GroupIndex(s);
        mGroup = mAccomplishmentGroupProvider->DataSymbol(idx);
    }
    UIList* pGroupList = mDir->Find<UIList>("groups.lst", true);
    MILO_ASSERT(pGroupList, 0x6A7);
    pGroupList->SetSelected(idx, -1);
    UpdateForGoalSelection();
}

inline Symbol AccomplishmentGroupProvider::DataSymbol(int i_iData) const {
    MILO_ASSERT(i_iData < NumData(), 0x140);
    return mGroups[i_iData];
}

void AccomplishmentPanel::RefreshGroupList(){
    MILO_ASSERT(mAccomplishmentGroupProvider, 0x6B0);
    mAccomplishmentGroupProvider->Update();
    static Message cUpdateGroupProviderMsg("update_group_provider", 0);
    cUpdateGroupProviderMsg[0] = mAccomplishmentGroupProvider;
    Handle(cUpdateGroupProviderMsg, true);
    SelectGroup(mGroup);
}

void AccomplishmentPanel::RefreshCategoryList(){
    MILO_ASSERT(mAccomplishmentCategoryProvider, 0x6BC);
    mAccomplishmentCategoryProvider->Update(SelectedAccomplishmentGroup());
    static Message cUpdateCategoryProviderMsg("update_category_provider", 0);
    cUpdateCategoryProviderMsg[0] = mAccomplishmentCategoryProvider;
    Handle(cUpdateCategoryProviderMsg, true);
    SelectCategory(mCategory);
}

inline void AccomplishmentCategoryProvider::Update(Symbol i_symGroup){
    MILO_ASSERT(i_symGroup != gNullStr, 0x174);
    mCategories.clear();
    std::list<Symbol>* pCategories = TheAccomplishmentMgr->GetCategoryListForGroup(i_symGroup);
    MILO_ASSERT(pCategories, 0x17A);
    for(std::list<Symbol>::iterator it = pCategories->begin(); it != pCategories->end(); ++it){
        Symbol key = *it;
        if(TheAccomplishmentMgr->GetNumAccomplishmentsInCategory(key) > 0) mCategories.push_back(key);
    }
    std::stable_sort(mCategories.begin(), mCategories.end(), AccomplishmentCategoryCmp(TheAccomplishmentMgr));
}

void AccomplishmentPanel::RefreshGoalList(){
    MILO_ASSERT(mAccomplishmentProvider, 0x6C8);
    mAccomplishmentProvider->Update(SelectedAccomplishmentCategory());
    UIList* uilist = mDir->Find<UIList>("accomplishments.lst", true);
    uilist->Refresh(true);
    uilist->SetProvider(mAccomplishmentGridProvider);
    SelectGoal(mGoal);
}

void AccomplishmentPanel::RefreshHeader(){
    Handle(refresh_header_msg, true);
}

void AccomplishmentPanel::Refresh(){
    RefreshGroupList();
    RefreshCategoryList();
    RefreshGoalList();
    Handle(refresh_msg, true);
}

int AccomplishmentPanel::GetTotalAccomplishments(){
    MILO_ASSERT(mAccomplishmentProvider, 0x6E7);
    return mAccomplishmentProvider->NumData();
}

int AccomplishmentPanel::GetNumCompleted(){
    MILO_ASSERT(mAccomplishmentProvider, 0x6EF);
    std::vector<Symbol>& goals = mAccomplishmentProvider->mGoals;
    int count = 0;
    BandProfile* profile = TheCampaign->GetProfile();
    for(std::vector<Symbol>::iterator it = goals.begin(); it != goals.end(); ++it){
        if(IsAccomplished(*it, profile)) count++;
    }
    return count;
}

bool AccomplishmentPanel::IsUserOnCorrectInstrument(){
    LocalBandUser* pUser = TheCampaign->GetUser();
    MILO_ASSERT(pUser, 0x6F8);
    Accomplishment* pAccomplishment = TheAccomplishmentMgr->GetAccomplishment(SelectedAccomplishment());
    MILO_ASSERT(pAccomplishment, 0x6FC);
    if(!pAccomplishment->IsUserOnValidController(pUser)) return false;
    else return true;
}

bool AccomplishmentPanel::HasCorrectPlayerCount(){
    LocalBandUser* pUser = TheCampaign->GetUser();
    MILO_ASSERT(pUser, 0x72A);
    Accomplishment* pAccomplishment = TheAccomplishmentMgr->GetAccomplishment(SelectedAccomplishment());
    MILO_ASSERT(pAccomplishment, 0x72E);
    MILO_ASSERT(TheBandUserMgr, 0x730);
    int num = TheBandUserMgr->GetNumParticipants();
    int min = pAccomplishment->GetRequiredMinPlayers();
    int max = pAccomplishment->GetRequiredMaxPlayers();
    if(min != -1 && num < min) return false;
    if(max != -1 && num > max) return false;
    if(pAccomplishment->GetRequiresUnisonAbility()){
        std::vector<BandUser*> users;
        TheBandUserMgr->GetParticipatingBandUsers(users);
        int newnum = TheBandUserMgr->GetNumParticipants();
        for(std::vector<BandUser*>::iterator it = users.begin(); it != users.end(); ++it){
            BandUser* pUser = *it;
            MILO_ASSERT(pUser, 0x751);
            if(pUser->GetControllerType() == kControllerVocals){
                newnum--;
                break;
            }
        }
        if(newnum < 2) return false;
    }
    if(pAccomplishment->GetRequiresBREAbility()){
        std::vector<BandUser*> users;
        TheBandUserMgr->GetParticipatingBandUsersInSession(users);
        int newnum = TheBandUserMgr->GetNumParticipants();
        for(std::vector<BandUser*>::iterator it = users.begin(); it != users.end(); ++it){
            BandUser* pUser = *it;
            MILO_ASSERT(pUser, 0x770);
            if(pUser->GetControllerType() == kControllerVocals){
                newnum--;
                break;
            }
        }
        if(newnum < 1) return false;
    }
    return true;
}

bool AccomplishmentPanel::HasLeaderboard() const {
    Accomplishment* acc = TheAccomplishmentMgr->GetAccomplishment(SelectedAccomplishment());
    if(acc) return acc->IsTrackedInLeaderboard();
    else return false;
}

Symbol AccomplishmentPanel::GetSelectedDetailsEntry(){
    if(GetState() != kUp) return "";
    else {
        DataNode handled = Handle(get_selected_details_entry_index_msg, true);
        int i = handled.Int();
        if(mAccomplishmentEntryProvider->NumData() > 0) return mAccomplishmentEntryProvider->DataSymbol(i);
        else return "";
    }
}

Symbol AccomplishmentPanel::GetAccomplishmentName(){
    if(IsSecret()) return acc_secret;
    else return SelectedAccomplishment();
}

Symbol AccomplishmentPanel::GetAccomplishmentDescription(){
    Accomplishment* acc = TheAccomplishmentMgr->GetAccomplishment(SelectedAccomplishment());
    if(acc){
        if(IsSecret()) return acc->GetSecretDescription();
        else return acc->GetDescription();
    }
    else return gNullStr;
}

Symbol AccomplishmentPanel::GetAccomplishmentFanValueToken(){
    Accomplishment* acc = TheAccomplishmentMgr->GetAccomplishment(SelectedAccomplishment());
    if(acc) return acc->GetMetaScoreValue();
    else return gNullStr;
}

Symbol AccomplishmentPanel::GetAccomplishmentFlavor(){
    if(IsSecret()) return gNullStr;
    else {
        Accomplishment* acc = TheAccomplishmentMgr->GetAccomplishment(SelectedAccomplishment());
        if(acc) return acc->GetFlavorText();
        else return gNullStr;
    }
}

void AccomplishmentPanel::UpdateDetailsListState(){
    Symbol selectedacc = SelectedAccomplishment();
    if(selectedacc == gNullStr || IsSecret()){
        Handle(hide_list_msg, true);
    }
    else {
        Accomplishment* acc = TheAccomplishmentMgr->GetAccomplishment(selectedacc);
        if(acc){
            mAccomplishmentEntryProvider->Update(acc);
            if(mAccomplishmentEntryProvider->NumData() > 0){
                Handle(show_list_msg, true);
            }
            else Handle(hide_list_msg, true);
            UIList* pDetailsList = mDir->Find<UIList>("details.lst", true);
            MILO_ASSERT(pDetailsList, 0x803);
            pDetailsList->SetProvider(mAccomplishmentEntryProvider);
            if(mAccomplishmentEntryProvider->NumData() > 0) pDetailsList->SetSelected(0, -1);
        }
    }
}

inline void AccomplishmentEntryProvider::Update(Accomplishment* acc){
    m_pAccomplishment = acc;
    MILO_ASSERT(m_pAccomplishment, 0x1F5);
    unk24.clear();
    BandProfile* profile = TheCampaign->GetProfile();
    m_pAccomplishment->InqIncrementalSymbols(profile, unk24);
}

bool AccomplishmentPanel::HasAward() const {
    if(IsSecret()) return false;
    else {
        Accomplishment* acc = TheAccomplishmentMgr->GetAccomplishment(SelectedAccomplishment());
        if(acc) return acc->HasAward();
        else return false;
    }
}

bool AccomplishmentPanel::ShouldShowProgress() const {
    if(!HasProgress()) return false;
    BandProfile* pProfile = TheCampaign->GetProfile();
    MILO_ASSERT(pProfile, 0x82A);
    Symbol selacc = SelectedAccomplishment();
    AccomplishmentProgress* prog = pProfile->GetAccomplishmentProgress();
    if(prog->IsAccomplished(selacc)) return false;
    else return true;
}

bool AccomplishmentPanel::HasProgress() const {
    if(IsSecret()) return false;
    else {
        Accomplishment* acc = TheAccomplishmentMgr->GetAccomplishment(SelectedAccomplishment());
        if(!acc) return false;
        else {
            if(acc->HideProgress()) return false;
            else {
                int i10 = 0;
                int i14 = 0;
                BandProfile* pProfile = TheCampaign->GetProfile();
                MILO_ASSERT(pProfile, 0x84E);
                return acc->InqProgressValues(pProfile, i10, i14);
            }
        }
    }
}

bool AccomplishmentPanel::GetCurrentShouldShowDenominator() const {
    Accomplishment* acc = TheAccomplishmentMgr->GetAccomplishment(SelectedAccomplishment());
    bool ret = false;
    if(acc) ret = acc->GetShouldShowDenominator();
    return ret;
}

Symbol AccomplishmentPanel::GetCurrentUnits(int i) const {
    Accomplishment* acc = TheAccomplishmentMgr->GetAccomplishment(SelectedAccomplishment());
    Symbol ret = gNullStr;
    if(acc) ret = acc->GetUnitsToken(i);
    return ret;
}

int AccomplishmentPanel::GetCurrentValue() const {
    if(IsSecret()) return 0;
    else {
        BandProfile* pProfile = TheCampaign->GetProfile();
        MILO_ASSERT(pProfile, 0x879);
        Accomplishment* acc = TheAccomplishmentMgr->GetAccomplishment(SelectedAccomplishment());
        int i10 = 0;
        if(acc){
            int i14 = 0;
            acc->InqProgressValues(pProfile, i10, i14);
        }
        return i10;
    }
}

int AccomplishmentPanel::GetMaxValue() const {
    if(IsSecret()) return 0;
    else {
        BandProfile* pProfile = TheCampaign->GetProfile();
        MILO_ASSERT(pProfile, 0x890);
        Accomplishment* acc = TheAccomplishmentMgr->GetAccomplishment(SelectedAccomplishment());
        int i10 = 0;
        int i14 = 0;
        if(acc){
            acc->InqProgressValues(pProfile, i10, i14);
        }
        return i14;
    }
}

bool AccomplishmentPanel::ShouldShowBest() const {
    if(!HasProgress()) return false;
    else {
        BandProfile* pProfile = TheCampaign->GetProfile();
        MILO_ASSERT(pProfile, 0x8A7);
        Symbol selacc = SelectedAccomplishment();
        AccomplishmentProgress* prog = pProfile->GetAccomplishmentProgress();
        if(!prog->IsAccomplished(selacc)){
            return false;
        }
        else {
            Accomplishment* acc = TheAccomplishmentMgr->GetAccomplishment(selacc);
            return !acc ? false : acc->ShowBestAfterEarn();
        }
    }
}

bool AccomplishmentPanel::IsSecret() const {
    Accomplishment* acc = TheAccomplishmentMgr->GetAccomplishment(SelectedAccomplishment());
    if(acc){
        BandProfile* pProfile = TheCampaign->GetProfile();
        MILO_ASSERT(pProfile, 0x8C8);
        return IsAccomplishmentSecret(acc, pProfile);
    }
    else return false;
}

void AccomplishmentPanel::SetRandomUnplayedSong(){
    Accomplishment* pAccomplishment = TheAccomplishmentMgr->GetAccomplishment(SelectedAccomplishment());
    MILO_ASSERT(pAccomplishment, 0x8D5);
    MILO_ASSERT(pAccomplishment->GetType() == kAccomplishmentTypeSongFilterConditional, 0x8D6);
    AccomplishmentSongFilterConditional* pFilterAccomplishment = dynamic_cast<AccomplishmentSongFilterConditional*>(pAccomplishment);
    MILO_ASSERT(pFilterAccomplishment, 0x8D9);
}

bool AccomplishmentPanel::CanLaunchSelectedEntry() const {
    Symbol selacc = SelectedAccomplishment();
    Accomplishment* acc = TheAccomplishmentMgr->GetAccomplishment(selacc);
    if(!acc) return false;
    if(!TheAccomplishmentMgr->IsAvailableToEarn(selacc)) return false;
    return acc->CanBeLaunched();
}

#pragma push
#pragma pool_data off
void AccomplishmentPanel::LaunchSelectedEntry(LocalBandUser* user){
    Symbol selacc = SelectedAccomplishment();
    TheCampaign->SetupLaunchedAccomplishmentInfo(selacc);
    BandProfile* pProfile = TheCampaign->GetProfile();
    MILO_ASSERT(pProfile, 0x91C);
    Accomplishment* pAccomplishment = TheAccomplishmentMgr->GetAccomplishment(selacc);
    MILO_ASSERT(pAccomplishment, 0x91F);
    if(pAccomplishment->GetType() == kAccomplishmentTypeLessonSongListConditional || pAccomplishment->GetType() == kAccomplishmentTypeLessonDiscSongConditional){
        Symbol entry = GetSelectedDetailsEntry();
        static Message cMsg("handle_goto_trainer_songlesson", 0, 0, 0, 0);
        cMsg[0] = entry;
        cMsg[1] = TheCampaign->GetRequiredTrackTypeForGoal(selacc);
        cMsg[2] = pAccomplishment->GetRequiredDifficulty();
        cMsg[3] = user;
        Handle(cMsg, true);
    }
    else if(pAccomplishment->GetType() == kAccomplishmentTypeTrainerListConditional){
        Symbol entry = GetSelectedDetailsEntry();
        static Message cMsg("handle_goto_trainer_lesson", 0, 0);
        cMsg[0] = entry;
        cMsg[1] = user;
        Handle(cMsg, true);
    }
    else if(pAccomplishment->GetType() == kAccomplishmentTypeTrainerCategoryConditional){
        Symbol entry = TheAccomplishmentMgr->GetFirstUnfinishedAccomplishmentEntry(pProfile, selacc);
        static Message cMsg("handle_goto_trainer_lesson", 0, 0);
        cMsg[0] = entry;
        cMsg[1] = user;
        Handle(cMsg, true);
    }
    else {
        BuildSelectedEntrySetList();
        Handle(handle_goto_difficultyselect_msg, true);
    }
}
#pragma pop

void AccomplishmentPanel::ClearCareerState(){
    SetCareerState(kCareerStateNone, true);
}

CareerState AccomplishmentPanel::GetCareerState() const { return mCareerState; }

void AccomplishmentPanel::SetCareerState(CareerState state, bool b){
    CareerState oldstate = mCareerState;
    mCareerState = state;
    if(mCareerState != 0 && GetState() == kUp){
        switch(mCareerState){
            case kCareerStateGroup:
                if(!b) Handle(handle_snap_state_group_msg, true);
                else if(oldstate == 2){
                    Handle(handle_state_category_to_group_msg, true);
                }
                else MILO_ASSERT(false, 0x97A);
                break;
            case kCareerStateCategory:
                if(!b) Handle(handle_snap_state_category_msg, true);
                else if(oldstate == 1){
                    Handle(handle_state_group_to_category_msg, true);
                }
                else if(oldstate == 3){
                    Handle(handle_state_goal_to_category_msg, true);
                }
                else MILO_ASSERT(false, 0x991);
                break;
            case kCareerStateGoal:
                if(!b) Handle(handle_snap_state_goal_msg, true);
                else if(oldstate == 4){
                    Handle(handle_state_details_to_goal_msg, true);
                }
                else if(oldstate == 2){
                    Handle(handle_state_category_to_goal_msg, true);
                }
                else MILO_ASSERT(false, 0x9A8);
                break;
            case kCareerStateDetails:
                if(!b) Handle(handle_snap_state_details_msg, true);
                else if(oldstate == 3){
                    Handle(handle_state_goal_to_details_msg, true);
                }
                else MILO_ASSERT(false, 0x9BA);
                break;
            default:
                MILO_ASSERT(false, 0x9C0);
                break;
        }
        RefreshHeader();
    }
}

void AccomplishmentPanel::SetSelectedGoal(Symbol s){
    mGoal = s;
    if(s != gNullStr){
        Accomplishment* pGoal = TheAccomplishmentMgr->GetAccomplishment(s);
        MILO_ASSERT(pGoal, 0x9D1);
        SetSelectedCategory(pGoal->GetCategory());
    }
}

void AccomplishmentPanel::SetSelectedCategory(Symbol s){
    mCategory = s;
    if(s != gNullStr){
        AccomplishmentCategory* pCategory = TheAccomplishmentMgr->GetAccomplishmentCategory(s);
        MILO_ASSERT(pCategory, 0x9E0);
        SetSelectedGroup(pCategory->GetGroup());
    }
}

void AccomplishmentPanel::SetSelectedGroup(Symbol s){ mGroup = s; }

void AccomplishmentPanel::UpdateCampaignMeterProgressLabel(UILabel* i_pLabel){
    MILO_ASSERT(i_pLabel, 0x9EE);
    if(GetCurrentShouldShowDenominator()){
        int curval = GetCurrentValue();
        int maxval = GetMaxValue();
        String cur(LocalizeSeparatedInt(curval));
        String max(LocalizeSeparatedInt(maxval));
        i_pLabel->SetTokenFmt(campaign_meter_progress, cur, max, GetCurrentUnits(0));
    }
    else {
        int curval = GetCurrentValue();
        String cur(LocalizeSeparatedInt(curval));
        i_pLabel->SetTokenFmt(campaign_meter_progress_simple, cur, GetCurrentUnits(0));
    }
}

void AccomplishmentPanel::UpdateHeaderLabel(UILabel* i_pLabel){
    MILO_ASSERT(i_pLabel, 0xA07);
    switch(mCareerState){
        case kCareerStateGroup:
            i_pLabel->SetTextToken(career_header_main);
            break;
        case kCareerStateCategory:
            i_pLabel->SetTokenFmt(career_header_group, mGroup);
            break;
        case kCareerStateGoal:
        case kCareerStateDetails:
            i_pLabel->SetTokenFmt(career_header_category, mGroup, mCategory);
            break;
        default:
            MILO_ASSERT(false, 0xA20);
            break;
    }
}

void AccomplishmentPanel::RefreshAll(){ Refresh(); }

void AccomplishmentPanel::FakeEarnSelected(){
    switch(mCareerState){
        case kCareerStateGroup:
            FakeEarnSelectedGroup();
            break;
        case kCareerStateCategory:
            FakeEarnSelectedCategory();
            break;
        case kCareerStateGoal:
        case kCareerStateDetails:
            FakeEarnSelectedGoal();
            break;
        default:
            MILO_ASSERT(false, 0xA45);
            break;
    }
    Refresh();
}

void AccomplishmentPanel::FakeEarnSelectedGoal(){
    Symbol selacc = SelectedAccomplishment();
    BandProfile* pProfile = TheCampaign->GetProfile();
    if(pProfile){
        std::vector<LocalBandUser*> owners;
        pProfile->GetAssociatedUsers(owners);
        MILO_ASSERT(!owners.empty(), 0xA57);
        TheAccomplishmentMgr->EarnAccomplishment(owners[0], selacc);
    }
}

void AccomplishmentPanel::FakeEarnSelectedGroup(){
    Symbol selacc = SelectedAccomplishmentGroup();
    BandProfile* pProfile = TheCampaign->GetProfile();
    if(pProfile){
        std::vector<LocalBandUser*> owners;
        pProfile->GetAssociatedUsers(owners);
        MILO_ASSERT(!owners.empty(), 0xA67);
        std::list<Symbol>* list = TheAccomplishmentMgr->GetCategoryListForGroup(selacc);
        if(list){
            for(std::list<Symbol>::iterator it = list->begin(); it != list->end(); ++it){
                Symbol key = *it;
                std::set<Symbol>* set = TheAccomplishmentMgr->GetAccomplishmentSetForCategory(key);
                if(set){
                    for(std::set<Symbol>::iterator sit = set->begin(); sit != set->end(); ++sit){
                        Symbol skey = *sit;
                        TheAccomplishmentMgr->EarnAccomplishment(owners[0], skey);
                    }
                }
            }
        }
    }
}

void AccomplishmentPanel::FakeEarnSelectedCategory(){
    Symbol selacc = SelectedAccomplishmentCategory();
    BandProfile* pProfile = TheCampaign->GetProfile();
    if(pProfile){
        std::vector<LocalBandUser*> owners;
        pProfile->GetAssociatedUsers(owners);
        MILO_ASSERT(!owners.empty(), 0xA8F);
        std::set<Symbol>* set = TheAccomplishmentMgr->GetAccomplishmentSetForCategory(selacc);
        if(set){
            for(std::set<Symbol>::iterator sit = set->begin(); sit != set->end(); ++sit){
                Symbol skey = *sit;
                TheAccomplishmentMgr->EarnAccomplishment(owners[0], skey);
            }
        }
    }
}

#pragma push
#pragma dont_inline on
BEGIN_HANDLERS(AccomplishmentPanel)
    HANDLE_ACTION(fake_earn_selected, FakeEarnSelected())
    HANDLE_EXPR(selected_accomplishment, SelectedAccomplishment())
    HANDLE_ACTION(set_other_user_to_view, mOtherUserToView = _msg->Obj<LocalBandUser>(2))
    HANDLE_EXPR(can_navigate_list, CanNavigateList())
    HANDLE_EXPR(can_launch_goal, CanLaunchGoal())
    HANDLE_ACTION(launch_goal, LaunchGoal(_msg->Obj<LocalBandUser>(2)))
    HANDLE_EXPR(is_user_on_correct_instrument, IsUserOnCorrectInstrument())
    HANDLE_EXPR(has_correct_playercount, HasCorrectPlayerCount())
    HANDLE_EXPR(get_total, GetTotalAccomplishments())
    HANDLE_EXPR(get_num_completed, GetNumCompleted())
    HANDLE_EXPR(has_leaderboard, HasLeaderboard())
    HANDLE_EXPR(get_accomplishment_description, GetAccomplishmentDescription())
    HANDLE_EXPR(get_accomplishment_name, GetAccomplishmentName())
    HANDLE_EXPR(get_accomplishment_fanvalue_token, GetAccomplishmentFanValueToken())
    HANDLE_EXPR(has_award, HasAward())
    HANDLE_EXPR(get_flavor_text, GetAccomplishmentFlavor())
    HANDLE_EXPR(should_show_progress, ShouldShowProgress())
    HANDLE_EXPR(get_current_value, GetCurrentValue())
    HANDLE_EXPR(get_current_units, GetCurrentUnits(_msg->Int(2)))
    HANDLE_EXPR(get_current_should_show_denominator, GetCurrentShouldShowDenominator())
    HANDLE_EXPR(get_max_value, GetMaxValue())
    HANDLE_EXPR(should_show_best, ShouldShowBest())
    HANDLE_EXPR(is_accomplishment_secret, IsSecret())
    HANDLE_ACTION(launch_selected_entry, LaunchSelectedEntry(_msg->Obj<LocalBandUser>(2)))
    HANDLE_EXPR(can_launch_selected_entry, CanLaunchSelectedEntry())
    HANDLE_ACTION(clear_career_state, ClearCareerState())
    HANDLE_EXPR(get_career_state, GetCareerState())
    HANDLE_ACTION(set_career_state, SetCareerState((CareerState)_msg->Int(2), false))
    HANDLE_ACTION(update_header_label, UpdateHeaderLabel(_msg->Obj<UILabel>(2)))
    HANDLE_ACTION(update_campaign_meter_progress, UpdateCampaignMeterProgressLabel(_msg->Obj<UILabel>(2)))
    HANDLE_ACTION(set_goal, SetSelectedGoal(_msg->Sym(2)))
    HANDLE_ACTION(set_category, SetSelectedCategory(_msg->Sym(2)))
    HANDLE_ACTION(set_group, SetSelectedGroup(_msg->Sym(2)))
    HANDLE_ACTION(refresh_all, RefreshAll())
    HANDLE_MESSAGE(ButtonDownMsg)
    HANDLE_MESSAGE(UIComponentScrollMsg)
    HANDLE_SUPERCLASS(TexLoadPanel)
    HANDLE_CHECK(0xAFF)
END_HANDLERS
#pragma pop