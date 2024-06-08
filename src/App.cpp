#include "App.h"
#include "ChecksumData_wii.h"
#include "game/Game.h"
#include "meta/Achievements.h"
#include "obj/Dir.h"
#include "os/ContentMgr_Wii.h"
#include "os/Debug.h"
#include "os/PlatformMgr.h"
#include "os/System.h"
#include "os/Timer.h"
#include "rndobj/HiResScreen.h"
#include "rndobj/Rnd.h"
#include "synth/Synth.h"
#include "ui/UI.h"
#include "utl/Cheats.h"
#include "utl/MakeString.h"
#include "utl/Rso_Utl.h"
#include "utl/Option.h"
#include <revolution/VI.h>

App::App(int argc, char** argv) {
    Timer init_time; init_time.Start();
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
    TheRnd->SetClearColor(Hmx::Color(1,0,0));
    TheRnd->Init();
    VISetBlack(true);
    VIFlush();
    OptionBool("fast", false);
    ObjDirPtr<ObjectDir> oPtr(0);
}

App::~App() {
    TheDebug.Exit(0, true);
}

#pragma pool_data off // TODO this is wrong, but without it it uses ...bss.0
void App::DrawRegular() {
    if (ThePlatformMgr.mConnected) ThePlatformMgr.Draw(); else {
        TIMER_THING("begin_draw", TheRnd->BeginDrawing())
        TIMER_THING("ui_draw", TheUI->Draw())
        TIMER_THING("platform_draw", ThePlatformMgr.Draw())
        TIMER_THING("end_draw", TheRnd->EndDrawing())
    }
}
#pragma pool_data on

void App::CaptureHiRes() {
    bool notPaused = false;
    if (TheGame && !TheGame->mIsPaused) notPaused = true;
    if (notPaused) TheGame->SetPaused(true, true, true);
    DrawRegular();
    int max = TheHiResScreen->mTiling * TheHiResScreen->mTiling;
    for (int i = 0; i <= max; i++) {
        DrawRegular();
        TheHiResScreen->Accumulate();
    }
    TheHiResScreen->Finish();

    if (notPaused) TheGame->SetPaused(false, true, true);
}

void App::Draw() {
    if (TheHiResScreen->mActive) CaptureHiRes();
    else DrawRegular();
}

void App::Run() { RunWithoutDebugging(); }

void App::RunWithoutDebugging() {
    Timer loop_timer; loop_timer.Restart();
    int frameticker = 0;
    while (true) {
        frameticker++;
        TIMER_THING("poll", ;)
        TIMER_THING("system_poll", SystemPoll(false))
        TIMER_THING("inclusive_ui_poll", {TheAchievements->Poll();})
        TIMER_THING("synth_poll", TheSynth->Poll())
        // net_poll
        TIMER_THING("inclusive_ui_poll", TheUI->Poll())
        Draw();


        loop_timer.Ms();
        loop_timer.Restart();
    }
}
