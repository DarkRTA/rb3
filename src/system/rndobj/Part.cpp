#include "rndobj/Part.h"
#include "math/Mtx.h"
#include "math/Rand.h"
#include "math/Rot.h"
#include "math/Trig.h"
#include "obj/Data.h"
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "obj/Task.h"
#include "os/Debug.h"
#include "os/File.h"
#include "os/System.h"
#include "os/Timer.h"
#include "rndobj/Anim.h"
#include "rndobj/Draw.h"
#include "rndobj/Mesh.h"
#include "rndobj/Mat.h"
#include "rndobj/Poll.h"
#include "rndobj/Trans.h"
#include "rndobj/Utl.h"
#include "types.h"
#include "utl/Loader.h"
#include "utl/MemMgr.h"
#include "obj/DataFunc.h"
#include "utl/Symbols.h"

PartOverride gNoPartOverride;
ParticleCommonPool *gParticlePool;
INIT_REVS(RndParticleSys)

namespace {
    int ParticlePoolSize() {
        return SystemConfig("rnd", "particlesys", "global_limit")->Int(1);
    }

    DataNode PrintParticlePoolSize(DataArray *) {
        MILO_LOG("Particle Pool Size:\n");
        if (gParticlePool) {
            int size = ParticlePoolSize();
            MILO_LOG(
                "   %d particles can be allocated, %.1f KB.\n",
                size,
                (float)(size * 176 * 0.0009765625f)
            );
            MILO_LOG(
                "   %d particles active, %d is the high water mark.\n",
                gParticlePool->NumActiveParticles(),
                gParticlePool->HighWaterMark()
            );
            MILO_LOG(
                "   Adding 30%%, suggesting a particle global limit of %d (set in default.dta).\n",
                (int)(gParticlePool->HighWaterMark() * 1.3f)
            );
        }
        return 0;
    }
}

void InitParticleSystem() {
    if (!gParticlePool)
        gParticlePool = new ParticleCommonPool();
    if (gParticlePool)
        gParticlePool->InitPool();
    DataRegisterFunc("print_particle_pool_size", PrintParticlePoolSize);
}

int GetParticleHighWaterMark() {
    int ret = 0;
    if (gParticlePool)
        ret = gParticlePool->mHighWaterMark;
    return ret;
}

void ParticleCommonPool::InitPool() {
    static int _x = MemFindHeap("main");
    MemTempHeap tmp(_x);
    int size = ParticlePoolSize();
    mPoolParticles = new RndFancyParticle[size];
    for (int i = 0; i < size - 1; i++) {
        mPoolParticles[i].prev = nullptr;
        mPoolParticles[i].next = &mPoolParticles[i + 1];
    }
    mPoolParticles[size - 1].prev = nullptr;
    mPoolParticles[size - 1].next = nullptr;
    mPoolFreeParticles = mPoolParticles;
}

RndParticle *ParticleCommonPool::AllocateParticle() {
    RndParticle *cur = mPoolFreeParticles;
    RndParticle *ret = nullptr;
    if (cur) {
        mPoolFreeParticles = mPoolFreeParticles->next;
        cur->prev = cur;
        mNumActiveParticles++;
        ret = cur;
        if (mNumActiveParticles > mHighWaterMark) {
            mHighWaterMark = mNumActiveParticles;
        }
    }
    return ret;
}

RndParticle *ParticleCommonPool::FreeParticle(RndParticle *p) {
    if (!p)
        return nullptr;
    else {
        RndParticle *ret = p->next;
        p->next = mPoolFreeParticles;
        p->prev = nullptr;
        mPoolFreeParticles = p;
        mNumActiveParticles--;
        return ret;
    }
}

void RndParticleSys::SetPersistentPool(int i1, Type ty) {
    delete[] mPersistentParticles;
    mMaxParticles = i1;
    mType = ty;
    if (mMaxParticles != 0) {
        RndParticle *p = nullptr;
        if (ty == 1) {
            mPersistentParticles = new RndFancyParticle[i1];
            RndFancyParticle *fp = (RndFancyParticle *)p;
            for (int i = 0; i != i1; i++) {
                (fp++)->next = fp;
            }
            p = fp;
        } else {
            mPersistentParticles = new RndParticle[i1];
            for (int i = 0; i != i1; i++) {
                (p++)->next = p;
            }
        }
        p->next = nullptr;
    } else
        mPersistentParticles = 0;
    mFreeParticles = mPersistentParticles;
    mActiveParticles = 0;
    mNumActive = 0;
    mEmitCount = 0;
}

void RndParticleSys::SetPool(int max, Type ty) {
    mMaxParticles = max;
    DataArray *cfg = SystemConfig("rnd", "particlesys", "local_limit");
    int limit = cfg->Int(1);
    if (mMaxParticles > limit) {
        mMaxParticles = limit;
    }
    if (mPreserveParticles) {
        SetPersistentPool(max, ty);
    } else {
        if (mActiveParticles) {
            for (RndParticle *p = mActiveParticles; p != nullptr; p = FreeParticle(p))
                ;
        }
        mType = ty;
        mActiveParticles = 0;
        mNumActive = 0;
        mEmitCount = 0;
    }
}

