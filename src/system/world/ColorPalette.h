#pragma once
#include "obj/Object.h"
#include "math/Color.h"
#include "utl/MemMgr.h"
#include <vector>

class ColorSet {
public:
    Hmx::Color mPrimary;
    Hmx::Color mSecondary;
};

/**
 * @brief Contains a set of colors.
 * Original _objects description:
 * "List of primary/secondary colors for OutfitConfig"
 */
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
    
    const Hmx::Color& GetColor(int idx) const {
        MILO_ASSERT(mColors.size(), 0x19);
        return mColors[idx % mColors.size()];
    }
    int NumColors() const { return mColors.size(); }

    DECLARE_REVS
    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(ColorPalette)
    static void Init(){
        REGISTER_OBJ_FACTORY(ColorPalette)
    }

    /** "Color for materials" */
    std::vector<Hmx::Color> mColors; // 0x1C
};

BinStream& operator>>(BinStream&, ColorSet&);
