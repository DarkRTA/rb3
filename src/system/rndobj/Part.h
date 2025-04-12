#pragma once
#include "math/Color.h"
#include "math/Vec.h"
#include "obj/ObjMacros.h"
#include "rndobj/Trans.h"
#include "rndobj/Draw.h"
#include "rndobj/Poll.h"
#include "rndobj/Anim.h"
#include "utl/BinStream.h"
#include "utl/MemMgr.h"

class RndMesh;
class RndMat;

class RndParticle {
public:
    NEW_ARRAY_OVERLOAD;
    DELETE_ARRAY_OVERLOAD;

    Hmx::Color col; // 0x0
    Hmx::Color colVel; // 0x10
    Vector4 pos; // 0x20
    Vector4 vel; // 0x30
    float deathFrame; // 0x40
    float birthFrame; // 0x44
    float size; // 0x48
    float sizeVel; // 0x4c
    float angle; // 0x50
    float swingArm; // 0x54
    RndParticle *prev; // 0x58
    RndParticle *next; // 0x5c
};

BinStream &operator>>(BinStream &, RndParticle &);

class RndFancyParticle : public RndParticle {
public:
    float growFrame;
    float growVel;
    float shrinkFrame;
    float shrinkVel;
    Hmx::Color midcolVel;
    float midcolFrame;
    float beginGrow;
    float midGrow;
    float endGrow;
    Vector4 bubbleDir;
    float bubbleFreq;
    float bubblePhase;
    float RPF;
    float swingArmVel; // 0xac
};

class ParticleCommonPool {
public:
    ParticleCommonPool()
        : mPoolParticles(0), mPoolFreeParticles(0), mNumActiveParticles(0),
          mHighWaterMark(0) {}
    void InitPool();
    RndParticle *AllocateParticle();
    RndParticle *FreeParticle(RndParticle *);

    int NumActiveParticles() const { return mNumActiveParticles; }
    int HighWaterMark() const { return mHighWaterMark; }

    RndParticle *mPoolParticles; // 0x0
    RndParticle *mPoolFreeParticles; // 0x4
    int mNumActiveParticles; // 0x8
    int mHighWaterMark; // 0xc
};

struct PartOverride {
    PartOverride()
        : mask(0), life(0), speed(0), deltaSize(0), startColor(0), midColor(0),
          endColor(0), pitch(0, 0), yaw(0, 0), mesh(0),
          box(Vector3(0, 0, 0), Vector3(0, 0, 0)) {}
    PartOverride &operator=(const PartOverride &p) {
        mask = p.mask;
        life = p.life;
        speed = p.speed;
        size = p.size;
        deltaSize = p.deltaSize;
        startColor = p.startColor;
        midColor = p.midColor;
        endColor = p.endColor;
        pitch = p.pitch;
        yaw = p.yaw;
        mesh = p.mesh;
        box = p.box;
        return *this;
    }
    unsigned int mask; // 0x0
    float life; // 0x4
    float speed; // 0x8
    float size; // 0xc
    float deltaSize; // 0x10
    Hmx::Color startColor; // 0x14
    Hmx::Color midColor; // 0x24
    Hmx::Color endColor; // 0x34
    Vector2 pitch; // 0x44
    Vector2 yaw; // 0x4c
    RndMesh *mesh; // 0x54
    Box box; // 0x58
};

/** "A ParticleSys object generates, animates, and draws large
 *  numbers of similar sprites. Currently particles are rendered only
 *  as points on the PC." */
