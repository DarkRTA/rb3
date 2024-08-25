#include "char/ClipCollide.h"
#include "rndobj/Graph.h"
#include "char/Character.h"
#include "char/Waypoint.h"
#include "char/CharClip.h"

ClipCollide::ClipCollide() : mReports(), mGraph(0), mChar(this, 0), mCharPath(""), mWaypoint(this, 0), mPosition(Symbol("front")), mClip(this, 0), mWorldLines(0), mMoveCamera(1), mMode() {
    mGraph = RndGraph::Get(this);
}

ClipCollide::~ClipCollide(){
    RndGraph::Free(this, false);
}