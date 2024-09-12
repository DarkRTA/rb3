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

    ObjPtr<RndMesh, ObjectDir> unk1c; // 0x1c
    ObjPtr<RndMesh, ObjectDir> unk28; // 0x28
    ObjPtr<RndTransformable, ObjectDir> unk34; // 0x34
    ObjPtr<RndTransformable, ObjectDir> unk40; // 0x40
    ObjPtr<RndTransformable, ObjectDir> unk4c; // 0x4c
    int unk58; // 0x58
    std::vector<int> unk5c; // 0x5c
    std::vector<bool> unk64; // 0x64
    ObjPtr<RndTransformable, ObjectDir> unk6c; // 0x6c
    ObjPtr<RndTransformable, ObjectDir> unk78; // 0x78
    ObjPtr<RndTransformable, ObjectDir> unk84; // 0x84
    ObjPtr<RndTransformable, ObjectDir> unk90; // 0x90
    ObjPtr<RndTransformable, ObjectDir> unk9c; // 0x9c
    ObjPtr<RndTransformable, ObjectDir> unka8; // 0xa8
    std::vector<float> unkb4; // 0xb4
    std::vector<float> unkbc; // 0xbc
    int unkc4; // 0xc4
    float unkc8; // 0xc8
    float unkcc; // 0xcc
    float unkd0; // 0xd0
    std::map<unsigned short, unsigned short> unkd4; // 0xd4
    std::map<unsigned short, unsigned short> unkf8; // 0xf8
};