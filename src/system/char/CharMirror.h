#ifndef CHAR_CHARMIRROR_H
#define CHAR_CHARMIRROR_H
#include "char/CharWeightable.h"
#include "char/CharPollable.h"
#include "obj/ObjPtr_p.h"
#include "char/CharBones.h"
#include "char/CharServoBone.h"
#include <vector>

class CharServoBone; // forward dec

class CharMirror : public CharWeightable, public CharPollable {
public:
    CharMirror();
    OBJ_CLASSNAME(CharMirror);
    OBJ_SET_TYPE(CharMirror);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual ~CharMirror(){}
    virtual void Poll();    
    virtual void PollDeps(std::list<Hmx::Object*>&, std::list<Hmx::Object*>&);

    ObjPtr<CharServoBone, ObjectDir> mServo;
    ObjPtr<CharServoBone, ObjectDir> mMirrorServo;
    CharBonesAlloc mBones;
    std::vector<int> mOps;
};

#endif
