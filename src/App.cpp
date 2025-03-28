#include "App.h"
#include "BudgetScreen.h"
#include "ChecksumData_wii.h"
#include "MSL_Common/null_def.h"
#include "beatmatch/BeatMatch.h"
#include "bandobj/Band.h"
#include "bandobj/PatchDir.h"
#include "char/Char.h"
#include "decomp.h"
#include "game/BandUserMgr.h"
#include "game/Game.h"
#include "game/GameMicManager.h"
#include "meta/Achievements.h"
#include "meta/FixedSizeSaveable.h"
#include "meta/WiiProfileMgr.h"
#include "meta_band/AccomplishmentManager.h"
#include "meta_band/AssetMgr.h"
#include "meta_band/BandSongMgr.h"
#include "meta_band/CharCache.h"
#include "meta_band/CharSync.h"
#include "meta_band/ClosetMgr.h"
#include "meta_band/ContextChecker.h"
#include "meta_band/LessonMgr.h"
#include "meta_band/MetaPanel.h"
#include "meta_band/MusicLibrary.h"
#include "meta_band/PrefabMgr.h"
#include "meta_band/ProfileMgr.h"
#include "meta_band/SaveLoadManager.h"
#include "meta_band/TrainingMgr.h"
#include "meta_band/UIStats.h"
#include "movie/CustomSplash_Wii.h"
#include "movie/Splash.h"
#include "net/Net.h"
#include "net_band/EntityUploader.h"
#include "net_band/RockCentral.h"
#include "obj/Data.h"
#include "obj/Dir.h"
#include "obj/Object.h"
#include "os/Archive.h"
#include "os/ContentMgr_Wii.h"
#include "os/Debug.h"
#include "os/PlatformMgr.h"
#include "os/System.h"
#include "os/Timer.h"
#include "os/UsbMidiGuitar.h"
#include "os/UsbMidiKeyboard.h"
#include "revolution/os/OSError.h"
#include "rndobj/HiResScreen.h"
#include "rndobj/Rnd.h"
#include "rndwii/Rnd.h"
#include "synth/BinkReader.h"
#include "synth/Synth.h"
#include "band3/tour/QuestManager.h"
#include "track/Track.h"
#include "ui/UI.h"
#include "ui/UIList.h"
#include "utl/Cheats.h"
#include "utl/Loader.h"
#include "utl/Magnu.h"
#include "utl/MakeString.h"
#include "utl/MemMgr.h"
#include "utl/Rso_Utl.h"
#include "utl/Option.h"
#include "world/World.h"
#include <revolution/VI.h>

#ifdef VERSION_SZBE69_B8
DECOMP_FORCEACTIVE(App, "_unresolved func.\n")
#endif
u64 sNullMicClientID;
ModalCallbackFunc *gRealCallback;

const int initArk = 2;
const int charArk = 5;
const int regularArks = 3;

extern bool gInitComplete;

#ifdef VERSION_SZBE69
#pragma push
#pragma dont_inline on
#endif
void AppDebugModal(bool &b, char *abc, bool b2) {
    if (!b) {
        static DataNode &notify_level = DataVariable("notify_level");
        int notif_lvl = notify_level.Int();
        if (notif_lvl == 2) {
            gRealCallback(b, abc, b2);
            return;
        } else if (notif_lvl == 1) {
            Hmx::Object *disp = ObjectDir::sMainDir->FindObject("cheat_display", false);
            if (disp) {
                static Message show("show_prio", 0, 0);
                show[0] = DataNode(abc);
                show[1] = DataNode(200);
                disp->Handle(show, 0);
            } else
                goto asdf;
        } else {
        asdf:
            MILO_LOG("%s\n", abc);
        }
    } else
        gRealCallback(b, abc, b2);
}

