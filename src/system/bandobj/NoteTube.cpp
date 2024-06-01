#include "NoteTube.h"
#include "obj/Object.h"
#include "os/Debug.h"
#include "decomp.h"

NoteTube::NoteTube() : unk_0x1C(false), unk_0x20(-1), unk_0x24(false), mGlowLevel(-1), unk_0x2C(0), unk_0x2D(0), 
    unk_0x30(0), unk_0x34(0), unk_0x38(0), unk_0x3C(0), unk_0x40(0), unk_0x44(0), unk_0x48(0), unk_0x4C(0), 
    unk_0x50(0), unk_0x54(0), unk_0x60(1) { mPoints.reserve(100); }

void NoteTube::SetNumPoints(int i) { 
    if (i > mPoints.capacity()) MILO_WARN("Reallocating NoteTube point buffer to %d; please alert HUD/Track owner!", i);
    mPoints.resize(i); 
}

void NoteTube::SetPointPos(int i, Vector3 v) {
    if (i < mPoints.size() ) mPoints[i] = v;
    else MILO_WARN("note tube has too few points\n");
    
    return;
}

DECOMP_FORCEACTIVE(NoteTube, "point pos query out of bounds\n")

void NoteTube::SetGlowLevel(int i) {
    mGlowLevel = 3 - i;
    MILO_ASSERT(( 0) <= (mGlowLevel) && (mGlowLevel) < ( NumGlowLevels()), 73);
}

void NoteTube::BakePlates() {
    if (unk_0x44) unk_0x44->Bake();
    if (unk_0x48) unk_0x48->Bake();
}


TubePlate::TubePlate(int i) : unk_0x0(Hmx::Object::New<RndMesh>()), unk_0x4(0), unk_0x8(i), 
    unk_0xC(3.40282346638528859812e38), unk_0x10(0), unk_0x14(0), unk_0x18(3.40282346638528859812e38), 
    unk_0x1C(3.40282346638528859812e38), unk_0x20(0), unk_0x24(0) {
    unk_0x0->mOwner->mVerts.reserve(unk_0x8, true);
    unk_0x0->mOwner->mFaces.reserve(unk_0x8); // evil regswap
    Reset();
}

TubePlate::~TubePlate() { delete unk_0x0; unk_0x0 = 0; } // why bother setting it to 0 in the dtor...?