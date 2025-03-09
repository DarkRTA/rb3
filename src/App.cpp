#include "App.h"
#include "BudgetScreen.h"
#include "ChecksumData_wii.h"
#include "MSL_Common/null_def.h"
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
#include "meta_band/AssetMgr.h"
#include "meta_band/BandSongMgr.h"
#include "meta_band/CharCache.h"
#include "meta_band/CharSync.h"
#include "meta_band/ClosetMgr.h"
#include "meta_band/ContextChecker.h"
#include "meta_band/LessonMgr.h"
#include "meta_band/MetaPanel.h"
#include "meta_band/PrefabMgr.h"
#include "meta_band/SaveLoadManager.h"
#include "meta_band/TrainingMgr.h"
#include "movie/CustomSplash_Wii.h"
#include "movie/Splash.h"
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
#include "tour/QuestManager.h"
#include "ui/UI.h"
#include "utl/Cheats.h"
#include "utl/Loader.h"
#include "utl/Magnu.h"
#include "utl/MakeString.h"
#include "utl/MemMgr.h"
#include "utl/Rso_Utl.h"
#include "utl/Option.h"
#include <revolution/VI.h>

DECOMP_FORCEACTIVE(App, "_unresolved func.\n")
u64 sNullMicClientID;
ModalCallbackFunc *gRealCallback;

const int initArk = 2;
const int charArk = 5;
const int regularArks = 3;

extern bool gInitComplete;

