#ifndef CHAR_CHARPOLLGROUP_H
#define CHAR_CHARPOLLGROUP_H
#include "char/CharPollable.h"
#include "char/CharWeightable.h"
#include "obj/ObjPtr_p.h"

class CharPollGroup : public CharPollable, public CharWeightable {
public:
    CharPollGroup();
    OBJ_CLASSNAME(CharPollGroup);
    OBJ_SET_TYPE(CharPollGroup);
    virtual DataNode Handle(DataArray*, bool);
    virtual void Poll();
    virtual void Enter();
    virtual void Exit();
    virtual void ListPollChildren(std::list<RndPollable*>&) const;
    virtual ~CharPollGroup();
    virtual void PollDeps(std::list<Hmx::Object*>&, std::list<Hmx::Object*>&);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);

    DECLARE_REVS;
    DELETE_OVERLOAD;

    ObjPtrList<CharPollable, ObjectDir> mPolls;
    ObjPtr<CharPollable, ObjectDir> mChangedBy;
    ObjPtr<CharPollable, ObjectDir> mChanges;
};

#endif
