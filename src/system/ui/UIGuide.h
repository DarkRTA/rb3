#pragma once
#include "obj/Object.h"
#include "utl/MemMgr.h"

/** "a guide used to line up UI elements" */
class UIGuide : public Hmx::Object {
public:
    enum Type {
        kGuideVertical,
        kGuideHorizontal
    };

    UIGuide();
    virtual ~UIGuide();
    OBJ_CLASSNAME(UIGuide);
    OBJ_SET_TYPE(UIGuide);
    virtual DataNode Handle(DataArray *, bool);
    virtual bool SyncProperty(DataNode &, DataArray *, int, PropOp);
    virtual void Save(BinStream &);
    virtual void Copy(const Hmx::Object *, Hmx::Object::CopyType);
    virtual void Load(BinStream &);

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD
    NEW_OBJ(UIGuide);
    static void Init() { REGISTER_OBJ_FACTORY(UIGuide); }

    /** "Horizontal or vertical guide?" */
    Type mType;
    /** "position in proportion to screen width (if vertical) or height (if horizontal)".
     * Ranges from 0 to 1. */
    float mPos;
};
