#include "bandobj/BandCamShot.h"
#include "char/Character.h"
#include "char/CharDriver.h"
#include "decomp.h"
#include "obj/Msg.h"
#include "obj/ObjMacros.h"
#include "obj/Task.h"
#include "obj/Utl.h"
#include "os/Debug.h"
#include "rndobj/Anim.h"
#include "rndobj/EventTrigger.h"
#include "rndobj/Rnd.h"
#include "rndobj/Trans.h"
#include "utl/Std.h"
#include "world/EventAnim.h"
#include "utl/Symbols.h"
#include "utl/Messages.h"
#include <cfloat>

INIT_REVS(BandCamShot)

std::list<BandCamShot::TargetCache> BandCamShot::sCache;
BandCamShot *gBandCamShotOwner;

std::list<BandCamShot::TargetCache>::iterator BandCamShot::CreateTargetCache(Symbol s) {
    sCache.push_front(TargetCache());
    sCache.front().unk0 = s;
    sCache.front().unk4 = FindTarget(s, true);
    return sCache.begin();
}

std::list<BandCamShot::TargetCache>::iterator BandCamShot::GetTargetCache(Symbol s) {
    FOREACH (it, sCache) {
        if (s == it->unk0)
            return it;
    }
    if (!LOADMGR_EDITMODE) {
        MILO_WARN(
            "%s creating target cache for %s, targets changed while playing camera",
            PathName(this),
            s
        );
    }
    return CreateTargetCache(s);
}

void BandCamShot::DeleteTargetCache(std::list<TargetCache>::iterator it) {
    sCache.erase(it);
}

BandCamShot::BandCamShot()
    : mTargets(this), mMinTime(0), mMaxTime(0), mZeroTime(0), mNextShots(this),
      mCurShot(this), unk15c(0), unk160(0), unk164(0), unk168(0), unk169(0), unk16a(0),
      mAnimsDuringNextShots(0) {
    SetNear(10.0f);
    SetFar(10000.0f);
    mShotIter = mNextShots.end();
}

RndTransformable *BandCamShot::FindTarget(Symbol s, bool b) {
    static Message msg("find_target", 0, 1);
    msg[0] = s;
    msg[1] = b;
    DataNode handled = HandleType(msg);
    RndTransformable *ret = 0;
    if (handled.Type() != kDataUnhandled) {
        ret = handled.Obj<RndTransformable>();
    }
    if (!ret) {
        if (Dir())
            ret = Dir()->Find<RndTransformable>(s.Str(), false);
    }
    return ret;
}

DECOMP_FORCEACTIVE(BandCamShot, "ObjPtr_p.h", "f.Owner()", "")

