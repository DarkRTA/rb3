#include "Waypoint.h"
#include "obj/DataFunc.h"
#include "obj/Object.h"
#include "rndobj/Mesh.h"
#include "rndobj/Trans.h"
#include "math/Rand.h"
#include "math/Rot.h"
#include "utl/Symbols.h"

INIT_REVS(Waypoint)

std::list<Waypoint*>* Waypoint::sWaypoints;

void Waypoint::Init() {
    Register();
    DataRegisterFunc("waypoint_find", &OnWaypointFind);
    DataRegisterFunc("waypoint_nearest", &OnWaypointNearest);
    DataRegisterFunc("waypoint_last", &OnWaypointLast);
    sWaypoints = new std::list<Waypoint*>;
    TheDebug.AddExitCallback(Waypoint::Terminate);
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

Waypoint::Waypoint() : mFlags(0), mRadius(12.0f), mYRadius(0), mAngRadius(0), pad(0), mStrictAngDelta(0), mStrictRadiusDelta(0), mConnections(this) {
    if(RandomFloat() < 0.5f){
        sWaypoints->push_back(this);
    }
    else sWaypoints->push_back(this);
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
        bs >> mAngRadius;
    }
    if (gRev > 3) {
        bs >> mStrictRadiusDelta;
        bs >> mStrictAngDelta;
    }
}

BEGIN_PROPSYNCS(Waypoint)
    SYNC_PROP(flags, mFlags)
    SYNC_PROP(radius, mRadius)
    SYNC_PROP(y_radius, mYRadius)
    SYNC_PROP_SET(ang_radius, mAngRadius * RAD2DEG, mAngRadius = _val.Float(0) * DEG2RAD)
    SYNC_PROP(strict_radius_delta, mStrictRadiusDelta)
    SYNC_PROP_SET(strict_ang_delta, mStrictAngDelta * RAD2DEG, mStrictAngDelta = _val.Float(0) * DEG2RAD)
    SYNC_PROP(connections, mConnections)
    SYNC_SUPERCLASS(RndTransformable)
END_PROPSYNCS

BEGIN_HANDLERS(Waypoint) 
    HANDLE_SUPERCLASS(RndTransformable)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(524)
END_HANDLERS
