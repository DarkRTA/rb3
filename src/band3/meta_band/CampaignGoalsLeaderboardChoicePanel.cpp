#include "meta_band/CampaignGoalsLeaderboardChoicePanel.h"
#include "meta_band/Accomplishment.h"
#include "os/Debug.h"
#include "utl/Messages.h"
#include "utl/Symbols.h"

GoalCmp::GoalCmp(const AccomplishmentManager* mgr) : m_pAccomplishmentMgr(mgr) {}

bool GoalCmp::operator()(Symbol lhs, Symbol rhs) const {
    if(lhs == campaign_metascore) return true;
    else if(rhs == campaign_metascore) return false;
    else {
        Accomplishment* pLHSAccomplishment = m_pAccomplishmentMgr->GetAccomplishment(lhs);
        MILO_ASSERT(pLHSAccomplishment, 0x31);
        Accomplishment* pRHSAccomplishment = m_pAccomplishmentMgr->GetAccomplishment(rhs);
        MILO_ASSERT(pRHSAccomplishment, 0x34);
        return pLHSAccomplishment->mIndex < pRHSAccomplishment->mIndex;
    }
}

CampaignGoalsLeaderboardChoicePanel::CampaignGoalsLeaderboardChoicePanel() : mCampaignGoalsLeaderboardChoiceProvider(0) {

}

Symbol CampaignGoalsLeaderboardChoicePanel::SelectedGoal(){
    if(GetState() != kUp) return "";
    else {
        DataNode handled = Handle(get_selected_index_msg, true);
        int handledInt = handled.Int();
        if(mCampaignGoalsLeaderboardChoiceProvider->NumData() > 0){
            return mCampaignGoalsLeaderboardChoiceProvider->DataSymbol(handledInt);
        }
        else {
            return "";
        }
    }
}

inline Symbol CampaignGoalsLeaderboardChoiceProvider::DataSymbol(int i_iData) const {
    MILO_ASSERT_RANGE(i_iData, 0, NumData(), 0x89);
    return unk20[i_iData];
}