BinStream &operator>>(BinStream &bs, BandCamShot::Target &tgt) {
    bs >> tgt.mTarget;
    if (BandCamShot::gRev > 0xA) {
        char b;
        bs >> b;
        tgt.mTeleport = b;
    } else {
        tgt.mTeleport = true;
    }
    bs >> tgt.mXfm;
    if (BandCamShot::gRev == 0) {
        Transform tf;
        bs >> tf;
    }
    bs >> tgt.mAnimGroup;
    char ret;
    bs >> ret;
    tgt.mReturn = ret;
    if (BandCamShot::gRev > 2) {
        if (BandCamShot::gRev < 0x1D) {
            bool b;
            int i;
            bs >> b;
            bs >> i;
        }
        if (BandCamShot::gRev < 0xC) {
            int i;
            bs >> i;
        }
    }
    if (BandCamShot::gRev > 3)
        bs >> tgt.mFastForward;
    else
        tgt.mFastForward = 0;
    if (BandCamShot::gRev > 0xA)
        bs >> tgt.mForwardEvent;
    else
        tgt.mForwardEvent = Symbol();
    if (BandCamShot::gRev > 5) {
        char b;
        bs >> b;
        tgt.mSelfShadow = b;
    } else
        tgt.mSelfShadow = 1;
    if (BandCamShot::gRev > 6) {
        char b;
        bs >> b;
        tgt.unk1 = b;
        char b2;
        bs >> b2;
        tgt.unk2 = b2;
        if (BandCamShot::gRev > 0x1F) {
            char bhide;
            bs >> bhide;
            tgt.mHide = bhide;
        } else
            tgt.mHide = 0;
    } else {
        tgt.unk1 = 0;
        tgt.unk2 = 1;
    }
    if (BandCamShot::gRev >= 8 && BandCamShot::gRev <= 28) {
        Symbol s;
        bs >> s;
        bs >> s;
        if (BandCamShot::gRev > 8) {
            bs >> s;
            bs >> s;
        }
    }
    if (BandCamShot::gRev > 9)
        bs >> tgt.mEnvOverride;
    if (BandCamShot::gRev >= 17 && BandCamShot::gRev <= 28) {
        bool b;
        bs >> b;
    }
    if (BandCamShot::gRev > 0x14) {
        if (BandCamShot::gRev < 0x1E) {
            int b;
            bs >> b;
            tgt.mForceLod = b;
        } else {
            char b;
            bs >> b;
            tgt.mForceLod = b;
        }
        if (BandCamShot::gRev < 0x19) {
            if (tgt.mForceLod <= 0) {
                tgt.mForceLod = -1;
            }
        }
        if (BandCamShot::gRev < 0x1B && tgt.mForceLod < 0) {
            tgt.mForceLod = -1;
        }
    }
    if (BandCamShot::gRev >= 22 && BandCamShot::gRev <= 28) {
        String s48;
        int i;
        bs >> s48;
        bs >> s48;
        bs >> i;
        bs >> i;
        if (BandCamShot::gRev > 0x17) {
            bs >> i;
            bs >> i;
            bs >> i;
        }
    }
    return bs;
}

SAVE_OBJ(BandCamShot, 0x14A)

BinStream &operator>>(BinStream &bs, OldTrigger &o) {
    bs >> o.frame;
    bs >> o.trigger;
    return bs;
}

EventAnim *MakeEventAnim(BandCamShot *shot) {
    EventAnim *anim = Hmx::Object::New<EventAnim>();
    anim->SetName(
        MakeString("%s_trigs.evntanm", FileGetBase(shot->Name(), 0)), shot->Dir()
    );
    return anim;
}

BEGIN_LOADS(BandCamShot)
    LOAD_REVS(bs)
    ASSERT_REVS(0x20, 0)
    if (gRev > 4)
        LOAD_SUPERCLASS(CamShot)
    bs >> mTargets;
    if (BandCamShot::gRev >= 2 && BandCamShot::gRev <= 18) {
        ObjPtr<BandCamShot> shotPtr(this);
        bs >> shotPtr;
        if (shotPtr)
            mNextShots.push_back(shotPtr);
    }
    if (gRev > 3)
        bs >> mZeroTime;
    if (gRev <= 4)
        LOAD_SUPERCLASS(CamShot)
    if (gRev == 0xD) {
        bool b;
        bs >> b;
        mPS3PerPixel = b;
    }
    EventAnim *anim = nullptr;
    if (gRev >= 15 && gRev <= 28) {
        std::vector<OldTrigger> trigs;
        bs >> trigs;
        if (trigs.size() != 0) {
            anim = MakeEventAnim(this);
            ObjList<EventAnim::KeyFrame> &keys = anim->mKeys;
            for (int i = 0; i < trigs.size(); i++) {
                ObjList<EventAnim::EventCall> *calls;
                if (trigs[i].frame == 0) {
                    calls = &anim->mStart;
                } else {
                    keys.push_back();
                    keys.back().mTime = trigs[i].frame;
                    calls = &keys.back().mCalls;
                }
                calls->push_back();
                calls->back().mDir = Dir();
                calls->back().mEvent =
                    Dir()->Find<EventTrigger>(trigs[i].trigger.mStr, false);
            }
        }
    }
    if (gRev >= 16 && gRev <= 28) {
        ObjPtr<EventTrigger> trig1(this);
        ObjPtr<EventTrigger> trig2(this);
        bs >> trig1;
        bs >> trig2;
        if (trig1 || trig2) {
            if (!anim)
                anim = MakeEventAnim(this);
            if (trig1) {
                ObjList<EventAnim::EventCall> &start = anim->mStart;
                start.push_back();
                anim->mStart.back().mDir = trig1->Dir();
                anim->mStart.back().mEvent = trig1;
            }
            if (trig2) {
                ObjList<EventAnim::EventCall> &end = anim->mEnd;
                end.push_back();
                anim->mEnd.back().mDir = trig2->Dir();
                anim->mEnd.back().mEvent = trig2;
            }
        }
    }
    if (gRev > 0x11) {
        bs >> mMinTime;
        bs >> mMaxTime;
    }
    if (gRev > 0x12)
        bs >> mNextShots;
    if (gRev >= 20 && gRev <= 30) {
        int i;
        bs >> i;
    }
    if (gRev >= 23 && gRev <= 28) {
        bool reset;
        bs >> reset;
        if (anim)
            anim->SetResetStart(reset);
    }
    if (gRev == 0x1C)
        bs >> mAnims;
    if (anim)
        mAnims.push_back(anim);
    ResetNextShot();
