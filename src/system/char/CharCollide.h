#ifndef CHAR_CHARCOLLIDE_H
#define CHAR_CHARCOLLIDE_H
#include "rndobj/Trans.h"
#include "rndobj/Mesh.h"
#include "obj/ObjPtr_p.h"

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
        int unk0;
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

    float GetRadius(const Vector3& v1, Vector3& vout) const {
        Subtract(v1, unk1a0, vout);
        float ret = unk178;
        if(mShape >= kCigar){
            float clamped = Clamp(unk180, unk184, unk190 * Dot(vout, unk194));
            ScaleAddEq(vout, unk194, -clamped);
            Interp(ret, unk17c, unk18c * (clamped - unk180), ret);
        }
        else if(mShape == kPlane){
            ret = Dot(vout, unk194);
            Scale(unk194, ret, vout);
        }
        return ret;
    }

    Shape mShape; // 0x90
    int mFlags; // 0x94
    ObjPtr<RndMesh, ObjectDir> mMesh; // 0x98
    int unka4, unka8, unkac, unkb0, unkb4;
    CharCollideStruct unk_structs[8]; // 0xb8 - 0x134, inclusive
    float mRadius[2]; // 0x138 - radius0 at 0x138, radius1 at 0x13c
    float mLength[2]; // 0x140 - length0 at 0x140, length1 at 0x144
    Transform unk148; // 0x148
    float unk178;
    float unk17c, unk180, unk184;
    bool unk188; // 0x188
    float unk18c;
    float unk190;
    Vector3 unk194;
    Vector3 unk1a0;
};

#endif
