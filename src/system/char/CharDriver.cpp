#include "char/CharDriver.h"
#include "CharClipDisplay.h"
#include "char/CharBoneDir.h"
#include "char/CharClip.h"
#include "char/CharClipDriver.h"
#include "char/CharClipGroup.h"
#include "char/Char.h"
#include "char/CharPollable.h"
#include "char/CharWeightable.h"
#include "decomp.h"
#include "math/Rand.h"
#include "math/Utl.h"
#include "obj/Data.h"
#include "obj/Msg.h"
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "obj/Task.h"
#include "os/Debug.h"
#include "rndobj/Highlightable.h"

INIT_REVS(CharDriver)

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
    CharClipDisplay::Init(Dir());
    std::vector<CharClipDisplay> displays;
    for(CharClipDriver* it = mFirst; it != nullptr; it = it->Next()){
        displays.push_back(CharClipDisplay());
        displays.back().unk1c = it->mBeat;
        displays.back().SetClip(it->mClip, false);
        displays.back().unk20 = it->mBlendFrac;
    }
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
    bool ret;
    if(mFirst){
        ret = false;
        if(!mFirst->Next() && (mFirst->mPlayFlags & 0xF0) != 0x10) ret = true;
    } else {
        ret = true;
    }
    return ret;
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
        mLastNode = clip;
        if(f1 == -1.0f) f1 = mBlendWidth;
        if(mPlayMultipleClips){
            for(CharClipDriver* it = mFirst; it != nullptr; it = it->Next()){
                if(clip == it->GetClip()) return nullptr;
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
        CharClipGroup* grp = mClips->Find<CharClipGroup>(cc, false);
        if(!grp){
            MILO_WARN("%s could not find group %s", PathName(this), cc);
            return nullptr;
        }
        else return Play(grp->GetClip(), i, f1, f2, f3);
    }
}

void CharDriver::SetStarved(Symbol starved){ mStarvedHandler = starved; }

void CharDriver::SetBeatScale(float beatscale, bool){
    CharClipDriver* playing = FirstPlaying();
    if(playing){
        float oldbeatscale = mBeatScale;
        for(CharClipDriver* d = playing; d != nullptr; d = d->Next()){
            if((playing->mPlayFlags & 0xF600) != 0x200){
                CharClip::SetDefaultBeatAlignModeFlag(d->mPlayFlags, 0);
                d->mTimeScale *= oldbeatscale / beatscale;
            }
        }
    }
    mBeatScale = beatscale;
}

void CharDriver::Poll(){
    float f17 = mBeatScale * TheTaskMgr.Beat();
    float f13 = mBeatScale * TheTaskMgr.DeltaBeat();
    if(mRealign && f17 > 0){
        SongPos& thePos = TheTaskMgr.mSongPos;
        f17 = mBeatScale * ((float)(thePos.GetBeat()) + (float)(thePos.GetTick()) / 480.0f);
        if(mOldBeat == kHugeFloat) mOldBeat = f17;
        if(std::floor(mOldBeat) != std::floor(f17)){
            CharClipDriver* playing = FirstPlaying();
            if(playing){
                int firstFlags = CharClipDriver::GetUpperFlags(playing->mPlayFlags);
                int flags = firstFlags;
                for(CharClipDriver* it = playing->Next(); it != nullptr; it = it->Next()){
                    MaxEq(flags, CharClipDriver::GetUpperFlags(it->mPlayFlags));
                }
                flags--;
                if(flags > 0){
                    int i12 = (int)std::floor(f17) ^ (int)std::floor(mOldBeat) + 1;
                    CharClipDriver* d = playing;
                    if(i12 & flags){
                        while(d){
                            d->mPlayFlags &= 0xffff0fff;
                            d = d->Next();
                        }
                        if(firstFlags - 1 > 0 && (i12 & firstFlags - 1)){
                            Play(playing->GetClip(), 0x38, -1, kHugeFloat, 0);
                        }
                    }
                }
            }
        }
    }
    mOldBeat = f17;
    if(Starved() && !mStarvedHandler.Null()){
        Dir()->Handle(Message(mStarvedHandler), true);
    }
    if(Starved() && mFirst){
        if((mFirst->mPlayFlags & 0xF0) == 0x30){
            int flags = mFirst->mPlayFlags;
            CharClip::SetDefaultBlendFlag(flags, 4);
            Play(mFirst->GetClip(), flags, -1, kHugeFloat, 0);
        }
    }
    if(Starved() && mFirst && (mFirst->mPlayFlags & 0xF0) == 0x40){
        Play(mLastNode, 0x44, -1, kHugeFloat, 0);
    }
    if(Starved() && mDefaultClip && mDefaultPlayStarved){
        Play(DataNode(mDefaultClip), 0x44, -1, kHugeFloat, 0);
    }
    if(mFirst){
        mFirst = mFirst->PreEvaluate(f17, f13, TheTaskMgr.DeltaSeconds());
    }
    if(mFirst){
        float f14 = Weight();
        f13 = mFirst->Evaluate(f17, f13, TheTaskMgr.DeltaSeconds());
        f13 = -(f14 * f13 - 1.0f);
        if(mPlayMultipleClips) f13 = f14;
        if(mBones){
            if(mApply == kApplyBlend || mApply == kApplyBlendWeights){
                if(mInternalBones){
                    mInternalBones->Enter();
                    mFirst->ScaleAdd(*mInternalBones, f14);
                    mInternalBones->Blend(*mBones);
                }
                else {
                    mFirst->GetClip()->ScaleDown(*mBones, f13);
                    mFirst->ScaleAdd(*mBones, f14);
                }
            }
            else if(mApply == kApplyAdd){
                mFirst->ScaleAdd(*mBones, f14);
            }
            else { // kApplyRotateTo
                MILO_ASSERT(mApply == kApplyRotateTo, 0x22F);
                mFirst->RotateTo(*mBones, f14);
            }
        }
    }
}

