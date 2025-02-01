#include "char/CharEyes.h"
#include "char/CharFaceServo.h"
#include "char/CharPollable.h"
#include "char/CharWeightSetter.h"
#include "char/CharLookAt.h"
#include "char/CharInterest.h"
#include "char/CharWeightable.h"
#include "decomp.h"
#include "math/Rand.h"
#include "math/Vec.h"
#include "obj/DataUtl.h"
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "obj/Task.h"
#include "rndobj/Graph.h"
#include "rndobj/Trans.h"
#include "utl/Symbols.h"

bool CharEyes::sDisableEyeDart;
bool CharEyes::sDisableEyeJitter;
bool CharEyes::sDisableInterestObjects;
bool CharEyes::sDisableProceduralBlink;
bool CharEyes::sDisableEyeClamping;

INIT_REVS(CharEyes)

CharEyes::EyeDesc::EyeDesc(Hmx::Object *o)
    : mEye(o), mUpperLid(o), mLowerLid(o), mLowerLidBlink(o), mUpperLidBlink(o) {}

CharEyes::EyeDesc::EyeDesc(const CharEyes::EyeDesc &desc)
    : mEye(desc.mEye), mUpperLid(desc.mUpperLid), mLowerLid(desc.mLowerLid),
      mLowerLidBlink(desc.mLowerLidBlink), mUpperLidBlink(desc.mUpperLidBlink) {}

CharEyes::EyeDesc &CharEyes::EyeDesc::operator=(const CharEyes::EyeDesc &desc) {
    mEye = desc.mEye;
    mUpperLid = desc.mUpperLid;
    mLowerLid = desc.mLowerLid;
    mUpperLidBlink = desc.mUpperLidBlink;
    mLowerLidBlink = desc.mLowerLidBlink;
    return *this;
}

void CharEyes::CharInterestState::ResetState() { unkc = -1.0f; }

CharEyes::CharInterestState::CharInterestState(Hmx::Object *o) : mInterest(o) {
    ResetState();
}

CharEyes::CharInterestState::CharInterestState(const CharEyes::CharInterestState &state)
    : mInterest(state.mInterest) {
    ResetState();
}

CharEyes::CharInterestState &
CharEyes::CharInterestState::operator=(const CharEyes::CharInterestState &state) {
    mInterest = state.mInterest;
    return *this;
}

void CharEyes::CharInterestState::BeginRefractoryPeriod() {
    unkc = TheTaskMgr.Seconds(TaskMgr::kRealTime);
}

bool CharEyes::CharInterestState::IsInRefractoryPeriod() {
    if (!mInterest || unkc < 0.0)
        return false;
    else {
        float secs = TheTaskMgr.Seconds(TaskMgr::kRealTime) - unkc;
        if (secs < mInterest->mRefractoryPeriod)
            return true;
        else
            return false;
    }
}

float CharEyes::CharInterestState::RefractoryTimeRemaining() {
    if (!mInterest || unkc < 0.0)
        return 0.0f;
    else {
        float secs = TheTaskMgr.Seconds(TaskMgr::kRealTime) - unkc;
        if (secs < mInterest->mRefractoryPeriod)
            return mInterest->mRefractoryPeriod - secs;
        else
            return 0.0f;
    }
}

CharEyes::CharEyes()
    : mEyes(this), mInterests(this), mFaceServo(this), mCamWeight(this), unk58(0, 0, 0),
      mDefaultFilterFlags(0), mViewDirection(this), mHeadLookAt(this),
      mMaxExtrapolation(19.5f), mMinTargetDist(35.0f), mUpperLidTrackUp(1.0f),
      mUpperLidTrackDown(1.0f), mLowerLidTrackUp(0.75f), mLowerLidTrackDown(0.75f),
      mLowerLidTrackRotate(0), mInterestFilterFlags(0), unka4(0, 0, 0), unkb4(0),
      unkc0(0), unkc4(0), unkc5(0), unkc8(this), unkd4(this), unke0(-1), unke4(0),
#ifdef MILO_DEBUG
      unke8(0), unkec(1.0f), unkf0(0),
#endif
      unkf4(0), unk124(0), unk128(-1.0f), unk12c(-1), unk13c(0), unk140(-1.0f), unk144(0),
      unk148(-1.0f), unk14c(-1.0f), unk15c(0), unk15d(1) {
    unkb8 = std::cos(0.52359879f);
    unk9c = RndOverlay::Find("eye_status", false);
}

