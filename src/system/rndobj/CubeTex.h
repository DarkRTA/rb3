#ifndef RNDOBJ_CUBETEX_H
#define RNDOBJ_CUBETEX_H
#include "obj/Object.h"
#include "utl/FilePath.h"
#include "rndobj/Bitmap.h"

class RndCubeTex : public Hmx::Object {
public:

    enum CubeFace {
        kCubeFaceRight,
        kCubeFaceLeft,
        kCubeFaceTop,
        kCubeFaceBottom,
        kCubeFaceFront,
        kCubeFaceBack,
        kNumCubeFaces
    };

    class CubeTexProperties {
    public:
        CubeTexProperties(){ Init(); }
        void Init(){ mOrder = mNumMips = mBpp = mHeight = mWidth = 0; }
        void Set(const RndBitmap&);
        void Load(BinStream&);

        int mWidth, mHeight, mBpp, mNumMips, mOrder;
    };

    RndCubeTex();
    virtual ~RndCubeTex();
    OBJ_CLASSNAME(CubeTex);
    OBJ_SET_TYPE(CubeTex);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void PreLoad(BinStream&);
    virtual void PostLoad(BinStream&);
    virtual void Select(int);
    virtual void Reset();
    virtual void Sync();

    void operator delete(void* v){
        _MemFree(v);
    }

    static Hmx::Object* NewObject();

    CubeTexProperties props;
    CubeTexProperties moreprops[6];
    FilePath mFile[6];
    RndBitmap mBitmap[6];
};

#endif // RNDOBJ_BITMAP_H
