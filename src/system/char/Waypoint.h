#ifndef CHAR_WAYPOINT_H
#define CHAR_WAYPOINT_H
#include "rndobj/Trans.h"
#include "obj/ObjVector.h"
#include <list>

class Waypoint : public RndTransformable { // 0xe4
public:
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

    int mFlags; // 0x90
    float mRadius; // 0x94
    float mYRadius; // 0x98
    float mAngRadius; // 0x9c
    int pad; // 0xa0
    float mStrictAngDelta; // 0xa4
    float mStrictRadiusDelta; // 0xa8
    ObjVector<ObjOwnerPtr<Waypoint, ObjectDir>, u16> mConnections; // 0xac

    static void Init();
    static void Terminate();
    static void Register(){
        REGISTER_OBJ_FACTORY(Waypoint);
    }

    NEW_OBJ(Waypoint)

    static std::list<Waypoint*>* sWaypoints;
    DECLARE_REVS
};

#endif // CHAR_WAYPOINT_H