class RndParticleSys : public RndAnimatable,
                       public RndPollable,
                       public RndTransformable,
                       public RndDrawable {
public:
    enum Type {
        kBasic = 0,
        kFancy = 1
    };

    class Burst {
    public:
        int unk0;
        int unk4;
        int unk8;
        int unkc;
    };

    RndParticleSys();
    OBJ_CLASSNAME(ParticleSys);
    OBJ_SET_TYPE(ParticleSys);
    virtual DataNode Handle(DataArray *, bool);
    virtual bool SyncProperty(DataNode &, DataArray *, int, PropOp);
    virtual void Save(BinStream &);
    virtual void Copy(const Hmx::Object *, Hmx::Object::CopyType);
    virtual void Load(BinStream &);
    virtual ~RndParticleSys();
    virtual void SetFrame(float, float);
    virtual float EndFrame();
    virtual void Replace(Hmx::Object *, Hmx::Object *);
    virtual void Enter();
    virtual void Poll();
    virtual void DrawShowing();
    virtual void UpdateSphere();
    virtual bool MakeWorldSphere(Sphere &, bool);
    virtual void Mats(std::list<class RndMat *> &, bool);
    virtual void SetPreserveParticles(bool b) { mPreserveParticles = b; }
    virtual void SetPool(int, Type);
    virtual void SetPersistentPool(int, Type);
    virtual void Highlight() { RndDrawable::Highlight(); }

    void SetGrowRatio(float);
    void SetShrinkRatio(float);
    void SetMat(RndMat *);
    void SetMesh(RndMesh *);
    void SetRelativeMotion(float, RndTransformable *);
    void SetSubSamples(int);
    void SetFrameDrive(bool);
    void SetPauseOffscreen(bool);
    void InitParticle(RndParticle *, const Transform *);
    void ExplicitParticles(int, bool, PartOverride &);
    void FreeAllParticles();
    int MaxParticles() const;
    RndParticle *AllocParticle();
    RndParticle *FreeParticle(RndParticle *);
    void MoveParticles(float, float);

    DataNode OnSetStartColor(const DataArray *);
    DataNode OnSetStartColorInt(const DataArray *);
    DataNode OnSetEndColor(const DataArray *);
    DataNode OnSetEndColorInt(const DataArray *);
    DataNode OnSetEmitRate(const DataArray *);
    DataNode OnAddEmitRate(const DataArray *);
    DataNode OnSetBurstInterval(const DataArray *);
    DataNode OnSetBurstPeak(const DataArray *);
    DataNode OnSetBurstLength(const DataArray *);
    DataNode OnExplicitPart(const DataArray *);
    DataNode OnExplicitParts(const DataArray *);
    DataNode OnSetLife(const DataArray *);
    DataNode OnSetSpeed(const DataArray *);
    DataNode OnSetRotate(const DataArray *);
    DataNode OnSetSwingArm(const DataArray *);
    DataNode OnSetDrag(const DataArray *);
    DataNode OnSetAlignment(const DataArray *);
    DataNode OnSetStartSize(const DataArray *);
    DataNode OnSetMat(const DataArray *);
    DataNode OnSetPos(const DataArray *);
    DataNode OnActiveParticles(const DataArray *);

    const Hmx::Color &StartColorLow() const { return mStartColorLow; }
    const Hmx::Color &StartColorHigh() const { return mStartColorHigh; }
    void SetStartColor(const Hmx::Color &low, const Hmx::Color &high) {
        mStartColorLow = low;
        mStartColorHigh = high;
    }

    const Hmx::Color &EndColorLow() const { return mEndColorLow; }
    const Hmx::Color &EndColorHigh() const { return mEndColorHigh; }
    void SetEndColor(const Hmx::Color &low, const Hmx::Color &high) {
        mEndColorLow = low;
        mEndColorHigh = high;
    }

    const Vector2 &EmitRate() const { return mEmitRate; }
    void SetEmitRate(float x, float y) { mEmitRate.Set(x, y); }
    const Vector2 &Speed() const { return mSpeed; }
    void SetSpeed(float x, float y) { mSpeed.Set(x, y); }
    const Vector2 &Life() const { return mLife; }
    void SetLife(float x, float y) { mLife.Set(x, y); }
    const Vector2 &StartSize() const { return mStartSize; }
    void SetStartSize(float x, float y) { mStartSize.Set(x, y); }

    void SetBoxExtent(const Vector3 &v1, const Vector3 &v2) {
        mBoxExtent1 = v1;
        mBoxExtent2 = v2;
    }

    void SetBubbleSize(float x, float y) {
        mBubbleSize.x = x;
        mBubbleSize.y = y;
    }
    void SetBubblePeriod(float x, float y) {
        mBubblePeriod.x = x;
        mBubblePeriod.y = y;
    }
    void SetForceDir(const Vector3 &v) { mForceDir = v; }
    void SetDeltaSize(float x, float y) {
        mDeltaSize.x = x;
        mDeltaSize.y = y;
    }

    void SetSpin(bool b) { mSpin = b; }
    void SetVelocityAlign(bool b) { mVelocityAlign = b; }
    void SetStretchWithVelocity(bool b) { mStretchWithVelocity = b; }
    void SetConstantArea(bool b) { mConstantArea = b; }

    void SetMaxBurst(int i) { mMaxBurst = i; }
    void SetTimeBetweenBursts(float f1, float f2) { mBurstInterval.Set(f1, f2); }
    void SetPeakRate(float f1, float f2) { mBurstPeak.Set(f1, f2); }
    void SetDuration(float f1, float f2) { mBurstLength.Set(f1, f2); }
    void SetRPM(float f1, float f2) { mRPM.Set(f1, f2); }
    void SetRPMDrag(float f) { mRPMDrag = f; }
    void SetStartOffset(float f1, float f2) { mStartOffset.Set(f1, f2); }
    void SetEndOffset(float f1, float f2) { mEndOffset.Set(f1, f2); }
    void SetDrag(float f) { mDrag = f; }
    void SetStretchScale(float f) { mStretchScale = f; }
    RndMesh *GetMesh() const { return mMesh; }
    Type GetType() const { return mType; }
    RndMat *GetMat() const { return mMat; }

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(RndParticleSys)
    static void Init() { REGISTER_OBJ_FACTORY(RndParticleSys) }

    Type mType; // 0xc8
    /** "maximum number of particles". Ranges from 0 to 3072. */
    int mMaxParticles; // 0xcc
    RndParticle *mPersistentParticles; // 0xd0
    RndParticle *mFreeParticles; // 0xd4
    RndParticle *mActiveParticles; // 0xd8
    int mNumActive; // 0xdcc
    float unke0; // 0xe0
    float unke4; // 0xe4
    int unke8; // 0xe8
    float unkec; // 0xec
    Vector2 mBubblePeriod; // 0xf0
    Vector2 mBubbleSize; // 0xf8
    /** "Frame range of particle life." */
    Vector2 mLife; // 0x100
    /** "Min point and max point, in object coordinates, of box region that particles are
     * emitted from." */
    Vector3 mBoxExtent1; // 0x108
    /** "Min point and max point, in object coordinates, of box region that particles are
     * emitted from." */
    Vector3 mBoxExtent2; // 0x114
    /** "Speed range, in world units per frame, of particles." */
    Vector2 mSpeed; // 0x120
    Vector2 mPitch; // 0x128
    Vector2 mYaw; // 0x130
    /** "Frame range to generate particles." */
    Vector2 mEmitRate; // 0x138
    /** "Size range, in world units, of particles." */
    Vector2 mStartSize; // 0x140
    /** "Change in size of particles, in world units." */
    Vector2 mDeltaSize; // 0x148
    /** "Random color ranges for start and end color of particles." */
    Hmx::Color mStartColorLow; // 0x150
    /** "Random color ranges for start and end color of particles." */
    Hmx::Color mStartColorHigh; // 0x160
    /** "Random color ranges for start and end color of particles." */
    Hmx::Color mEndColorLow; // 0x170
    /** "Random color ranges for start and end color of particles." */
    Hmx::Color mEndColorHigh; // 0x180
    ObjPtr<RndMesh> mMesh; // 0x190
    /** "material for particle system" */
    ObjPtr<RndMat> mMat; // 0x19c
    bool mPreserveParticles; // 0x1a8
    Transform mRelativeXfm; // 0x1ac
    Transform mLastWorldXfm; // 0x1ec
    float mRelativeMotion; // 0x20c
    ObjOwnerPtr<RndTransformable> mRelativeParent; // 0x210
    /** "Specify a collide plane to reflect particles. Used to bounce particles off
     * surfaces." */
    ObjPtr<RndTransformable> mBounce; // 0x21c
    /** "Force direction in world coordinates, in units per frame added to each particle's
     * velocity. Can be used for gravity." */
    Vector3 mForceDir; // 0x228
    float mDrag; // 0x234
    Vector2 mRPM; // 0x238
    float mRPMDrag; // 0x240
    Vector2 mStartOffset; // 0x244
    Vector2 mEndOffset; // 0x24c
    float mStretchScale; // 0x254
    /** "Ratio of screen height to width" */
    float mScreenAspect; // 0x258
    int mSubSamples; // 0x25c
    Transform mSubSampleXfm; // 0x260
    float mGrowRatio; // 0x290
    float mShrinkRatio; // 0x294
    float mMidColorRatio; // 0x298
    Hmx::Color mMidColorLow; // 0x29c
    Hmx::Color mMidColorHigh; // 0x2ac
    std::vector<Burst> mBursts; // 0x2bc
    int mMaxBurst; // 0x2c4
    float mTimeTillBurst; // 0x2c8
    Vector2 mBurstInterval; // 0x2cc
    Vector2 mBurstPeak; // 0x2d4
    Vector2 mBurstLength; // 0x2dc
    int unk2e4;
    float unk2e8;
};

extern ParticleCommonPool *gParticlePool;
extern PartOverride gNoPartOverride;

void InitParticleSystem();
int GetParticleHighWaterMark();
