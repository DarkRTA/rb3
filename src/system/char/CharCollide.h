#pragma once
#include "math/Vec.h"
#include "rndobj/Trans.h"
#include "rndobj/Mesh.h"
#include "math/SHA1.h"
#include "obj/ObjPtr_p.h"

/** "Feeds the bones when executed." */
class CharCollide : public RndTransformable {
public:
    enum Shape {
        kPlane = 0,
        kSphere = 1,
        kInsideSphere = 2,
        kCigar = 3,
        kInsideCigar = 4,
    };

    struct CharCollideStruct {
        CharCollideStruct(){}
        int unk0; // size?
        Vector3 vec;
    };

    CharCollide();
    OBJ_CLASSNAME(CharCollide)
    OBJ_SET_TYPE(CharCollide)
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, CopyType);
    virtual void Load(BinStream&);
    virtual ~CharCollide();
    virtual void Highlight();

    void CopyOriginalToCur();
    float Radius() const;
    Shape GetShape() const { return mShape; }
    const Vector3& Axis() const;
    void SyncShape();
    int NumSpheres();
    void Deform();
    void ClearMesh(){ mMesh = 0; }

    float GetRadius(const Vector3& v1, Vector3& vout) const {
        Subtract(v1, unk1a0, vout);
        float ret = mCurRadius[0];
        if(mShape >= kCigar){
            float clamped = Clamp(mCurLength[0], mCurLength[1], unk190 * Dot(vout, unk194));
            ScaleAddEq(vout, unk194, -clamped);
            Interp(ret, mCurRadius[1], unk18c * (clamped - mCurLength[0]), ret);
        }
        else if(mShape == kPlane){
            ret = Dot(vout, unk194);
            Scale(unk194, ret, vout);
        }
        return ret;
    }
    
    void SyncWorldState(){
        unk1a0 = WorldXfm().v;
        if(mShape >= 3 || mShape == 0){
            unk194 = WorldXfm().m.x;
            unk190 = 1.0f / LengthSquared(unk194);
        }
        if(mShape >= 3){
            unk18c = 1.0f / (mCurLength[1] - mCurLength[0]);
        }
    }

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(CharCollide)
    static void Init(){
        REGISTER_OBJ_FACTORY(CharCollide)
    }

    /** "Type of collision" */
    Shape mShape; // 0x90
    int mFlags; // 0x94
    /** "Optional mesh that will deform, used to resize ourselves.  If this is set, make sure you are not parented to any bone with scale, such as an exo bone" */
    ObjPtr<RndMesh> mMesh; // 0x98
    CSHA1::Digest mDigest; // 0xa4
    CharCollideStruct unk_structs[8]; // 0xb8 - 0x134, inclusive
    // radius0: "Radius of the sphere, or of length0 hemisphere if cigar"
    // radius1: "cigar: Radius of length1 hemisphere"
    float mOrigRadius[2]; // 0x138 - radius0 at 0x138, radius1 at 0x13c
    // length0: "cigar: placement of radius0 hemisphere along X axis, must be < than length0, not used for sphere shapes"
    // length1: "cigar: placement of radius1 hemisphere along X axis, must be >= length0"
    float mOrigLength[2]; // 0x140 - length0 at 0x140, length1 at 0x144
    Transform unk148; // 0x148
    float mCurRadius[2]; // 0x178
    float mCurLength[2]; // 0x180
    /** "For spheres + cigars, finds mesh points along positive y axis (the green one), makes a better fit for spheres where only one side should be the fit, like for chest and back collision volumes" */
    bool mMeshYBias; // 0x188
    float unk18c;
    float unk190;
    Vector3 unk194;
    Vector3 unk1a0;
};
