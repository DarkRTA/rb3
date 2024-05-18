#ifndef CHAR_CHARMESHHIDE_H
#define CHAR_CHARMESHHIDE_H
#include "obj/Object.h"
#include "obj/ObjPtr_p.h"
#include "obj/ObjVector.h"
#include "rndobj/Draw.h"

class CharMeshHide : public Hmx::Object {
public:

    class Hide {
    public:
        Hide(Hmx::Object*);
        Hide(const Hide&);
        Hide& operator=(const Hide&);

        ObjPtr<RndDrawable, ObjectDir> mDraw;
        int mFlags;
        bool mShow;
    };

    CharMeshHide();
    virtual ~CharMeshHide();
    OBJ_CLASSNAME(CharMeshHide);
    OBJ_SET_TYPE(CharMeshHide);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);

    DECLARE_REVS;

    NEW_OVERLOAD;
    DELETE_OVERLOAD;

    static void Init();
    NEW_OBJ(CharMeshHide);

    ObjVector<Hide> mHides;
    int mFlags;
};

#endif
