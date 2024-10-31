#include "meta_band/CampaignSongInfoPanel.h"
#include "BandProfile.h"
#include "Campaign.h"
#include "SongStatusMgr.h"
#include "Utl.h"
#include "game/Defines.h"
#include "meta_band/BandSongMgr.h"
#include "obj/ObjMacros.h"
#include "os/Debug.h"
#include "ui/UILabel.h"
#include "ui/UIList.h"
#include "ui/UIListLabel.h"
#include "ui/UIPanel.h"
#include "utl/Messages.h"
#include "utl/Messages2.h"
#include "utl/Messages3.h"
#include "utl/Messages4.h"
#include "utl/Symbol.h"
#include "utl/Symbols.h"
#include "utl/Symbols3.h"

CampaignSongInfoPanel::CampaignSongInfoPanel() : mCampaignSourceProvider(0) {

}

Symbol CampaignSongInfoPanel::SelectedSource() const {
    if(GetState() != kUp){
        return "";
    }
    else {
        UIList* pSourcesList = mDir->Find<UIList>("sources.lst", true);
        MILO_ASSERT(pSourcesList, 0x71);
        return pSourcesList->SelectedSym(true);
    }
}

ScoreType CampaignSongInfoPanel::SelectedScoreType() const {
    if(GetState() != kUp){
        return kScoreBand;
    }
    else {
        UIList* pInstrumentsList = mDir->Find<UIList>("instruments.lst", true);
        MILO_ASSERT(pInstrumentsList, 0x7F);
        return SymToScoreType(pInstrumentsList->SelectedSym(true));
    }
}

inline void CampaignSourceProvider::Update(){
    unk20.clear();
    std::set<Symbol> srcs;
    TheSongMgr->InqAvailableSongSources(srcs);
    if(srcs.size() > 1) unk20.push_back(all);
    for(std::set<Symbol>::iterator it = srcs.begin(); it != srcs.end(); ++it){
        Symbol cur = *it;
        unk20.push_back(cur);
    }
}

void CampaignSongInfoPanel::Refresh(){
    MILO_ASSERT(mCampaignSourceProvider, 0x88);
    mCampaignSourceProvider->Update();
    UIList* pSourceList = mDir->Find<UIList>("sources.lst", true);
    MILO_ASSERT(pSourceList, 0x8D);
    pSourceList->SetProvider(mCampaignSourceProvider);
    Handle(refresh_instrument_list_msg, true);
    SelectDefaultInstrument();
    Handle(update_details_msg, true);
}

void CampaignSongInfoPanel::SelectDefaultInstrument(){
    LocalBandUser* pUser = TheCampaign->GetUser();
    MILO_ASSERT(pUser, 0x9F);
    Symbol scoreTypeSym = ScoreTypeToSym(TrackTypeToScoreType(ControllerTypeToTrackType(pUser->GetControllerType(), false), false, false));
    UIList* pInstrumentList = mDir->Find<UIList>("instruments.lst", true);
    MILO_ASSERT(pInstrumentList, 0xA6);
    pInstrumentList->SetSelected(scoreTypeSym, true, -1);
    Handle(update_details_msg, true);
}

void CampaignSongInfoPanel::Enter(){
    UIPanel::Enter();
    MILO_ASSERT(!mCampaignSourceProvider, 0xB3);
    mCampaignSourceProvider = new CampaignSourceProvider();
    Refresh();
}

void CampaignSongInfoPanel::Unload(){
    UIPanel::Unload();
    RELEASE(mCampaignSourceProvider);   
}

void CampaignSongInfoPanel::Load(){ UIPanel::Load(); }

int CampaignSongInfoPanel::GetCareerScore() const {
    ScoreType ty = SelectedScoreType();
    Symbol src = SelectedSource();
    BandProfile* pProfile = TheCampaign->GetProfile();
    MILO_ASSERT(pProfile, 0xCD);
    SongStatusMgr* pSongStatusMgr = pProfile->GetSongStatusMgr();
    MILO_ASSERT(pSongStatusMgr, 0xCF);
    if(src == all){
        return pSongStatusMgr->CalculateTotalScore(ty, gNullStr);
    }
    else {
        return pSongStatusMgr->CalculateTotalScore(ty, src);
    }
}

int CampaignSongInfoPanel::GetSongCount() const {
    Symbol src = SelectedSource();
    ScoreType ty = SelectedScoreType();
    BandProfile* pProfile = TheCampaign->GetProfile();
    MILO_ASSERT(pProfile, 0xE3);
    SongStatusMgr* pSongStatusMgr = pProfile->GetSongStatusMgr();
    MILO_ASSERT(pSongStatusMgr, 0xE5);
    if(src == all){
        return pSongStatusMgr->GetTotalSongs(ty, gNullStr);
    }
    else {
        return pSongStatusMgr->GetTotalSongs(ty, src);
    }
}

