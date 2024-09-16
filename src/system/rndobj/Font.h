#ifndef RNDOBJ_FONT_H
#define RNDOBJ_FONT_H
#include "obj/Object.h"
#include "obj/ObjMacros.h"
#include "obj/ObjPtr_p.h"
#include "utl/MemMgr.h"
#include <string.h>
#include <map>  

class RndMat;

struct MatChar {
    float width;
    float height;
};

class RndFont : public Hmx::Object {
public:

    struct CharInfo {
        float unk0;
        float unk4;
        float charWidth;
        float unkc;
    };

    struct KernInfo { public:
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

    void GetTexCoords(unsigned short, Vector2&, Vector2&) const;
    void GetKerning(std::vector<KernInfo>&) const;
    void SetKerning(const std::vector<KernInfo>&);
    void SetBaseKerning(float);
    void SetCellSize(float, float);
    void SetBitmapSize(const Vector2&, unsigned int, unsigned int);
    RndTex* ValidTexture() const;
    void UpdateChars();
    void BleedTest();
    int NonTransparentColumn(RndBitmap&, int, int, int, int);
    RndMat* GetMat() const { return mMat; }
    bool HasChar(char c) const { // fak

    } 

    NEW_OVERLOAD
    NEW_OBJ(RndFont)
    static void Init(){
        REGISTER_OBJ_FACTORY(RndFont)
    }
    DECLARE_REVS

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

class BitmapLocker {
public:
    BitmapLocker(RndFont* f) {
        RndBitmap bmp;
        RndTex* t = f->ValidTexture();
        if (t) {
            const char* c = t->File().c_str();
            int len = strlen(c);
            if (len >= 4 && UsingCD() && stricmp(c + len - 4, ".bmp")) {
                t->LockBitmap(bmp, 3);
            }
            bmp.LoadBmp("", false, false);
        }
    }
};

BinStream& operator>>(BinStream&, MatChar&);
BinStream& operator>>(BinStream&, RndFont::KernInfo&);

#endif // RNDOBJ_FONT_H
