#pragma once
#include "char/CharBones.h"
#include "char/CharPollable.h"
#include "obj/ObjPtr_p.h"

/** "Blends itself into another CharBones, clearing self each frame" */
class CharBonesBlender : public CharPollable, public CharBonesAlloc {
public:
    CharBonesBlender();
    OBJ_CLASSNAME(CharBonesBlender);
    OBJ_SET_TYPE(CharBonesBlender);
    virtual DataNode Handle(DataArray*, bool);
    virtual void Poll();
    virtual void Enter();
    virtual ~CharBonesBlender();
    virtual void PollDeps(std::list<Hmx::Object*>&, std::list<Hmx::Object*>&);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void ReallocateInternal();
    
    void SetDest(CharBonesObject*);
    void SetClipType(Symbol);

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(CharBonesBlender)
    static void Init(){
        REGISTER_OBJ_FACTORY(CharBonesBlender)
    }
    
    /** "CharBones to blend into" */
    ObjPtr<CharBonesObject> mDest; // 0x5c
    /** "What type of clip we can accommodate" */
    Symbol mClipType; // 0x68
};
