#pragma once
#include "char/CharPollable.h"
#include "rndobj/Highlightable.h"
#include "obj/ObjPtr_p.h"
#include "rndobj/Trans.h"
#include "math/Vec.h"

/** "Offsets a dest bone." */
class CharBoneOffset : public CharPollable, public RndHighlightable {
public:
    CharBoneOffset();
    OBJ_CLASSNAME(CharBoneOffset);
    OBJ_SET_TYPE(CharBoneOffset);
    virtual DataNode Handle(DataArray*, bool);
    virtual void Poll();
    virtual ~CharBoneOffset(){}
    virtual void PollDeps(std::list<Hmx::Object*>&, std::list<Hmx::Object*>&);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void Highlight();

    void ApplyToLocal();

    DECLARE_REVS
    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(CharBoneOffset)
    static void Init(){
        REGISTER_OBJ_FACTORY(CharBoneOffset)
    }

    /** "The bone to offset" */
    ObjPtr<RndTransformable> mDest; // 0x10
    /** "the offset" */
    Vector3 mOffset; // 0x1c
};
