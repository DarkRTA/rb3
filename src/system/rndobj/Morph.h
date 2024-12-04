#pragma once
#include "obj/Data.h"
#include "obj/ObjMacros.h"
#include "rndobj/Anim.h"
#include "obj/ObjVector.h"
#include "rndobj/Mesh.h"
#include "math/Key.h"

/**
 * @brief A set of RndMesh poses that can be blended between.
 * Commonly used for lipsync.
 * Original _objects description:
 * "A Morph object animates between multiple Mesh poses using
 * weight keyframes. This is an expensive technique, equivalent to a
 * MeshAnim for each active pose, so use only when skinning or a
 * single MeshAnim isn't enough. For example, we use it for
 * viseme-driven facial animation."
 */
class RndMorph : public RndAnimatable {
public:

    /** An individual state of a RndMorph. */
    class Pose {
    public:
        Pose(Hmx::Object* owner_morph) : mesh(owner_morph) {}

        ObjPtr<RndMesh> mesh; // 0x0
        Keys<float, float> weights; // 0xc
    };

    RndMorph();
    OBJ_CLASSNAME(Morph);
    OBJ_SET_TYPE(Morph);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual ~RndMorph(){}
    virtual void SetFrame(float, float);
    virtual float EndFrame();
    virtual void Print();

    void SetNumPoses(int num){ mPoses.resize(num); }
    int NumPoses() const { return mPoses.size(); }
    Pose& PoseAt(int idx){ return mPoses[idx]; }
    void SetIntensity(float intensity){ mIntensity = intensity; }
    void SetTarget(RndMesh* target){ mTarget = target; }

    DataNode OnSetIntensity(const DataArray*);
    DataNode OnSetTarget(const DataArray*);
    DataNode OnSetPoseWeight(const DataArray*);
    DataNode OnPoseMesh(const DataArray*);
    DataNode OnSetPoseMesh(const DataArray*);

    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    DECLARE_REVS;
    NEW_OBJ(RndMorph)
    static void Init(){ REGISTER_OBJ_FACTORY(RndMorph) }

    /** "[Number of] mesh keyframes to blend" */
    ObjVector<Pose> mPoses; // 0x10

    /** "Mesh for the morph to occur" */
    ObjPtr<RndMesh, ObjectDir> mTarget; // 0x1c

    /** "Interpolates the normals if set to true, otherwise normals are not affected." */
    bool mNormals; // 0x28

    /** "Smooths the interpolation of the morphing." */
    bool mSpline; // 0x29

    /** "Modifier for weight interpolation" */
    float mIntensity; // 0x2c
};
