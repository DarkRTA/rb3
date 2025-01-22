#pragma once
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "obj/ObjPtr_p.h"
#include "obj/ObjVector.h"
#include "rndobj/Draw.h"

/** "Hides meshes based on flags in other CharMeshHide." */
class CharMeshHide : public Hmx::Object {
public:

    class Hide {
    public:
        Hide(Hmx::Object*);
        Hide(const Hide&);
        Hide& operator=(const Hide&);

        ObjPtr<RndDrawable> mDraw; // 0x0
        int mFlags; // 0xc
        bool mShow; // 0x10
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

    static void HideAll(const ObjPtrList<CharMeshHide>&, int);
    void HideDraws(int);
    int Flags() const { return mFlags; }

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;

    static void Init();
    static void Register(){
        REGISTER_OBJ_FACTORY(CharMeshHide)
    }
    NEW_OBJ(CharMeshHide);

    ObjVector<Hide> mHides; // 0x1c
    int mFlags; // 0x28
};
