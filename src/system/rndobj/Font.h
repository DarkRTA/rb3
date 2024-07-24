#ifndef RNDOBJ_FONT_H
#define RNDOBJ_FONT_H
#include "obj/Object.h"
#include "obj/ObjPtr_p.h"
#include "utl/MemMgr.h"
#include <map>

class RndMat;

struct MatChar {
    float width;
    float height;
};

class RndFont : public Hmx::Object {
public:

    class CharInfo {
        float unk0;
        float unk4;
        float charWidth;
        float unkc;
    };

    class KernInfo {
        short unk0;
        short unk2;
        int unk4;
    };

    RndFont();
    virtual ~RndFont();
    virtual void Replace(Hmx::Object*, Hmx::Object*);
    OBJ_CLASSNAME(Font);
    OBJ_SET_TYPE(Font);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void Print();

    void GetKerning(std::vector<KernInfo>&) const;
    void SetKerning(const std::vector<KernInfo>&);
    void SetBaseKerning(float);

    NEW_OVERLOAD;
    NEW_OBJ(RndFont)
    static void Init(){
        REGISTER_OBJ_FACTORY(RndFont)
    }

    ObjPtr<RndMat, ObjectDir> mMat; // 0x1c
    ObjOwnerPtr<RndFont, ObjectDir> mTextureOwner; // 0x28
    std::map<char, MatChar> unk34; // 0x34
    int unk4c; // 0x4c
    float mBaseKerning; // 0x50
    Vector2 mCellSize; // 0x54 - cell width, cell height
    float mDeprecatedSize; // 0x5c
    std::vector<unsigned short> mChars; // 0x60
    bool mMonospace; // 0x68
    Vector2 unk6c; // 0x6c
    bool mPacked; // 0x74
    ObjPtr<RndFont, ObjectDir> unk78; // 0x78
}; 

#endif // RNDOBJ_FONT_H
