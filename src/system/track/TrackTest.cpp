#include "track/TrackTest.h"
#include "utl/Symbols.h"

TrackTest::TrackTest(TrackDir *d) : mDir(d), mWidget(d), mSlot(0) {}

BEGIN_CUSTOM_PROPSYNC(TrackTest)
    SYNC_PROP(widget, o.mWidget)
    SYNC_PROP(slot, o.mSlot)
END_CUSTOM_PROPSYNC