#pragma once
#include "obj/Object.h"
#include "obj/ObjMacros.h"
#include "obj/ObjPtr_p.h"
#include "os/System.h"
#include "rndobj/Bitmap.h"
#include "utl/MemMgr.h"
#include <string.h>
#include <map>  

class RndMat;

struct MatChar {
    float width;
    float height;
};

/**
 * @brief Implements fonts for use with RndText objects.
 *  Additionally, RndFont can dynamically update the font atlas, cell sizes, and similar.
 *  Original _objects description:
 *   "Font objects determine the appearance for Text objects."
 */

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
    float CharAdvance(unsigned short, unsigned short) const;
    float CharAdvance(unsigned short) const;
    float Kerning(unsigned short, unsigned short) const;
    float CharWidth(unsigned short) const;
    bool CharDefined(unsigned short) const;
    void SetCharInfo(RndFont::CharInfo*, RndBitmap&, const Vector2&);

    RndMat* GetMat() const { return mMat; }
    void SetNextFont(RndFont* font){ unk78 = font; }
    RndFont* NextFont() const { return unk78; }
    bool IsMonospace() const { return mMonospace; }
    bool IsPacked() const { return mPacked; }
    float CellDiff() const { return mCellSize.y / mCellSize.x; }
    bool HasChar(unsigned short c) const {
        return unk34.count(c) != 0;
    }

    NEW_OVERLOAD
    DELETE_OVERLOAD
    NEW_OBJ(RndFont)
    static void Init(){
        REGISTER_OBJ_FACTORY(RndFont)
    }
    DECLARE_REVS

    ObjPtr<RndMat> mMat; // 0x1c
    ObjOwnerPtr<RndFont> mTextureOwner; // 0x28
    std::map<unsigned short, CharInfo> unk34; // 0x34
    int unk4c; // 0x4c
    float mBaseKerning; // 0x50
    Vector2 mCellSize; // 0x54 - cell width, cell height
    float mDeprecatedSize; // 0x5c
    std::vector<unsigned short> mChars; // 0x60
    bool mMonospace; // 0x68
    Vector2 unk6c; // 0x6c
    bool mPacked; // 0x74
    ObjPtr<RndFont> unk78; // 0x78
}; 

class BitmapLocker {
public:
    BitmapLocker(RndFont* f) : mTexture(0), mPbm(0) {
        mTexture = f->ValidTexture();
        if(mTexture){
            const char* filestr = mTexture->mFilepath.c_str();
            int fplen = strlen(filestr);
#ifdef MILO_DEBUG
            if(UsingCD() || fplen < 4 || stricmp(filestr + fplen - 4, ".bmp") != 0){
#endif
                mTexture->LockBitmap(mBm, 3);
                if(mBm.Pixels()){
                    mPbm = &mBm;
                }
#ifdef MILO_DEBUG
            }
            else {
                mBm.LoadBmp(filestr, false, false);
                if(mBm.Pixels()){
                    mPbm = &mBm;
                }
                mTexture = nullptr;
            }
#endif
        }
    }

    ~BitmapLocker(){
        if(mTexture) mTexture->UnlockBitmap();
    }

    RndBitmap* PtrToBitmap() const { return mPbm; }

    RndTex* mTexture; // 0x0
    RndBitmap* mPbm; // 0x4
    RndBitmap mBm; // 0x8
};

BinStream& operator>>(BinStream&, MatChar&);
BinStream& operator>>(BinStream&, RndFont::KernInfo&);
