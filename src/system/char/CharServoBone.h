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

    DELETE_OVERLOAD;

    RndEnviron* mPelvis;
    float* mFacingRotDelta;
    Vector3* mFacingPosDelta;
    float* mFacingRot;
    Vector3* mFacingPos;
    bool mMoveSelf;
    bool mDeltaChanged;
    Character* mMe;
    Symbol mClipType;
    ObjPtr<Waypoint, ObjectDir> mWay;
};

#endif
