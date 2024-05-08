#ifndef TRACK_TRACKDIR_H
#define TRACK_TRACKDIR_H

#include "obj/Object.h"
#include "ui/PanelDir.h"

class TrackDir : public PanelDir {
public:
    TrackDir();
    OBJ_CLASSNAME(TrackDir)

    float SecondsToY(float) const;
    void AddActiveWidget(class TrackWidget*);
    float CutOffY() const;
    NEW_OBJ(TrackDir)

    bool unk_0x20C;
};

#endif // TRACK_TRACKDIR_H