int CampaignSongInfoPanel::GetSongsCompleted(Difficulty diff) const {
    ScoreType ty = SelectedScoreType();
    Symbol src = SelectedSource();
    BandProfile* pProfile = TheCampaign->GetProfile();
    MILO_ASSERT(pProfile, 0xF9);
    SongStatusMgr* pSongStatusMgr = pProfile->GetSongStatusMgr();
    MILO_ASSERT(pSongStatusMgr, 0xFB);
    if(src == all){
        return pSongStatusMgr->GetCompletedSongs(ty, diff, gNullStr);
    }
    else {
        return pSongStatusMgr->GetCompletedSongs(ty, diff, src);
    }
}

int CampaignSongInfoPanel::GetStarCount() const {
    Symbol src = SelectedSource();
    ScoreType ty = SelectedScoreType();
    BandProfile* pProfile = TheCampaign->GetProfile();
    MILO_ASSERT(pProfile, 0x10F);
    SongStatusMgr* pSongStatusMgr = pProfile->GetSongStatusMgr();
    MILO_ASSERT(pSongStatusMgr, 0x111);
    if(src == all){
        return pSongStatusMgr->GetPossibleStars(ty, gNullStr);
    }
    else {
        return pSongStatusMgr->GetPossibleStars(ty, src);
    }
}

int CampaignSongInfoPanel::GetStarsEarned(Difficulty diff) const {
    ScoreType ty = SelectedScoreType();
    Symbol src = SelectedSource();
    BandProfile* pProfile = TheCampaign->GetProfile();
    MILO_ASSERT(pProfile, 0x125);
    SongStatusMgr* pSongStatusMgr = pProfile->GetSongStatusMgr();
    MILO_ASSERT(pSongStatusMgr, 0x127);
    if(src == all){
        return pSongStatusMgr->GetTotalBestStars(ty, diff, gNullStr);
    }
    else {
        return pSongStatusMgr->GetTotalBestStars(ty, diff, src);
    }
}

const char* CampaignSongInfoPanel::GetInstrumentIcon(){
    return GetFontCharFromScoreType(SelectedScoreType(), 0);
}

Symbol CampaignSongInfoPanel::GetMusicLibraryBackScreen(){
    MILO_ASSERT(GetState() == kUp, 0x13E);
    DataNode handled = Handle(get_musiclibrary_backscreen_msg, true);
    return handled.Sym();
}

Symbol CampaignSongInfoPanel::GetMusicLibraryNextScreen(){
    MILO_ASSERT(GetState() == kUp, 0x14A);
    DataNode handled = Handle(get_musiclibrary_nextscreen_msg, true);
    return handled.Sym();
}

void CampaignSongInfoPanel::CreateAndSubmitMusicLibraryTask(){

}

void CampaignSongInfoPanel::Launch(){
    CreateAndSubmitMusicLibraryTask();
    Handle(handle_goto_musiclibrary_msg, true);
}

BEGIN_HANDLERS(CampaignSongInfoPanel)
    HANDLE_EXPR(get_career_score, GetCareerScore())
    HANDLE_EXPR(get_song_count, GetSongCount())
    HANDLE_EXPR(get_songs_completed, GetSongsCompleted((Difficulty)_msg->Int(2)))
    HANDLE_EXPR(get_star_count, GetStarCount())
    HANDLE_EXPR(get_stars_earned, GetStarsEarned((Difficulty)_msg->Int(2)))
    HANDLE_EXPR(get_instrument_icon, GetInstrumentIcon())
    HANDLE_ACTION(launch, Launch())
    HANDLE_SUPERCLASS(UIPanel)
    HANDLE_CHECK(0x18A)
END_HANDLERS

inline Symbol CampaignSourceProvider::DataSymbol(int i_iData) const {
    MILO_ASSERT(i_iData < NumData(), 0x55);
    return unk20[i_iData];
}

inline int CampaignSourceProvider::NumData() const { return unk20.size(); }

inline void CampaignSourceProvider::Text(int, int i_iData, UIListLabel* slot, UILabel* label) const {
    MILO_ASSERT(i_iData < NumData(), 0x41);
    Symbol sym = DataSymbol(i_iData);
    if(slot->Matches("name")){
        label->SetTextToken(sym);
    }
    else {
        label->SetTextToken(gNullStr);
    }
}