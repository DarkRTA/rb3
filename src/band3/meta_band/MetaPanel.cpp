#include "meta_band/MetaPanel.h"
#include "AccomplishmentPanel.h"
#include "BandScreen.h"
#include "BandStorePanel.h"
#include "BandStoreUIPanel.h"
#include "Calibration.h"
#include "CampaignCareerLeaderboardPanel.h"
#include "CampaignGoalsLeaderboardChoicePanel.h"
#include "CampaignSongInfoPanel.h"
#include "CharacterCreatorPanel.h"
#include "ChooseColorPanel.h"
#include "ClosetPanel.h"
#include "ContentDeletePanel.h"
#include "ContentLoadingPanel.h"
#include "CustomizePanel.h"
#include "EditSetlistPanel.h"
#include "GameTimePanel.h"
#include "ManageBandPanel.h"
#include "NewAwardPanel.h"
#include "game/BandUserMgr.h"
#include "meta/CreditsPanel.h"
#include "meta/HAQManager.h"
#include "meta/HeldButtonPanel.h"
#include "meta/Meta.h"
#include "meta/MetaMusicManager.h"
#include "meta/MoviePanel.h"
#include "meta_band/BandPreloadPanel.h"
#include "meta_band/BandSongMgr.h"
#include "meta_band/BandUI.h"
#include "meta_band/CampaignGoalsLeaderboardPanel.h"
#include "meta_band/EventDialogPanel.h"
#include "meta_band/InterstitialPanel.h"
#include "meta_band/MainHubPanel.h"
#include "meta_band/MetaNetMsgs.h"
#include "meta_band/NameGenerator.h"
#include "meta_band/OvershellPanel.h"
#include "net/NetMessage.h"
#include "obj/Dir.h"
#include "os/PlatformMgr.h"

bool MetaPanel::sUnlockAll;
bool MetaPanel::sIsPlaytest;
bool MetaPanel::sLaunchedGoalMsgsOnly;

NetMessage *BandEventPreviewMsg::NewNetMessage() { return new BandEventPreviewMsg(); }
NetMessage *TriggerBackSoundMsg::NewNetMessage() { return new TriggerBackSoundMsg(); }
NetMessage *VerifyBuildVersionMsg::NewNetMessage() { return new VerifyBuildVersionMsg(); }
NetMessage *AppendSongToSetlistMsg::NewNetMessage() {
    return new AppendSongToSetlistMsg();
}
NetMessage *RemoveLastSongFromSetlistMsg::NewNetMessage() {
    return new RemoveLastSongFromSetlistMsg();
}

DataNode MetaPanel::ToggleUnlockAll(DataArray *) { return sUnlockAll = !sUnlockAll; }
DataNode MetaPanel::ToggleIsPlaytest(DataArray *) { return sIsPlaytest = !sIsPlaytest; }
DataNode MetaPanel::ToggleLaunchedGoalMsgsOnly(DataArray *) {
    return sLaunchedGoalMsgsOnly = !sLaunchedGoalMsgsOnly;
}

void MetaPanel::Init() {
    MetaInit();
    CampaignGoalsLeaderboardPanel::Init();
    CampaignCareerLeaderboardPanel::Init();
    CampaignGoalsLeaderboardChoicePanel::Init();
    CampaignSongInfoPanel::Init();
    AccomplishmentPanel::Init();
    NewAwardPanel::Init();
    BackdropPanel::Init();
    BandPreloadPanel::Init();
    BandScreen::Init();
    BandStorePanel::Init();
    BandStoreUIPanel::Init();
    CalibrationPanel::Init();
    CalibrationWelcomePanel::Init();
    CharacterCreatorPanel::Init();
    ChooseColorPanel::Init();
    ClosetPanel::Init();
    ContentDeletePanel::Init();
    ContentLoadingPanel::Init();
    CreditsPanel::Init();
    CustomizePanel::Init();
    EditSetlistPanel::Init();
    EventDialogPanel::Init();
    GameTimePanel::Init();
    HeldButtonPanel::Init();
    InterstitialPanel::Init();
    OvershellPanel::Init();
    MainHubPanel::Init();
    ManageBandPanel::Init();
    MetaPanel::Register();
    MoviePanel::Init();
}

MetaPanel::MetaPanel()
    : mTour(new Tour(SystemConfig("tour"), TheSongMgr, *TheBandUserMgr, true)),
      mCampaign(new Campaign(SystemConfig("campaign"))),
      mNameGenerator(new NameGenerator(SystemConfig("name_generator"))),
      mMetaMusicMgr(new MetaMusicManager(SystemConfig("synth", "metamusic"))),
      mHAQMgr(new HAQManager()), unk58(0), mMusic(0), mSongPreview(TheSongMgr), unkd4(0) {
    mSongPreview.SetName("song_preview", ObjectDir::Main());
    // MusicLibrary::Init(this + 0x60);
    mRecentIndices.reserve(3);
    for (int i = 0; i < 3; i++)
        mRecentIndices.push_back(-1);
    ThePlatformMgr.AddSink(this, "xmp_state_changed");
    TheBandUI.AddSink(this, "current_screen_changed");
    mHAQMgr->Init();
}

MetaPanel::~MetaPanel() {
    RELEASE(mTour);
    RELEASE(mCampaign);
    RELEASE(mNameGenerator);
    RELEASE(mMetaMusicMgr);
    RELEASE(mHAQMgr);
    TheBandUI.RemoveSink(this, "current_screen_changed");
}