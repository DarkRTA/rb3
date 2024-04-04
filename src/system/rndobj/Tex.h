#ifndef RNDOBJ_TEX_H
#define RNDOBJ_TEX_H

#include "obj/Object.h"
#include "rndobj/Bitmap.h"
#include "utl/BinStream.h"
#include "utl/FilePath.h"
#include "utl/Loader.h"

class RndTex : public Hmx::Object {
public:
    enum Type {
        Regular = 1,
        Rendered = 2,
        Movie = 4,
        BackBuffer = 8,
        FrontBuffer = 0x18,
        RenderedNoZ = 0x22,
        ShadowMap = 0x42,
        DepthVolumeMap = 0xA2,
        DensityMap = 0x122,
        Scratch = 0x200,
        DeviceTexture = 0x1000
    };

    // be prepared for virtual spew...
    RndTex();
    virtual ~RndTex();
    OBJ_CLASSNAME(RndTex)
    OBJ_SET_TYPE(RndTex)
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode &, DataArray *, int, PropOp);
    virtual void Save(BinStream &);
    virtual void Copy(const Hmx::Object*, CopyType);
    virtual void Load(BinStream&);
    virtual void Print();
    virtual void PreLoad(BinStream&);
    virtual void PostLoad(BinStream&);
    virtual void SetMipMapK(float);
    virtual void LockBitmap(RndBitmap&, int);
    virtual void UnlockBitmap() {}
    virtual void MakeDrawTarget() {}
    virtual void FinishDrawTarget() {}
    virtual void Compress() {}
    virtual bool TexelsLock(void*&) {return false;}
    virtual void TexelsUnlock() {}
    virtual int TexelsPitch() const;
    virtual void Select(int) {}
    virtual void PresyncBitmap() {}
    virtual void SyncBitmap() {}

    DataNode OnSetRendered(const DataArray*);
    DataNode OnSetBitmap(const DataArray*);

    void SetBitmap(FileLoader*);
    void SetBitmap(const FilePath&);
    void SaveBitmap(const char*);

    DELETE_OVERLOAD;

    RndBitmap mBitmap;
    float mMipMapK;
    Type mType;
    int mWidth;
    int mHeight;
    int mBpp;
    FilePath mFilename;
    FileLoader* mLoader;
    bool mIsPowerOf2;
    bool mOptimizeForPS3;
    int unk60; // this is def a ptr to something judging by the fact it gets released in the dtor
};

bool UseBottomMip();
void CopyBottomMip(RndBitmap&, const RndBitmap&);
char* CheckDim(int, RndTex::Type, bool);
TextStream& operator<<(TextStream&, RndTex::Type);

#endif // RNDOBJ_TEX_H
