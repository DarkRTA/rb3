#ifndef RNDOBJ_PART_H
#define RNDOBJ_PART_H
#include "math/Color.h"
#include "math/Vec.h"
#include "rndobj/Trans.h"
#include "rndobj/Draw.h"
#include "rndobj/Poll.h"
#include "rndobj/Anim.h"

class RndMesh;
class RndMat;

struct RndParticle {
    Hmx::Color col;
    Hmx::Color colVel;
    Vector4 pos;
    Vector4 vel;
    float deathFrame;
    float birthFrame;
    float size;
    float sizeVel;
    float angle;
    float swingArm;
    RndParticle* prev;
    RndParticle* next;
};

class RndParticleSys : public RndAnimatable, public RndPollable, public RndTransformable, public RndDrawable {
public:
    enum Type {
        t0, t1, t2
    };

    RndParticleSys();
    OBJ_CLASSNAME(ParticleSys);
    OBJ_SET_TYPE(ParticleSys);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual ~RndParticleSys();
    virtual void SetFrame(float, float);
    virtual float EndFrame();
    virtual void Replace(Hmx::Object*, Hmx::Object*);
    virtual void Enter();
    virtual void Poll();
    virtual void DrawShowing();
    virtual void UpdateSphere();
    virtual bool MakeWorldSphere(Sphere&, bool);
    virtual void Mats(std::list<class RndMat*>&, bool);
    virtual void SetPreserveParticles(bool);
    virtual void SetPool(int, Type);
    virtual void SetPersistentPool(int, Type);
    virtual void Highlight();

    void SetGrowRatio(float);
    void SetShrinkRatio(float);
    void SetMesh(RndMesh*);
    void SetRelativeMotion(float, RndTransformable*);
    void SetSubSamples(int);
    void SetFrameDrive(bool);
    void SetPauseOffscreen(bool);

    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(RndParticleSys)
    static void Init(){ REGISTER_OBJ_FACTORY(RndParticleSys) }

    Type mType; // fancy?
    int mMaxParticles; // 0xcc
    int unkd0;
    int unkd4;
    int unkd8;
    int unkdc;
    float unke0;
    float unke4;
    int unke8;
    float unkec;
    Vector2 mBubblePeriod; // 0xf0
    Vector2 mBubbleSize; // 0xf8
    Vector2 mLife; // 0x100
    Vector3 mBoxExtent1; // 0x108
    Vector3 mBoxExtent2; // 0x114
    Vector2 mSpeed; // 0x120
    Vector2 mPitch; // 0x128
    Vector2 mYaw; // 0x130
    Vector2 mEmitRate; // 0x138
    Vector2 mStartSize; // 0x140
    Vector2 mDeltaSize; // 0x148
    Hmx::Color mStartColorLow; // 0x150
    Hmx::Color mStartColorHigh; // 0x160
    Hmx::Color mEndColorLow; // 0x170
    Hmx::Color mEndColorHigh; // 0x180
    ObjPtr<RndMesh, ObjectDir> mMesh; // 0x190
    ObjPtr<RndMat, ObjectDir> mMat; // 0x19c
    bool mPreserveParticles; // 0x1a8
    Transform mRelativeXfm; // 0x1ac
    Transform mLastWorldXfm; // 0x1ec
    float mRelativeMotion; // 0x20c
    ObjOwnerPtr<RndTransformable, ObjectDir> mRelativeParent; // 0x210
    ObjPtr<RndTransformable, ObjectDir> mBounce; // 0x21c
    Vector3 mForceDir; // 0x228
    float mDrag; // 0x234
    Vector2 mRPM; // 0x238
    float mRPMDrag; // 0x240
    Vector2 mStartOffset; // 0x244
    Vector2 mEndOffset; // 0x24c
    float mStretchScale; // 0x254
    float mScreenAspect; // 0x258
    int mSubSamples; // 0x25c
    Transform mSubSampleXfm; // 0x260
    float mGrowRatio; // 0x290
    float mShrinkRatio; // 0x294
    float mMidColorRatio; // 0x298
    Hmx::Color mMidColorLow; // 0x29c
    Hmx::Color mMidColorHigh; // 0x2ac
    std::vector<int> unk2bc;
    int mMaxBurst; // 0x2c4
    float unk2c8;
    Vector2 mTimeBetween; // 0x2cc
    Vector2 mPeakRate; // 0x2d4
    Vector2 mDuration; // 0x2dc
    int unk2e4;
    float unk2e8;
};

void InitParticleSystem();

#endif // RNDOBJ_PART_H
