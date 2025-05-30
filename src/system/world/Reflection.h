#pragma once
#include "rndobj/Draw.h"
#include "rndobj/Trans.h"
#include "char/Character.h"
#include <list>

class WorldReflection : public RndDrawable, public RndTransformable {
public:
    WorldReflection();
    OBJ_CLASSNAME(WorldReflection);
    OBJ_SET_TYPE(WorldReflection);
    virtual DataNode Handle(DataArray *, bool);
    virtual bool SyncProperty(DataNode &, DataArray *, int, PropOp);
    virtual void Save(BinStream &);
    virtual void Copy(const Hmx::Object *, Hmx::Object::CopyType);
    virtual void Load(BinStream &);
    virtual void DrawShowing();
    virtual void Highlight() { RndDrawable::Highlight(); }
    virtual ~WorldReflection();

    void DoHide();
    void UnHide();
    void DoLOD(int);

    DECLARE_REVS;

    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(WorldReflection)
    static void Init() { REGISTER_OBJ_FACTORY(WorldReflection) }

    ObjPtrList<RndDrawable> mDraws; // 0xb0
    ObjPtrList<Character> mLodChars; // 0xc0
    float mVerticalStretch; // 0xd0
    std::list<void *> unkd4; // 0xd4
    RndCam *unkdc; // 0xdc
    bool unke0; // 0xe0
    ObjPtrList<RndDrawable> mHideList; // 0xe4
    ObjPtrList<RndDrawable> mShowList; // 0xf4
    ObjPtrList<RndDrawable> unk104; // 0x104
    ObjPtrList<RndDrawable> unk114; // 0x114
};