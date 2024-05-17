#include "Waypoint.h"
#include "obj/DataFunc.h"
#include "obj/Object.h"
#include "rndobj/Mesh.h"
#include "rndobj/Trans.h"
#include "utl/Symbols.h"
#include "utl/Symbols4.h"

INIT_REVS(Waypoint)

std::list<Waypoint*>* Waypoint::sWaypoints;

void Waypoint::Init() {
    Hmx::Object::RegisterFactory(StaticClassName(), NewObject);
    DataRegisterFunc("waypoint_find", &OnWaypointFind);
    DataRegisterFunc("waypoint_nearest", &OnWaypointNearest);
    DataRegisterFunc("waypoint_last", &OnWaypointLast);
    sWaypoints = new std::list<Waypoint*>;
}

void Waypoint::Terminate() {
    delete sWaypoints;
    sWaypoints = 0;
}

Waypoint* Waypoint::Find(int flags2) {
    for (std::list<Waypoint*>::iterator i = sWaypoints->begin(); i != sWaypoints->end(); i++) {
        if ((*i)->mFlags & flags2) return *i;
    } return NULL;
}

DataNode Waypoint::OnWaypointFind(DataArray* da) {
    return DataNode(Waypoint::Find(da->Int(1)));
}

Waypoint::Waypoint() : mConnections(this) {

}

Waypoint::~Waypoint() {

}

void Waypoint::Highlight() { }

SAVE_OBJ(Waypoint, 460)

void Waypoint::Load(BinStream& bs) {
    LOAD_REVS(bs)
    ASSERT_REVS(5, 0)
    Hmx::Object::Load(bs);
    if (gRev < 5) { RndMesh* x = Hmx::Object::New<RndMesh>(); x->RndDrawable::Load(bs); delete x; } // why not just DumpLoad...?
    RndTransformable::Load(bs);
    bs >> mFlags;
    bs >> mConnections;
    if (gRev > 1) {
        bs >> mRadius;
    } else mRadius = 12;
    if (gRev > 2) {
        bs >> mYRadius;
        bs >> d;
    }
    if (gRev > 3) {
        bs >> mStrictRadiusDelta;
        bs >> e;
    }
}

BEGIN_PROPSYNCS(Waypoint)
    SYNC_PROP(flags, mFlags)
    SYNC_PROP(radius, mRadius)
    SYNC_PROP(y_radius, mYRadius)

    SYNC_PROP(strict_radius_delta, mStrictRadiusDelta)
    SYNC_PROP(connections, mConnections)
    SYNC_SUPERCLASS(RndTransformable)
END_PROPSYNCS

BEGIN_HANDLERS(Waypoint) 
    HANDLE_SUPERCLASS(RndTransformable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(524)
END_HANDLERS