END_LOADS

BEGIN_COPYS(BandCamShot)
    COPY_SUPERCLASS(CamShot)
    CREATE_COPY(BandCamShot)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mTargets)
        COPY_MEMBER(mZeroTime)
        COPY_MEMBER(mMinTime)
        COPY_MEMBER(mMaxTime)
        COPY_MEMBER(mNextShots)
        ResetNextShot();
    END_COPYING_MEMBERS
END_COPYS

void BandCamShot::TeleportTarget(
    RndTransformable *t, const TransformNoScale &tns, bool b3
) {
    t->SetLocalXfm(tns);
    Character *charObj = dynamic_cast<Character *>(t);
    if (charObj) {
        charObj->SetTeleported(true);
        static Message msg("teleport_char", 0, 0);
        msg[0] = t;
        msg[1] = b3;
        HandleType(msg);
    }
}

void BandCamShot::StartAnim() {
    if (mCurShot && mCurShot != this) {
        mCurShot->EndAnim();
    }
    ResetNextShot();
    CamShot::StartAnim();
    int numChars = 0;
    Character *chars[32];
    FOREACH (it, mTargets) {
        if (!it->mTarget.Null()) {
            Target &cur = *it;
            std::list<BandCamShot::TargetCache>::iterator cache =
                CreateTargetCache(cur.mTarget);
            if (cache->unk4) {
                cache->unkc.Set(cache->unk4->mLocalXfm);
                if (cur.mTeleport != 0) {
                    TeleportTarget(cache->unk4, cur.mXfm, false);
                }
            }
            Character *charObj = dynamic_cast<Character *>(cache->unk4);
            if (charObj) {
                MILO_ASSERT(numChars < 32, 0x231);
                chars[numChars] = charObj;
                numChars++;
                charObj->mSelfShadow = cur.mSelfShadow;
                charObj->SetMinLod(cur.mForceLod);
                charObj->SetShowing(!cur.mHide);
                static Message msg("play_group", 0, 0, 0, 0, 0);
                msg[0] = charObj;
                msg[1] = cur.mAnimGroup;
                msg[2] = cur.mFastForward / FramesPerUnit();
                msg[3] = Units();
                msg[4] = cur.mForwardEvent;
                HandleType(msg);
                if (cur.mEnvOverride) {
                    cache->unk8 = charObj->GetEnv();
                    charObj->SetEnv(cur.mEnvOverride);
                }
            }
        }
    }
    unk164 = GetTotalDuration();
    DoHide();
    if (!sHideAllCharactersHack) {
        int showing = 0;
        for (int i = 0; i < numChars; i++) {
            showing |= chars[i]->Showing();
        }
        if (numChars != 0 && showing == 0 && TheRnd->InGame()) {
            for (int i = 0; i < numChars; i++) {
                chars[i]->SetShowing(true);
            }
        }
    } else {
        for (int i = 0; i < numChars; i++) {
            chars[i]->SetShowing(false);
        }
    }
}