CharEyes::~CharEyes() {}

void CharEyes::Enter() {
    unka4.Zero();
    unkb4 = 0;
    unkbc = 0;
    unkb0 = 1.0f;
    unkc0 = -1.0f;
    unkc4 = 0;
    unk124 = 0;
    unk128 = -1.0f;
    unk12c = -1;
    unk13c = 0;
    unk140 = -1.0f;
    unk144 = 0;
    unk148 = -1.0f;
    unk14c = -1.0f;
    unkc5 = 0;
    mInterestFilterFlags = mDefaultFilterFlags;
    unk15c = 0;
    unke4 = 0;
    unkf4 = 0;
    RndTransformable *head = GetHead();
    if (head) {
        unka4 = head->WorldXfm().m.y;
        Normalize(unka4, unka4);
    }
    for (ObjVector<EyeDesc>::iterator it = mEyes.begin(); it != mEyes.end(); ++it) {
        it->mEye->Enter();
    }
    for (ObjVector<CharInterestState>::iterator it = mInterests.begin();
         it != mInterests.end();
         ++it) {
        it->ResetState();
    }
    RndPollable::Enter();
}

void CharEyes::Exit() {
    unkd4 = 0;
    unke0 = -1;
    mInterests.clear();
    for (ObjVector<EyeDesc>::iterator it = mEyes.begin(); it != mEyes.end(); ++it) {
        it->mEye->Exit();
    }
    RndPollable::Exit();
}

void CharEyes::Highlight() {
#ifdef MILO_DEBUG
    if (GetHead()) {
        RndGraph *oneframe = RndGraph::GetOneFrame();
        RndTransformable *trans = 0;
        for (ObjVector<EyeDesc>::iterator it = mEyes.begin(); it != mEyes.end(); ++it) {
            trans = it->mEye->GetSource();
            if (trans) {
                const Transform &tf1 = trans->WorldXfm();
                const Transform &tf2 = trans->WorldXfm();
                Vector3 v100(
                    tf1.m.y.x * 3.0f + tf2.v.x,
                    tf1.m.y.y * 3.0f + tf2.v.y,
                    tf1.m.y.z * 3.0f + tf2.v.z
                );
                if (it->mEye->unkb1)
                    oneframe->AddLine(
                        trans->WorldXfm().v, v100, Hmx::Color(1.0f, 0.0f, 0.0f), true
                    );
                else
                    oneframe->AddLine(
                        trans->WorldXfm().v, v100, Hmx::Color(0.0f, 1.0f, 0.0f), true
                    );
            }
        }
        Vector3 v10c(GetHead()->WorldXfm().v);
        if (trans) {
            float f1 = unkc8 ? unkc8->mMaxViewAngleCos : unkb8;
            float f2 = unkb0;
            if (unk124) {
                oneframe->AddSphere(
                    unk58, mEyeDartRulesetData.mMaxRadius, Hmx::Color(0.9f, 0.9f, 0.9f)
                );
                Vector3 v118(unk58.x + unk130.x, unk58.y + unk130.y, unk58.z + unk130.z);
                EnforceMinimumTargetDistance(v10c, v118, v118);
                oneframe->AddSphere(v118, 0.5f, Hmx::Color(0.0f, 0.0f, 1.0f));
                oneframe->AddLine(
                    trans->WorldXfm().v,
                    v118,
                    f2 < f1 ? Hmx::Color(1.0f, 0.0f, 0.0f) : Hmx::Color(0.2f, 0.2f, 1.0f),
                    true
                );
            } else {
                oneframe->AddLine(
                    trans->WorldXfm().v,
                    unk58,
                    f2 < f1 ? Hmx::Color(1.0f, 0.0f, 0.0f) : Hmx::Color(1.0f, 1.0f, 1.0f),
                    true
                );
            }
            if (unk13c) {
                oneframe->AddString3D(
                    "p blink!", trans->WorldXfm().v, Hmx::Color(1.0f, 1.0f, 1.0f)
                );
            }
        }
        if (unkd4) {
            if (unkd4 != unkc8) {
                const char *nametouse = unkc8 ? unkc8->Name() : "GENERATED";
                oneframe->AddString3D(
                    MakeString("focus = '%s' (looking at %s)", unkd4->Name(), nametouse),
                    v10c,
                    Hmx::Color(1.0f, 0.0f, 0.0f)
                );
            } else {
                oneframe->AddString3D(
                    MakeString("focus = '%s'", unkd4->Name()),
                    v10c,
                    Hmx::Color(0.0f, 1.0f, 0.0f)
                );
            }
        } else {
            if (unkc8) {
                oneframe->AddString3D(
                    MakeString("interest = '%s'", unkc8->Name()),
                    v10c,
                    Hmx::Color(0.0f, 1.0f, 0.0f)
                );
            }
        }
        if (mInterests.size() != 0) {
            // more happens here
        }
    }
#endif
}

