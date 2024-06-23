#ifndef RNDOBJ_GENERATOR_H
#define RNDOBJ_GENERATOR_H
#include "math/Mtx.h"
#include "rndobj/Anim.h"
#include "rndobj/Draw.h"
#include "rndobj/Trans.h"
#include "rndobj/Part.h"
#include "rndobj/Mesh.h"
#include "rndobj/MultiMesh.h"
#include "rndobj/TransAnim.h"

class RndGenerator : public RndAnimatable, public RndTransformable, public RndDrawable {
public:

    class Instance {
    public:
        int pad[16];
    };

    RndGenerator();
    OBJ_CLASSNAME(Generator);
    OBJ_SET_TYPE(Generator);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual ~RndGenerator();
    virtual void SetFrame(float, float);
    virtual float StartFrame();
    virtual float EndFrame();
    virtual void ListAnimChildren(std::list<RndAnimatable*>&) const;
    virtual void DrawShowing();
    virtual void UpdateSphere();
    virtual bool MakeWorldSphere(Sphere&, bool);
    virtual void ListDrawChildren(std::list<RndDrawable*>&);
    virtual void Highlight() { RndDrawable::Highlight(); }
    virtual void Print();

    void DrawMesh(Transform&, float);
    void DrawMultiMesh(Transform&, float);
    void DrawParticleSys(Transform&, float);
    
    void Generate(float);
    void ResetInstances();
    void SetPath(RndTransAnim*, float, float);
    void SetRateVar(float lo, float hi) { mRateGenLow = lo; mRateGenHigh = hi; }
    void SetScaleVar(float lo, float hi) { mScaleGenLow = lo; mScaleGenHigh = hi; }
    void SetPathVar(float x, float y, float z) { mPathVarMaxX = x; mPathVarMaxY = y; mPathVarMaxZ = z; }

    DataNode OnSetPath(const DataArray*);
    DataNode OnSetRateVar(const DataArray*);
    DataNode OnSetScaleVar(const DataArray*);
    DataNode OnSetPathVar(const DataArray*);
    DataNode OnGenerate(const DataArray*);

    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(RndGenerator)
    static void Init(){ REGISTER_OBJ_FACTORY(RndGenerator) }

    std::list<Instance> mInstances; // 0xc0
    ObjPtr<RndTransAnim, ObjectDir> mPath; // 0xc8
    float mPathStartFrame; // 0xd4
    float mPathEndFrame; // 0xd8
    ObjPtr<RndMesh, ObjectDir> mMesh; // 0xdc
    ObjPtr<RndMultiMesh, ObjectDir> mMultiMesh; // 0xe8
    ObjPtr<RndParticleSys, ObjectDir> mParticleSys; // 0xf4
    float mNextFrameGen; // 0x100
    float mRateGenLow; // 0x104
    float mRateGenHigh; // 0x108
    float mScaleGenLow; // 0x10c
    float mScaleGenHigh; // 0x110
    float mPathVarMaxX; // 0x114
    float mPathVarMaxY; // 0x118
    float mPathVarMaxZ; // 0x11c
    RndParticle* mCurParticle; // 0x120
    std::list<Instance>::iterator mCurMultiMesh; // 0x124
};

#endif
