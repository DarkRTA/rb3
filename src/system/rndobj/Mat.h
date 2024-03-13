#ifndef RNDOBJ_MAT_H
#define RNDOBJ_MAT_H
#include "rndobj/Tex.h"
#include "obj/Object.h"
#include "obj/ObjPtr_p.h"
#include "math/Color.h"
#include "math/Mtx.h"
#include <vector>

struct MatPerfSettings {
    unsigned char uc;
};

struct MatShaderOptions {
    int i1, i2;
};

class RndMat : public Hmx::Object {
public:
    RndMat();
    virtual ~RndMat();
    OBJ_CLASSNAME(Mat);
    OBJ_SET_TYPE(Mat);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);

    Hmx::Color mColor; // 0x1C
    Transform unk20; // 0x20
    ObjPtr<RndTex, ObjectDir> unk5c;
    int unk68;
    ObjPtr<RndMat, ObjectDir> unk6c;
    float unk78;
    ObjPtr<RndTex, ObjectDir> unk7c;
    float unk88;
    ObjPtr<RndTex, ObjectDir> unk8c;
    std::vector<int> unk98;
    MatPerfSettings unka0;
    MatShaderOptions unka4;
    unsigned char unkac, unkad;
    int unkb0, unkb4;
};

#endif