BEGIN_COPYS(RndParticleSys)
    CREATE_COPY_AS(RndParticleSys, f)
    MILO_ASSERT(f, 0xD6);
    COPY_SUPERCLASS(Hmx::Object)
    COPY_SUPERCLASS(RndPollable)
    COPY_SUPERCLASS(RndAnimatable)
    COPY_SUPERCLASS(RndTransformable)
    COPY_SUPERCLASS(RndDrawable)
    COPY_MEMBER_FROM(f, mPreserveParticles)
    if (mPreserveParticles) {
        SetPool(f->mMaxParticles, f->mType);
        for (RndParticle *p = f->mActiveParticles; p != nullptr; p = p->next) {
            RndParticle *alloced = AllocParticle();
            if (!alloced)
                break;
            RndParticle *next = alloced->next;
            RndParticle *prev = alloced->prev;
            *alloced = *p;
            alloced->next = next;
            alloced->prev = prev;
        }
    }
    COPY_MEMBER_FROM(f, mNumActive)
    unke4 = GetFrame();
    if (ty != kCopyFromMax) {
        COPY_MEMBER_FROM(f, mLife)
        COPY_MEMBER_FROM(f, mScreenAspect)
        COPY_MEMBER_FROM(f, mBoxExtent1)
        COPY_MEMBER_FROM(f, mBoxExtent2)
        COPY_MEMBER_FROM(f, mSpeed)
        COPY_MEMBER_FROM(f, mPitch)
        COPY_MEMBER_FROM(f, mYaw)
        COPY_MEMBER_FROM(f, mEmitRate)
        COPY_MEMBER_FROM(f, mMaxBurst)
        COPY_MEMBER_FROM(f, mBurstInterval)
        COPY_MEMBER_FROM(f, mBurstPeak)
        COPY_MEMBER_FROM(f, mBurstLength)
        COPY_MEMBER_FROM(f, mStartSize)
        COPY_MEMBER_FROM(f, mDeltaSize)
        COPY_MEMBER_FROM(f, mStartColorLow)
        COPY_MEMBER_FROM(f, mStartColorHigh)
        COPY_MEMBER_FROM(f, mEndColorLow)
        COPY_MEMBER_FROM(f, mEndColorHigh)
        COPY_MEMBER_FROM(f, mBounce)
        COPY_MEMBER_FROM(f, mForceDir)
        COPY_MEMBER_FROM(f, mMat)
        COPY_MEMBER_FROM(f, mBubblePeriod)
        COPY_MEMBER_FROM(f, mBubbleSize)
        COPY_MEMBER_FROM(f, mBubble)
        COPY_MEMBER_FROM(f, mRotate)
        COPY_MEMBER_FROM(f, mRPM)
        COPY_MEMBER_FROM(f, mRPMDrag)
        COPY_MEMBER_FROM(f, mRotRandomDir)
        COPY_MEMBER_FROM(f, mDrag)
        COPY_MEMBER_FROM(f, mStartOffset)
        COPY_MEMBER_FROM(f, mEndOffset)
        COPY_MEMBER_FROM(f, mAlignWithVelocity)
        COPY_MEMBER_FROM(f, mStretchWithVelocity)
        COPY_MEMBER_FROM(f, mConstantArea)
        COPY_MEMBER_FROM(f, mPerspectiveStretch)
        COPY_MEMBER_FROM(f, mStretchScale)
        COPY_MEMBER_FROM(f, mFastForward)
        mNeedForward = mFastForward;
        COPY_MEMBER_FROM(f, mGrowRatio)
        COPY_MEMBER_FROM(f, mShrinkRatio)
        COPY_MEMBER_FROM(f, mMidColorRatio)
        COPY_MEMBER_FROM(f, mMidColorLow)
        COPY_MEMBER_FROM(f, mMidColorHigh)
        COPY_MEMBER_FROM(f, mMesh)
        COPY_MEMBER_FROM(f, mFrameDrive)
        COPY_MEMBER_FROM(f, mPauseOffscreen)
        unkec = 0;
        mElapsedTime = 0;
        if (!mPreserveParticles) {
            SetPool(f->mMaxParticles, f->mType);
        }
        RndTransformable *parent = f->mRelativeParent;
        if (parent != f)
            parent = f->mRelativeParent;
        else
            parent = this;
        SetRelativeMotion(f->mRelativeMotion, parent);
        SetSubSamples(f->mSubSamples);
    }
END_COPYS

SAVE_OBJ(RndParticleSys, 0x13D)

BEGIN_LOADS(RndParticleSys)
    LOAD_REVS(bs)
    ASSERT_REVS(0x25, 0)
    if (gRev > 0x16)
        LOAD_SUPERCLASS(Hmx::Object);
    if (gRev > 0x1B)
        LOAD_SUPERCLASS(RndPollable);
    if (gRev != 0) {
        LOAD_SUPERCLASS(RndAnimatable)
        LOAD_SUPERCLASS(RndTransformable)
        LOAD_SUPERCLASS(RndDrawable)
    }
    bs >> mLife;
    if (gRev > 0x23)
        bs >> mScreenAspect;
    bs >> mBoxExtent1;
    bs >> mBoxExtent2;
    bs >> mSpeed;
    bs >> mPitch;
    bs >> mYaw;
    bs >> mEmitRate;
    if (gRev > 0x20) {
        bs >> mMaxBurst >> mBurstInterval >> mBurstPeak >> mBurstLength;
    }
    bs >> mStartSize;
    if (gRev > 0xF)
        bs >> mDeltaSize;
    bs >> mStartColorLow;
    bs >> mStartColorHigh;
    bs >> mEndColorLow;
    bs >> mEndColorHigh;
    if (gRev > 0x19)
        bs >> mBounce;
    else if (gRev > 1) {
        bool ba7;
        bs >> ba7;
        if (gRev > 0xB) {
            Plane c;
            bs >> c;
        } else {
            Vector3 v1, v2;
            bs >> v1 >> v2;
            float f144 = -Dot(v2, v1);
        }
        if (ba7) {
            bool old = LOADMGR_EDITMODE;
            TheLoadMgr.SetEditMode(true);
            mBounce = Dir()->New<RndTransformable>(
                MakeString("%s_bounce.trans", FileGetBase(Name(), nullptr))
            );
            TheLoadMgr.SetEditMode(old);
            Transform tf140;
            Plane p150;
            Vector3 v11c(p150.On());
            Vector3 v128(reinterpret_cast<Vector3 &>(p150));
            Cross(Vector3(0, 1, 0), v128, tf140.m.x);
            Cross(v128, tf140.m.x, tf140.m.y);
            Normalize(tf140.m.x, tf140.m.x);
            Normalize(tf140.m.y, tf140.m.y);
            mBounce->SetWorldXfm(tf140);
        }
    } else {
        std::list<Plane> planes;
        bs >> planes;
    }
    bs >> mForceDir;
    bs >> mMat;
    if (gRev == 0x18) {
        char buf[0x80];
        bs.ReadString(buf, 0x80);
        if (!mMat && buf[0] != '\0') {
            mMat = LookupOrCreateMat(buf, Dir());
        }
    }
    if (gRev > 0x11) {
        bs >> (int &)mType >> mGrowRatio >> mShrinkRatio >> mMidColorRatio;
        bs >> mMidColorLow >> mMidColorHigh;
    } else if (gRev < 0xD) {
        int i94;
        bs >> i94;
    }
    bs >> mMaxParticles;
    if (gRev > 2) {
        if (gRev < 7) {
            int i98;
            bs >> i98;
        } else if (gRev < 0xD) {
            int i9c;
            bs >> i9c;
        }
    }
    if (gRev > 3) {
        bs >> mBubblePeriod >> mBubbleSize;
        LOAD_BITFIELD(bool, mBubble);
    }
    if (gRev > 0x1D) {
        LOAD_BITFIELD(bool, mRotate);
        bs >> mRPM >> mRPMDrag;
        if (gRev > 0x24) {
            LOAD_BITFIELD(bool, mRotRandomDir);
        }
        bs >> mDrag;
    }
    if (gRev > 0x1F) {
        bs >> mStartOffset >> mEndOffset;
        LOAD_BITFIELD(bool, mAlignWithVelocity);
        LOAD_BITFIELD(bool, mStretchWithVelocity);
        LOAD_BITFIELD(bool, mConstantArea);
        bs >> mStretchScale;
    }
    if (gRev > 0x21) {
        LOAD_BITFIELD(bool, mPerspectiveStretch);
    }
    if (gRev >= 5 && gRev <= 14) {
        bool baf;
        bs >> baf;
        int u1 = 0;
        if (baf)
            u1 = 2;
        if (mMat)
            mMat->SetZMode((RndMat::ZMode)u1);
    }
    if (gRev >= 6 && gRev <= 16) {
        String str;
        bs >> str;
    }
    if (gRev == 8) {
        bool b1b0;
        bs >> b1b0;
    }
    if (gRev == 0xD) {
        int i1a0;
        bs >> i1a0;
    }
    if (gRev > 0x13)
        bs >> mRelativeMotion;
    else if (gRev > 0xC) {
        bool i1b1;
        bs >> i1b1;
        mRelativeMotion = i1b1;
    }
    if (gRev > 0x1A)
        bs >> mRelativeParent;
    SetRelativeMotion(mRelativeMotion, mRelativeParent);
    if (gRev > 0x12)
        bs >> mMesh;
    if (gRev > 0x1E || gRev == 0x15)
        bs >> mSubSamples;
    SetSubSamples(mSubSamples);
    if (gRev > 0x1B) {
        LOAD_BITFIELD(bool, mFrameDrive);
    } else
        mFrameDrive = true;
    if (gRev > 0x22) {
        LOAD_BITFIELD(bool, mPauseOffscreen);
    } else
        mPauseOffscreen = false;
    if (gRev > 0x1C) {
        LOAD_BITFIELD(bool, mFastForward);
    } else
        mFastForward = false;
    mNeedForward = mFastForward;
    if (gRev > 0xA) {
        bs >> mPreserveParticles;
        if (mPreserveParticles) {
            int count;
            bs >> count;
            SetPool(mMaxParticles, mType);
            for (int i = 0; i < count; i++) {
                RndParticle *p = AllocParticle();
                if (p) {
                    p->angle = 0;
                    p->swingArm = 0;
                    p->vel.Set(0, 0, 0, 0);
                    bs >> *p;
                } else {
                    MILO_NOTIFY_ONCE_BETA(
                        "Unable to allocate all particles for %s\n", PathName(this)
                    );
                    RndParticle pp;
                    bs >> pp;
                }
            }
        } else
            SetPool(mMaxParticles, mType);
    } else
        SetPool(mMaxParticles, mType);

    unkec = 0;
    unke4 = GetFrame();
