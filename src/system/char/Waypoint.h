#pragma once
#include "rndobj/Trans.h"
#include "obj/ObjVector.h"
#include <list>

/** "A waypoint for character movement. Characters walk to
 *  these, start themselves out from these, etc." */
class Waypoint : public RndTransformable { // 0xe4
public:
    Waypoint();
    virtual ~Waypoint();
    OBJ_CLASSNAME(Waypoint)
    OBJ_SET_TYPE(Waypoint)
    virtual void Save(BinStream &);
    virtual void Copy(const Hmx::Object *, Hmx::Object::CopyType);
    virtual void Load(BinStream &);
    virtual DataNode Handle(DataArray *, bool);
    virtual bool SyncProperty(DataNode &, DataArray *, int, PropOp);
    virtual void Highlight();

    void Constrain(Transform &);
    void ShapeDelta(const Vector3 &, Vector3 &);
    float ShapeDelta(float);
    void ShapeDeltaBox(const Vector3 &, float, float, Vector3 &);
    float ShapeDeltaAng(float, float);

    void SetRadius(float r) { mRadius = r; }
    void SetStrictRadiusDelta(float r) { mStrictRadiusDelta = r; }
    void SetAngRadius(float r) { mAngRadius = r; }
    void SetStrictAngDelta(float d) { mStrictAngDelta = d; }

    static DataNode OnWaypointFind(DataArray *);
    static DataNode OnWaypointNearest(DataArray *);
    static DataNode OnWaypointLast(DataArray *);
    static Waypoint *Find(int);
    static std::list<Waypoint *> *sWaypoints;

    static void Init();
    static void Terminate();
    static void Register() { REGISTER_OBJ_FACTORY(Waypoint); }
    NEW_OBJ(Waypoint)
    DECLARE_REVS

    /** "Flags for this waypoint, should be a bitfield per app" */
    int mFlags; // 0x90
    /** "Radius within we can stop from a walk, or be tethered to" */
    float mRadius; // 0x94
    /** "If positive, makes this shape a box with radius the x axis X half width, and
     * y_radius the Y axis half width" */
    float mYRadius; // 0x98
    /** "Angular slop in degrees away from y axis" */
    float mAngRadius; // 0x9c
    int pad; // 0xa0
    /** "degrees beyond ang radius you can never rotate past, if >= 0" */
    float mStrictAngDelta; // 0xa4
    /** "how much beyond radius you will never leave, it will forcibly pull you back,
     * ignored if <= 0" */
    float mStrictRadiusDelta; // 0xa8
    /** "Waypoints we can walk to" */
    ObjVector<ObjOwnerPtr<Waypoint> > mConnections; // 0xac
};
