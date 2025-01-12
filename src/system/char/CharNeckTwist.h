#ifndef CHAR_CHARNECKTWIST_H
#define CHAR_CHARNECKTWIST_H
#include "char/CharPollable.h"
#include "obj/ObjPtr_p.h"
#include "rndobj/Trans.h"

class CharNeckTwist : public CharPollable {
public:
    CharNeckTwist();
    OBJ_CLASSNAME(CharNeckTwist);
    OBJ_SET_TYPE(CharNeckTwist);
    virtual DataNode Handle(DataArray*, bool);
    virtual void Poll();
    virtual ~CharNeckTwist(){}
    virtual void PollDeps(std::list<Hmx::Object*>&, std::list<Hmx::Object*>&);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);

    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    DECLARE_REVS;
    NEW_OBJ(CharNeckTwist)
    static void Init(){
        REGISTER_OBJ_FACTORY(CharNeckTwist)
    }

    ObjPtr<RndTransformable, ObjectDir> mTwist; // 0x8
    ObjPtr<RndTransformable, ObjectDir> mHead; // 0x14
};

#endif
