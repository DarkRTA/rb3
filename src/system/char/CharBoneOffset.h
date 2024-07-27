#ifndef CHAR_CHARBONEOFFSET_H
#define CHAR_CHARBONEOFFSET_H
#include "char/CharPollable.h"
#include "rndobj/Highlightable.h"
#include "obj/ObjPtr_p.h"
#include "rndobj/Trans.h"
#include "math/Vec.h"

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

    ObjPtr<RndTransformable, ObjectDir> mDest; // 0x10
    Vector3 mOffset; // 0x1c
};

#endif
