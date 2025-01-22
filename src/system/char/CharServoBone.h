#pragma once
#include "rndobj/Highlightable.h"
#include "char/CharPollable.h"
#include "char/CharBonesMeshes.h"
#include "char/Waypoint.h"
#include "obj/ObjPtr_p.h"

// forward decs
class RndEnviron;
class Vector3;
class Character;
class CharClipDriver;

/** "Sets bone transforms and regulates Character center to a spot." */
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
    void MoveToFacing(Transform&);
    void MoveToDeltaFacing(Transform&);
    void Regulate();
    void DoRegulate(Waypoint*, CharClipDriver*, float, float);
    void SetRegulateWaypoint(Waypoint* wp){ mRegulate = wp; }

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(CharServoBone)
    static void Init(){
        REGISTER_OBJ_FACTORY(CharServoBone)
    }

    RndTransformable* mPelvis; // 0x74
    float* mFacingRotDelta; // 0x78
    Vector3* mFacingPosDelta; // 0x7c
    float* mFacingRot; // 0x80
    Vector3* mFacingPos; // 0x84
    /** "Move ourselves around when playing animations" */
    bool mMoveSelf; // 0x88
    bool mDeltaChanged; // 0x89
    Character* mMe; // 0x8c
    /** "What degrees of freedom we can accomodate" */
    Symbol mClipType; // 0x90
    /** "Waypoint to regulate to" */
    ObjPtr<Waypoint> mRegulate; // 0x94
};
