#include "TrackTest.h"
#include "obj/Object.h"
#include "track/TrackWidget.h"
#include "utl/Symbols.h"

TrackTest::TrackTest(TrackDir* d) : mDir(d), mWidget(d, NULL), mSlot(0) {}

bool PropSync(TrackTest& e, DataNode& _val, DataArray* _prop, int _i, PropOp _op) {
    if(_i == _prop->Size()) return true; \
    else { \
        Symbol sym = _prop->Sym(_i);
    SYNC_PROP(widget, e.mWidget);
    SYNC_PROP(slot, e.mSlot);
    }
    return false;
}