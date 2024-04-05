#include "App.h"
#include "os/Debug.h"
#include "rndobj/HiResScreen.h"
#include "game/Game.h"

App::~App() {
    TheDebug.Exit(0, true);
}

void App::DrawRegular() {

}

void App::CaptureHiRes() {
    bool x = false;
    if (TheGame && TheGame->mIsPaused) x = true;
    if (x) TheGame->SetPaused(true, true, true);
    DrawRegular();

    if (x) TheGame->SetPaused(false, false, false);
}

void App::Draw() {
    if (TheHiResScreen->mActive) CaptureHiRes();
    else DrawRegular();
}

void App::Run() { RunWithoutDebugging(); }
void App::RunWithoutDebugging() {
    
}