bool BandCamShot::IterateNextShot() {
    bool ret = true;
    MILO_ASSERT(!mNextShots.empty(), 0x278);
    if (mShotIter == mNextShots.end()) {
        mShotIter = mNextShots.begin();
    } else {
        ObjPtrList<BandCamShot>::iterator curItr = mShotIter;
        ++mShotIter;
        if (mShotIter == mNextShots.end()) {
            ret = false;
            mShotIter = curItr;
        }
    }
    return ret;
}

void BandCamShot::ResetNextShot() {
    mShotIter = mNextShots.end();
    mCurShot = this;
    unk15c = 0;
    unk160 = 0;
}

void BandCamShot::SetPreFrame(float f1, float f2) {
    unk16a = true;
    if (ShouldSetNextShot(f1)) {
        if (mCurShot != this)
            mCurShot->ResetNextShot();
    } else {
        float sub = f1 - Duration();
        while (sub < unk15c && mShotIter != mNextShots.begin()) {
            ++mShotIter;
            unk160 = (*mShotIter)->GetTotalDuration();
            unk15c -= unk160;
            mCurShot = *mShotIter;
        }
        f1 = sub - unk15c;
        while (f1 >= unk160) {
            if (IterateNextShot()) {
                f1 -= unk160;
                unk15c += unk160;
                if (mCurShot)
                    mCurShot->EndAnim();
                mCurShot = *mShotIter;
                mCurShot->StartAnim();
                unk160 = (*mShotIter)->GetTotalDuration();
            } else
                unk160 = FLT_MAX;
        }
    }
    if (mCurShot != this) {
        mCurShot->SetPreFrame(f1, 1);
    }
}

void BandCamShot::SetFrame(float frame, float blend) {
    if (!unk16a) {
        SetPreFrame(frame, blend);
    }
    float f4 = frame;
    if (!ShouldSetNextShot(frame)) {
        f4 = frame - (unk15c + Duration());
    }
    if (CheckShotOver(frame)) {
        SetShotOver();
    }
    if (this == mCurShot) {
        AnimateShot(f4, blend);
    } else {
        if (mAnimsDuringNextShots) {
            FOREACH (it, mAnims) {
                (*it)->SetFrame(frame, 1);
            }
        }
        mCurShot->SetFrameEx(f4, blend);
        RndAnimatable::SetFrame(frame, blend);
    }
    unk16a = false;
}

void BandCamShot::SetFrameEx(float frame, float blend) {
    unk168 = true;
    SetFrame(frame, blend);
    unk168 = false;
}

void BandCamShot::AnimateShot(float frame, float blend) {
    FOREACH (it, mTargets) {
    }
    CamShot::SetFrame(frame, blend);
}

void BandCamShot::EndAnim() {
    if (mCurShot && mCurShot != this) {
        mCurShot->EndAnim();
        ResetNextShot();
    } else {
        FOREACH (it, mTargets) {
            if (!(*it).mTarget.Null()) {
                Target &cur = *it;
                std::list<BandCamShot::TargetCache>::iterator cache =
                    GetTargetCache(cur.mTarget);
                if (cur.mTeleport && cur.mReturn && cache->unk4) {
                    TeleportTarget(cache->unk4, cache->unkc, true);
                }
                Character *charObj = dynamic_cast<Character *>(cache->unk4);
                if (charObj) {
                    charObj->SetMinLod(-1);
                    charObj->SetSelfShadow(true);
                    charObj->SetShowing(true);
                    if (cur.mEnvOverride) {
                        charObj->SetEnv(cache->unk8);
                    }
                }
                DeleteTargetCache(cache);
            }
        }
        CamShot::EndAnim();
    }
}

