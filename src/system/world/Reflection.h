#ifndef WORLD_REFLECTION_H
#define WORLD_REFLECTION_H
#include "rndobj/Draw.h"
#include "rndobj/Trans.h"
#include "char/Character.h"
#include <list>

class WorldReflection : public RndDrawable, public RndTransformable {
public:
    WorldReflection();
    OBJ_CLASSNAME(WorldReflection);
    OBJ_SET_TYPE(WorldReflection);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void DrawShowing();
    virtual void Highlight();
    virtual ~WorldReflection();

    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(WorldReflection)
    static void Init(){
        REGISTER_OBJ_FACTORY(WorldReflection)
    }
    
    ObjPtrList<RndDrawable, ObjectDir> unkb0;
    ObjPtrList<Character, ObjectDir> unkc0;
    float unkd0;
    std::list<int> unkd4;
    const char* unkdc;
    bool unke0;
    ObjPtrList<RndDrawable, ObjectDir> unke4;
    ObjPtrList<RndDrawable, ObjectDir> unkf4;
    ObjPtrList<RndDrawable, ObjectDir> unk104;
    ObjPtrList<RndDrawable, ObjectDir> unk114;
};

#endif
