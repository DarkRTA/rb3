#ifndef RNDOBJ_MORPH_H
#define RNDOBJ_MORPH_H
#include "rndobj/Anim.h"
#include "obj/ObjVector.h"
#include "rndobj/Mesh.h"

class RndMorph : public RndAnimatable {
public:
    class Pose {
    public:
        Pose(Hmx::Object*);
    };

    RndMorph();
    OBJ_CLASSNAME(Morph);
    OBJ_SET_TYPE(Morph);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual ~RndMorph();
    virtual void SetFrame(float, float);
    virtual float EndFrame();
    virtual void Print();

    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(RndMorph)
    static void Init(){ REGISTER_OBJ_FACTORY(RndMorph) }

    ObjVector<Pose> mPoses; // 0x10
    ObjPtr<RndMesh, ObjectDir> mTarget; // 0x1c
    bool mNormals; // 0x28
    bool mSpline; // 0x29
    float mIntensity; // 0x2c
};

#endif
