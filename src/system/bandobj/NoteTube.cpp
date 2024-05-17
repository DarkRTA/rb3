#include "NoteTube.h"
#include "os/Debug.h"

NoteTube::NoteTube() : unk_0x1C(false), unk_0x20(-1), unk_0x24(false), mGlowLevel(-1), unk_0x2C(0), unk_0x2D(0), 
    unk_0x30(0), unk_0x34(0), unk_0x38(0), unk_0x3C(0), unk_0x40(0), unk_0x44(0), unk_0x48(0), unk_0x4C(0), 
    unk_0x50(0), unk_0x54(0), unk_0x60(1) { mPoints.reserve(100); }

void NoteTube::SetNumPoints(int i) { 
    if (i > mPoints.capacity()) MILO_WARN("Reallocating NoteTube point buffer to %d; please alert HUD/Track owner!", i);
    mPoints.resize(i); 
}

void NoteTube::SetPointPos(int i, Vector3 v) {
    if (i < mPoints.size() ) mPoints[i] = v;
    else MILO_WARN("note tube has too few points");
    
    return;
}

void NoteTube::SetGlowLevel(int i) {
    mGlowLevel = 3 - i;
    MILO_ASSERT(( 0) <= (mGlowLevel) && (mGlowLevel) < ( NumGlowLevels()), 73);
}