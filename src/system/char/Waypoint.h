#ifndef CHAR_WAYPOINT_H
#define CHAR_WAYPOINT_H

#include "obj/ObjPtr_p.h"
#include "obj/ObjVector.h"
#include "rndobj/Trans.h"
#include <list>

class Waypoint : public RndTransformable { // 0xe4
    Waypoint();
    virtual ~Waypoint();
    OBJ_CLASSNAME(Waypoint)
    OBJ_SET_TYPE(Waypoint)
    virtual void Save(BinStream&);
    virtual void Load(BinStream&);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Highlight();

    static DataNode OnWaypointFind(DataArray*);
    static DataNode OnWaypointNearest(DataArray*);
    static DataNode OnWaypointLast(DataArray*);
    static Waypoint* Find(int);

    int mFlags;
    float mRadius, mYRadius, d;
    int pad, e;
    float mStrictRadiusDelta;
    ObjVector<ObjOwnerPtr<Waypoint, ObjectDir>, u16> mConnections; // this is an ObjVector :D

    static void Init();
    static void Terminate();

    NEW_OBJ(Waypoint)

    static std::list<Waypoint*>* sWaypoints;
    DECLARE_REVS
};

#endif // CHAR_WAYPOINT_H
