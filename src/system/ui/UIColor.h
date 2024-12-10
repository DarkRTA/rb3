#pragma once
#include "obj/Object.h"
#include "math/Color.h"

 /**
 * @brief A color to used by UI objects.
 * Original _objects description:
 * "Just a color, used by UI components"
 */
class UIColor : public Hmx::Object {
public:
    UIColor();
    virtual ~UIColor(){}
    OBJ_CLASSNAME(UIColor);
    OBJ_SET_TYPE(UIColor);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);

    const Hmx::Color& GetColor() const;
    void SetColor(const Hmx::Color&);

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(UIColor);
    static void Init(){
        REGISTER_OBJ_FACTORY(UIColor);
    }

    /** The color. */
    Hmx::Color mColor;
};