END_LOADS

RndParticle *RndParticleSys::AllocParticle() {
    RndParticle *p;
    if (mPreserveParticles) {
        p = mFreeParticles;
        if (!mFreeParticles)
            return nullptr;
        mFreeParticles = p->next;
    } else {
        p = gParticlePool->AllocateParticle();
        if (!p) {
            ParticlePoolSize();
            return nullptr;
        }
    }
    p->prev = p;
    if (mActiveParticles) {
        mActiveParticles->prev = p;
    }
    p->next = mActiveParticles;
    mActiveParticles = p;
    mNumActive++;
    return p;
}

void RndParticleSys::InitParticle(RndParticle *p, const Transform *t) {
    InitParticle(CalcFrame(), p, t, gNoPartOverride);
}

void RndParticleSys::InitParticle(
    float frame, RndParticle *particle, const Transform *tf, PartOverride &partOverride
) {
    particle->birthFrame = frame;
    if (partOverride.mask & 1) {
        particle->deathFrame = particle->birthFrame + partOverride.life;
    } else {
        particle->deathFrame = particle->birthFrame + RandomFloat(mLife.x, mLife.y);
    }

    particle->pos.w = particle->deathFrame > particle->birthFrame
        ? 1.0f / (particle->deathFrame - particle->birthFrame)
        : 0;

    RndMesh *mesh = mMesh;
    if (partOverride.mask & 0x100) {
        mesh = partOverride.mesh;
    }

    if (mesh && !mesh->Faces().empty()) {
        RandomPointOnMesh(mesh, particle->Pos3(), particle->Vel3());
    } else {
        if (partOverride.mask & 0x200) {
            particle->pos.x =
                RandomFloat(partOverride.box.mMin.x, partOverride.box.mMax.x);
            particle->pos.y =
                RandomFloat(partOverride.box.mMin.y, partOverride.box.mMax.y);
            particle->pos.z =
                RandomFloat(partOverride.box.mMin.z, partOverride.box.mMax.z);
        } else {
            particle->pos.x = RandomFloat(mBoxExtent1.x, mBoxExtent2.x);
            particle->pos.y = RandomFloat(mBoxExtent1.y, mBoxExtent2.y);
            particle->pos.z = RandomFloat(mBoxExtent1.z, mBoxExtent2.z);
        }
        float f8, f9;
        if (partOverride.mask & 0x80) {
            f8 = RandomFloat(partOverride.pitch.x, partOverride.pitch.y);
            f9 = RandomFloat(partOverride.yaw.x, partOverride.yaw.y);
        } else {
            f8 = RandomFloat(mPitch.x, mPitch.y);
            f9 = RandomFloat(mYaw.x, mYaw.y);
        }

        float cosPitch = FastCos(f8);
        float sinPitch = FastSin(f9);
        particle->vel.x = -cosPitch * sinPitch;
        particle->vel.y = cosPitch * FastCos(f9);
        particle->vel.z = FastSin(f8);
    }

    particle->Vel3() *=
        partOverride.mask & 2 ? partOverride.speed : RandomFloat(mSpeed.x, mSpeed.y);
    float f11 = particle->deathFrame != particle->birthFrame
        ? 1.0f / (particle->deathFrame - particle->birthFrame)
        : 0;
    if (mRotate) {
        particle->angle = RandomFloat(0, PI * 2);
        particle->swingArm = RandomFloat(mStartOffset.x, mStartOffset.y);
    } else {
        particle->angle = 0;
        particle->swingArm = 0;
    }
    if (partOverride.mask & 0x10) {
        particle->col = partOverride.startColor;
    } else {
        particle->col.red = RandomFloat(mStartColorLow.red, mStartColorHigh.red);
        particle->col.green = RandomFloat(mStartColorLow.green, mStartColorHigh.green);
        particle->col.blue = RandomFloat(mStartColorLow.blue, mStartColorHigh.blue);
        particle->col.alpha = RandomFloat(mStartColorLow.alpha, mStartColorHigh.alpha);
    }
    if (partOverride.mask & 4) {
        particle->size = partOverride.size;
    } else {
        particle->size = RandomFloat(mStartSize.x, mStartSize.y);
    }
    if (partOverride.mask & 8) {
        particle->sizeVel = partOverride.deltaSize;
    } else {
        particle->sizeVel = RandomFloat(mDeltaSize.x, mDeltaSize.y);
    }
    if (particle->sizeVel < -particle->size) {
        particle->sizeVel = -particle->size;
    }
    if (partOverride.mask & 0x40) {
        particle->colVel = partOverride.endColor;
    } else {
        particle->colVel.red = RandomFloat(mEndColorLow.red, mEndColorHigh.red);
        particle->colVel.green = RandomFloat(mEndColorLow.green, mEndColorHigh.green);
        particle->colVel.blue = RandomFloat(mEndColorLow.blue, mEndColorHigh.blue);
        particle->colVel.alpha = RandomFloat(mEndColorLow.alpha, mEndColorHigh.alpha);
    }

    if (mType == kFancy) {
        RndFancyParticle *fancyParticle = static_cast<RndFancyParticle *>(particle);
        if (mBubble) {
            fancyParticle->bubbleFreq =
                (PI * 2) / RandomFloat(mBubblePeriod.x, mBubblePeriod.y);
            fancyParticle->bubblePhase = RandomFloat(0, PI * 2);
            float f8 = RandomFloat(0, PI * 2);
            Scale(
                Vector3(FastSin(f8), 0, FastCos(f8)),
                RandomFloat(mBubbleSize.x, mBubbleSize.y),
                fancyParticle->Bubble3()
            );
            Vector3 vac;
            Scale(fancyParticle->Bubble3(), FastSin(fancyParticle->bubblePhase), vac);
            Add(fancyParticle->Pos3(), vac, fancyParticle->Pos3());
            fancyParticle->bubblePhase =
                -(frame * fancyParticle->bubbleFreq - fancyParticle->bubblePhase);
        }
        if (mRotate) {
            fancyParticle->RPF = RandomFloat(mRPM.x, mRPM.y) * 0.003490658709779382f;
            if (mRotRandomDir && RandomInt() & 0x100000) {
                fancyParticle->RPF = -fancyParticle->RPF;
            }
            fancyParticle->swingArmVel =
                f11 * (RandomFloat(mEndOffset.x, mEndOffset.y) - fancyParticle->swingArm);
        } else {
            fancyParticle->RPF = 0;
            fancyParticle->swingArmVel = 0;
        }
        if (mGrowRatio) {
            fancyParticle->growFrame =
                Interp(fancyParticle->birthFrame, fancyParticle->deathFrame, mGrowRatio);
            fancyParticle->growVel = fancyParticle->growFrame != fancyParticle->birthFrame
                ? fancyParticle->size
                    / (fancyParticle->growFrame - fancyParticle->birthFrame)
                : 0;

        } else {
            fancyParticle->growFrame = fancyParticle->birthFrame;
            fancyParticle->growVel = 0;
        }
        if (mShrinkRatio != 1) {
            fancyParticle->shrinkFrame = Interp(
                fancyParticle->birthFrame, fancyParticle->deathFrame, mShrinkRatio
            );
            fancyParticle->shrinkVel =
                fancyParticle->shrinkFrame != fancyParticle->deathFrame
                ? (fancyParticle->size + fancyParticle->sizeVel)
                    / (fancyParticle->shrinkFrame - fancyParticle->deathFrame)
                : 0;
        } else {
            fancyParticle->shrinkFrame = fancyParticle->deathFrame;
            fancyParticle->shrinkVel = 0;
        }

        fancyParticle->beginGrow = fancyParticle->growFrame > fancyParticle->birthFrame
            ? 1.0f / (fancyParticle->growFrame - fancyParticle->birthFrame)
            : 0;

        fancyParticle->midGrow = fancyParticle->shrinkFrame > fancyParticle->growFrame
            ? 1.0f / (fancyParticle->shrinkFrame - fancyParticle->growFrame)
            : 0;

        fancyParticle->endGrow = fancyParticle->deathFrame > fancyParticle->shrinkFrame
            ? 1.0f / (fancyParticle->deathFrame - fancyParticle->shrinkFrame)
            : 0;

        if (mGrowRatio) {
            fancyParticle->size = 0;
        }
        if (fancyParticle->shrinkFrame != fancyParticle->growFrame) {
            f11 = 1.0f / (fancyParticle->shrinkFrame - fancyParticle->growFrame);
        }
        fancyParticle->midcolFrame =
            Interp(fancyParticle->birthFrame, fancyParticle->deathFrame, mMidColorRatio);
        if (partOverride.mask & 0x20) {
            fancyParticle->midcolVel = partOverride.midColor;
        } else {
            fancyParticle->midcolVel.red =
                RandomFloat(mMidColorLow.red, mMidColorHigh.red);
            fancyParticle->midcolVel.green =
                RandomFloat(mMidColorLow.green, mMidColorHigh.green);
            fancyParticle->midcolVel.blue =
                RandomFloat(mMidColorLow.blue, mMidColorHigh.blue);
            fancyParticle->midcolVel.alpha =
                RandomFloat(mMidColorLow.alpha, mMidColorHigh.alpha);
        }
        fancyParticle->vel.w = fancyParticle->midcolFrame > fancyParticle->birthFrame
            ? 1.0f / (fancyParticle->midcolFrame - fancyParticle->birthFrame)
            : 0;
        fancyParticle->bubbleDir.w =
            fancyParticle->deathFrame > fancyParticle->midcolFrame
            ? 1.0f / (fancyParticle->deathFrame - fancyParticle->midcolFrame)
            : 0;
        Subtract(fancyParticle->colVel, fancyParticle->midcolVel, fancyParticle->colVel);
        if (fancyParticle->deathFrame != fancyParticle->midcolFrame) {
            Multiply(
                fancyParticle->colVel,
                1.0f / (fancyParticle->deathFrame - fancyParticle->midcolFrame),
                fancyParticle->colVel
            );
        }
        if (fancyParticle->midcolFrame != fancyParticle->birthFrame) {
            Subtract(
                fancyParticle->midcolVel, fancyParticle->col, fancyParticle->midcolVel
            );
            if (fancyParticle->midcolFrame != fancyParticle->birthFrame) {
                Multiply(
                    fancyParticle->colVel,
                    1.0f / (fancyParticle->midcolFrame - fancyParticle->birthFrame),
                    fancyParticle->colVel
                );
            }
        }
    } else {
        Subtract(particle->colVel, particle->col, particle->colVel);
        Multiply(particle->colVel, f11, particle->colVel);
    }

    particle->sizeVel *= f11;
    Transform tfa0;
    if (!tf) {
        MakeLocToRel(tfa0);
        tf = &tfa0;
    }
    Multiply(particle->Pos3(), *tf, particle->Pos3());
    Multiply(particle->Vel3(), *tf, particle->Vel3());
    if (mBubble && mType == kFancy) {
        RndFancyParticle *fancyParticle = static_cast<RndFancyParticle *>(particle);
        Multiply(fancyParticle->Bubble3(), *tf, fancyParticle->Bubble3());
    }
}

