#pragma once
#include "obj/ObjPtr_p.h"
#include "obj/PropSync_p.h"
#include "track/TrackDir.h"
#include "track/TrackWidget.h"

class TrackTest {
public:
    TrackTest(TrackDir *);

    TrackDir *mDir;
    /** "Widget to test" */
    ObjPtr<TrackWidget> mWidget;
    /** "Slot to add widgets in". Ranges from 0 to 10. */
    int mSlot;
};

bool PropSync(TrackTest &, DataNode &, DataArray *, int, PropOp);