DECOMP_FORCEACTIVE(CharEyes, "%s", "r=%f")

void CharEyes::UpdateOverlay() {
    if (unk9c && unk9c->Showing()) {
        *unk9c << Dir()->Name() << ": ";
        if (unkc8) {
            if (unkd4) {
                if (streq(unkc8->Name(), unkd4->Name())) {
                    *unk9c << "Look(FOC) ";
                    goto lol;
                }
            }
            *unk9c << "Look(" << unkc8->Name() << ") ";
        } else
            *unk9c << "Look(GEN) ";
    lol:
        if (unkd4) {
            Transform &headxfm = GetHead()->WorldXfm();
            Vector3 v34(headxfm.m.y);
            Normalize(v34, v34);
            const char *str = unkd4->IsWithinViewCone(headxfm.v, v34) ? "t" : "f";
            *unk9c << "Foc(" << unkd4->Name() << " p(" << unke0 << ") v(" << str << ")) ";
        } else
            *unk9c << "Foc(NA) ";
        *unk9c << "t(" << unkb4 << ") ";
        Vector3 v40(GetHead()->WorldXfm().v);
        Vector3 v4c;
        Vector3 v58(unk58);
        RndTransformable *target = GetTarget();
        if (target)
            v58 = target->WorldXfm().v;
        Subtract(v58, v40, v4c);
        float len = Length(v4c);
        *unk9c << "Dist(" << len << ") ";
        if (unk13c)
            *unk9c << "P Blink! ";
        if (unk124)
            *unk9c << "Dart! ";
        if (unkc5)
            *unk9c << "Close! ";
        *unk9c << "\n";
    }
}

DECOMP_FORCEACTIVE(
    CharEyes,
    "no_lids",
    "eyes.disable_clamping",
    "eyes.debug_clamping",
    "eyes.disable_llidnorm",
    "cheat.disable_eye_darts",
    "cheat.disable_procedural_blinks",
    "cheat.disable_interest_objects",
    "ObjPtr_p.h",
    "f.Owner()",
    ""
)

bool CharEyes::EitherEyeClamped() {
    for (ObjVector<EyeDesc>::iterator it = mEyes.begin(); it != mEyes.end(); ++it) {
        if (it->mEye && it->mEye->unkb1)
            return true;
    }
    return false;
}

void CharEyes::ClearAllInterestObjects() { mInterests.clear(); }

void CharEyes::AddInterestObject(CharInterest *interest) {
    if (interest) {
        CharInterestState state(this);
        state.mInterest = interest;
        mInterests.push_back(state);
    }
}

bool CharEyes::SetFocusInterest(CharInterest *interest, int i) {
    if (unkd4 && unke0 > i)
        return false;
    bool temp = interest != unkd4;
    unkd4 = interest;
    unke0 = i;
    if (temp)
        unke4 = true;
    if (!unkd4)
        unke0 = -1;
    return true;
}

bool CharEyes::EyesOnTarget(float f) {
    for (ObjVector<EyeDesc>::iterator it = mEyes.begin(); it != mEyes.end(); ++it) {
        RndTransformable *src = it->mEye->GetSource();
        if (src) {
            Vector3 v80;
            Subtract(unk58, src->WorldXfm().v, v80);
            Vector3 v8c(src->WorldXfm().m.y);
            Vector3 v98(v80);
            v98.z = 0;
            v8c.z = 0;
            float dot = Dot(v8c, v98);
            if (std::acos(Clamp<float>(-1, 1, dot / (Length(v8c) * Length(v98))))
                    * 57.295776f
                > f) {
                return false;
            }
        }
    }
    return true;
}

void CharEyes::EnforceMinimumTargetDistance(
    const Vector3 &v1, const Vector3 &v2, Vector3 &vout
) {
    Vector3 v2c;
    Subtract(v2, v1, v2c);
    float vlen = Length(v2c);
    bool b1 = false;
    unkc5 = false;
    if (unkc8 && unkc8->ShouldOverrideMinTargetDistance())
        b1 = true;
    float f4;
    if (b1)
        f4 = unkc8->MinTargetDistanceOverride();
    else
        f4 = mMinTargetDist;
    if (vlen < f4) {
        Vector3 v38;
        ScaleToMagnitude(v2c, f4, v38);
        Add(v1, v38, vout);
        unkc5 = true;
    }
}

