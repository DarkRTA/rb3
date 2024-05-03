#ifndef TRACK_TRACKTEST_H
#define TRACK_TRACKTEST_H

#include "obj/ObjPtr_p.h"
#include "obj/PropSync_p.h"
#include "track/TrackDir.h"
#include "track/TrackWidget.h"

class TrackTest {
    public:
    TrackTest(TrackDir*);

    TrackDir* mDir;    
    ObjPtr<TrackWidget, ObjectDir> mWidget;
    int mSlot;
};

bool PropSync(TrackTest&, DataNode&, DataArray*, int, PropOp);

#endif // TRACK_TRACKTEST_H