#include "tour/TourDesc.h"
#include "obj/Data.h"
#include "os/Debug.h"
#include "utl/MakeString.h"
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
                pGigEntry->FindData(gig, entry->mQuest, true);
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

Symbol TourDesc::GetWelcome() const {
    return MakeString("%s_welcome", mName);
}

Symbol TourDesc::GetConclusionText() const {
    return MakeString("%s_conclusion", mName);
}

int TourDesc::GetIndex() const { return mIndex; }
int TourDesc::GetNumGigs() const { return m_vEntries.size(); }

TourDescEntry* TourDesc::GetTourDescEntryForGigNum(int i_iGigNum) const {
    MILO_ASSERT(( 0) <= ( i_iGigNum) && ( i_iGigNum) < ( m_vEntries.size()), 0xB0);
    return m_vEntries[i_iGigNum];
}

int TourDesc::GetNumSongsForGigNum(int num) const {
    TourDescEntry* pEntry = GetTourDescEntryForGigNum(num);
    MILO_ASSERT(pEntry, 0xB9);
    return pEntry->mNumSongs;
}

Symbol TourDesc::GetFilterForGigNum(int num) const {
    TourDescEntry* pEntry = GetTourDescEntryForGigNum(num);
    MILO_ASSERT(pEntry, 0xC2);
    return pEntry->mFilter;
}

Symbol TourDesc::GetSetlistTypeForGigNum(int num, int i_iIndex) const {
    TourDescEntry* pEntry = GetTourDescEntryForGigNum(num);
    MILO_ASSERT(pEntry, 0xCB);
    std::vector<Symbol>& rSetlistTypeVector = pEntry->mSetlistTypes;
    MILO_ASSERT(i_iIndex < rSetlistTypeVector.size(), 0xCE);
    return rSetlistTypeVector[i_iIndex];
}

bool TourDesc::HasSpecificQuest(int num) const {
    return GetSpecificQuestForGigNum(num) != "";
}

bool TourDesc::HasQuestGroup(int num) const {
    return GetQuestGroupForGigNum(num) != "";
}

bool TourDesc::HasQuestTier(int num) const {
    return GetQuestTierForGigNum(num) != -1;
}

bool TourDesc::HasAnnouncementScreen(int num) const {
    return GetAnnouncementScreenForGigNum(num) != "";
}

int TourDesc::GetQuestTierForGigNum(int num) const {
    TourDescEntry* pEntry = GetTourDescEntryForGigNum(num);
    MILO_ASSERT(pEntry, 0xF0);
    return pEntry->mTier;
}

Symbol TourDesc::GetQuestGroupForGigNum(int num) const {
    TourDescEntry* pEntry = GetTourDescEntryForGigNum(num);
    MILO_ASSERT(pEntry, 0xF9);
    return pEntry->mGroup;
}

Symbol TourDesc::GetSpecificQuestForGigNum(int num) const {
    TourDescEntry* pEntry = GetTourDescEntryForGigNum(num);
    MILO_ASSERT(pEntry, 0x102);
    return pEntry->mQuest;
}

Symbol TourDesc::GetCityForGigNum(int num) const {
    TourDescEntry* pEntry = GetTourDescEntryForGigNum(num);
    MILO_ASSERT(pEntry, 0x10B);
    return pEntry->mCity;
}

Symbol TourDesc::GetAnnouncementScreenForGigNum(int num) const {
    TourDescEntry* pEntry = GetTourDescEntryForGigNum(num);
    MILO_ASSERT(pEntry, 0x114);
    return pEntry->mAnnouncementScreen;
}

Symbol TourDesc::GetFlavorForGigNum(int num) const {
    TourDescEntry* pEntry = GetTourDescEntryForGigNum(num);
    MILO_ASSERT(pEntry, 0x11D);
    return pEntry->mFlavor;
}

Symbol TourDesc::GetMapScreenForGigNum(int num) const {
    TourDescEntry* pEntry = GetTourDescEntryForGigNum(num);
    MILO_ASSERT(pEntry, 0x126);
    return pEntry->mMapScreen;
}

Symbol TourDesc::GetVenueForGigNum(int num) const {
    TourDescEntry* pEntry = GetTourDescEntryForGigNum(num);
    MILO_ASSERT(pEntry, 0x12F);
    return pEntry->mVenue;
}

int TourDesc::GetNumStarsPossibleForTour() const {
    int size = m_vEntries.size();
    int stars = 0;
    for(int i = 0; i < size; i++){
        stars += GetNumSongsForGigNum(i) * 10;
    }
    return stars;
}

int TourDesc::GetNumSongs() const {
    int size = m_vEntries.size();
    int songs = 0;
    for(int i = 0; i < size; i++){
        songs += GetNumSongsForGigNum(i);
    }
    return songs;
}

Symbol TourDesc::GetTourBronzeGoal() const { return mTourStarsBronzeGoal; }
Symbol TourDesc::GetTourSilverGoal() const { return mTourStarsSilverGoal; }
Symbol TourDesc::GetTourGoldGoal() const { return mTourStarsGoldGoal; }

bool TourDesc::HasRequiredCampaignLevel() const {
    Symbol level = mRequiredCampaignLevel;
    return level != gNullStr;
}

Symbol TourDesc::GetRequiredCampaignLevel() const { return mRequiredCampaignLevel; }
Symbol TourDesc::GetLeaderboardGoal() const { return mLeaderboardGoal; }

bool TourDesc::HasLeaderboardGoal() const {
    Symbol goal = mLeaderboardGoal;
    return goal != gNullStr;
}

const char* TourDesc::GetArt() const {
    return MakeString("ui/tour/tour_art/%s_keep.png", mName.Str());
}

const char* TourDesc::GetGrayArt() const {
    const char* gray = MakeString("%s_gray", mName.Str());
    return MakeString("ui/tour/tour_art/%s_keep.png", gray);
}

Symbol TourDesc::GetGigGuideMap() const {
    return mGigGuideMap;
}