bool CharEyes::IsHeadIKWeightIncreasing() {
    if (mHeadLookAt) {
        float weight = mHeadLookAt->Weight();
        return (weight > 0 && weight - unkf4 > 0);
    } else
        return false;
}

RndTransformable *CharEyes::GetTarget() {
    if (mEyes.empty() || !mEyes[0].mEye)
        return nullptr;
    else {
        return mEyes[0].mEye->GetDest();
    }
}

Vector3 CharEyes::GenerateDartOffset() {
    Vector3 vout;
    float start = mEyeDartRulesetData.mMinRadius;
    float end = mEyeDartRulesetData.mMaxRadius;
    if (mEyeDartRulesetData.mScaleWithDistance
        && mEyeDartRulesetData.mReferenceDistance > 0.1f) {
        Vector3 v48;
        Subtract(unk58, GetHead()->WorldXfm().v, v48);
        float len = Length(v48);
        start *= len / mEyeDartRulesetData.mReferenceDistance;
        end *= len / mEyeDartRulesetData.mReferenceDistance;
    }
    float mult = RandomFloat(0, 1) > 0.5f ? 1.0f : -1.0f;
    vout[0] = RandomFloat(start, end) * mult;
    mult = RandomFloat(0, 1) > 0.5f ? 1.0f : -1.0f;
    vout[1] = RandomFloat(start, end) * mult;
    mult = RandomFloat(0, 1) > 0.5f ? 1.0f : -1.0f;
    vout[2] = RandomFloat(start, end) * mult;
    return vout;
}

void CharEyes::DartUpdate() {
    unk128 -= TheTaskMgr.DeltaSeconds();
    if (unk124) {
        if (unk128 < 0) {
            unk12c--;
            if (unk12c < 0) {
                unk124 = false;
                unk128 = RandomFloat(
                    mEyeDartRulesetData.mMinSecsBetweenSequences,
                    mEyeDartRulesetData.mMaxSecsBetweenSequences
                );
            } else {
                unk128 = RandomFloat(
                    mEyeDartRulesetData.mMinSecsBetweenDarts,
                    mEyeDartRulesetData.mMaxSecsBetweenDarts
                );
                unk130 = GenerateDartOffset();
            }
        }
    } else if (unk128 < 0 && EyesOnTarget(mEyeDartRulesetData.mOnTargetAngleThresh)
               && !unk13c) {
        unk124 = true;
        unk12c = RandomInt(
            mEyeDartRulesetData.mMinDartsPerSequence,
            mEyeDartRulesetData.mMaxDartsPerSequence
        );
        unk128 = RandomFloat(
            mEyeDartRulesetData.mMinSecsBetweenDarts,
            mEyeDartRulesetData.mMaxSecsBetweenDarts
        );
        unk130 = GenerateDartOffset();
    }
}

void CharEyes::SetEnableBlinks(bool b1, bool b2) {
    unk15d = b1;
    if (b2 && !unk15d && unk13c && mFaceServo) {
        mFaceServo->SetProceduralBlinkWeight(0);
        unk13c = false;
        unk58 = unk150;
    }
}

// fn_804CCF70
RndTransformable *CharEyes::GetHead() {
    if (mViewDirection)
        return mViewDirection;
    else if (!mEyes.empty() && mEyes[0].mEye) {
        RndTransformable *src = mEyes[0].mEye->GetSource();
        if (src)
            return src->TransParent();
    }
    return 0;
}

CharInterest *CharEyes::GetCurrentInterest() {
    if (unkd4)
        return unkd4;
    if (unkc8)
        return unkc8;
    return 0;
}

void CharEyes::Replace(Hmx::Object *from, Hmx::Object *to) {
    Hmx::Object::Replace(from, to);
    CharWeightable::Replace(from, to);
    CharPollable::Replace(from, to);
    for (ObjVector<EyeDesc>::iterator it = mEyes.begin(); it != mEyes.end(); it) {
        if (it->mEye == from) {
            it->mEye = dynamic_cast<CharLookAt *>(to);
        }
        if (!it->mEye)
            it = mEyes.erase(it);
        else
            ++it;
    }
    for (ObjVector<CharInterestState>::iterator it = mInterests.begin();
         it != mInterests.end();
         it) {
        if (it->mInterest == from) {
            it->mInterest = dynamic_cast<CharInterest *>(to);
        }
        if (!it->mInterest)
            it = mInterests.erase(it);
        else
            ++it;
    }
}