void AppDebugModal(bool &b, char *abc, bool b2) {
    if (!b) {
        static DataNode &notify_level = DataVariable("notify_level");
        int notif_lvl = notify_level.Int();
        if (notif_lvl == 2) {
            gRealCallback(b, abc, b2);
            return;
        } else if (notif_lvl == 1) {
            Hmx::Object *disp = ObjectDir::Main()->FindObject("cheat_display", false);
            if (disp) {
                static Message show("show_prio", 0, 0);
                show->Node(2) = DataNode(abc);
                show->Node(3) = DataNode(200);
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
    Timer init_time;
    init_time.Start();
    InitMakeString();
    class String s;
    if (argc == 0) {
        s = "band_r_wii.elf";
        argv = &s.mStr;
        argc = 1;
    }
    RsoAddIniter(CntSdRsoInit, CntSdRsoTerminate);
    EnableKeyCheats(false);
    SetFileChecksumData();
    SystemPreInit(argc, argv, "config/band_preinit_keep.dta");
    TheRnd->PreInit();
    TheRnd->SetClearColor(Hmx::Color(1, 0, 0));
    TheRnd->Init();
    VISetBlack(true);
    VIFlush();
    bool fast = OptionBool("fast", false);
    Splash spl;
    if (fast || !UsingCD()) {
        spl.SetWaitForSplash(false);
    }
    if (ThePlatformMgr.GetRegion() == 1) {
        spl.AddScreen("ui/startup/eng/startup_autosave_esrb_keep.milo", 4000);
    } else {
        spl.AddScreen("ui/startup/eng/startup_autosave_keep.milo", 4000);
    }
    spl.AddScreen("ui/startup/startup_mtv_keep.milo", 2000);
    if (spl.unk_0x64 && UsingCD()) {
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
    if (fast || !UsingCD()) {
        csplash.unk_490 = 0;
    }
    csplash.Init();
    csplash.Show();
    SynthInit();
    //	Movie::Init();
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
    MagnuInit();
    if (TheSplasher)
        TheSplasher->Poll();
    if (TheSplasher)
        TheSplasher->Poll();
    static DataNode &notify_level = DataVariable("notify_level");
    notify_level = DataNode(1);
    gRealCallback = TheDebug.SetModalCallback(AppDebugModal);
    BinkReaderHeapInit();
    FixedSizeSaveable::Init(151, 5688);
    BandUserMgrInit();
    if (TheSplasher)
        TheSplasher->Poll();
    // TheNet.Init();
    if (TheSplasher)
        TheSplasher->Poll();
    // TheRockCentral.Init(false);
    if (TheSplasher)
        TheSplasher->Poll();
    // TheEntityUploader->Init();
    if (TheSplasher)
        TheSplasher->Poll();
    GameMicManager::Init();
    UsbMidiKeyboard::Init();
    UsbMidiGuitar::Init();
    if (TheSplasher)
        TheSplasher->Poll();
    {
        ObjDirPtr<ObjectDir> oPtr(0);
        DirLoader *ldr = nullptr;
        FilePath fp(SystemConfig("sound", "banks", "common")->Str(1));
        if (ldr != nullptr && ldr->IsLoaded()) {
            if (ldr != nullptr) {
                TheLoadMgr.PollUntilLoaded(ldr, nullptr);
                ObjectDir *dir = ldr->GetDir();
            }
        }
    }

    SaveLoadManager::Init();
    CharInit();
    if (TheSplasher)
        TheSplasher->Poll();
    // BeatMatchInit();
    if (TheSplasher)
        TheSplasher->Poll();
    // TrackInit();
    if (TheSplasher)
        TheSplasher->Poll();
    // WorldInit();
    if (TheSplasher)
        TheSplasher->Poll();
    BandInit();
    if (TheSplasher)
        TheSplasher->Poll();
    TheSongMgr.Init();
    MetaPanel::Init();
    if (TheSplasher)
        TheSplasher->Poll();
    GameInit();
    if (TheSplasher)
        TheSplasher->Poll();
    // BandOffline::Init()
    if (TheSplasher)
        TheSplasher->Poll();
    BudgetScreen::Register();
    if (TheSplasher)
        TheSplasher->Poll();
    ContextCheckerInit();
    if (TheSplasher)
        TheSplasher->Poll();
    TheSynth->Init();
    if (TheSplasher)
        TheSplasher->Poll();
    CharCache::Init();
    PrefabMgr::Init(nullptr);
    CharSync::Init(nullptr);
    AssetMgr::Init();
    LessonMgr::Init();
    ClosetMgr::Init();
    TrainingMgr::Init();
    PatchDir::Init();
    if (TheSplasher)
        TheSplasher->Poll();
    TheWiiProfileMgr.Init(151, 45);
    TheUI.Init();
    TheCharSync->UpdateCharCache();
    if (TheSplasher)
        TheSplasher->Poll();
    TheQuestMgr.Init(SystemConfig("tour"));
    // InitStoreOverlay();
    if (TheSplasher)
        TheSplasher->Poll();
    if (UsingCD() && NewFile("charnames.zbm", 0x10002) == nullptr) {
        ThePlatformMgr.SetDiskError(kDiskError);
    }
    if (TheArchive != nullptr) {
        TheArchive->SetArchivePermission(1, &charArk);
    }
    TheLoadMgr.PollUntilEmpty();
    float total_time = init_time.SplitMs();
    if (TheArchive != nullptr) {
        TheArchive->SetArchivePermission(7, &regularArks);
        if (Archive::DebugArkOrder()) {
            MILO_LOG("Startup Time: %f %f\n", splasher_time, splasher_time - total_time);
        }
    }
    spl.EndSplasher();
    EnableKeyCheats(true);
    MemSetAllowTemp("main", 0);
    MemPushHeap(MemFindHeap("fast"));
    MemPushHeap(MemFindHeap("main"));
}

App::~App() { TheDebug.Exit(0, true); }

#pragma pool_data off // TODO this is wrong, but without it it uses ...bss.0
void App::DrawRegular() {
    if (ThePlatformMgr.mConnected)
        ThePlatformMgr.Draw();
    else {
        TIMER_ACTION("begin_draw", TheRnd->BeginDrawing())
        TIMER_ACTION("ui_draw", TheUI.Draw())
        TIMER_ACTION("platform_draw", ThePlatformMgr.Draw())
        TIMER_ACTION("end_draw", TheRnd->EndDrawing())
    }
}
#pragma pool_data on

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
        TIMER_ACTION("inclusive_ui_poll", { TheAchievements->Poll(); })
        TIMER_ACTION("synth_poll", TheSynth->Poll())
        // net_poll
        TIMER_ACTION("inclusive_ui_poll", TheUI.Poll())
        Draw();

        loop_timer.Ms();
        loop_timer.Restart();
    }
}