RndParticle *RndParticleSys::FreeParticle(RndParticle *p) {
    if (!p)
        return nullptr;
    else {
        if (p == mActiveParticles) {
            mActiveParticles = p->next;
        } else {
            p->prev->next = p->next;
        }
        if (p->next) {
            p->next->prev = p->prev;
        }
        if (!p->prev) {
            MILO_FAIL("Already deallocated particle");
        }
        p->prev = nullptr;
        RndParticle *ret = nullptr;
        if (mPreserveParticles) {
            ret = p->next;
            p->next = mFreeParticles;
            mFreeParticles = p;
        } else {
            ret = gParticlePool->FreeParticle(p);
        }
        mNumActive--;
        return ret;
    }
}

void RndParticleSys::SetSubSamples(int num) {
    mSubSamples = num;
    Transpose(mRelativeXfm, mSubSampleXfm);
    Multiply(WorldXfm(), mSubSampleXfm, mSubSampleXfm);
}

void RndParticleSys::SetRelativeMotion(float motion, RndTransformable *parent) {
    mRelativeParent = parent ? parent : this;
    mRelativeMotion = motion;
    if (motion == 1) {
        mRelativeXfm = mRelativeParent->WorldXfm();
    } else {
        mLastWorldXfm = mRelativeParent->WorldXfm();
        mRelativeXfm.Reset();
    }
}

