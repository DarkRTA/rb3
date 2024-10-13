#include "tour/TourDesc.h"
#include "obj/Data.h"
#include "os/Debug.h"
#include "utl/Symbol.h"
#include "utl/Symbols.h"
#include "utl/Symbols2.h"
#include "utl/Symbols3.h"
#include "utl/Symbols4.h"

TourDesc::TourDesc(DataArray* arr, int i) : mName(""), mIndex(i), mRequiredCampaignLevel(gNullStr), mLeaderboardGoal(gNullStr), mDifficulty(gNullStr), mGigGuideMap(gNullStr) {
    Configure(arr);
}

TourDesc::~TourDesc(){
    Cleanup();
}

void TourDesc::Cleanup(){
    for(std::vector<TourDescEntry*>::iterator it = m_vEntries.begin(); it != m_vEntries.end(); ++it){
        TourDescEntry* pEntry = *it;
        MILO_ASSERT(pEntry, 0x2A);
        delete pEntry;
    }
    m_vEntries.clear();
}

void TourDesc::Configure(DataArray* i_pConfig){
    MILO_ASSERT(i_pConfig, 0x33);
    mName = i_pConfig->Sym(0);
    MILO_ASSERT(m_vEntries.empty(), 0x38);
    i_pConfig->FindData(required_campaign_level, mRequiredCampaignLevel, true);
    i_pConfig->FindData(gigguide_map, mGigGuideMap, true);
    i_pConfig->FindData(difficulty_token, mDifficulty, true);
    i_pConfig->FindData(leaderboard_goal, mLeaderboardGoal, false);
    i_pConfig->FindData(tour_stars_bronze_goal, mTourStarsBronzeGoal, true);
    i_pConfig->FindData(tour_stars_silver_goal, mTourStarsSilverGoal, true);
    i_pConfig->FindData(tour_stars_gold_goal, mTourStarsGoldGoal, true);
    DataArray* pGigArray = i_pConfig->FindArray(gigs, true);
    MILO_ASSERT(pGigArray, 0x51);

    for(int i = 1; i < pGigArray->Size(); i++){
        DataArray* pGigEntry = pGigArray->Array(i);
        MILO_ASSERT(pGigEntry, 0x55);
        TourDescEntry* entry = new TourDescEntry();
        if(!pGigEntry->FindData(gig_tier, entry->mTier, false)){
            if(!pGigEntry->FindData(gig_group, entry->mGroup, false)){
                pGigEntry->FindData(gig, entry->mGig, true);
            }
        }
        pGigEntry->FindData(filter, entry->mFilter, false);
        pGigEntry->FindData(num_songs, entry->mNumSongs, false);
        pGigEntry->FindData(city, entry->mCity, true);
        pGigEntry->FindData(announce, entry->mAnnouncementScreen, false);
        pGigEntry->FindData(flavor, entry->mFlavor, false);
        pGigEntry->FindData(map, entry->mMapScreen, true);
        pGigEntry->FindData(venue, entry->mVenue, false);
        DataArray* pSetlistTypeArray = pGigEntry->FindArray(setlist_type, true);
        MILO_ASSERT(pSetlistTypeArray, 0x79);
        MILO_ASSERT(pSetlistTypeArray->Size() == 4, 0x7C);
        for(int j = 1; j < pSetlistTypeArray->Size(); j++){
            Symbol sym = pSetlistTypeArray->Node(j).Sym();
            entry->mSetlistTypes.push_back(sym);
        }
        m_vEntries.push_back(entry);
    }
}

Symbol TourDesc::GetName() const { return mName; }

Symbol TourDesc::GetDescription() const {
    return MakeString("%s_desc", mName);
}