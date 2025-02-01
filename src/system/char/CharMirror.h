#pragma once
#include "char/CharWeightable.h"
#include "char/CharPollable.h"
#include "obj/ObjPtr_p.h"
#include "char/CharBones.h"
#include "char/CharServoBone.h"
#include <vector>

/** "Duplicates or mirrors another character's motions, given
 *  the matching bone servo." */
class CharMirror : public CharWeightable, public CharPollable {
public:
    struct MirrorOp {
        void *ptr; // 0x0
        Symbol op; // 0x4
    };

    CharMirror();
    OBJ_CLASSNAME(CharMirror);
    OBJ_SET_TYPE(CharMirror);
    virtual DataNode Handle(DataArray *, bool);
    virtual bool SyncProperty(DataNode &, DataArray *, int, PropOp);
    virtual void Save(BinStream &);
    virtual void Copy(const Hmx::Object *, Hmx::Object::CopyType);
    virtual void Load(BinStream &);
    virtual ~CharMirror() {}
    virtual void Poll();
    virtual void PollDeps(std::list<Hmx::Object *> &, std::list<Hmx::Object *> &);

    void SetServo(CharServoBone *);
    void SetMirrorServo(CharServoBone *);
    void SyncBones();

    DECLARE_REVS;
    DELETE_OVERLOAD;
    NEW_OBJ(CharMirror)
    static void Init() { REGISTER_OBJ_FACTORY(CharMirror) }

    /** "The servo to change" */
    ObjPtr<CharServoBone> mServo; // 0x20
    /** "The servo we want to mirror" */
    ObjPtr<CharServoBone> mMirrorServo; // 0x2c
    CharBonesAlloc mBones; // 0x38
    std::vector<MirrorOp> mOps; // 0xac
};