void RndParticleSys::DrawShowing() {
    if (mFrameDrive) {
        UpdateRelativeXfm();
    } else {
        if (unke8 > 1) {
            UpdateRelativeXfm();
            UpdateParticles();
        } else if (mRelativeMotion == 1) {
            UpdateRelativeXfm();
        }
        unke8 = 0;
    }
}

void RndParticleSys::UpdateSphere() {
    Sphere s;
    MakeWorldSphere(s, true);
    Transform tf;
    FastInvert(WorldXfm(), tf);
    Multiply(s, tf, s);
    SetSphere(s);
}

bool RndParticleSys::MakeWorldSphere(Sphere &s, bool b2) {
    if (b2) {
        s.Zero();
        for (RndParticle *p = mActiveParticles; p != nullptr; p = p->next) {
            Sphere s38;
            Multiply(p->Pos3(), mRelativeXfm, s38.center);
            s38.radius = p->size * 0.5f;
            s.GrowToContain(s38);
        }
        return true;
    } else {
        Sphere &mySphere = mSphere;
        if (mySphere.GetRadius()) {
            Multiply(mySphere, WorldXfm(), s);
            return true;
        } else
            return false;
    }
}

void RndParticleSys::SetFrameDrive(bool b) {
    mFrameDrive = b;
    if (mFrameDrive) {
        unke4 = GetFrame();
    } else
        unke8 = 0;
    unkec = 0;
}

void RndParticleSys::SetPauseOffscreen(bool b) {
    mPauseOffscreen = b;
    unkec = 0;
}

void RndParticleSys::SetFrame(float frame, float blend) {
    RndAnimatable::SetFrame(frame, blend);
    if (mFrameDrive) {
        UpdateParticles();
        unke4 = frame;
        unkec = 0;
    }
}

float RndParticleSys::EndFrame() {
    if (mFrameDrive) {
        return Max(mLife.x, mLife.y);
    } else
        return 0;
}

void RndParticleSys::Poll() {
    if (!mFrameDrive) {
        mElapsedTime += (GetRate() == k30_fps_ui ? TheTaskMgr.DeltaUISeconds()
                                                 : TheTaskMgr.DeltaSeconds())
            * 30.0f;
        if (unke8 == 0) {
            if (Showing()
                && (mActiveParticles || mExplicitParts || mEmitRate.x > 0
                    || mEmitRate.y > 0 || mMaxBurst > 0)) {
                UpdateRelativeXfm();
                UpdateParticles();
            } else
                unke4 = CalcFrame();
        } else if (mActiveParticles && unke8 % 60 == 0 && !mPreserveParticles) {
            float calced = CalcFrame();
            RndParticle *p = mActiveParticles;
            while (p) {
                if (CheckParticleLife(calced, p)) {
                    p = FreeParticle(p);
                } else
                    p = p->next;
            }
        }
        if (mSubSamples > 0 && Dirty()) {
            MakeLocToRel(mSubSampleXfm);
        }
        unke8++;
    }
}

void RndParticleSys::MakeLocToRel(Transform &tf) {
    if (mRelativeMotion == 1) {
        if (mRelativeParent == this) {
            tf.Reset();
            return;
        }
    }
    Transpose(mRelativeXfm, tf);
    Multiply(WorldXfm(), tf, tf);
}

void RndParticleSys::CreateParticles(float f1, float f2, const Transform &tf) {
    if (f2 <= 0 || mNumActive >= mMaxParticles)
        return;
    else {
        mEmitCount += f2 * RandomFloat(mEmitRate.x, mEmitRate.y);
        mEmitCount += CheckBursts(f2) + (float)mExplicitParts;
        mExplicitParts = 0;
        while (mEmitCount >= 1.0f && mNumActive < mMaxParticles) {
            RndParticle *p = AllocParticle();
            if (!p) {
                mEmitCount = 0;
                return;
            }
            InitParticle(f1, p, &tf, gNoPartOverride);
            mEmitCount -= 1.0f;
        }
    }
}

void RndParticleSys::UpdateRelativeXfm() {
    if (mRelativeMotion == 1) {
        mRelativeXfm = mRelativeParent->WorldXfm();
    } else if (mRelativeMotion) {
        Transform &worldXfm = mRelativeParent->WorldXfm();
        Invert(mLastWorldXfm.m, mLastWorldXfm.m);
        Multiply(mLastWorldXfm.m, worldXfm.m, mLastWorldXfm.m);
        Hmx::Quat q28(0, 0, 0, 1);
        FastInterp(q28, Hmx::Quat(mLastWorldXfm.m), mRelativeMotion, q28);
        MakeRotMatrix(q28, mLastWorldXfm.m);
        Subtract(mRelativeXfm.v, mLastWorldXfm.v, mRelativeXfm.v);
        Multiply(mRelativeXfm, mLastWorldXfm.m, mRelativeXfm);
        Normalize(mRelativeXfm.m, mRelativeXfm.m);
        Interp(mLastWorldXfm.v, worldXfm.v, mRelativeMotion, mLastWorldXfm.v);
        Add(mRelativeXfm.v, mLastWorldXfm.v, mRelativeXfm.v);
        mLastWorldXfm = worldXfm;
    }
}

void RndParticleSys::Enter() {
    mElapsedTime = 0;
    mNeedForward = mFastForward;
    RndPollable::Enter();
}