void BandCamShot::Store() {
    FOREACH (it, mTargets) {
        it->Store(this);
    }
}

void BandCamShot::View() {
    FOREACH (it, mTargets) {
        RndTransformable *t;
        bool b = false;
        Target &cur = *it;
        if (!(*it).mTarget.Null()) {
            t = GetTargetCache(cur.mTarget)->unk4;
            if (t)
                b = true;
        }
        if (b) {
            TeleportTarget(t, cur.mXfm, false);
            Character *charObj = dynamic_cast<Character *>(t);
            if (charObj)
                FreezeChar(charObj, false);
        }
    }
    StartAnim();
}

void BandCamShot::ViewFreeze() {
    View();
    TheTaskMgr.SetSecondsAndBeat(
        TheTaskMgr.Seconds(TaskMgr::kRealTime), TheTaskMgr.Beat(), false
    );
    FOREACH (it, mTargets) {
        Character *charObj;
        bool b = false;
        Target &cur = *it;
        if (!(*it).mTarget.Null()) {
            charObj = dynamic_cast<Character *>(GetTargetCache(cur.mTarget)->unk4);
            if (charObj)
                b = true;
        }
        if (b) {
            charObj->Poll();
            FreezeChar(charObj, true);
        }
    }
}

void BandCamShot::FreezeChar(Character *c, bool b) { c->mFrozen = b; }

void BandCamShot::Freeze() {
    FOREACH (it, mTargets) {
        Character *charObj;
        bool b = false;
        Target &cur = *it;
        if (!(*it).mTarget.Null()) {
            charObj = dynamic_cast<Character *>(GetTargetCache(cur.mTarget)->unk4);
            if (charObj)
                b = true;
        }
        if (b) {
            FreezeChar(charObj, true);
        }
    }
}

DataNode BandCamShot::AddTarget(DataArray *target) {
    MILO_ASSERT(target->Size() != 2, 0x3AD);
    mTargets.push_back(Target(this));
    mTargets.back().mTarget = target->Sym(2);
    mTargets.back().Store(this);
    return 0;
}

float BandCamShot::GetTotalDuration() {
    float sum = Duration();
    std::list<BandCamShot *> shots;
    ListNextShots(shots);
    FOREACH (it, shots) {
        sum += (*it)->Duration();
    }
    return sum;
}

int BandCamShot::GetNumShots() {
    std::list<BandCamShot *> shots;
    ListNextShots(shots);
    return shots.size() + 1;
}

float BandCamShot::GetTotalDurationSeconds() {
    float secs = CamShot::GetDurationSeconds();
    std::list<BandCamShot *> shots;
    ListNextShots(shots);
    for (std::list<BandCamShot *>::iterator it = shots.begin(); it != shots.end(); ++it) {
        secs += (*it)->CamShot::GetDurationSeconds();
    }
    return secs;
}

void BandCamShot::CheckNextShots() {
    std::list<BandCamShot *> shots;
    ListNextShots(shots);
}

BandCamShot *BandCamShot::InitialShot() {
    BandCamShot *initialShot = this;
    std ::vector<ObjRef *>::const_reverse_iterator ref = Refs().rbegin();
    std ::vector<ObjRef *>::const_reverse_iterator refEnd = Refs().rend();
    for (; ref != refEnd;) {
        BandCamShot *cur = dynamic_cast<BandCamShot *>((*ref)->RefOwner());
        if (cur) {
            FOREACH (it, cur->mNextShots) {
                if (*it == initialShot) {
                    initialShot = cur;
                    MILO_ASSERT(cur != this, 0x3FC);
                    ref = cur->Refs().rbegin();
                    refEnd = cur->Refs().rend();
                    break;
                }
            }
        } else
            ++ref;
    }
    return initialShot;
}