void CharEyes::ForceBlink() {
    unk13c = true;
    unk140 = TheTaskMgr.Seconds(TaskMgr::kRealTime);
    unk144++;
}

void CharEyes::ListPollChildren(std::list<RndPollable *> &plist) const {
    for (ObjVector<EyeDesc>::const_iterator it = mEyes.begin(); it != mEyes.end(); ++it) {
        plist.push_back((*it).mEye);
    }
}

void CharEyes::PollDeps(
    std::list<Hmx::Object *> &changedBy, std::list<Hmx::Object *> &change
) {
    for (ObjVector<CharInterestState>::iterator it = mInterests.begin();
         it != mInterests.end();
         ++it) {
        ObjectDir *dir = (*it).mInterest->Dir();
        if (dir == Dir()) {
            changedBy.push_back((*it).mInterest);
        }
    }
    if (!mEyes.empty()) {
        changedBy.push_back(GetHead());
        change.push_back(GetTarget());
    }
    if (mHeadLookAt)
        changedBy.push_back(mHeadLookAt);
    if (mFaceServo)
        changedBy.push_back(mFaceServo);
}

SAVE_OBJ(CharEyes, 0x575)

BinStream &operator>>(BinStream &bs, CharEyes::EyeDesc &desc) {
    bs >> desc.mEye;
    bs >> desc.mUpperLid;
    if (CharEyes::gRev > 6)
        bs >> desc.mLowerLid;
    if (CharEyes::gRev > 0xF) {
        bs >> desc.mUpperLidBlink;
        bs >> desc.mLowerLidBlink;
    }
    return bs;
}

BinStream &operator>>(BinStream &bs, CharEyes::CharInterestState &state) {
    bs >> state.mInterest;
    return bs;
}

BEGIN_LOADS(CharEyes)
    LOAD_REVS(bs)
    ASSERT_REVS(0x12, 0)
    LOAD_SUPERCLASS(Hmx::Object)
    if (gRev > 5)
        LOAD_SUPERCLASS(CharWeightable)
    if (gRev > 4)
        bs >> mEyes;
    else {
        ObjPtrList<CharLookAt> pList(this, kObjListNoNull);
        bs >> pList;
        mEyes.resize(pList.size());
        int idx = 0;
        for (ObjPtrList<CharLookAt>::iterator it = pList.begin(); it != pList.end();
             ++it) {
            mEyes[idx].mEye = *it;
            mEyes[idx].mUpperLid = 0;
            mEyes[idx].mLowerLid = 0;
            mEyes[idx].mLowerLidBlink = 0;
            mEyes[idx].mUpperLidBlink = 0;
            idx++;
        }
    }
    if (gRev == 3 || gRev == 4) {
        ObjPtr<RndTransformable> tPtr(this);
        bs >> tPtr;
    }
    mInterests.clear();
    if (gRev >= 4 && gRev <= 8) {
        ObjPtr<RndTransformable> tPtr(this);
        int cnt;
        bs >> cnt;
        for (int i = 0; i < cnt; i++) {
            bs >> tPtr;
            int x;
            bs >> x;
        }
    } else if (gRev > 8)
        bs >> mInterests;
    if (gRev > 4)
        bs >> mFaceServo;
    else
        mFaceServo = 0;
    if (gRev > 7)
        bs >> mCamWeight;
    if (gRev > 9)
        bs >> mDefaultFilterFlags;
    if (gRev > 10)
        bs >> mViewDirection;
    if (gRev > 0xB)
        bs >> mHeadLookAt;
    if (gRev > 0xC)
        bs >> mMaxExtrapolation;
    if (gRev > 0xD)
        bs >> mMinTargetDist;
    if (gRev > 0xE) {
        bs >> mUpperLidTrackUp;
        bs >> mUpperLidTrackDown;
        bs >> mLowerLidTrackUp;
        if (gRev < 0x11) {
            int x, y;
            bs >> x;
            bs >> mLowerLidTrackDown;
            bs >> y;
        } else
            bs >> mLowerLidTrackDown;
    }
    if (gRev > 0x11)
        bs >> mLowerLidTrackRotate;
END_LOADS