void RndParticleSys::RunFastForward() {
    mNeedForward = false;
    float f1 = (mEmitRate.x + mEmitRate.y) * 0.5f;
    if (f1 < 0.0001f)
        return;
    else {
        float f6 = 1.0f / f1;
        float f3 = Min(f6 * (float)MaxParticles(), (mLife.x + mLife.y) * 0.5f);
        f6 = Max(1.0f, f6);
        float f4 = CalcFrame();
        Transform tf78;
        MakeLocToRel(tf78);
        for (float f5 = f4 - f3; f5 <= f4; f5 += f6) {
            MoveParticles(f5, f6);
            CreateParticles(f5, f6, tf78);
        }
    }
}

void RndParticleSys::ExplicitParticles(int i1, bool b2, PartOverride &partOverride) {
    if (b2) {
        float calced = CalcFrame();
        Transform tf48;
        MakeLocToRel(tf48);
        for (int i = 0; i < i1 && mNumActive < mMaxParticles; i++) {
            RndParticle *p = AllocParticle();
            if (!p)
                break;
            InitParticle(calced, p, &tf48, partOverride);
        }
    } else
        mExplicitParts += i1;
}

void RndParticleSys::FreeAllParticles() {
    for (RndParticle *p = mActiveParticles; p != nullptr; p = FreeParticle(p))
        ;
    mEmitCount = 0;
}

bool RndParticleSys::Burst::Set(float f1, float f2) {
    if (f2 > 0) {
        unk0 = f1;
        unk4 = f2 * 0.5f;
        unkc = f2;
        unk8 = 1.0f / unk4;
        return true;
    } else
        return false;
}

float RndParticleSys::Burst::Emit(float f1) {
    unkc -= f1;
    if (unkc < 0)
        return -1;
    float ret = unkc;
    if (ret > unk4) {
        ret = unk4 * 2.0f - ret;
    }
    ret *= unk8;
    return ret * ret * 3.0f - ret * ret * ret * 2.0f * unk0 * f1;
}

float RndParticleSys::CheckBursts(float f1) {
    if (f1 > 1)
        f1 = 1;
    float sum = 0;
    for (std::vector<Burst>::iterator it = mBursts.begin(); it != mBursts.end();) {
        float emit = it->Emit(f1);
        if (emit < 0)
            it = mBursts.erase(it);
        else {
            sum += emit;
            ++it;
        }
    }
    if (mBursts.size() < mMaxBurst) {
        mTimeTillBurst -= f1;
        if (mTimeTillBurst <= 0) {
            Burst burst;
            if (burst.Set(
                    RandomFloat(mBurstPeak.x, mBurstPeak.y),
                    RandomFloat(mBurstLength.x, mBurstLength.y)
                )) {
                mBursts.push_back(burst);
            }
            mTimeTillBurst = RandomFloat(mBurstInterval.x, mBurstInterval.y);
        }
    }
    return sum;
}

void RndParticleSys::MoveParticles(float, float) { START_AUTO_TIMER("psysmove"); }

RndParticleSys::~RndParticleSys() {
    if (mPreserveParticles) {
        if (mPersistentParticles)
            delete[] mPersistentParticles;
    } else if (mActiveParticles) {
        for (RndParticle *p = mActiveParticles; p != nullptr; p = FreeParticle(p))
            ;
    }
}

RndParticleSys::RndParticleSys()
    : mType(kBasic), mMaxParticles(0), mPersistentParticles(0), mFreeParticles(0),
      mActiveParticles(0), mNumActive(0), mEmitCount(0), unke4(0), unke8(0), unkec(0),
      mBubblePeriod(10, 10), mBubbleSize(1, 1), mLife(100, 100), mBoxExtent1(0, 0, 0),
      mBoxExtent2(0, 0, 0), mSpeed(1, 1), mPitch(0, 0), mYaw(0, 0), mEmitRate(1, 1),
      mStartSize(1, 1), mDeltaSize(0, 0), mStartColorLow(1, 1, 1),
      mStartColorHigh(1, 1, 1), mEndColorLow(1, 1, 1), mEndColorHigh(1, 1, 1),
      mMesh(this), mMat(this), mPreserveParticles(0), mRelativeParent(this),
      mBounce(this), mForceDir(0, 0, 0), mDrag(0), mRPM(0, 0), mRPMDrag(0),
      mStartOffset(0, 0), mEndOffset(0, 0), mStretchScale(1), mScreenAspect(1),
      mSubSamples(0), mGrowRatio(0), mShrinkRatio(1), mMidColorRatio(0.5),
      mMidColorLow(1, 1, 1), mMidColorHigh(1, 1, 1), mMaxBurst(0), mTimeTillBurst(0),
      mBurstInterval(15, 35), mBurstPeak(4, 8), mBurstLength(20, 30), mExplicitParts(0),
      mElapsedTime(0) {
    mFrameDrive = false;
    mBubble = false;
    mRotate = false;
    mRotRandomDir = true;
    mAlignWithVelocity = false;
    mStretchWithVelocity = false;
    mPauseOffscreen = false;
    mFastForward = false;
    mNeedForward = false;
    mConstantArea = false;
    mPerspectiveStretch = false;
    SetRelativeMotion(0, this);
    SetSubSamples(0);
}

void RndParticleSys::Replace(Hmx::Object *from, Hmx::Object *to) {
    RndTransformable::Replace(from, to);
    if (from == mRelativeParent) {
        RndTransformable *t = dynamic_cast<RndTransformable *>(to);
        SetRelativeMotion(mRelativeMotion, t);
    }
}

void RndParticleSys::SetMat(RndMat *mat) { mMat = mat; }

void RndParticleSys::SetMesh(RndMesh *mesh) {
    if (mesh) {
        SetTransParent(mesh, false);
        SetTransConstraint(RndTransformable::kParentWorld, 0, false);
        if (!mesh->GetKeepMeshData()) {
            MILO_WARN(
                "keep_mesh_data should be checked for %s.  It's the mesh emitter for %s.\n",
                PathName(mesh),
                PathName(this)
            );
        }
    } else if (mMesh) {
        SetTransParent(0, false);
        SetTransConstraint(RndTransformable::kNone, 0, false);
    }
    mMesh = mesh;
}

void RndParticleSys::SetGrowRatio(float f) {
    if (f >= 0.0f && f <= mShrinkRatio)
        mGrowRatio = f;
}

void RndParticleSys::SetShrinkRatio(float f) {
    if (f >= mGrowRatio && f <= 1.0f)
        mShrinkRatio = f;
}

void RndParticleSys::Mats(std::list<class RndMat *> &mats, bool b) {
    if (mMat) {
        mMat->mShaderOptions = GetDefaultMatShaderOpts(this, mMat);
        mats.push_back(mMat);
    }
}

