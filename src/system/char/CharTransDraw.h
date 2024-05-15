#ifndef CHAR_CHARTRANSDRAW_H
#define CHAR_CHARTRANSDRAW_H
#include "rndobj/Draw.h"
#include "obj/ObjPtr_p.h"
#include "char/Character.h"

class CharTransDraw : public RndDrawable {
public:
    CharTransDraw();
    OBJ_CLASSNAME(CharTransDraw);
    OBJ_SET_TYPE(CharTransDraw);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void DrawShowing();
    virtual ~CharTransDraw();

    void SetDrawModes(Character::DrawMode);

    DELETE_OVERLOAD;

    DECLARE_REVS;

    ObjPtrList<Character, ObjectDir> mChars;
};

#endif
