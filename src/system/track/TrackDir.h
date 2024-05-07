#ifndef TRACK_TRACKDIR_H
#define TRACK_TRACKDIR_H

#include "obj/Object.h"
#include "ui/PanelDir.h"

class TrackDir : public PanelDir {
public:
    TrackDir();
    OBJ_CLASSNAME(TrackDir)

    NEW_OBJ(TrackDir)
};

#endif // TRACK_TRACKDIR_H