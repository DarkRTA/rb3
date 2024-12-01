#include "tour/QuestFilterPanel.h"
#include "meta_band/TexLoadPanel.h"
#include "obj/ObjMacros.h"
#include "os/Debug.h"
#include "tour/Tour.h"
#include "tour/TourPerformer.h"
#include "tour/TourProgress.h"
#include "ui/UIList.h"
#include "ui/UIPanel.h"
#include "utl/Messages.h"
#include "utl/Messages2.h"
#include "utl/Messages4.h"
#include "utl/Symbol.h"
#include "utl/Symbols.h"
#include "utl/Symbols2.h"
#include "utl/Symbols3.h"

QuestFilterPanel::QuestFilterPanel() : m_symQuest(""), m_pQuestFilterProvider(0) {

}

Symbol QuestFilterPanel::GetSelectedFilter(){
    if(GetState() != kUp) return "";
    else {
        DataNode handled = Handle(get_selected_filter_index_msg, true);
        int i = handled.Int();
        if(m_pQuestFilterProvider->NumData() > 0){
            return m_pQuestFilterProvider->DataSymbol(i);
        }
        else return "";
    }
}

inline Symbol QuestFilterProvider::DataSymbol(int i_iData) const {
    MILO_ASSERT_RANGE( i_iData, 0, NumData(), 0xD0);
    return m_vQuestFilters[i_iData];
}

TourSetlistType QuestFilterPanel::GetSelectedSetlistType(){
    if(GetState() != kUp) return kTourSetlist_Invalid;
    DataNode handled = Handle(get_selected_filter_index_msg, true);
    int i = handled.Int();
    TourSetlistType ret;
    if(m_pQuestFilterProvider->NumData() > 0){
        TourProgress* prog = TheTour->GetTourProgress();
        if(prog){
            TourDesc* desc = TheTour->GetTourDesc(prog->GetTourDesc());
            if(desc){
                Symbol gigtype = desc->GetSetlistTypeForGigNum(prog->GetCurrentGigNum(), i);
                if(gigtype == random) ret = kTourSetlist_Random;
                else if(gigtype == custom) ret = kTourSetlist_Custom;
                return ret;
            }
        }
        ret = kTourSetlist_Fixed;
    }
    else ret = kTourSetlist_Invalid;
    return ret;
}

void QuestFilterPanel::LoadIcons(){
    const char* artStr = "ui/tour/setlist_art/%s_keep.png";
    AddTex(MakeString(artStr, "setlist_random"), "setlist_random", true, false);
    AddTex(MakeString(artStr, "setlist_custom"), "setlist_custom", true, false);
    AddTex(MakeString(artStr, "setlist_fixed"), "setlist_fixed", true, false);
}

void QuestFilterPanel::Load(){
    TexLoadPanel::Load();
    MILO_ASSERT(!m_pQuestFilterProvider, 0x147);
    LoadIcons();
}

void QuestFilterPanel::FinishLoad(){
    TexLoadPanel::FinishLoad();
    MILO_ASSERT(!m_pQuestFilterProvider, 0x150);
    TourProgress* pProgress = TheTour->GetTourProgress();
    MILO_ASSERT(pProgress, 0x153);
    UIList* pList = mDir->Find<UIList>("filters.lst", true);
    MILO_ASSERT(pList, 0x156);
    m_pQuestFilterProvider = new QuestFilterProvider(mTexs, *pProgress, pList);
}

void QuestFilterPanel::Enter(){
    UIPanel::Enter();
    TourProgress* pProgress = TheTour->GetTourProgress();
    MILO_ASSERT(pProgress, 0x161);
    pProgress->ClearPerformanceState();
    TourPerformerImpl* pPerformer = TheTour->m_pTourPerformer;
    MILO_ASSERT(pPerformer, 0x166);
    Refresh();
}

void QuestFilterPanel::Unload(){
    TexLoadPanel::Unload();
    RELEASE(m_pQuestFilterProvider);
}

void QuestFilterPanel::UpdateFilters(){
    MILO_ASSERT(m_pQuestFilterProvider, 0x17B);
    m_pQuestFilterProvider->Update();
    static Message cUpdateFilterProviderMsg("update_filter_provider", 0);
    cUpdateFilterProviderMsg[0] = m_pQuestFilterProvider;
    Handle(cUpdateFilterProviderMsg, true);
}

void QuestFilterPanel::Refresh(){
    TourProgress* pProgress = TheTour->GetTourProgress();
    MILO_ASSERT(pProgress, 0x187);
    m_symQuest = pProgress->mCurrentQuest;
    UpdateFilters();
    Handle(update_all_msg, true);
}

Symbol QuestFilterPanel::GetBackScreen(){
    MILO_ASSERT(GetState() == kUp, 0x194);
    return Handle(get_backscreen_msg, true).Sym();
}

Symbol QuestFilterPanel::GetSongSelectScreen(){
    MILO_ASSERT(GetState() == kUp, 0x1A0);
    return Handle(get_songselect_screen_msg, true).Sym();
}

Symbol QuestFilterPanel::GetDiffSelectScreen(){
    MILO_ASSERT(GetState() == kUp, 0x1AC);
    return Handle(get_diffselect_screen_msg, true).Sym();
}

void QuestFilterPanel::HandleFilterSelected(){

}

Symbol QuestFilterPanel::GetGigFilter(){
    MILO_ASSERT(m_symQuest != "", 0x1D4);
    TourProgress* pProgress = TheTour->GetTourProgress();
    MILO_ASSERT(pProgress, 0x1D8);
    return pProgress->GetFilterForCurrentGig();
}

BEGIN_HANDLERS(QuestFilterPanel)
    HANDLE_ACTION(cheat_win_quest, CheatWinQuest())
    HANDLE_ACTION(cheat_cycle_challenge, CheatCycleChallenge())
    HANDLE_ACTION(cheat_cycle_setlist, CheatCycleSetlist())
    HANDLE_EXPR(update_details, 0)
    HANDLE_ACTION(handle_leader_toggled_filters, HandleLeaderToggledFilters(_msg->Int(2)))
    HANDLE_ACTION(handle_filter_selected, HandleFilterSelected())
    HANDLE_EXPR(are_current_filters_valid, AreCurrentFiltersValid())
    HANDLE_SUPERCLASS(TexLoadPanel)
    HANDLE_CHECK(0x244)
END_HANDLERS