App::App(int argc, char **argv) {
    static const int kESRBMs = 4000;
    static const int kRegularSplashMs = 4000;
    Timer init_time;
    init_time.Start();
    InitMakeString();
    class String s;
    if (argc == 0) {
#ifdef MILO_DEBUG
        s = "band_r_wii.elf";
#else
        s = "band_s_wii.elf";
#endif
        const char *c = s.c_str();
        argv = const_cast<char **>(&c);
        argc = 1;
    }
    RsoAddIniter(CntSdRsoInit, CntSdRsoTerminate);
    EnableKeyCheats(false);
    SetFileChecksumData();
    SystemPreInit(argc, argv, "config/band_preinit_keep.dta");
    TheRnd->PreInit();
    ThePlatformMgr.mDiscErrorMgr->mActive = true;
#ifdef MILO_DEBUG
    TheRnd->SetClearColor(Hmx::Color(1, 0, 0));
#else
    TheRnd->SetClearColor(Hmx::Color(0, 0, 0));
#endif
    TheRnd->Init();
    VISetBlack(true);
    VIFlush();
    bool fast = OptionBool("fast", false);
    Splash spl;
#ifdef MILO_DEBUG
    if (fast || !UsingCD()) {
#else
    if (fast) {
#endif
        spl.SetWaitForSplash(false);
    }
    if (ThePlatformMgr.GetRegion() == 1) {
        spl.AddScreen("ui/startup/eng/startup_autosave_esrb_keep.milo", kRegularSplashMs);
    } else {
        spl.AddScreen("ui/startup/eng/startup_autosave_keep.milo", kRegularSplashMs);
    }
    spl.AddScreen("ui/startup/startup_mtv_keep.milo", 2000);
#ifdef VERSION_SZBE69_B8
    if (spl.Unk64() && UsingCD()) {
#else
    if (spl.Unk64()) {
#endif
        if (TheRnd->GetAspect() == Rnd::kWidescreen) {
            spl.AddScreen("ui/startup/startup_movie_keep_wide.milo", 2000);
        } else {
            spl.AddScreen("ui/startup/startup_movie_keep.milo", 2000);
        }
    } else {
        spl.AddScreen("ui/startup/startup_harmonix_keep.milo", 2000);
    }
    spl.AddScreen("ui/startup/startup_ea_keep.milo", 2000);
    spl.PrepareNext();

    gInitComplete = false;

    CustomSplash csplash;
#ifdef VERSION_SZBE69_B8
    if (fast || !UsingCD()) {
#else
    if (fast) {
#endif
        csplash.SetUnk490(0);
    }
    csplash.Init();
    csplash.Show();
    SynthInit();
    Movie::Init();
    csplash.EndShow();
    gInitComplete = true;
    TheRnd->BeginDrawing();
    TheRnd->EndDrawing();
    spl.BeginSplasher();
    float splasher_time = init_time.SplitMs();
    if (TheArchive != nullptr) {
        TheArchive->SetArchivePermission(1, &initArk);
    }
    spl.PrepareRemaining();
    SystemInit("config/band_keep.dta");
#ifdef MILO_DEBUG
    MagnuInit();
#endif
    PollTheSplasher();
    PollTheSplasher();
    static DataNode &notify_level = DataVariable("notify_level");
    notify_level = DataNode(1);
    gRealCallback = TheDebug.SetModalCallback(AppDebugModal);
    BinkReaderHeapInit();
    FixedSizeSaveable::Init(151, 5688);
    BandUserMgrInit();
    PollTheSplasher();
    TheNet.Init();
    PollTheSplasher();
    TheRockCentral.Init(false);
    PollTheSplasher();
    TheEntityUploader.Init();
    PollTheSplasher();
    GameMicManager::Init();
    UsbMidiKeyboard::Init();
    UsbMidiGuitar::Init();
    PollTheSplasher();
    {
        ObjDirPtr<ObjectDir> oPtr;
        Loader *ldr = nullptr;
        oPtr.LoadFile(
            SystemConfig("sound", "banks", "common")->Str(1), 0, 1, kLoadFront, 0
        );
        TheSynth->SetUnk40(oPtr.Ptr());
        PollTheSplasher();
    }

    SaveLoadManager::Init();
    CharInit();
    PollTheSplasher();
    BeatMatchInit();
    PollTheSplasher();
    TrackInit();
    PollTheSplasher();
    WorldInit();
    PollTheSplasher();
    BandInit();
    PollTheSplasher();
    TheSongMgr.Init();
    MetaPanel::Init();
    PollTheSplasher();
    GameInit();
    PollTheSplasher();
#ifdef MILO_DEBUG
    // BandOffline::Init()
    PollTheSplasher();
    BudgetScreen::Register();
    PollTheSplasher();
#endif
    ContextCheckerInit();
    PollTheSplasher();
    TheSynth->SetDolby(0, 1);
    PollTheSplasher();
    CharCache::Init();
    PrefabMgr::Init(nullptr);
    CharSync::Init(nullptr);
    AssetMgr::Init();
    LessonMgr::Init();
    ClosetMgr::Init();
    TrainingMgr::Init();
    PatchDir::Init();
    PollTheSplasher();
    TheWiiProfileMgr.Init(151, 45);
    TheUI.Init();
    TheCharSync->UpdateCharCache();
    PollTheSplasher();
    TheQuestMgr.Init(SystemConfig("tour"));
    // InitStoreOverlay();
    PollTheSplasher();
#ifdef VERSION_SZBE69_B8
    if (UsingCD())
#endif
        if (NewFile("charnames.zbm", 0x10002) == nullptr) {
            ThePlatformMgr.SetDiskError(kDiskError);
        }
    if (TheArchive != nullptr) {
        TheArchive->SetArchivePermission(1, &charArk);
    }
    TheLoadMgr.PollUntilEmpty();
    float total_time = init_time.SplitMs();
    if (TheArchive != nullptr) {
        TheArchive->SetArchivePermission(7, &regularArks);
#ifdef MILO_DEBUG
        if (Archive::DebugArkOrder()) {
            MILO_LOG("Startup Time: %f %f\n", splasher_time, splasher_time - total_time);
        }
#else
        Archive::DebugArkOrder();
#endif
    }
    spl.EndSplasher();
    EnableKeyCheats(true);
    AutoGlitchReport::EnableCallback();
    MemSetAllowTemp("main", 0);
    MemPushHeap(MemFindHeap("fast"));
    MemPushHeap(MemFindHeap("main"));
    gGCNewLists = false;
    // gFrameMissThreshold = 166;
}
#ifdef VERSION_SZBE69
#pragma pop
#endif

App::~App() { TheDebug.Exit(0, true); }

void App::DrawRegular() {
    if (ThePlatformMgr.mHomeMenuWii->mHomeMenuActive)
        ThePlatformMgr.Draw();
    else {
        TIMER_ACTION("begin_draw", TheRnd->BeginDrawing())
        TIMER_ACTION("ui_draw", TheUI.Draw())
        TIMER_ACTION("platform_draw", ThePlatformMgr.Draw())
        TIMER_ACTION("end_draw", TheRnd->EndDrawing())
    }
}

void App::CaptureHiRes() {
    bool notPaused = false;
    if (TheGame && !TheGame->mIsPaused)
        notPaused = true;
    if (notPaused)
        TheGame->SetPaused(true, true, true);
    DrawRegular();
    int max = TheHiResScreen.mTiling * TheHiResScreen.mTiling;
    for (int i = 0; i <= max; i++) {
        DrawRegular();
        TheHiResScreen.Accumulate();
    }
    TheHiResScreen.Finish();

    if (notPaused)
        TheGame->SetPaused(false, true, true);
}

void App::Draw() {
    if (TheHiResScreen.mActive)
        CaptureHiRes();
    else
        DrawRegular();
}

void PollTriFrame(float, float) {
    static DataNode &venue_test = DataVariable("venue_test");
}

void App::Run() { RunWithoutDebugging(); }

void App::RunWithoutDebugging() {
    Timer loop_timer;
    loop_timer.Restart();
    int frameticker = 0;
    while (true) {
        {
            OSReport("checking consistency %d...\n");
            // MemCheckConsistency(__FILE__, 864);
        }
        frameticker++;
        SetGPHangDetectEnabled(false, __FUNCTION__);
        TIMER_ACTION("poll", ;)
        TIMER_ACTION("system_poll", SystemPoll(false))
        TIMER_ACTION("inclusive_ui_poll", {
            TheAchievements->Poll();
            TheUIStats->Poll();
            TheAccomplishmentMgr->Poll();
            PrefabMgr::GetPrefabMgr()->Poll();
            TheSaveLoadMgr->Poll();
            TheProfileMgr.Poll();
            TheMusicLibrary->Poll();
        })
        TIMER_ACTION("synth_poll", TheSynth->Poll())
        TIMER_ACTION("net_poll", {
            TheNet.Poll();
            TheRockCentral.Poll();
            TheEntityUploader.Poll();
        })
        TIMER_ACTION("inclusive_ui_poll", TheUI.Poll())
        TheTaskMgr.Poll();
        SetGPHangDetectEnabled(1, __FUNCTION__);
        Draw();

        float f = loop_timer.SplitMs();
        loop_timer.Restart();
        PollTriFrame(0, f);
    }
}
