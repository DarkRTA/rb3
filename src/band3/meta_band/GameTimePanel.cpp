#include "meta_band/GameTimePanel.h"
#include "obj/Task.h"
#include "ui/UIPanel.h"
#include "utl/Loader.h"

GameTimePanel::GameTimePanel() : mTempo(0) {

}

void GameTimePanel::Load(){
    UIPanel::Load();
    mPeriod = TheLoadMgr.SetLoaderPeriod(10.0f);
}

void GameTimePanel::Unload(){
    UIPanel::Unload();
    TheLoadMgr.SetLoaderPeriod(mPeriod);
    // TheGamePanel.unk150 = true;
}

void GameTimePanel::Exit(){ UIPanel::Exit(); }

void GameTimePanel::Enter(){
    UIPanel::Enter();
    // TheGamePanel.unk150 = false;
    mTempo = TheTaskMgr.DeltaBeat() / TheTaskMgr.DeltaSeconds();
    mTimer.Restart();
}

void GameTimePanel::Poll(){

}