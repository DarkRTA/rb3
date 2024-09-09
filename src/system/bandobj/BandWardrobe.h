#pragma once
#include "obj/Object.h"
#include "obj/Dir.h"
#include "char/FileMerger.h"

class TargetNames {
public:
    Symbol names[4];
};

class BandWardrobe : public virtual Hmx::Object {
public:
    BandWardrobe();
    OBJ_CLASSNAME(BandWardrobe);
    OBJ_SET_TYPE(BandWardrobe);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual ~BandWardrobe();

    ObjDirPtr<ObjectDir> unk8; // 0x8
    ObjDirPtr<ObjectDir> unk14; // 0x14
    ObjPtr<FileMerger, ObjectDir> unk20; // 0x20
    std::list<int> unk2c; // 0x2c
    TargetNames unk34; // 0x34
    TargetNames unk44; // 0x44
    TargetNames unk54; // 0x54
    TargetNames* unk64; // 0x64
    int unk68; // 0x68
    int unk6c; // 0x6c
    int unk70; // 0x70
    int unk74; // 0x74
    Symbol unk78; // 0x78
    int unk7c; // 0x7c
    int unk80; // 0x80
    Symbol unk84; // 0x84
    Symbol unk88; // 0x88
    Symbol unk8c; // 0x8c
    ObjPtr<Hmx::Object, ObjectDir> unk90; // 0x90
    bool unk9c; // 0x9c
    bool unk9d; // 0x9d
    Symbol unka0; // 0xa0
    Symbol unka4[4]; // 0xa4
    int unkb4; // 0xb4
};

extern BandWardrobe* TheBandWardrobe;