float CharDriver::EvaluateFlags(int flags){
    float f4 = 1;
    float f3 = 0;
    for(CharClipDriver* it = mFirst; it != nullptr; it = it->Next()){
        float sigmoid = Sigmoid(it->mBlendFrac);
        if(flags & it->GetClip()->Flags()){
            f3 += f4 * sigmoid;
        }
        f4 *= 1.0f - sigmoid;
    }
    return f3;
}

CharClipDriver* CharDriver::Last(){
    CharClipDriver* d = mFirst;
    while(d && d->Next()) d = d->Next();
    return d;
}

CharClipDriver* CharDriver::Before(CharClipDriver* driver){
    CharClipDriver* d = mFirst;
    while(d && d->Next() != driver) d = d->Next();
    return d;
}

CharClipDriver* CharDriver::FirstPlaying(){
    CharClipDriver* d;
    for(d = mFirst; d != nullptr && !d->mBlendFrac; d = d->Next());
    return d;
}

CharClip* CharDriver::FirstClip(){
    if(mFirst) return mFirst->GetClip();
    else return nullptr;
}

CharClip* CharDriver::FirstPlayingClip(){
    CharClipDriver* d = FirstPlaying();
    if(d) return d->GetClip();
    else return nullptr;
}

void CharDriver::Offset(float f1, float f2){
    if(mFirst) mFirst->mBeat += RandomFloat(f1, f2);
}

float CharDriver::TopClipFrame(){
    CharClipDriver* it = mFirst;
    if(!it) return 0;
    else {
        while(it->Next()) it = it->Next();
        if(!it->GetClip()) return 0;
        else {
            float avg = it->GetClip()->AverageBeatsPerSecond();
            float frame = 0;
            if(avg < 0) return frame;
            else frame = (it->mBeat - it->GetClip()->StartBeat()) / avg;
            return frame;
        }
    }
}

void CharDriver::PollDeps(std::list<Hmx::Object*>& changedBy, std::list<Hmx::Object*>& change){
    change.push_back(mBones);
}

void CharDriver::Replace(Hmx::Object* from, Hmx::Object* to){
    RndHighlightable::Replace(from, to);
    CharWeightable::Replace(from, to);
    CharPollable::Replace(from, to);
    if(mFirst) mFirst = mFirst->DeleteClip(from);
}

SAVE_OBJ(CharDriver, 0x2D6);

BEGIN_LOADS(CharDriver)
    LOAD_REVS(bs)
    ASSERT_REVS(0xE, 0)
    LOAD_SUPERCLASS(Hmx::Object)
    LOAD_SUPERCLASS(CharWeightable)
    if(gRev < 3){
        int x; bs >> x;
    }
    bs >> mBones;
    if(gRev < 8){
        FilePath fp;
        bs >> fp;
        if(gRev > 6 && fp.empty()){
            bs >> mClips;
        }
    }
    else bs >> mClips;
    if(gRev > 8) bs >> mBlendWidth;
    if(gRev > 1) bs >> mRealign;
    else mRealign = false;
    if(gRev > 5) bs >> (int&)mApply;
    else if(gRev > 4){
        bool b48; bs >> b48;
        mApply = (ApplyMode)(b48 != false);
    }
    else mApply = kApplyBlend;
    if(gRev > 9) bs >> mClipType;
    if(gRev > 0xC) bs >> mPlayMultipleClips;
    if(gRev <= 9 && mClips){
        mClipType = mClips->Type();
        if(mClipType.Null()){
            for(ObjDirItr<CharClip> it(mClips, true); it != nullptr; ++it){
                mClipType = it->Type();
                break;
            }
        }
    }
    SyncInternalBones();
    if(gRev > 3){
        mTestClip.Load(bs, false, mClips);
    }
    if(gRev > 0xB){
        mDefaultClip.Load(bs, false, mClips);
    }
    if(gRev > 0xD) bs >> mDefaultPlayStarved;
END_LOADS

BEGIN_COPYS(CharDriver)
    COPY_SUPERCLASS(Hmx::Object)
    COPY_SUPERCLASS(CharWeightable)
    CREATE_COPY(CharDriver)
    BEGIN_COPYING_MEMBERS
        mBones = c->GetBones();
        COPY_MEMBER(mClips)
        COPY_MEMBER(mRealign)
        COPY_MEMBER(mBeatScale)
        COPY_MEMBER(mBlendWidth)
        COPY_MEMBER(mTestClip)
        COPY_MEMBER(mClipType)
        COPY_MEMBER(mApply)
        COPY_MEMBER(mDefaultClip)
        COPY_MEMBER(mDefaultPlayStarved)
        COPY_MEMBER(mPlayMultipleClips)
        SyncInternalBones();
    END_COPYING_MEMBERS
END_COPYS