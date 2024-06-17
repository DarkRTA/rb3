#ifndef CHAR_CHARSERVOBONE_H
#define CHAR_CHARSERVOBONE_H
#include "rndobj/Highlightable.h"
#include "char/CharPollable.h"
#include "char/CharBonesMeshes.h"
#include "obj/ObjPtr_p.h"

// forward decs
class RndEnviron;
class Vector3;
class Character;
class Waypoint;

class CharServoBone : public RndHighlightable, public CharPollable, public CharBonesMeshes {
public:
    CharServoBone();
    virtual ~CharServoBone();
    virtual void Highlight();
    OBJ_CLASSNAME(CharServoBone);
    OBJ_SET_TYPE(CharServoBone);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void Poll();    
    virtual void PollDeps(std::list<Hmx::Object*>&, std::list<Hmx::Object*>&);
    virtual void Enter();
    virtual void SetName(const char*, class ObjectDir*);
    virtual void ReallocateInternal();

    void SetClipType(Symbol);
    void SetMoveSelf(bool);
    void ZeroDeltas();

    DECLARE_REVS;
    DELETE_OVERLOAD;

    RndEnviron* mPelvis; // 0x74
    float* mFacingRotDelta; // 0x78
    Vector3* mFacingPosDelta; // 0x7c
    float* mFacingRot; // 0x80
    Vector3* mFacingPos; // 0x84
    bool mMoveSelf; // 0x88
    bool mDeltaChanged; // 0x89
    Character* mMe; // 0x8c
    Symbol mClipType; // 0x90
    ObjPtr<Waypoint, ObjectDir> mRegulate; // 0x94
};

#endif