bool BandCamShot::ListNextShots(std::list<BandCamShot *> &shots) {
    if (unk169) {
        MILO_WARN("%s infinite camera shot loop detected!", PathName(this));
        return false;
    } else {
        unk169 = true;
        for (ObjPtrList<BandCamShot>::iterator it = mNextShots.begin();
             it != mNextShots.end();) {
            shots.push_back(*it);
            if (!(*it)->ListNextShots(shots)) {
                ObjPtrList<BandCamShot>::iterator yeet = it;
                ++it;
                mNextShots.erase(yeet);
            } else {
                ++it;
            }
        }
        unk169 = false;
        return true;
    }
}

float BandCamShot::EndFrame() { return GetTotalDuration(); }

bool BandCamShot::CheckShotStarted() { return !unk168 && CamShot::CheckShotStarted(); }

bool BandCamShot::CheckShotOver(float f) {
    return !unk168 && f >= unk164 && CamShot::CheckShotOver(f);
}

void BandCamShot::Target::Store(BandCamShot *shot) {
    if (!mTarget.Null()) {
        std::list<BandCamShot::TargetCache>::iterator it =
            shot->CreateTargetCache(mTarget);
        if (it->unk4) {
            mXfm.Set(it->unk4->mLocalXfm);
            shot->DeleteTargetCache(it);
        }
    }
}

void BandCamShot::Target::UpdateTarget(Symbol s, BandCamShot *shot) {
    if (mTarget != s) {
        mTarget = s;
        mAnimGroup = Symbol("");
    }
    Store(shot);
}

#pragma push
#pragma pool_data off
BEGIN_CUSTOM_PROPSYNC(BandCamShot::Target)
    SYNC_PROP_SET(target, o.mTarget, o.UpdateTarget(_val.Sym(), gBandCamShotOwner))
    SYNC_PROP_MODIFY(anim_group, o.mAnimGroup, gBandCamShotOwner->StartAnim())
    SYNC_PROP(fast_forward, o.mFastForward)
    SYNC_PROP(forward_event, o.mForwardEvent) {
        static Symbol _s("force_lod");
        if (sym == _s) {
            if (_op == kPropSet)
                o.mForceLod = _val.Int();
            else
                _val = DataNode(o.mForceLod);
            return true;
        }
    }
    {
        static Symbol _s("teleport");
        if (sym == _s) {
            if (_op == kPropSet)
                o.mTeleport = _val.Int();
            else
                _val = DataNode(o.mTeleport);
            return true;
        }
    }
    {
        static Symbol _s("return");
        if (sym == _s) {
            if (_op == kPropSet)
                o.mReturn = _val.Int();
            else
                _val = DataNode(o.mReturn);
            return true;
        }
    }
    {
        static Symbol _s("self_shadow");
        if (sym == _s) {
            if (_op == kPropSet)
                o.mSelfShadow = _val.Int();
            else
                _val = DataNode(o.mSelfShadow);
            return true;
        }
    }
    {
        static Symbol _s("hide");
        if (sym == _s) {
            if (_op == kPropSet)
                o.mHide = _val.Int();
            else
                _val = DataNode(o.mHide);
            return true;
        }
    }
    SYNC_PROP(env_override, o.mEnvOverride)
    SYNC_PROP_SET(target_ptr, gBandCamShotOwner->FindTarget(o.mTarget, false), )
END_CUSTOM_PROPSYNC
#pragma pop

BEGIN_PROPSYNCS(BandCamShot)
    gBandCamShotOwner = this;
    SYNC_PROP(targets, mTargets)
    SYNC_PROP(zero_time, mZeroTime)
    SYNC_PROP(min_time, mMinTime)
    SYNC_PROP(max_time, mMaxTime)
    SYNC_PROP_MODIFY_ALT(next_shots, mNextShots, CheckNextShots(); ResetNextShot();)
    SYNC_PROP(anims_during_nextshots, mAnimsDuringNextShots)
    SYNC_PROP_SET(total_duration, GetTotalDuration(), )
    SYNC_SUPERCLASS(CamShot)
