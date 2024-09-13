#pragma once
#include "obj/Object.h"
#include "rndobj/Mesh.h"
#include "rndobj/Trans.h"

class ChordShapeGenerator : public Hmx::Object {
public:
    ChordShapeGenerator();
    virtual ~ChordShapeGenerator(){}
    OBJ_CLASSNAME(ChordShapeGenerator);
    OBJ_SET_TYPE(ChordShapeGenerator);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);

    DataNode OnGenerate(const DataArray*);
    DataNode OnInvert(const DataArray*);
    DataNode OnSetStringFret(const DataArray*);
    DataNode OnGetStringTrans(const DataArray*);

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;

    ObjPtr<RndMesh, ObjectDir> mFingerSrcMesh; // 0x1c
    ObjPtr<RndMesh, ObjectDir> mChordSrcMesh; // 0x28
    ObjPtr<RndTransformable, ObjectDir> mBaseXSection; // 0x34
    ObjPtr<RndTransformable, ObjectDir> mContourXSection; // 0x40
    ObjPtr<RndTransformable, ObjectDir> mBaseHeight; // 0x4c
    int mNumSlots; // 0x58
    std::vector<int> mStringFrets; // 0x5c
    std::vector<bool> unk64; // 0x64
    ObjPtr<RndTransformable, ObjectDir> mString0; // 0x6c
    ObjPtr<RndTransformable, ObjectDir> mString1; // 0x78
    ObjPtr<RndTransformable, ObjectDir> mString2; // 0x84
    ObjPtr<RndTransformable, ObjectDir> mString3; // 0x90
    ObjPtr<RndTransformable, ObjectDir> mString4; // 0x9c
    ObjPtr<RndTransformable, ObjectDir> mString5; // 0xa8
    std::vector<float> mFretHeights; // 0xb4
    std::vector<float> mGradeDistances; // 0xbc
    int unkc4; // 0xc4
    float unkc8; // 0xc8
    float unkcc; // 0xcc
    float unkd0; // 0xd0
    std::map<unsigned short, unsigned short> unkd4; // 0xd4
    std::map<unsigned short, unsigned short> unkf8; // 0xf8
};