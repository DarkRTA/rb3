#include "Trans.h"
#include "os/System.h"
#include <new>
#include "utl/PoolAlloc.h"

void RndTransformable::Init() {
    RegisterFactory(StaticClassName(), (*NewObject));
    Symbol dingus_a("rnd");
    DataArray* dingus_da = SystemConfig(dingus_a);
    Symbol dingus_b("shadow_plane");
    // dingus_da->FindData(dingus_b, sShadowPlane, true);
}

RndTransformable::RndTransformable() : mParent(this, NULL),  mTarget(this, NULL), mConstraint(kNone), mPreserveScale(0) {
    mLocalXfm.Reset();
    mWorldXfm.Reset();
    vptr = new (_PoolAlloc(0xc, 0xc, FastPool)) (std::vector<int>);
}
