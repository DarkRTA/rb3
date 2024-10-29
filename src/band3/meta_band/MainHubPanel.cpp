#include "meta_band/MainHubPanel.h"
#include "meta_band/LockStepMgr.h"
#include "meta_band/SessionMgr.h"
#include "meta_band/MainHubMessageProvider.h"

MainHubPanel::MainHubPanel() : mHubState(kMainHubState_Main), mHubOverride(kMainHubOverride_None), mMessageProvider(0), mCurrentMessage(0), mMessageRotationMs(3000.0f), unkb8(0), unkbc(0), unkc0(10) {
    mMachineMgr = TheSessionMgr->mMachineMgr;
    mWaitingStateLock = new LockStepMgr("main_hub_waiting", this);
}

MainHubPanel::~MainHubPanel(){
    delete mMessageProvider;
    delete mWaitingStateLock;
}