BEGIN_COPYS(CharEyes)
    COPY_SUPERCLASS(Hmx::Object)
    COPY_SUPERCLASS(CharWeightable)
    CREATE_COPY(CharEyes)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mEyes)
        COPY_MEMBER(mInterests)
        COPY_MEMBER(mFaceServo)
        COPY_MEMBER(unka4)
        COPY_MEMBER(unkb4)
        COPY_MEMBER(mCamWeight)
        COPY_MEMBER(mDefaultFilterFlags)
        COPY_MEMBER(mViewDirection)
        COPY_MEMBER(mHeadLookAt)
        COPY_MEMBER(mMaxExtrapolation)
        COPY_MEMBER(mMinTargetDist)
        COPY_MEMBER(mUpperLidTrackUp)
        COPY_MEMBER(mUpperLidTrackDown)
        COPY_MEMBER(mLowerLidTrackUp)
        COPY_MEMBER(mLowerLidTrackDown)
        COPY_MEMBER(mLowerLidTrackRotate)
    END_COPYING_MEMBERS
END_COPYS

DataNode CharEyes::OnToggleForceFocus(DataArray *da) {
    if (unkd4)
        SetFocusInterest(0, 0);
    else
        SetFocusInterest(unkc8, 0);
    return 0;
}

DataNode CharEyes::OnToggleInterestOverlay(DataArray *da) {
    ToggleInterestsDebugOverlay();
    return 0;
}

void CharEyes::ToggleInterestsDebugOverlay() {
    if (unk9c)
        unk9c->SetOverlay(!unk9c->Showing());
}

BEGIN_HANDLERS(CharEyes)
    HANDLE(add_interest, OnAddInterest)
    HANDLE_ACTION(force_blink, ForceBlink())
#ifdef MILO_DEBUG
    HANDLE(toggle_force_focus, OnToggleForceFocus)
    HANDLE(toggle_interest_overlay, OnToggleInterestOverlay)
#endif
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x660)
END_HANDLERS

DataNode CharEyes::OnAddInterest(DataArray *arr) {
    mInterests.push_back(CharInterestState(arr->Obj<CharInterest>(1)));
    return 0;
}

BEGIN_CUSTOM_PROPSYNC(CharEyes::EyeDesc)
    SYNC_PROP(eye, o.mEye)
    SYNC_PROP(upper_lid, o.mUpperLid)
    SYNC_PROP(lower_lid, o.mLowerLid)
    SYNC_PROP(upper_lid_blink, o.mUpperLidBlink)
    SYNC_PROP(lower_lid_blink, o.mLowerLidBlink)
END_CUSTOM_PROPSYNC

BEGIN_CUSTOM_PROPSYNC(CharEyes::CharInterestState)
    SYNC_PROP(interest, o.mInterest)
END_CUSTOM_PROPSYNC

BEGIN_PROPSYNCS(CharEyes)
    SYNC_PROP(eyes, mEyes)
    SYNC_PROP(view_direction, mViewDirection)
    SYNC_PROP(interests, mInterests)
    SYNC_PROP(face_servo, mFaceServo)
    SYNC_PROP(camera_weight, mCamWeight)
    SYNC_PROP_BITFIELD_STATIC(default_interest_categories, mDefaultFilterFlags, 0x67B)
    SYNC_PROP(head_lookat, mHeadLookAt)
    SYNC_PROP(max_extrapolation, mMaxExtrapolation)
#ifdef MILO_DEBUG
    SYNC_PROP(disable_eye_dart, sDisableEyeDart)
    SYNC_PROP(disable_eye_jitter, sDisableEyeJitter)
    SYNC_PROP(disable_interest_objects, sDisableInterestObjects)
    SYNC_PROP(disable_procedural_blink, sDisableProceduralBlink)
    SYNC_PROP(disable_eye_clamping, sDisableEyeClamping)
    SYNC_PROP_BITFIELD_STATIC(interest_filter_testing, mInterestFilterFlags, 0x684)
#endif
    SYNC_PROP(min_target_dist, mMinTargetDist)
    SYNC_PROP(ulid_track_up, mUpperLidTrackUp)
    SYNC_PROP(ulid_track_down, mUpperLidTrackDown)
    SYNC_PROP(llid_track_up, mLowerLidTrackUp)
    SYNC_PROP(llid_track_down, mLowerLidTrackDown)
    SYNC_PROP(llid_track_rotate, mLowerLidTrackRotate)
    SYNC_SUPERCLASS(CharWeightable)
END_PROPSYNCS