#pragma push
#pragma dont_inline on
BEGIN_HANDLERS(RndParticleSys)
    HANDLE_EXPR(hi_emit_rate, Max(mEmitRate.x, mEmitRate.y))
    HANDLE(set_start_color, OnSetStartColor)
    HANDLE(set_end_color, OnSetEndColor)
    HANDLE(set_start_color_int, OnSetStartColorInt)
    HANDLE(set_end_color_int, OnSetEndColorInt)
    HANDLE(set_emit_rate, OnSetEmitRate)
    HANDLE(set_burst_interval, OnSetBurstInterval)
    HANDLE(set_burst_peak, OnSetBurstPeak)
    HANDLE(set_burst_length, OnSetBurstLength)
    HANDLE(add_emit_rate, OnAddEmitRate)
    HANDLE(launch_part, OnExplicitPart)
    HANDLE(launch_parts, OnExplicitParts)
    HANDLE(set_life, OnSetLife)
    HANDLE(set_speed, OnSetSpeed)
    HANDLE(set_rotate, OnSetRotate)
    HANDLE(set_swing_arm, OnSetSwingArm)
    HANDLE(set_drag, OnSetDrag)
    HANDLE(set_alignment, OnSetAlignment)
    HANDLE(set_start_size, OnSetStartSize)
    HANDLE(set_mat, OnSetMat)
    HANDLE(set_pos, OnSetPos)
    HANDLE_ACTION(set_mesh, SetMesh(_msg->Obj<RndMesh>(2)))
    HANDLE(active_particles, OnActiveParticles)
    HANDLE_EXPR(max_particles, MaxParticles())
    HANDLE_ACTION(
        set_relative_parent,
        SetRelativeMotion(mRelativeMotion, _msg->Obj<RndTransformable>(2))
    )
    HANDLE_ACTION(clear_all_particles, FreeAllParticles())
    HANDLE_SUPERCLASS(RndDrawable)
    HANDLE_SUPERCLASS(RndAnimatable)
    HANDLE_SUPERCLASS(RndTransformable)
    HANDLE_SUPERCLASS(RndPollable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x7B6)
END_HANDLERS
#pragma pop

DataNode RndParticleSys::OnSetStartColor(const DataArray *da) {
    DataArray *arr1 = da->Array(2);
    DataArray *arr2 = da->Array(3);
    SetStartColor(
        Hmx::Color(arr1->Float(0), arr1->Float(1), arr1->Float(2), arr1->Float(3)),
        Hmx::Color(arr2->Float(0), arr2->Float(1), arr2->Float(2), arr2->Float(3))
    );
    return 0;
}

DataNode RndParticleSys::OnSetStartColorInt(const DataArray *da) {
    Hmx::Color col1(da->Int(2));
    Hmx::Color col2(da->Int(3));
    col1.alpha = da->Float(4);
    col2.alpha = da->Float(5);
    SetStartColor(col1, col2);
    return 0;
}

DataNode RndParticleSys::OnSetEndColor(const DataArray *da) {
    DataArray *arr1 = da->Array(2);
    DataArray *arr2 = da->Array(3);
    SetEndColor(
        Hmx::Color(arr1->Float(0), arr1->Float(1), arr1->Float(2), arr1->Float(3)),
        Hmx::Color(arr2->Float(0), arr2->Float(1), arr2->Float(2), arr2->Float(3))
    );
    return 0;
}

DataNode RndParticleSys::OnSetEndColorInt(const DataArray *da) {
    Hmx::Color col1(da->Int(2));
    Hmx::Color col2(da->Int(3));
    col1.alpha = da->Float(4);
    col2.alpha = da->Float(5);
    SetEndColor(col1, col2);
    return 0;
}

DataNode RndParticleSys::OnSetEmitRate(const DataArray *da) {
    SetEmitRate(da->Float(2), da->Float(3));
    return 0;
}

DataNode RndParticleSys::OnAddEmitRate(const DataArray *da) {
    float add = da->Float(2);
    mEmitRate.x = Max(0.0f, mEmitRate.x + add);
    mEmitRate.y = Max(0.0f, mEmitRate.y + add);
    return DataNode(!mEmitRate);
}

DataNode RndParticleSys::OnSetBurstInterval(const DataArray *da) {
    SetMaxBurst(da->Int(2));
    SetTimeBetweenBursts(da->Float(3), da->Float(4));
    return 0;
}

DataNode RndParticleSys::OnSetBurstPeak(const DataArray *da) {
    SetPeakRate(da->Float(2), da->Float(3));
    return 0;
}

DataNode RndParticleSys::OnSetBurstLength(const DataArray *da) {
    SetDuration(da->Float(2), da->Float(3));
    return 0;
}

DataNode RndParticleSys::OnExplicitPart(const DataArray *da) {
    ExplicitParticles(1, false, gNoPartOverride);
    return 0;
}

DataNode RndParticleSys::OnExplicitParts(const DataArray *da) {
    bool b = false;
    if (da->Size() >= 4 && da->Int(3) != 0)
        b = true;
    ExplicitParticles(da->Int(2), b, gNoPartOverride);
    return 0;
}

DataNode RndParticleSys::OnSetLife(const DataArray *da) {
    SetLife(da->Float(2), da->Float(3));
    return 0;
}

DataNode RndParticleSys::OnSetSpeed(const DataArray *da) {
    SetSpeed(da->Float(2), da->Float(3));
    return 0;
}

DataNode RndParticleSys::OnSetRotate(const DataArray *da) {
    SetRotate(da->Int(2));
    SetRPM(da->Float(3), da->Float(4));
    SetRPMDrag(da->Float(4));
    return 0;
}

DataNode RndParticleSys::OnSetSwingArm(const DataArray *da) {
    SetStartOffset(da->Float(2), da->Float(3));
    SetEndOffset(da->Float(4), da->Float(5));
    return 0;
}

DataNode RndParticleSys::OnSetDrag(const DataArray *da) {
    SetDrag(da->Float(2));
    return 0;
}

DataNode RndParticleSys::OnSetAlignment(const DataArray *da) {
    SetAlignWithVelocity(da->Int(2));
    SetStretchWithVelocity(da->Int(3));
    SetConstantArea(da->Int(4));
    SetStretchScale(da->Float(5));
    return 0;
}

DataNode RndParticleSys::OnSetStartSize(const DataArray *da) {
    SetStartSize(da->Float(2), da->Float(3));
    return 0;
}

DataNode RndParticleSys::OnSetMat(const DataArray *da) {
    SetMat(da->Obj<RndMat>(2));
    return 0;
}

DataNode RndParticleSys::OnSetPos(const DataArray *da) {
    SetBoxExtent(
        Vector3(da->Float(2), da->Float(3), da->Float(4)),
        Vector3(da->Float(5), da->Float(6), da->Float(7))
    );
    return 0;
}

DataNode RndParticleSys::OnActiveParticles(const DataArray *da) {
    return mActiveParticles != nullptr;
}

