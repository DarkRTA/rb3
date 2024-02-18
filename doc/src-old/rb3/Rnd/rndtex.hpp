#ifndef RND_RNDTEX_HPP
#define RND_RNDTEX_HPP
#include "obj/Object.h"
#include "utl/FilePath.h"
#include "Rnd/rndbitmap.hpp"

class RndTex : public Hmx::Object {
public:

    // taken from fn_8064084C
    enum Type { 
        Regular = 0x1,
        Rendered = 0x2,
        Movie = 0x4,
        BackBuffer = 0x8,
        FrontBuffer = 0x18,
        RenderedNoZ = 0x22,
        ShadowMap = 0x42,
        DepthVolumeMap = 0xA2,
        DensityMap = 0x122,
        Scratch = 0x200,
        DeviceTexture = 0x1000,
    };

    RndTex();
    virtual ~RndTex();
    virtual Symbol ClassName() const;
    virtual void SetType(Symbol);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);

    virtual void Print();
    virtual void PreLoad(BinStream&);
    virtual void PostLoad(BinStream&);

    static Symbol StaticClassName();
    static Hmx::Object* NewObject();

    RndBitmap bitmap;
    float mipmapK;
    Type type;
    int width;
    int height;
    int bpp;
    FilePath fpath;
    int unk58;
    bool unk5c;
    bool forPS3; // optimize for ps3
    int unk60;
    
};

#endif // RND_RNDTEX_HPP
