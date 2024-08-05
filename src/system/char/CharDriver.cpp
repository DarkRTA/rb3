#include "char/CharDriver.h"
#include "char/CharBoneDir.h"
#include "char/CharClip.h"
#include "char/CharClipDriver.h"
#include "char/CharClipGroup.h"
#include "char/Char.h"
#include "os/Debug.h"

CharDriver::CharDriver() : mBones(this, 0), mClips(this, 0), mFirst(0), mTestClip(this, 0), mDefaultClip(this, 0),
    mDefaultPlayStarved(0), mStarvedHandler(), mLastNode(0), mOldBeat(1e+30f), mRealign(0), mBeatScale(1.0f), mBlendWidth(1.0f),
    mClipType(), mApply(kApplyBlend), mInternalBones(0), mPlayMultipleClips(0) {

}

CharDriver::~CharDriver(){
    if(mFirst) mFirst->DeleteStack();
    delete mInternalBones;
}

void CharDriver::Highlight(){
    if(gCharHighlightY == -1.0f) CharDeferHighlight(this);
    else gCharHighlightY = Display(gCharHighlightY);
}

void CharDriver::Enter(){
    Clear();
    mLastNode = DataNode(0);
    mOldBeat = 1e+30f;
    mBeatScale = 1.0f;
    RndPollable::Enter();
    if(mDefaultClip) Play(DataNode(mDefaultClip), 1, -1.0f, 1e+30f, 0.0f);
}

void CharDriver::Exit(){ RndPollable::Exit(); }

void CharDriver::Clear(){
    if(mFirst) mFirst->DeleteStack();
    mFirst = 0;
}

void CharDriver::Transfer(const CharDriver& driver){
    Clear();
    mClips = driver.mClips;
    mLastNode = driver.mLastNode;
    mRealign = driver.mRealign;
    mBeatScale = driver.mBeatScale;
    mBlendWidth = driver.mBlendWidth;
    if(driver.mFirst) mFirst = new CharClipDriver(this, *driver.mFirst);
}

void CharDriver::SetClips(ObjectDir* dir){
    if(dir != mClips){
        mLastNode = DataNode((Hmx::Object*)0);
        mClips = dir;
    }
}

void CharDriver::SetBones(CharBonesObject* obj){
    mBones = obj;
}

void CharDriver::SetApply(ApplyMode mode){
    if(mode != mApply){
        mApply = mode;
        SyncInternalBones();
    }
}

void CharDriver::SetClipType(Symbol ty){
    if(mClipType != ty){
        mClipType = ty;
        SyncInternalBones();
    }
}

void CharDriver::SyncInternalBones(){
    Clear();
    mLastNode = DataNode((Hmx::Object*)0);
    if(mInternalBones && mClipType.Null()){
        delete mInternalBones;
        mInternalBones = 0;
    }
    else if(!mInternalBones && mApply == kApplyBlendWeights && !mClipType.Null()){
        mInternalBones = new CharBonesAlloc();
    }
    if(mInternalBones){
        mInternalBones->ClearBones();
        CharBoneDir::StuffBones(*mInternalBones, mClipType);
    }
}

bool CharDriver::Starved(){
    if(mFirst){
        if(mFirst->mNext) return false;
        if((mFirst->mPlayFlags & 0xF0) == 0x10) return false;
    }
    return true;
}

CharClipDriver* CharDriver::Play(CharClip* clip, int i, float f1, float f2, float f3){
    if(!clip){
        MILO_NOTIFY_ONCE("%s: Could not find clip to play.", PathName(this));
        return 0;
    }
    else {
        mLastNode = DataNode(clip);
        if(f1 == -1.0f) f1 = mBlendWidth;
        if(mPlayMultipleClips){
            for(CharClipDriver* it = mFirst; it != 0; it = it->mNext){
                if(clip == it->mClip) return 0;
            }
        }
        mFirst = new CharClipDriver(this, clip, i, f1, mFirst, f2, f3, mPlayMultipleClips);
        return mFirst;
    }
}

CharClipDriver* CharDriver::Play(const DataNode& node, int i, float f1, float f2, float f3){
    DataNode thisnode(node);
    CharClip* found = FindClip(node, true);
    CharClipDriver* driver = Play(found, i, f1, f2, f3);
    mLastNode = thisnode;
    return driver;
}

CharClipDriver* CharDriver::PlayGroup(const char* cc, int i, float f1, float f2, float f3){
    if(!mClips){
        MILO_WARN("%s has no clips", PathName(this));
        return 0;
    }
    else {
        CharClipGroup* grp = dynamic_cast<CharClipGroup*>(mClips->FindObject(cc, false));
        if(!grp){
            MILO_WARN("%s could not find group %s", PathName(this), cc);
            return 0;
        }
        else return Play(grp->GetClip(), i, f1, f2, f3);
    }
}

void CharDriver::SetStarved(Symbol starved){ mStarvedHandler = starved; }

void CharDriver::PollDeps(std::list<Hmx::Object*>& changedBy, std::list<Hmx::Object*>& change){
    change.push_back(mBones);
}
