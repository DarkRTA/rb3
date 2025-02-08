#include "bandtrack/Tail.h"
#include "bandtrack/GraphicsUtl.h"
#include "math/Mtx.h"
#include "obj/Object.h"
#include "obj/Task.h"
#include "os/Debug.h"
#include "rndobj/Group.h"
#include "rndobj/Mesh.h"

Tail::Tail(GemRepTemplate &tmp)
    : mGroup(Hmx::Object::New<RndGroup>()), mTail1(Hmx::Object::New<RndMesh>()),
      mTail2(Hmx::Object::New<RndMesh>()), unk10(0), unk14("normal"), unk1c(-1),
      mTemplate(tmp), mTailGeomOwner(0), unk28(0), unk4e4(0), unk4e8(0), unk4ec(0),
      unk4f0(0), unk4f4(0) {
    mGroup->AddObject(mTail1);
    mTail1->SetTransParent(mGroup, false);
    mGroup->AddObject(mTail2);
    mTail2->SetTransParent(mGroup, false);
}

Tail::~Tail() {
    UnhookAllParents(mGroup);
    ReleaseMeshes();
    RELEASE(mGroup);
    RELEASE(mTail1);
    RELEASE(mTail2);
}

void Tail::Init(
    int i1,
    const Transform &tf,
    bool b3,
    Symbol s,
    RndGroup *grp,
    const Tail::SlideInfo &info,
    Tail *tail
) {
    unk18 = 0;
    unk1c = i1;
    mSlideInfo = info;
    if (mSlideInfo.unk0) {
        static float severity = 3.5f;
        mInterpolator.Reset(
            mSlideInfo.unk4, mSlideInfo.unk8, 0, mSlideInfo.unkc, severity
        );
    }
    ConfigureMeshes(tail);
    SetType(s, b3);
    mGroup->SetLocalXfm(tf);
    grp->AddObject(mGroup);
    mWhammy.Clear();
    unk4e4 = 0;
    unk4e8 = 0;
    unk4e0 = 0;
    unk4ec = 0;
    unk4f0 = 0;
    unk4f4 = false;
    UpdateVerts(mTemplate.kTailMinAlpha, false);
}

void Tail::MoveSlot(const Transform &tf) {
    if (mGroup) {
        Transform tf38(tf);
        tf38.v.y = mGroup->mLocalXfm.v.y;
        mGroup->SetLocalXfm(tf38);
    }
}

void Tail::SetType(Symbol s, bool b) {
    unk14 = s;
    if (unk14 == "unison") {
        unk14 = "star";
    }
    bool isStar = unk14 == "star";
    RndMat *tailMat;
    if (unk18 == 1) {
        tailMat = mTemplate.GetTailMiss();
    } else if (isStar) {
        tailMat = mTemplate.GetTailBonus();
    } else if (b) {
        tailMat = mTemplate.GetTailChord();
    } else {
        tailMat = mTemplate.GetSlotMat(0, unk1c);
    }
    MILO_ASSERT(tailMat, 0x8A);
    mTail1->SetMat(tailMat);
    mTail2->SetMat(tailMat);
    mTail1->SetShowing(unk14 != "invisible");
    mTail2->SetShowing(false);
    if (unk18 == 2)
        Hit();
}

void Tail::ConfigureMeshes(Tail *tail) {
    if (tail) {
        mTailGeomOwner = tail->mTailGeomOwner;
        unk28 = false;
    } else {
        mTailGeomOwner = mTemplate.GetTail();
        unk28 = true;
    }
    MILO_ASSERT(mTailGeomOwner, 0xAC);
    mTail1->SetGeomOwner(mTailGeomOwner);
    mTail2->SetGeomOwner(mTailGeomOwner);
    Hmx::Matrix3 m38;
    m38.Identity();
    m38.x.x = -1.0f;
    mTail2->SetLocalRot(m38);
}

void Tail::ReleaseMeshes() {
    if (unk28)
        mTemplate.ReturnTail(mTailGeomOwner);
    mTailGeomOwner = nullptr;
    mTail1->SetGeomOwner(mTail1);
    mTail2->SetGeomOwner(mTail2);
    mTail1->SetShowing(false);
    mTail2->SetShowing(false);
}

void Tail::SetDuration(float f1, float f2, float f3) {
    if (unk18 != 4) {
        if (unk18 == 2) {
            unk10 = Max(f1, unk10);
        } else {
            unk10 = Max(f2, unk10);
        }
        unk10 = Min(unk10, f3);
        unk4ec = f3 - unk10;
    }
}

void Tail::Hit() {
    unk18 = 2;
    if (!mSlideInfo.unk0) {
        mTail2->SetShowing(true);
    }
    if (unk28)
        mWhammy.Clear();
}

void Tail::Release() {
    if (unk18 != 4) {
        unk18 = 3;
        HandleMistake();
    }
}

void Tail::Done() {
    if (unk18 == 2) {
        unk18 = 4;
        unk10 = 0;
        unk4ec = 0;
        mTail1->SetShowing(false);
        mTail2->SetShowing(false);
    }
}

void Tail::HandleMistake() { mTail2->SetShowing(false); }

void Tail::Poll(float f1, float f2, float f3) {
    if (mTailGeomOwner) {
        bool t3 = unk18 == 2 && !mSlideInfo.unk0;
        float fvar1 = t3 ? mTemplate.kTailOffsetX * mTemplate.GetTailScaleX() : 0;
        mTail1->SetLocalPos(Vector3(-fvar1, unk10, 0));
        mTail2->SetLocalPos(Vector3(fvar1, unk10, 0));
        if (unk28) {
            if (t3) {
                float delta = TheTaskMgr.DeltaSeconds();
                static float pulseRate = 1.0f / mTemplate.kTailPulseRate;
                for (float time = TheTaskMgr.Seconds(TaskMgr::kRealTime) - delta;
                     time < TheTaskMgr.Seconds(TaskMgr::kRealTime);
                     time += pulseRate) {
                    unk4e4 = Interp(unk4e4, f2, mTemplate.kTailPulseSmoothing);
                    float f4 = Interp(
                        mTemplate.kTailFrequencyRange.x,
                        mTemplate.kTailFrequencyRange.y,
                        -unk4e4
                    );
                    float f6 = Interp(
                        mTemplate.kTailAmplitudeRange.x,
                        mTemplate.kTailAmplitudeRange.y,
                        -unk4e4
                    );
                    mWhammy.Set(f6 * std::sin(unk4e0));
                    unk4e0 += pulseRate * f4;
                }
                unk4e8 = Interp(unk4e8, f2, mTemplate.kTailAlphaSmoothing);
                f2 = Interp(mTemplate.kTailMinAlpha, mTemplate.kTailMaxAlpha, -unk4e8);
            } else {
                unk4e0 = 0;
                f2 = mTemplate.kTailMinAlpha;
                unk4e8 = 0;
            }

            if (unk4ec != unk4f0 || t3 || mSlideInfo.unk0 || unk4f4) {
                UpdateVerts(f2, t3);
                unk4f0 = unk4ec;
                unk4f4 = t3;
            }
        }
    }
}

void Tail::UpdateVerts(float f1, bool b2) {}