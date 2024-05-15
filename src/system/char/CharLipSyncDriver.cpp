#include "char/CharLipSyncDriver.h"

CharLipSyncDriver::CharLipSyncDriver() : mLipSync(this, 0), mClips(this, 0), mBlinkClip(this, 0), mSongOwner(this, 0), mSongOffset(0.0f),
    mLoop(0), mSongPlayer(0), mBones(this, 0), mTestClip(this, 0), mTestWeight(1.0f), mOverrideClip(this, 0), mOverrideWeight(0.0f),
    mOverrideOptions(this, 0), mApplyOverrideAdditively(0), mAlternateDriver(this, 0) {

}

CharLipSyncDriver::~CharLipSyncDriver(){

}

void CharLipSyncDriver::PollDeps(std::list<Hmx::Object*>& changedBy, std::list<Hmx::Object*>& change){
    change.push_back(mBones);
}

SAVE_OBJ(CharLipSyncDriver, 0x111)