BinStream &operator>>(BinStream &bs, RndParticle &part) {
    bs >> part.pos >> part.col >> part.size;
    return bs;
}

bool AngleVectorSync(Vector2 &vec, DataNode &_val, DataArray *_prop, int _i, PropOp _op) {
    if (_i == _prop->Size())
        return true;
    else {
        Symbol sym = _prop->Sym(_i);
        float *coord = nullptr;
        if (sym == x) {
            coord = &vec.x;
            goto sync;
        } else if (sym == y) {
            coord = &vec.y;
            goto sync;
        } else
            return false;
    sync:
        if (_op == kPropSet)
            *coord = DegreesToRadians(_val.Float());
        else if (_op == kPropGet)
            _val = RadiansToDegrees(*coord);
        else
            return false;
    }
    return true;
}

#pragma push
#pragma pool_data off
BEGIN_PROPSYNCS(RndParticleSys)
    SYNC_PROP(mat, mMat)
    SYNC_PROP_SET(max_parts, mMaxParticles, SetPool(_val.Int(), GetType()))
    SYNC_PROP(emit_rate, mEmitRate)
    SYNC_PROP(screen_aspect, mScreenAspect)
    SYNC_PROP(life, mLife)
    SYNC_PROP(speed, mSpeed)
    SYNC_PROP(start_size, mStartSize)
    SYNC_PROP(delta_size, mDeltaSize)
    SYNC_PROP(force_dir, mForceDir)
    SYNC_PROP(bounce, mBounce)
    SYNC_PROP(start_color_low, mStartColorLow)
    SYNC_PROP(start_color_high, mStartColorHigh)
    SYNC_PROP(start_alpha_low, mStartColorLow.alpha)
    SYNC_PROP(start_alpha_high, mStartColorHigh.alpha)
    SYNC_PROP(end_color_low, mEndColorLow)
    SYNC_PROP(end_color_high, mEndColorHigh)
    SYNC_PROP(end_alpha_low, mEndColorLow.alpha)
    SYNC_PROP(end_alpha_high, mEndColorHigh.alpha)
    SYNC_PROP(preserve, mPreserveParticles)
    SYNC_PROP_SET(fancy, mType, SetPool(mMaxParticles, (Type)_val.Int()))
    SYNC_PROP_SET(grow_ratio, mGrowRatio, SetGrowRatio(_val.Float()))
    SYNC_PROP_SET(shrink_ratio, mShrinkRatio, SetShrinkRatio(_val.Float()))
    SYNC_PROP(drag, mDrag)
    SYNC_PROP(mid_color_ratio, mMidColorRatio)
    SYNC_PROP(mid_color_low, mMidColorLow)
    SYNC_PROP(mid_color_high, mMidColorHigh)
    SYNC_PROP(mid_alpha_low, mMidColorLow.alpha)
    SYNC_PROP(mid_alpha_high, mMidColorHigh.alpha) {
        static Symbol _s("bubble");
        if (sym == _s) {
            if (_op == kPropSet) {
                mBubble = _val.Int();
            } else
                _val = mBubble;
            return true;
        }
    }
    SYNC_PROP(bubble_period, mBubblePeriod)
    SYNC_PROP(bubble_size, mBubbleSize)
    SYNC_PROP(max_burst, mMaxBurst)
    SYNC_PROP(time_between, mBurstInterval)
    SYNC_PROP(peak_rate, mBurstPeak)
    SYNC_PROP(duration, mBurstLength) {
        static Symbol _s("spin");
        if (sym == _s) {
            if (_op == kPropSet) {
                mRotate = _val.Int();
            } else
                _val = mRotate;
            return true;
        }
    }
    SYNC_PROP(rpm, mRPM)
    SYNC_PROP(rpm_drag, mRPMDrag)
    SYNC_PROP(start_offset, mStartOffset)
    SYNC_PROP(end_offset, mEndOffset) {
        static Symbol _s("random_direction");
        if (sym == _s) {
            if (_op == kPropSet) {
                mRotRandomDir = _val.Int();
            } else
                _val = mRotRandomDir;
            return true;
        }
    }
    {
        static Symbol _s("velocity_align");
        if (sym == _s) {
            if (_op == kPropSet) {
                mAlignWithVelocity = _val.Int();
            } else
                _val = mAlignWithVelocity;
            return true;
        }
    }
    {
        static Symbol _s("stretch_with_velocity");
        if (sym == _s) {
            if (_op == kPropSet) {
                mStretchWithVelocity = _val.Int();
            } else
                _val = mStretchWithVelocity;
            return true;
        }
    }
    SYNC_PROP(stretch_scale, mStretchScale) {
        static Symbol _s("constant_area");
        if (sym == _s) {
            if (_op == kPropSet) {
                mConstantArea = _val.Int();
            } else
                _val = mConstantArea;
            return true;
        }
    }
    {
        static Symbol _s("perspective");
        if (sym == _s) {
            if (_op == kPropSet) {
                mPerspectiveStretch = _val.Int();
            } else
                _val = mPerspectiveStretch;
            return true;
        }
    }
    SYNC_PROP_SET(mesh_emitter, mMesh, SetMesh(_val.Obj<RndMesh>()))
    SYNC_PROP(box_extent_1, mBoxExtent1)
    SYNC_PROP(box_extent_2, mBoxExtent2) {
        static Symbol _s("pitch");
        if (sym == _s) {
            AngleVectorSync(mPitch, _val, _prop, _i + 1, _op);
            return true;
        }
    }
    {
        static Symbol _s("yaw");
        if (sym == _s) {
            AngleVectorSync(mYaw, _val, _prop, _i + 1, _op);
            return true;
        }
    }
    SYNC_PROP_SET(
        relative_parent,
        mRelativeParent,
        SetRelativeMotion(mRelativeMotion, _val.Obj<RndTransformable>())
    )
    SYNC_PROP_SET(
        relative_motion, mRelativeMotion, SetRelativeMotion(_val.Float(), mRelativeParent)
    )
    SYNC_PROP_SET(subsamples, mSubSamples, SetSubSamples(_val.Int()))
    SYNC_PROP_SET(frame_drive, mFrameDrive, SetFrameDrive(_val.Int())) {
        static Symbol _s("pre_spawn");
        if (sym == _s) {
            if (_op == kPropSet) {
                mFastForward = _val.Int();
            } else
                _val = mFastForward;
            return true;
        }
    }
    SYNC_PROP_SET(pause_offscreen, mPauseOffscreen, SetPauseOffscreen(_val.Int()))
    SYNC_SUPERCLASS(RndAnimatable)
    SYNC_SUPERCLASS(RndTransformable)
    SYNC_SUPERCLASS(RndDrawable)
END_PROPSYNCS
#pragma pop
