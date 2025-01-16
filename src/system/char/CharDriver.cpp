#include "char/CharDriver.h"
#include "char/CharBoneDir.h"
#include "char/CharClip.h"
#include "char/CharClipDriver.h"
#include "char/CharClipGroup.h"
#include "char/Char.h"
#include "decomp.h"
#include "math/Utl.h"
#include "obj/Data.h"
#include "os/Debug.h"

DECOMP_FORCEACTIVE(CharDriver, "%s %s, beat: %.2f")

CharDriver::CharDriver() : mBones(this), mClips(this), mFirst(0), mTestClip(this), mDefaultClip(this),
    mDefaultPlayStarved(0), mStarvedHandler(), mLastNode(0), mOldBeat(kHugeFloat), mRealign(0), mBeatScale(1.0f), mBlendWidth(1.0f),
    mClipType(), mApply(kApplyBlend), mInternalBones(0), mPlayMultipleClips(0) {

}

CharDriver::~CharDriver(){
    if(mFirst) mFirst->DeleteStack();
    delete mInternalBones;
}

void CharDriver::Highlight(){
#ifdef MILO_DEBUG
    if(gCharHighlightY == -1.0f) CharDeferHighlight(this);
    else gCharHighlightY = Display(gCharHighlightY);
#endif
}

float CharDriver::Display(float f){
    MakeString("%d");
    MakeString("debug_draw");
}

void CharDriver::Enter(){
    Clear();
    mLastNode = 0;
    mOldBeat = kHugeFloat;
    mBeatScale = 1.0f;
    RndPollable::Enter();
    if(mDefaultClip) Play(DataNode(mDefaultClip), 1, -1.0f, kHugeFloat, 0.0f);
}

void CharDriver::Exit(){ RndPollable::Exit(); }

void CharDriver::Clear(){
    if(mFirst) mFirst->DeleteStack();
    mFirst = nullptr;
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
        mLastNode = NULL_OBJ;
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
    mLastNode = NULL_OBJ;
    if(mInternalBones && mClipType.Null()){
        RELEASE(mInternalBones);
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
        if(mFirst->Next()) return false;
        if((mFirst->mPlayFlags & 0xF0) == 0x10) return false;
    }
    return true;
}

CharClip* MyFindClip(const DataNode& n, ObjectDir* dir){
    DataNode& node = n.Evaluate();
    Hmx::Object* obj;
    if(node.Type() == kDataObject){
        obj = node.mValue.object;
    }
    else {
        MILO_ASSERT(node.Type() == kDataSymbol || node.Type() == kDataString, 0x12A);
        obj = dir->FindObject(node.LiteralStr(), false);
    }
    if(!obj) return nullptr;
    else {
        CharClip* clip = dynamic_cast<CharClip*>(obj);
        if(clip) return clip;
        else {
            CharClipGroup* group = dynamic_cast<CharClipGroup*>(obj);
            if(!group){
                MILO_NOTIFY_ONCE("%s: MyFindClip %s bad object type, not CharClip or CharClipGroup", PathName(dir), PathName(obj));
                clip = nullptr;
            }
            else clip = group->GetClip();
        }
        return clip;
    }
}

CharClip* CharDriver::FindClip(const DataNode& node, bool warn){
    if(!mClips){
        MILO_FAIL("%s: trying to FindClip with no mClips", PathName(this));
    }
    CharClip* clip = MyFindClip(node, mClips);
    if(!clip && warn){
        String str;
        str << node;
        MILO_NOTIFY_ONCE("%s: missing \"%s\" in %s", PathName(this), str, mClips->Name());
    }
    return clip;
}

CharClipDriver* CharDriver::Play(CharClip* clip, int i, float f1, float f2, float f3){
    if(!clip){
        MILO_NOTIFY_ONCE("%s: Could not find clip to play.", PathName(this));
        return nullptr;
    }
    else {
        mLastNode = DataNode(clip);
        if(f1 == -1.0f) f1 = mBlendWidth;
        if(mPlayMultipleClips){
            for(CharClipDriver* it = mFirst; it != nullptr; it = it->mNext){
                if(clip == it->mClip) return nullptr;
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
        return nullptr;
    }
    else {
        CharClipGroup* grp = dynamic_cast<CharClipGroup*>(mClips->FindObject(cc, false));
        if(!grp){
            MILO_WARN("%s could not find group %s", PathName(this), cc);
            return nullptr;
        }
        else return Play(grp->GetClip(), i, f1, f2, f3);
    }
}

void CharDriver::SetStarved(Symbol starved){ mStarvedHandler = starved; }

CharClipDriver* CharDriver::FirstPlaying(){
    CharClipDriver* d;
    for(d = mFirst; d != nullptr && !d->mBlendFrac; d = d->Next());
    return d;
}

void CharDriver::PollDeps(std::list<Hmx::Object*>& changedBy, std::list<Hmx::Object*>& change){
    change.push_back(mBones);
}
