#pragma once
#include "rndobj/Draw.h"
#include "obj/ObjPtr_p.h"
#include "char/Character.h"

/** "Defers drawing translucent parts of characters until this object is drawn" */
class CharTransDraw : public RndDrawable {
public:
    CharTransDraw();
    OBJ_CLASSNAME(CharTransDraw);
    OBJ_SET_TYPE(CharTransDraw);
    virtual DataNode Handle(DataArray *, bool);
    virtual bool SyncProperty(DataNode &, DataArray *, int, PropOp);
    virtual void Save(BinStream &);
    virtual void Copy(const Hmx::Object *, Hmx::Object::CopyType);
    virtual void Load(BinStream &);
    virtual void DrawShowing();
    virtual ~CharTransDraw();

    void SetDrawModes(Character::DrawMode);

    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    DECLARE_REVS;
    NEW_OBJ(CharTransDraw)
    static void Init() { REGISTER_OBJ_FACTORY(CharTransDraw) }

    /** "The Characters whose translucent bits we will draw" */
    ObjPtrList<Character> mChars; // 0x20
};
