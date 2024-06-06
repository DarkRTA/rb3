#ifndef WORLD_COLORPALETTE_H
#define WORLD_COLORPALETTE_H
#include "obj/Object.h"
#include "math/Color.h"
#include "utl/MemMgr.h"
#include <vector>

class ColorSet {
public:
    Hmx::Color mPrimary;
    Hmx::Color mSecondary;
};

class ColorPalette : public Hmx::Object {
    public:
    ColorPalette();
    virtual ~ColorPalette(){}
    OBJ_CLASSNAME(ColorPalette);
    OBJ_SET_TYPE(ColorPalette);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    
    NEW_OVERLOAD
    DECLARE_REVS
    NEW_OBJ(ColorPalette)

    std::vector<Hmx::Color> mColors;
};

BinStream& operator>>(BinStream&, ColorSet&);

#endif
