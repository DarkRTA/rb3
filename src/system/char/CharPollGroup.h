#pragma once
#include "char/CharPollable.h"
#include "char/CharWeightable.h"
#include "obj/ObjPtr_p.h"

/** "Group of Charpollable, polled in the order given, use when the automatic CharPollable
 * sorting is not correct or sufficient." */
class CharPollGroup : public CharPollable, public CharWeightable {
public:
    CharPollGroup();
    OBJ_CLASSNAME(CharPollGroup);
    OBJ_SET_TYPE(CharPollGroup);
    virtual DataNode Handle(DataArray *, bool);
    virtual void Poll();
    virtual void Enter();
    virtual void Exit();
    virtual void ListPollChildren(std::list<RndPollable *> &) const;
    virtual ~CharPollGroup();
    virtual void PollDeps(std::list<Hmx::Object *> &, std::list<Hmx::Object *> &);
    virtual bool SyncProperty(DataNode &, DataArray *, int, PropOp);
    virtual void Save(BinStream &);
    virtual void Copy(const Hmx::Object *, Hmx::Object::CopyType);
    virtual void Load(BinStream &);

    /** "sort the pollables" */
    void SortPolls();

    DECLARE_REVS;
    DELETE_OVERLOAD;
    NEW_OBJ(CharPollGroup)
    static void Init() { REGISTER_OBJ_FACTORY(CharPollGroup) }

    /** "Ordered list of CharPollables, will be polled in this order." */
    ObjPtrList<CharPollable> mPolls; // 0x20
    /** "Explicit thing I am changed by, to force sorting, if set, ignores polls" */
    ObjPtr<CharPollable> mChangedBy; // 0x30
    /** "Explicit thing I change, to force sorting, if set, ignores polls" */
    ObjPtr<CharPollable> mChanges; // 0x3c
};
