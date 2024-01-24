#ifndef RND_RNDCUBETEX_HPP
#define RND_RNDCUBETEX_HPP
#include "hmx/object.hpp"
#include "rndbitmap.hpp"
#include "filepath.hpp"

class RndCubeTex : public Hmx::Object {
public:

    class CubeTexProperties {
    public:
        CubeTexProperties();
        void Init();

        int unk0, unk4, unk8, unkc, unk10;
    };

    RndCubeTex();
    virtual ~RndCubeTex();
    virtual Symbol ClassName() const;
    virtual void SetType(Symbol);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void PreLoad(BinStream&);
    virtual void PostLoad(BinStream&);

    static Symbol StaticClassName();
    static Hmx::Object* NewObject();

    CubeTexProperties props;
    CubeTexProperties moreprops[6];
    FilePath paths[6];
    RndBitmap bitmaps[6];
};

#endif