END_PROPSYNCS

BEGIN_HANDLERS(BandCamShot)
    HANDLE(test_delta, OnTestDelta)
    HANDLE_EXPR(total_duration_seconds, GetTotalDurationSeconds())
    HANDLE_ACTION(store, Store())
    HANDLE_ACTION(view, View())
    HANDLE_ACTION(freeze, Freeze())
    HANDLE_ACTION(view_freeze, ViewFreeze())
    HANDLE(add_target, AddTarget)
    HANDLE_EXPR(initial_shot, InitialShot())
    HANDLE_EXPR(num_shots, GetNumShots())
    HANDLE(allowable_next_shots, OnAllowableNextShots)
    HANDLE(list_all_next_shots, OnListAllNextShots)
    HANDLE(list_targets, OnListTargets)
    HANDLE(list_anim_groups, OnListAnimGroups)
    HANDLE_SUPERCLASS(CamShot)
    HANDLE_CHECK(0x4A4)
END_HANDLERS

DataNode BandCamShot::OnListTargets(const DataArray *da) {
    DataNode handled = HandleType(list_targets_msg);
    if (handled.Type() != kDataUnhandled) {
        return DataNode(handled.Array(), kDataArray);
    } else
        return ObjectList(Dir(), "Trans", true);
}

DataNode BandCamShot::OnListAnimGroups(const DataArray *da) {
    Symbol sym = da->Sym(2);
    static Message m("list_anim_groups", 0);
    m[0] = sym;
    DataNode handled = HandleType(m);
    if (handled.Type() != kDataUnhandled) {
        return DataNode(handled.Array(), kDataArray);
    } else {
        Character *c = dynamic_cast<Character *>(FindTarget(sym, false));
        if (c) {
            ObjectDir *thedir = c->GetDriver() && c->GetDriver()->ClipDir()
                ? c->GetDriver()->ClipDir()
                : Dir();
            return ObjectList(thedir, "CharClipGroup", true);
        } else {
            handled = DataNode(new DataArray(1), kDataArray);
            handled.Array()->Node(0) = Symbol();
            return handled;
        }
    }
}

DataNode BandCamShot::OnTestDelta(DataArray *arr) {
    float f4 = arr->Float(2);
    bool ret = true;
    if (f4 != 0) {
        if ((mMinTime != 0 || !(f4 >= mMinTime)) && (mMaxTime != 0 || !(f4 <= mMaxTime)))
            ret = false;
    }
    return ret;
}

DataNode BandCamShot::OnAllowableNextShots(const DataArray *da) {
    DataArrayPtr ptr;
    for (ObjDirItr<BandCamShot> it(Dir(), true); it != nullptr; ++it) {
        if (this != it && mNextShots.find(it) == mNextShots.end()) {
            std::list<BandCamShot *> shots;
            it->ListNextShots(shots);
            if (std::find(shots.begin(), shots.end(), this) == shots.end()) {
                ptr->Insert(ptr->Size(), &*it);
            }
        }
    }
    static DataNode &milo_prop_path = DataVariable("milo_prop_path");
    if (milo_prop_path.Type() == kDataArray) {
        if (milo_prop_path.Array()->Size() == 2) {
            ptr->Insert(
                ptr->Size(), *NextItr(mNextShots.begin(), milo_prop_path.Array()->Int(1))
            );
        }
    }
    return ptr;
}

DataNode BandCamShot::OnListAllNextShots(const DataArray *da) {
    std::list<BandCamShot *> shots;
    ListNextShots(shots);
    DataArrayPtr ptr;
    for (std::list<BandCamShot *>::iterator it = shots.begin(); it != shots.end(); ++it) {
        ptr->Insert(ptr->Size(), DataNode(*it));
    }
    return ptr;
}
